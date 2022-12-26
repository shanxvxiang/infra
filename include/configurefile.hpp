#ifndef __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
#define __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H

#include "infra.hpp"
 
class ConfigureFileParseImplement : public ConfigureFileBaseVisitor {

  antlrcpp::Any visitAllConfigFile(ConfigureFileParser::AllConfigFileContext* ctx) {
    return visitChildren(ctx);
  };
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::cout << "KEY: " << key;
    std::cout << "size: " << ctx->INT().size() << std::endl;
    for (auto oneint: ctx->INT()) std::cout << oneint->getText() << ",";
    return 0;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::cout << "KEY: " << key;
    std::cout << "size: " << ctx->STRING().size() << std::endl;
    for (auto onestr: ctx->STRING()) std::cout << onestr->getText() << ",";
    return 0;
  };

  antlrcpp::Any visitAssignIpAddress(ConfigureFileParser::AssignIpAddressContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::cout << "KEY: " << key;
    std::cout << "size: " << ctx->IPADDRESS().size() << std::endl;
    for (auto oneip: ctx->IPADDRESS()) std::cout << oneip->getText() << ",";
    return 0;
  };
};



#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
