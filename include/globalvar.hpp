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
const char* DefineField(void* classdefinescanner, const char* name);
const char* DefineFieldType(void* classdefinescanner, int type);
const char* DefineFieldCategory(void* classdefinescanner, int prop);
  
const char* DefineClass(void *classdefinescanner, const char* name, const char* base, const char* summary);
const char* EndofDefineClass(void* classdefinescanner);


const char* DefineValueOrder(void* classdefinescanner, char *name, int isfirst = 1);
const char* DefineClassValue(void* classdefinescanner, char *name, int defaultorder = 1);

const char* DefineFieldValue(void* classdefinescanner, char *name, int isfirst = 1);
const char* DefineFieldLine(void* classdefinescanner, int linemode);
const char* DefineValueLevel(void* classdefinescanner, int level);
const char* EndofValueClass(void* classdefinescanner);



#endif  // __RAYMON_SHAN_GLOBAL_VAR_HPP



