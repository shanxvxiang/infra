#ifndef __RAYMON_SHAN_PARSE_CONFIGURE_FILE_HPP
#define __RAYMON_SHAN_PARSE_CONFIGURE_FILE_HPP

#include "infra.hpp"

class ConfigureFileParameter {
  std::multimap<std::string, std::any> configureFileMap;
public:
  bool InsertConfigureMap(std::string key, std::any value) {
    configureFileMap.insert(std::pair<std::string, std::any>(key, value));
    return true;
  }
  
  void IteratorConfigureMap() {
    configureFileMap.insert(std::pair<std::string, std::any>("kkkk", NULL));
    
    for (auto elem : configureFileMap) {
      std::cout << elem.first << " ";
      if (elem.second.type() == typeid(int))
	std::cout << std::any_cast<int>(elem.second) << std::endl;
      else if (elem.second.type() == typeid(std::string))
	std::cout << std::any_cast<std::string>(elem.second) << std::endl;
      else if (elem.second.type() == typeid(sockaddr_in)) {
	struct sockaddr_in addr = std::any_cast<sockaddr_in>(elem.second);
	std::cout << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << std::endl;
      }
      else if (elem.second.type() == typeid(NULL))
	std::cout << "NULL LLL" << std::endl;
      else
	std::cout << elem.second.type().name() << std::endl;
    }
  }
  // struct sockaddr_in
};

class ConfigureFileParseImplement : public ConfigureFileBaseVisitor {
  class ConfigureFileParameter para;
  
  antlrcpp::Any visitAllConfigFile(ConfigureFileParser::AllConfigFileContext* ctx) {
    return visitChildren(ctx);
  };
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    int value = infra::StoI(ctx->INT()->getText());
    para.InsertConfigureMap(key, value);
    return value;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::string value = std::any_cast<std::string>(ctx->STRING()->getText());
    infra::RemoveEscapeChar(value);
    para.InsertConfigureMap(key, value);  
    return value;
  };

  antlrcpp::Any visitAssignIpAddress(ConfigureFileParser::AssignIpAddressContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::string value = std::any_cast<std::string>(ctx->IPADDRESS()->getText());
    int pos = value.find(':');

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(value.substr(0, pos).c_str());
    addr.sin_port = htons(stoi(value.substr(pos+1)));
    para.InsertConfigureMap(ctx->KEYWORD()->getText(), addr);
    return addr;
  };
  
public:
  void IteratorParameter (void) {
    para.IteratorConfigureMap();
  }
};

#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_HPP
