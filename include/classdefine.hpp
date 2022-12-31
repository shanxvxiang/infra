#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

class PumlParseImplement : public PumlBaseVisitor {


public:
  PumlParseImplement() {
  
  };
  std::any visitAllPUMLFile(PumlParser::AllPUMLFileContext *ctx) {
    return visitChildren(ctx);
  }

  std::any visitDefineClass(PumlParser::DefineClassContext *ctx) {
    std::string classname = ctx->IDENTIFIER()->getText();
    std::cout << "class:" << classname << std::endl;
    return visitChildren(ctx);    
  }

  std::any visitDefineAttribute(PumlParser::DefineAttributeContext *ctx) {
    std::string type = ctx->TYPE()->getText();
    std::string attr = ctx->IDENTIFIER()->getText();
    std::cout << "type:" << type << " attr:" << attr << std::endl;
    return 0;
  }

  std::any visitGeneralization(PumlParser::GeneralizationContext *ctx) {
    std::string classname0 = ctx->IDENTIFIER(0)->getText();
    std::string classname1 = ctx->IDENTIFIER(1)->getText();
    std::cout << "class0:" << classname0 << "--|> class1::" << classname1 << std::endl;    
    return 0;
  }

  std::any visitAggregation(PumlParser::AggregationContext *ctx) {
    std::string classname0 = ctx->IDENTIFIER(0)->getText();
    std::string classname1 = ctx->IDENTIFIER(1)->getText();
    std::cout << "class0:" << classname0 << "--o class1::" << classname1 << std::endl;    
    return 0;

  }
};

class ClassDefine {
public:
  ClassDefine() {
    const char *ret;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    ClassDefineFile(DataDefineFile.c_str());
  };
  
  char* ClassDefineFile(const char *name) {
    std::filebuf classbuf;
    
    if (!classbuf.open(name, std::ios::in)) {
      _LOG_CRIT(ERROR_INVALID_CLASSFILE "%s", name);
      exit(1);
    } else {
      std::istream *classfile = new std::istream(&classbuf);
      antlr4::ANTLRInputStream *classinput = new antlr4::ANTLRInputStream(*classfile);
      PumlLexer *classlexer = new PumlLexer(classinput);
      antlr4::CommonTokenStream *classtokens = new antlr4::CommonTokenStream(classlexer);
      PumlParser *classparser = new PumlParser(classtokens);
      antlr4::tree::ParseTree *classtree = classparser->allPUMLFile();
      PumlParseImplement *classimpl = new PumlParseImplement();
      classimpl->visit(classtree);
      
      classbuf.close();
      delete classimpl;
      delete classparser;
      delete classtokens;
      delete classlexer;
      delete classinput;
      delete classfile;
    };
    return NULL;
  };

};
#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
