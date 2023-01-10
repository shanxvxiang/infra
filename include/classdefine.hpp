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

const char* DefineString(const char* identifier) {
  printf("in define string %s \n", identifier);
  return 0;
};
const char* DefineInt(const char* identifier)  {
  return 0;
};
const char* DefinePercent(const char* identifier) {
  return 0;
};
const char* DefineMoney(const char* identifier) {
  return 0;
};
const char* DefineHash(const char* identifier) {
  return 0;
};
const char* DefineTime(const char* identifier) {
  return 0;
};


#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
