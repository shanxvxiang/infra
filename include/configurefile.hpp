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
  
  void IteratorConfigureMap(void) {
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
	std::cout << "NULL" << std::endl;
      else
	std::cout << elem.second.type().name() << std::endl;
    }
  }

  char* GetSingleConfigureParameter (std::string key, std::any &value) {
    int valuecount = configureFileMap.count(key);
    std::multimap<std::string, std::any>::iterator found;
	
    if (valuecount == 0) {
      return (char*)ERROR_NO_KEY;
    } else if (valuecount > 1) {
      return (char*)ERROR_TOO_MORE_KEY;
    }
    found = configureFileMap.find(key);
    if (found->second.type() != value.type()) {
      return (char*)ERROR_INVALID_TYPE_KEY;
    }
    value = found->second;
    return NULL;
  }
};

class ConfigureFileParseImplement : public ConfigureFileBaseVisitor {

  ConfigureFileParameter *parameter;
public:
  ConfigureFileParseImplement(ConfigureFileParameter *para) {
    parameter = para;    
  };
  antlrcpp::Any visitAllConfigFile(ConfigureFileParser::AllConfigFileContext* ctx) {
    return visitChildren(ctx);
  };
  
  antlrcpp::Any visitAssignInt(ConfigureFileParser::AssignIntContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    int value = infra::StoI(ctx->INT()->getText());
    parameter->InsertConfigureMap(key, value);
    return value;
  };
  
  antlrcpp::Any visitAssignString(ConfigureFileParser::AssignStringContext* ctx) {
    std::string key = ctx->KEYWORD()->getText();
    std::string value = std::any_cast<std::string>(ctx->STRING()->getText());
    infra::RemoveEscapeChar(value);
    parameter->InsertConfigureMap(key, value);  
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
    parameter->InsertConfigureMap(ctx->KEYWORD()->getText(), addr);
    return addr;
  };
  
public:

};

class ConfigureFile {
  static ConfigureFileParameter parameter;  

public:
  void IteratorParameter (void) {
    parameter.IteratorConfigureMap();
  };
  
  ConfigureFile(char *name) {
    std::filebuf cfgbuf;
    if (!cfgbuf.open(name, std::ios::in)) {
      _LOG_CRIT(ERROR_NO_CONFIGURE ":%s", name);
      exit(1);
    } else {
      std::istream *cfgfile = new std::istream(&cfgbuf);
      antlr4::ANTLRInputStream *cfginput = new antlr4::ANTLRInputStream(*cfgfile);
      ConfigureFileLexer *cfglexer = new ConfigureFileLexer(cfginput);
      antlr4::CommonTokenStream *cfgtokens = new antlr4::CommonTokenStream(cfglexer);
      ConfigureFileParser *cfgparser = new ConfigureFileParser(cfgtokens);
      antlr4::tree::ParseTree *cfgtree = cfgparser->allConfigFile();
      ConfigureFileParseImplement *cfgimpl = new ConfigureFileParseImplement(&parameter);
      cfgimpl->visit(cfgtree);
      IteratorParameter();
      
      cfgbuf.close();
      delete cfgimpl;
      delete cfgparser;
      delete cfgtokens;
      delete cfglexer;
      delete cfginput;
      delete cfgfile;
    }
  };

  static char* GetSingleConfigureParameter (std::string key, std::any &value) {
    return parameter.GetSingleConfigureParameter(key, value);
  };
};

ConfigureFileParameter ConfigureFile::parameter;  
#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_HPP
