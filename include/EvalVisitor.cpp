//
// Created by raymon on 11/12/22.
//

/*EvalVisitor.cpp*/
#include "EvalVisitor.h"
using namespace std;

antlrcpp::Any VarSymbol:: containsKey(std::string s)
{
    MAP_STRING_T::iterator m_it = symbol.find(s);
    if (m_it != symbol.end())
    {
        return m_it->second;
    }
    else return NULL;
}

antlrcpp::Any EvalVisitor::visitAssign(ExprParser::AssignContext* ctx)
{
    std::string s = ctx->ID()->getText();   //其中ctx表示标签所代表的语法树,ID是此语法树中的ID分支
    antlrcpp::Any value = visit(ctx->expr()); //因为expr不是一个终结符，调用visit()访问expr的值
    var->put(s, value); //存入符号表
    std::cout << "in visitAssign" << std::endl;
    return value;
}

antlrcpp::Any EvalVisitor::visitPrintExpr(ExprParser::PrintExprContext* ctx)
{
    antlrcpp::Any value = visit(ctx->expr());  //因为expr不是一个终结符，调用visit()访问expr的值
    if (value.type() == typeid(std::string))        //对返回值的类型进行判断 antlrcpp::Any类的is()方法
        std::cout << std::any_cast<std::string>(&value) << std::endl;  //antlrcpp::Any类的as<>()方法返回给定类型值
    else
        std::cout << *std::any_cast<int>(&value) << std::endl;
    std::cout << "in visitPrintExpr" << std::endl;
    return 0;
}

antlrcpp::Any EvalVisitor::visitInt(ExprParser::IntContext* ctx)
{
    std::string s = ctx->INT()->getText(); //终结符getText()返回值
    int value = stoi(s);
    std::cout << "in visitInt" << std::endl;
    return antlrcpp::Any(value);
}

antlrcpp::Any EvalVisitor::visitId(ExprParser::IdContext* ctx)
{
    std::string id = ctx->ID()->getText();
    antlrcpp::Any anyone = var->containsKey(id); //符号表查询id对应的值
    std::cout << "in visitId" << std::endl;
    return anyone; //返回对应值
    //由于没有写错误检查如果没有对id进行赋值 就会返回为0;
}

antlrcpp::Any EvalVisitor::visitAddSub(ExprParser::AddSubContext* ctx)
{
    antlrcpp::Any l = visit(ctx->expr(0)); //暂时理解为addsub语法中,含有两个expr，此处相当于按索引值判定左右子树
    antlrcpp::Any r = visit(ctx->expr(1));
    std::cout << "in visitAddSub" << std::endl;
    if (ctx->op->getType() == ExprParser::ADD) return (*std::any_cast<int>(&l)) + (*std::any_cast<int>(&r));
    else return (*std::any_cast<int>(&l)) - (*std::any_cast<int>(&r));
}

antlrcpp::Any EvalVisitor::visitMulDiv(ExprParser::MulDivContext* ctx)
{
    antlrcpp::Any l = visit(ctx->expr(0));
    antlrcpp::Any r = visit(ctx->expr(1));
    std::cout << "in visitMulDiv" << std::endl;
    if (ctx->op->getType() == ExprParser::MUL) return (*std::any_cast<int>(&l)) * (*std::any_cast<int>(&r));
    else return (*std::any_cast<int>(&l)) / (*std::any_cast<int>(&r));
}

antlrcpp::Any EvalVisitor::visitParens(ExprParser::ParensContext* ctx)
{
    std::cout << "in visitParens" << std::endl;
    return visit(ctx->expr()); //返回对应值
}
