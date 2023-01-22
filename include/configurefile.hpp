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
    std::cout << "Begin iter\n";
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
    std::cout << "End iter\n";
  }

  template<typename T>
  const char* GetSingleConfigureParameter (std::string key, T &value) {
    int valuecount = configureFileMap.count(key);
    std::multimap<std::string, std::any>::iterator found;
	
    if (valuecount == 0) {
      return ERROR_NO_KEY;
    } else if (valuecount > 1) {
      return ERROR_TOO_MORE_KEY;
    }
    found = configureFileMap.find(key);
    if (found->second.type() != typeid(T)) {
      return ERROR_INVALID_TYPE_KEY;
    }
    value = std::any_cast<T>(found->second);
    return NULL;
  }
};

class ConfigureFile {
public:
  static ConfigureFileParameter parameter;

public:
  void IteratorParameter (void) {
    parameter.IteratorConfigureMap();
  };
  
  ConfigureFile(const char *name) {
    configfilein = fopen(name, "r" );
    if (!configfilein) {
      _LOG_CRIT("%s, <%s>", ERROR_NO_CONFIGURE, name);
      exit(1);
    }
    ConfigFileName = name;
    configfileparse();
  };

  template<typename T>
  static const char* GetSingleConfigureParameter (std::string key, T &value) {
    return parameter.GetSingleConfigureParameter(key, value);
  };
};

template<typename T>
const char* GetSingleConfigureParameter (std::string key, T &value) {
  return ConfigureFile::GetSingleConfigureParameter(key, value);
};

const char* AssignInt(const char* key, char* value) {
  int intvalue = STools::StoI(value);
  ConfigureFile::parameter.InsertConfigureMap(key, intvalue);
  return 0;
};

const char* AssignString(const char* key, char* value) {
  STools::RemoveEscapeChar(value);
  ConfigureFile::parameter.InsertConfigureMap(key, std::string(value));  
  return 0;  
};

const char*  AssignIpaddress(const char* key, char* value) {
  sockaddr_in addr;
  char* colon = strchr(value, ':');
  *colon = 0;
  addr.sin_family = AF_INET;
  inet_aton(value, &addr.sin_addr);   // TODO return
  addr.sin_port = htons(atoi(colon + 1));  // TODO return
  ConfigureFile::parameter.InsertConfigureMap(key, addr);
  *colon = ':';
  return 0;  
};

ConfigureFileParameter ConfigureFile::parameter;


#endif  // __RAYMON_SHAN_PARSE_CONFIGURE_FILE_HPP
