#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

int DoClassDefineParse(FILE* in, const char* name);

class ClassDefine {
public:
  ClassDefine() {
    const char *ret;
    FILE *classdefinein;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    classdefinein = fopen(DataDefineFile.c_str(), "r");
    if (!classdefinein) {
      _LOG_CRIT("%s, <%s>", ERROR_INVALID_CLASSFILE, DataDefineFile.c_str());
      exit(1);
    }
    //    ClassDefineName = DataDefineFile.c_str();
    DoClassDefineParse(classdefinein, DataDefineFile.c_str());
  };
};

const char* DefineType(int type, const char* id) {
  printf("in define type %d, name %s \n", type, id);
  return 0;
};

const char* DefineProperty(int prop) {
  printf("in define property %d \n", prop);
  return 0;
}

const char* DefineClass(const char* name) {
  printf("in DefineClass:%s \n", name);
  return 0;  
};
const char* DefineInheritClass(const char* name, const char* base) {
  printf("in DefineInheritClass:%s base:%s \n", name, base);  
  return 0;  
};
const char* DefineAggregationClass(const char* name, const char* summary) {
  printf("in DefineAggregationClass:%s aggr:%s \n", name, summary);    
  return 0;  
};
const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary) {
  printf("in DefineInheritAggregationClass:%s base:%s aggr:%s \n", name, base, summary);  
  return 0;  
}


#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
