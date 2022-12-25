#ifndef __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
#define __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H

#include "ConfigureFileBaseVisitor.h"

class ConfigureFileImplement : public ConfigureFileBaseVisitor {

  /*  antlrcpp::Any visitAllConfig(ConfigureFileParser::AllConfigContext* ctx) {
    std::cout << "beging allconfig" << std::endl;
    return visitChildren(ctx);
    };*/
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();

    for (auto oneint: ctx->INT()) {
      std::cout << oneint->getText() << "    ";
    }
    std::cout << std::endl << ctx->INT().size() << "    ";

    std::string intv = ctx->INT(1)->getText();

    std::cout << std::endl << "INT: " << key << "=" << intv << std::endl;
    return 0;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::string strv = ctx->STRING()->getText();

    std::cout << "STR: " << key << "=" << strv << std::endl;
    return 0;
  };
};


#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
