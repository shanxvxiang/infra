#ifndef __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
#define __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H

#include "infra.hpp"

class ConfigureFileParameter {
  std::multimap<std::string, std::any> configureFileMap;
public:
  bool InsertConfigureMap(std::string key, std::any value) {
    configureFileMap.insert(std::pair<std::string, std::any>(key, value));

    std::cout << "in insert" << typeid(value).name() << std::endl;
    return true;
  }
  void IteratorConfigureMap() {
    for (auto elem : configureFileMap) {
      std::cout << elem.first << " ";
      if (elem.second.type() == typeid(int))
	std::cout << std::any_cast<int>(elem.second) << std::endl;
      else
	std::cout << typeid(elem.second).name() << std::endl;
    }
  }
  // struct sockaddr
};

class ConfigureFileParseImplement : public ConfigureFileBaseVisitor {
  class ConfigureFileParameter para;
  
  antlrcpp::Any visitAllConfigFile(ConfigureFileParser::AllConfigFileContext* ctx) {
    return visitChildren(ctx);
  };
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    int value = stoi(ctx->INT()->getText());
    para.InsertConfigureMap(key, value);
    return value;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    para.InsertConfigureMap(ctx->KEYWORD()->getText(), ctx->STRING());
    return 0;
  };

  antlrcpp::Any visitAssignIpAddress(ConfigureFileParser::AssignIpAddressContext* ctx) {
    para.InsertConfigureMap(ctx->KEYWORD()->getText(), ctx->IPADDRESS());   
    return 0;
  };
  
public:
  void IteratorParameter (void) {
    para.IteratorConfigureMap();
  }
};

#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
