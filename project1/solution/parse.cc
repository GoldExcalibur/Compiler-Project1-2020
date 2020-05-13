#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <math.h>
#include <map>

#include "IR.h"
#include "IRMutator.h"
#include "IRPrinter.h"
#include "IRVisitor.h"
#include "type.h"

#include "CCPrinter.h"

using namespace Boost::Internal;

const int INF = 128;

bool compare_str(const std::string& s1, const std::string& s2){
    int i = 0, j = 0;
    while(i < s1.size() && j < s2.size()){
        if(s1[i] == ' ')++i;
        else if(s2[j] == ' ') ++j;
        else{
            if(s1[i] == s2[j]) ++i, ++j;
            else return false;
        }
    }
    if(i == s1.size() &&  j == s2.size()) return true;
    else return false;
}

void erase_blank(std::string& s1){
    std::string tmp;
    for(int i = 0; i < s1.size(); ++i){
        if(s1[i] != ' ') tmp += s1[i]; 
    }
    s1 = tmp;
}

class Case{
public:
    std::string name;
    std::vector<std::string> ins;
    std::vector<std::string> outs;
    std::string instr;
    std::string outstr;
    std::string data_type;
    std::string kernel;
    Case(){};
    Case(const std::vector<std::string> & m){
        int i = 0;
        for(; i < m.size(); ++i){
            if(i == 0) name = m[i];
            else if(i == 1){
                ins = handle(m[i]);
            }
            else if(i == 2){
                outs = handle(m[i]);
            }
            else if(i == 3) data_type = m[i];
            else{ kernel = m[i];}
        }
    }
    std::vector<std::string> handle(const std::string& m){
        std::vector<std::string> result;
        int index1 = 0, index2 = -1;
        while((index1 = m.find("\"", index1)) != -1){
            index2 = m.find("\"", index1+1);
            result.push_back(m.substr(index1+1, index2-index1-1));
            index1 = index2+1;
        }
        return result;
    }

    void print(){
        std::cout << name << std::endl;
        std::cout << data_type << std::endl;
        std::cout << kernel << std::endl;
        for(int i = 0; i < ins.size(); ++i) std::cout << ins[i] << " ";
        std::cout << std::endl;
        for(int i = 0; i < outs.size(); ++i) std::cout << outs[i] << " ";
        std::cout << std::endl;
    }

};

Case parse_json(std::string src){
    std::ifstream ifile(src, std::ios::in);
    if(!ifile.is_open()){
        std::cout << "Parse Json Error" << std::endl;
    }
    char buffer[302];
    int colcnt = 0;
    std::vector<std::string> content;
    while(!ifile.eof()){
        ifile.getline(buffer, 300);
        if(buffer[0] == '{' || buffer[0] == '}') continue;
        std::string tmp = buffer;
        int pos = tmp.find(":");
        tmp = tmp.substr(pos+1);
        int pos1 = -1, pos2 = -1;
        if(colcnt == 1 || colcnt == 2){
            pos1 = tmp.find_first_of("[");
            pos2 = tmp.find_last_of("]");
            tmp = tmp.substr(pos1, pos2-pos1+1);
        }
        else{
            pos1 = tmp.find_first_of("\"");
            pos2 = tmp.find_last_of("\"");
            tmp = tmp.substr(pos1+1,pos2-pos1-1);
        }
        content.push_back(tmp);
        std::cout << tmp << std::endl;
        ++colcnt;
    }
    Case result = Case(content);
    return result;
}

Case example;

// 0P 1S 2LHS 3RHS 4TRef 5SRef 6Const 7CList 8AList 9 Op 10 IdExpr 11 Id
enum nodetype {P, S, LHS, RHS, TRef, SRef, Const, CList, AList, Op, IdExpr, Id};
std::vector<std::string> nodetype2name({"P", "S", "LHS", "RHS", "TRef", "SRef", "Const", 
    "CList", "AList", "Op", "IdExpr", "Id"});

Type index_type = Type::int_scalar(32);
Type data_type = Type::float_scalar(32);
Type bool_type = Type::uint_scalar(32);

std::map<std::string, Expr> loop_indexs;
std::map<std::string, Expr> inputs;
std::map<std::string, Expr> outputs;

// bandcheck's map
std::map<std::string, int> bandcheck_dom;
std::map<std::string, Expr> bandcheck_expr;

class AST {
public:
    nodetype t;           // type of this node
    std::string str;      // str of this node
    std::vector<AST> child;
    AST* father;
    Expr ep;            //
    Stmt sp;
    Group gp;
    float value; // only meaningful for const

    AST(){};
    AST(nodetype a, std::string b){
        t = a, str = b;
        std::cout << a << " " << str << std::endl;
    };

    AST& operator=(const AST& other){
        t = other.t;
        str = other.str;
        child = other.child;
        father = other.father;
        return *this;
    }

    void build_tree(){
        if(t == 3 && child.size() > 0) ;
        else build();
        for(int i = 0; i < child.size(); ++i) child[i].build_tree();
    }

    void travel(){
        std::cout << t << " " << nodetype2name[t] << " " << str << std::endl;
        for(int i = 0; i < child.size(); ++i) child[i].travel();
    }

    void build(){
        switch(t){
            case P: build_P();break;
            case S: build_S();break;
            case LHS: build_LHS(); break;
            case RHS: build_RHS(); break;
            case TRef: build_TRef(); break;
            case SRef: build_SRef(); break;
            case CList: build_CList(); break;
            case AList: build_AList(); break;
            case IdExpr: build_IdExpr(); break;
            default: std::cout << nodetype2name[t] << " Not Implemented !" << std::endl;
        }
    }

    void build_P(){
        int s1 = 0, s2 = -1;
        std::string tmp;
        while((s2 = str.find(";", s1)) != -1){
            tmp = str.substr(s1, s2 - s1+1);
            child.push_back(AST((nodetype) 1, tmp));
            (child.back()).father = this;
            s1 = s2+1;
        }
    }

    void build_S(){
        int s1 = -1, s2 = -1;
        std::string tmp;
        s1 = str.find("=", 0);
        tmp = str.substr(0, s1);
        child.push_back(AST((nodetype) 2, tmp));
        (child.back()).father = this;
        s2 = str.find(";", s1+1);
        tmp = str.substr(s1+1, s2-1-s1-1+1);
        child.push_back(AST((nodetype) 3, tmp));
        (child.back()).father = this;
    }

    void build_LHS(){
        child.push_back(AST((nodetype) 4, str));
        (child.back()).father = this;
    }

    void build_RHS(){
        int s1 = -1, s2 = -1;
        std::string ops = "+-   */%"; // operator priority
        std::stack<char> v1;
        std::vector<AST> v2;
        std::string tmp;
        AST ch;
        int i = 0;
        while(i < str.size()){
            char c = str[i];
            if((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')){
                s1 = str.find_first_of("<", i+1);
                s2 = str.find_first_of(">", s1+1);
                tmp = str.substr(s1, s2-s1+1);
                if(tmp.find(',') == -1) ch = AST((nodetype) 5, str.substr(i, s2-i+1));
                else{
                    s1 = str.find_first_of("[", s2+1);
                    s2 = str.find_first_of("]", s1+1);
                    ch = AST((nodetype) 4, str.substr(i, s2-i+1));
                }
                i = s2+1;
                v2.push_back(ch);
            }
            else if(c >= '0' && c <= '9'){
                s1 = i;
                while(true){
                    ++s1;
                    if(str[s1] == '.' || (str[s1] >= '0' && str[s1] <= '9')) continue;
                    else break;
                }
                tmp = str.substr(i, s1-i);
                ch = AST((nodetype) 6, tmp);
                v2.push_back(ch);
                i = s1;
            }
            else if(c == '('){
                v1.push(c);
                ++i;
            }
            else if(c == ')'){
                while(v1.top() != '('){
                    RHS_helper(v1, v2);
                }
                v1.pop();
                ++i;
            }
            else if(c == '*' || c == '-' || c == '/' || c == '+' || c == '%'){
                int c_pri = ops.find(c);
                int top_pri = -1;
                while(!v1.empty()){
                    top_pri = ops.find(v1.top());
                    if(c_pri + 2 < top_pri){
                       RHS_helper(v1, v2);
                    }
                    else break;
                }
                v1.push(c);
                ++i;
            }
            else ++i;
        }
        while(!v1.empty()){
            RHS_helper(v1, v2);
        }
        if(!v2.empty()){
            if(v2.size() == 1){
                if(v2[0].t != 3){
                    child.push_back(v2[0]);
                    v2[0].father = this;
                    v2.pop_back();
                }
            }
            else std::cout << "surprise at build_RHS" << std::endl;
        }
    }

    void RHS_helper(std::stack<char>& v1, std::vector<AST>& v2){
        AST ch2 = v2.back();
        v2.pop_back();
        AST ch1 = v2.back();
        v2.pop_back();
        std::string tmp = ch1.str + +" " + v1.top() + " " + ch2.str;
        AST op = AST((nodetype) 9, std::string(1, v1.top()));
        v1.pop();
        if(!v1.empty()){
            if(v1.top() == '(') tmp = "(" + tmp + ")";
        } 
        AST* ch3 = new AST((nodetype) 3, tmp);
        if(compare_str(str, tmp)) ch3 = this;
        ch3->child.push_back(ch1);
        ch3->child.push_back(op);
        ch3->child.push_back(ch2);
        ch1.father = ch3;
        op.father = ch3;
        ch2.father = ch3;
        v2.push_back(*ch3);
    }

    void build_TRef(){
        int s1 = -1, s2 = -1;
        std::string tmp;
        s1 = str.find("<", 0);
        tmp = str.substr(0, s1); // tensor name fix me
        erase_blank(tmp);

        child.push_back(AST((nodetype) 11, tmp));
        (child.back()).father = this;

        s2 = str.find(">", s1+1);
        tmp = str.substr(s1+1, s2-s1-1);
        child.push_back(AST((nodetype) 7, tmp));
        (child.back()).father = this;

        s1 = str.find("[", s2+1);
        s2 = str.find("]", s1+1);
        tmp = str.substr(s1+1, s2-s1-1);
        child.push_back(AST((nodetype) 8, tmp));
        (child.back()).father = this;
    }

    void build_SRef(){
        int s1 = -1, s2 = -1;
        std::string tmp;
        s1 = str.find("<", 0);
        tmp = str.substr(0, s1); // scalar name fix me
        child.push_back(AST((nodetype) 11, tmp));
        (child.back()).father = this;

        s2 = str.find(">", s1+1);
        tmp = str.substr(s1+1, s2-s1-1);
        child.push_back(AST((nodetype) 7, tmp));
        (child.back()).father = this;
    }


    void build_CList(){
        int i = 0;
        std::string tmp = "";
        AST ch;
        for(; i < str.size(); ++i){
            if(str[i] >= '0' && str[i] <= '9') tmp += str[i];
            else if(str[i] == ','){
                child.push_back(AST((nodetype) 6, tmp));
                child.back().father = this;
                tmp = "";
            }
        }
        if(tmp != "") child.push_back(AST((nodetype) 6, tmp));
        child.back().father = this;
    }

    void build_AList(){
        int i = 0;
        std::string tmp;
        for(; i < str.size(); ++i){
            if(str[i] == ' ') continue;
            else if(str[i] == ','){
                child.push_back(AST((nodetype) 10, tmp)); // IdExpr
                child.back().father = this;
                tmp = "";
            }
            else tmp += str[i];
        }
        if(tmp != ""){
            child.push_back(AST((nodetype) 10, tmp)); // IdExpr
            child.back().father = this;
        }
    }

    void build_IdExpr(){
        int s1 = -1;
        std::string ops = "+-    */%";
        std::stack<char> v1;
        std::vector<AST> v2;
        std::string tmp;
        AST ch = AST();
        int i = 0;
        while(i < str.size()){
            char c = str[i];
            if((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z')){
                s1 = i;
                while(true){
                    ++s1;
                    if((str[s1] >= 'A' && str[s1] <= 'Z')||(str[s1] >= 'a' && str[s1] <= 'z')) continue;
                    break;
                }
                tmp = str.substr(i, s1 - i);
                std:: cout << "haha" << tmp << std::endl;
                ch = AST((nodetype) 10, tmp); // Id
                v2.push_back(ch);
                i = s1;
            }
            else if(c >= '0' && c <= '9'){
                s1 = i;
                while(true){
                    ++s1;
                    if(str[s1] >= '0' && str[s1] <= '9') continue;
                    else break;
                }
                tmp = str.substr(i, s1-i);
                ch = AST((nodetype) 6, tmp); // Const
                v2.push_back(ch);
                i = s1;
            }
            else if(c == '('){
                v1.push(c);
                ++i;
            }
            else if(c == ')'){
                while(v1.top() != '('){
                    IdExpr_helper(v1, v2);
                }
                v1.pop();
                ++i;
            }
            else if(c == '*' || c == '-' || c == '/' || c == '+' || c == '%'){
                int c_pri = ops.find(c);
                int top_pri = -1;
                while(!v1.empty()){
                    top_pri = ops.find(v1.top());
                    if(c_pri + 2 < top_pri){
                        IdExpr_helper(v1, v2);
                    }
                    else break;
                }
                v1.push(c);
                ++i;
            }
            else ++i;
        }
        while(!v1.empty()){
            IdExpr_helper(v1, v2);
        }
    }

    void IdExpr_helper(std::stack<char>& v1, std::vector<AST>& v2){
        AST ch2 = v2.back();
        v2.pop_back();
        AST ch1 = v2.back();
        v2.pop_back();
        std::string tmp = ch1.str + +" " + v1.top() + " " + ch2.str;
        AST op = AST((nodetype) 9, std::string(1, v1.top()));
        v1.pop();
        if(!v1.empty()){
            if(v1.top() == '(') tmp = "(" + tmp + ")";
        } 
        AST* ch3 = new AST((nodetype) 10, tmp);
        if(compare_str(str, tmp)) ch3 = this;
        ch3->child.push_back(ch1);
        ch3->child.push_back(op);
        ch3->child.push_back(ch2);
        ch1.father = ch3;
        op.father = ch3;
        ch2.father = ch3;
        v2.push_back(*ch3);
    }


    void build_IR(){
        for(int i = 0; i < child.size(); ++i) child[i].build_IR();
        IR();
    }

    void IR(){
        switch(t){
            case P: IR_P(); break;
            case S: IR_S(); break;
            case LHS: IR_LHS(); break;
            case RHS: IR_RHS(); break;
            case TRef: IR_TRef(); break;
            case SRef: IR_SRef(); break;
            case CList: IR_CList(); break;
            case AList: IR_AList(); break;
            case IdExpr: IR_IdExpr(); break;
            case Const: IR_Const(); break;
           // case Id: IR_Id(); break;
            default: std::cout << nodetype2name[t] << " Not Implemented !" << std::endl;
        }
    }

    void IR_P(){
        std::vector<Stmt> sp_list;
        for(int i = 0; i < child.size(); ++i){
            std::cout << (int) child[i].sp.node_type() << std::endl;
            sp_list.push_back(child[i].sp);
        }
        std::vector<Expr> ins;
        std::map<std::string, Expr>::iterator p;
        for(p = inputs.begin(); p != inputs.end(); ++p) ins.push_back(p->second);
        std::vector<Expr> outs;
        for(p = outputs.begin(); p != outputs.end(); ++p) outs.push_back(p->second);
        std::cout << "IR P " << str << std::endl;
        std::cout << "insize " << ins.size() <<  "outsize " << outs.size() << "stmt size " << sp_list.size() << std::endl;
        gp = Kernel::make(example.name, ins, outs, sp_list, KernelType::CPU);
        inputs.clear();
        outputs.clear();
    }

    void IR_S(){
        Stmt true_stmt = Move::make(child[0].ep, child[1].ep, MoveType::MemToMem);
        Stmt fake_stmt;
        fake_stmt = Move::make(child[0].ep, child[0].ep, MoveType::MemToMem);
        
        
        std::vector<Expr> tmp; // indexs for loop
        for(std::map<std::string, Expr>::iterator p = loop_indexs.begin(); p != loop_indexs.end(); ++p){
            //std::cout << p->first << " ";
            tmp.push_back(p->second);
        }

        Expr cond_all, cond1, cond2;
        std::map<std::string, int>::iterator i = bandcheck_dom.begin();
        cond1 = Compare::make(data_type, CompareOpType::LE, Expr(int(0)), bandcheck_expr[i->first]);
        cond2 = Compare::make(data_type, CompareOpType::LT, bandcheck_expr[i->first], Expr(int(i->second)));
        cond_all = Binary::make(bool_type, BinaryOpType::And, cond1, cond2);
        while((++i) != bandcheck_dom.end()){
            cond1 = Compare::make(data_type, CompareOpType::LE, Expr(int(0)), bandcheck_expr[i->first]);
            cond_all = Binary::make(bool_type, BinaryOpType::And, cond_all, cond1);
            cond2 = Compare::make(data_type, CompareOpType::LT, bandcheck_expr[i->first], Expr(int(i->second)));
            cond_all = Binary::make(bool_type, BinaryOpType::And, cond_all, cond2);
        }
        Stmt main_stmt = IfThenElse::make(cond_all, true_stmt, fake_stmt);

        std::cout << "loop index in S " << tmp.size() << std::endl;
        sp = LoopNest::make(tmp, {main_stmt});
        loop_indexs.clear();
        bandcheck_dom.clear();
        bandcheck_expr.clear();
    }

    void IR_LHS(){
        ep = child[0].ep;
    }

    void IR_RHS(){
        if(child.size() == 3){
            Expr ch1 = child[0].ep;
            Expr ch2 = child[2].ep;
            switch(child[1].str[0]){
                case '+': ep = Binary::make(data_type, BinaryOpType::Add, ch1, ch2);break;
                case '-': ep = Binary::make(data_type, BinaryOpType::Sub, ch1, ch2);break;
                case '*': ep = Binary::make(data_type, BinaryOpType::Mul, ch1, ch2);break;
                case '/': ep = Binary::make(data_type, BinaryOpType::Div, ch1, ch2);break;
                case '%': ep = Binary::make(data_type, BinaryOpType::Mod, ch1, ch2);break;
                default: std::cout << "Not Implemented !" << std::endl;
           }
        }
        else ep = child[0].ep;
        //std::cout << nodetype2name[t] << " " << str << " " << child.size() << std::endl;
        
    }

    void IR_SRef(){
        std::string sname = child[0].str;
        std::vector<size_t> bound_list;
        if(child[1].child.size() == 1) bound_list.push_back((size_t) child[1].child[0].value);
        else std::cout << "surprise at IR_SRef!" << std::endl;
        std::vector<Expr> index_list;
        ep = Var::make(data_type, sname, index_list, bound_list);
        if(sname == example.outs[0]) {
            if(outputs.find(sname) == outputs.end()) outputs[sname] = ep;
        }
        else{
            if(inputs.find(sname) == inputs.end()) inputs[sname] = ep;
        }
    }

    void IR_TRef() {
        
        std::string tname = child[0].str;
        std::vector<size_t> bound_list;
        for(int i = 0; i < child[1].child.size(); ++i){
            //std::cout << child[1].child[i].value << " " ;
            bound_list.push_back((size_t) child[1].child[i].value);
        }
        std::vector<Expr> index_list;
        for(int i = 0; i < child[2].child.size(); ++i){
            //std::cout << child[2].child[i].str << " "  ;
            index_list.push_back(child[2].child[i].ep);

        }
        //std::cout << tname << std::endl;
        ep = Var::make(data_type, tname, index_list, bound_list);
        if(compare_str(tname, example.outs[0])) {
            if(outputs.find(tname) == outputs.end()) outputs[tname] = ep;
        }
        else{
            if(inputs.find(tname) == inputs.end()) inputs[tname] = ep;
        }

        std::string index_name;
        int up_bound;
        for(int i = 0; i < child[1].child.size(); ++i){
          // std::cout << child[1].child[i].value << " " ;
            index_name = child[2].child[i].str;
            up_bound = child[1].child[i].value;
            if(bandcheck_dom.find(index_name) != bandcheck_dom.end()){
                if(bandcheck_dom[index_name] > up_bound){
                    bandcheck_dom[index_name] = child[1].child[i].value;
                    bandcheck_expr[index_name] = child[2].child[i].ep;
                }
            }
            else{
                bandcheck_dom[index_name] = child[1].child[i].value;
                bandcheck_expr[index_name] = child[2].child[i].ep;
            }

        }
    }

    void IR_CList(){

    }

    void IR_AList(){
        
    }

    void IR_IdExpr(){
        Expr dom_inf = Dom::make(index_type, -INF, 2*INF); // fix me->Ok
        if(child.size()){
            Expr ch1 = Expr(child[0].ep);
            Expr ch2 = Expr(child[2].ep);
            switch(child[1].str[0]){
                case '+': ep = Binary::make(index_type, BinaryOpType::Add, ch1, ch2); break;
                case '-': ep = Binary::make(index_type, BinaryOpType::Sub, ch1, ch2); break;
                case '*': ep = Binary::make(index_type, BinaryOpType::Mul, ch1, ch2); break;
                case '/': ep = Binary::make(index_type, BinaryOpType::Div, ch1, ch2); break;
                case '%': ep = Binary::make(index_type, BinaryOpType::Mod, ch1, ch2);break;
                default: std::cout << "Not Implemented Op, so sad!";
            }
        }
        else{
            ep = Index::make(index_type, str, dom_inf, IndexType::Spatial);
            if(loop_indexs.find(str) == loop_indexs.end()) loop_indexs[str] = ep;
        }
    }
    
    void IR_Const(){
        int xsd = str.find(".");
        int zhengshu = -1, xiaoshu = -1;
        if(xsd == -1){
            zhengshu = atoi(str.c_str());
            std::cout << zhengshu << std::endl;
            value = zhengshu;
            ep = Expr(zhengshu);
        }
        else{
            zhengshu = atoi(str.substr(0, xsd).c_str());
            int xiaoshulen = str.size()-xsd-1;
            xiaoshu = atoi(str.substr(xsd+1, xiaoshulen).c_str());
            float result = zhengshu + (xiaoshu/pow(10, xiaoshulen));
            std::cout << result << std::endl;
            value = result;
            ep = Expr(result);
        }
    }
};


std::string src2dst(const std::string& src){
    std::string dst = "./kernels/";
    std::cout << src << std::endl;
    int s1 = src.rfind("/");
    int s2 = src.rfind(".json");
    dst +=  "kernel_" + src.substr(s1+1, s2-s1-1) + ".cc";
    return dst;
}


int main(){
    std::string src;
    for(int i = 1; i <= 10; ++i){
        if(i == 6) continue;
        src = "./cases/case" + std::to_string(i) + ".json";
        if(access(src.c_str(), 0) == -1) continue;
        example = parse_json(src);
        example.print();
        AST root = AST((nodetype) 0, example.kernel);
        root.build_tree();
        std::cout << "-----" << std::endl;
        root.travel();
        std::cout << "*****" << std::endl;
        root.build_IR();

        std::cout << root.str <<std::endl;

        Group kernel = root.gp;

        // visitor
        IRVisitor visitor;
        root.gp.visit_group(&visitor);

        // mutator
        //IRMutator mutator;
        //kernel = mutator.mutate(kernel);

        // printer
        //IRPrinter printer;
        CCPrinter printer;
        std::string code = printer.print(root.gp);

        std::string dst;
        dst = src2dst(src);
        std::ofstream ofile(dst, std::ios::out);
        ofile << code;
        ofile.close();

        std::cout << "######" << std::endl;
        std::cout << code;
    }
   
    return 0;
}