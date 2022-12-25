//
// Created by raymon on 11/12/22.
//
/*EvalVisitor.h*/
#ifndef PARSE_EVALVISITOR_H
#define PARSE_EVALVISITOR_H

#include "ExprBaseVisitor.h"
#include <map>
/*map传入antlrcp::Any类似boost::any可以使用任意类型*/
typedef std::map<std::string, antlrcpp::Any> MAP_STRING_T;
/*简易符号表*/
class VarSymbol
{
private:
    MAP_STRING_T symbol;
public:
    inline void put(std::string s, antlrcpp::Any t) { symbol[s] = t; } /*存入符号及数值*/
    antlrcpp::Any containsKey(std::string s); /*查询符号对应数值*/
};

/*继承默认访问器类并对其方法进行重写*/
class EvalVisitor : public ExprBaseVisitor
{
private:
    VarSymbol *var ;
public:
    EvalVisitor()
    {
        var = new VarSymbol;
    }
    ~EvalVisitor()
    {
        delete var;
    }
    /* 对应语法文件中ID '=' expr NEWLINE */
    antlrcpp::Any visitAssign(ExprParser::AssignContext* ctx) ; /*函数名是由 visit + 语法文件中#Label首字符大写组成*/
    /* 对应语法文件中expr NEWLINE */
    antlrcpp::Any visitPrintExpr(ExprParser::PrintExprContext* ctx) ;
    /* 对应语法文件中INT */
    antlrcpp::Any visitInt(ExprParser::IntContext* ctx);
    /* 对应语法文件中Id */
    antlrcpp::Any visitId(ExprParser::IdContext* ctx);
    /* 对应语法文件中expr op=('-'|'+') expr */
    antlrcpp::Any visitAddSub(ExprParser::AddSubContext* ctx);
    /* 对应语法文件中expr op=('*'|'/') expr */
    antlrcpp::Any visitMulDiv(ExprParser::MulDivContext* ctx);
    /* 对应语法文件中'(' expr ')' */
    antlrcpp::Any visitParens(ExprParser::ParensContext* ctx);
};

#endif //PARSE_EVALVISITOR_H
