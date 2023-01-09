#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

class PumlParseImplement  {


public:
  PumlParseImplement() {
  
  };

};

class ClassDefine {
public:
  ClassDefine() {
    const char *ret;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    ClassDefineFile(DataDefineFile.c_str());
  };
  
  char* ClassDefineFile(const char *name) {

    return NULL;
  };

};
#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
