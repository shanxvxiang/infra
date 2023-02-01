#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

int DoClassDefineParse(FILE* in, struct ScanExtra* extra);

class ClassDefine {
  ScanExtra  scanExtra;
  DataClass* pendingClass;
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
    scanExtra.fileName = DataDefineFile;
    scanExtra.classDefine = this;
    DoClassDefineParse(classdefinein, &scanExtra);
  };
  const char* DefineType(int type, const char* id) {
    printf("in define type %d, name %s \n", type, id);
    return 0;
  };
  const char* DefineProperty(int prop) {
    printf("in define property %d \n", prop);
    return 0;
  };
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
};

const char* DefineType(void* classdefinescanner, int type, const char* id) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineType(type, id);
};
const char* DefineProperty(void* classdefinescanner, int prop) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineProperty(prop);
}
const char* DefineClass(void* classdefinescanner, const char* name) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineClass(name);
};
const char* DefineInheritClass(void* classdefinescanner, const char* name, const char* base) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineInheritClass(name, base);
};
const char* DefineAggregationClass(void* classdefinescanner, const char* name, const char* summary) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineAggregationClass(name, summary);    
  return 0;  
};
const char* DefineInheritAggregationClass(void* classdefinescanner,
					  const char* name, const char* base, const char* summary) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineInheritAggregationClass(name, base, summary);  
}


#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
