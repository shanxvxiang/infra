#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

extern "C" {
  const char* DefineString(const char* identifier);
  const char* DefineInt(const char* identifier);
  const char* DefinePercent(const char* identifier);
  const char* DefineMoney(const char* identifier);
  const char* DefineHash(const char* identifier);
  const char* DefineTime(const char* identifier);

  const char* DefineProperty(int prop);
  
  const char* DefineClass(const char* name);
  const char* DefineInheritClass(const char* name, const char* base);
  const char* DefineAggregationClass(const char* name, const char* summary);
  const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary);
}



extern FILE *classdefinein;

class ClassDefine {
public:
  ClassDefine() {
    const char *ret;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    classdefinein = fopen(DataDefineFile.c_str(), "r");
    classdefineparse();
  };
};

const char* DefineString(const char* id) {
  printf("in define string %s \n", id);
  return 0;
};
const char* DefineInt(const char* id)  {
  return 0;
};
const char* DefinePercent(const char* id) {
  return 0;
};
const char* DefineMoney(const char* id) {
  return 0;
};
const char* DefineHash(const char* id) {
  return 0;
};
const char* DefineTime(const char* id) {
  return 0;
};

const char* DefineProperty(int prop) {
  printf("in define property %d \n", prop);
  return 0;
}

const char* DefineClass(const char* name) {
  printf("in define class %s \n", name);
  return 0;  
};
const char* DefineInheritClass(const char* name, const char* base) {
  return 0;  
};
const char* DefineAggregationClass(const char* name, const char* summary) {
  return 0;  
};
const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary) {
  return 0;  
}


#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
