#ifndef __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
#define __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H

#include "infra.hpp"

class ConfigureFileParameter {
  struct stringWithType {
    std::type_info *stringType;
    std::string stringValue;
  };
  std::multimap<std::string, stringWithType> configureFileMap;

public:
  bool InsertConfigureMap(std::string key, std::type_info &type, std::string value) {
    stringWithType swt;
    swt.stringType = &type;
    swt.stringValue = value;
    configureFileMap.insert(std::pair<std::string, stringWithType>(key, swt));
    return true;
  }
  void IteratorConfigureMap() {
    for (auto elem : configureFileMap)
      std::cout << elem.first << " " << elem.second.stringValue << std::endl;    
  }
  // struct sockaddr
};

class ConfigureFileParseImplement : public ConfigureFileBaseVisitor {

  class ConfigureFileParameter para;
  
  antlrcpp::Any visitAllConfigFile(ConfigureFileParser::AllConfigFileContext* ctx) {
    return visitChildren(ctx);
  };
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    para.InsertConfigureMap(ctx->KEYWORD()->getText(),
			   (std::type_info &)typeid(int),
			   ctx->INT()->getText());
    //    std::cout << "size: " << ctx->INT().size() << std::endl;
    //    for (auto oneint: ctx->INT()) std::cout << oneint->getText() << ",";
    return 0;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    para.InsertConfigureMap(ctx->KEYWORD()->getText(),
			   (std::type_info &)typeid(std::string),
			   ctx->STRING()->getText());    
    return 0;
  };

  antlrcpp::Any visitAssignIpAddress(ConfigureFileParser::AssignIpAddressContext* ctx) {
    para.InsertConfigureMap(ctx->KEYWORD()->getText(),
			   (std::type_info &)typeid(sockaddr),
			   ctx->IPADDRESS()->getText());   
    return 0;
  };
  
public:
  void IteratorParameter (void) {
    para.IteratorConfigureMap();
  }
};

#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_H
