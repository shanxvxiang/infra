#ifndef __RAYMON_SHAN_GLOBAL_VAR_HPP
#define __RAYMON_SHAN_GLOBAL_VAR_HPP

#include "infra.hpp"

// GLOBAL VARS
#ifndef __RAYMON_SHAN_FOR_L_Y
#define EXTERN
#else   // __RAYMON_SHAN_FOR_L_Y
#define EXTERN extern
#endif  // __RAYMON_SHAN_FOR_L_Y

EXTERN std::string LogPath;
EXTERN int LogFileLines;
EXTERN int LogFileLevel;
EXTERN int LogTermLevel;

EXTERN std::string DataDefineFile;

//EXTERN const char *ConfigFileName;
//EXTERN const char *ClassDefineName;

#undef  EXTERN

//extern FILE *configfilein;
//extern FILE *classdefinein;

const char* AssignInt(const char* key, char* value);
const char* AssignString(const char* key, char* value);
const char* AssignIpaddress(const char* key, char* value);


struct ScanExtra {
  std::string fileName;
  class ClassDefine *classDefine;
};
const char* DefineType(void *classdefinescanner, int type, const char* identifier);
const char* DefineProperty(void *classdefinescanner, int prop);
  
const char* DefineClass(void *classdefinescanner, const char* name);
const char* DefineInheritClass(void *classdefinescanner, const char* name, const char* base);
const char* DefineAggregationClass(void *classdefinescanner, const char* name, const char* summary);
const char* DefineInheritAggregationClass(void *classdefinescanner,
					  const char* name, const char* base, const char* summary);

#endif  // __RAYMON_SHAN_GLOBAL_VAR_HPP



