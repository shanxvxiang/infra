#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

int DoClassDefineParse(FILE* in, struct ScanExtra* extra);

class ClassDefine {
  ScanExtra scanExtra;
  int pendingFieldCategory;
  int pendingFieldType;
  DataClass *pendingInheritClass;
  DataClass *pendingAggregationClass;
  DataField *pendFieldList;

public:
  void RenewPendingField(void) {
    pendingFieldCategory = 0;
    pendingFieldType = 0;
  };
  void RenewPendingClass(void) {
    pendingInheritClass = NULL;
    pendingAggregationClass = NULL;
    pendFieldList = NULL;
  };
  void ChainFieldList(DataField *field) {
    DataField **pnext = &pendFieldList;
    while (*pnext != NULL) pnext = &((*pnext)->nextField);
    *pnext = field;
  };
  void FreeAllFieldList(DataField *field) {
    DataField **pnext = &field;
    DataField *now;
    while (*pnext != NULL)  {
      now = *pnext;
      pnext = &((*pnext)->nextField);
      delete now;
    }
  };
  ClassDefine() {
    const char *ret;
    FILE *classdefinein;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    classdefinein = fopen(DataDefineFile.c_str(), "r");
    if (!classdefinein) {
      _LOG_CRIT("%s, <%s>", ERROR_INVALID_CLASSFILE, DataDefineFile.c_str());
      exit(1);
    }
    RenewPendingField();
    RenewPendingClass();
    scanExtra.fileName = DataDefineFile;
    scanExtra.classDefine = this;
    printf("this %p\n", this);
    DoClassDefineParse(classdefinein, &scanExtra);
    
  };

  const char* DefineField(const char* name) {
    //DataField *newfield = new DataField(pendingFieldCategory, pendingFieldType, name);
    //ChainFieldList(newfield);
    //RenewPendingField();
    //    printf("in DefineField %s \n", name);
    return 0;
  };
  const char* DefineFieldType(int type) {
    //pendingFieldType = type;
    return 0;
  };
  const char* DefineFieldCategory(int cate) {
    //pendingFieldCategory = cate;
    return 0;
  };
  const char* DefineClass(const char* name) {
    //DataClass *newclass = new DataClass(NULL, NULL, pendFieldList, name);
    //newclass->TravelClass();
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
  };
};

const char* DefineField(void* classdefinescanner, const char* name) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  printf("in out %p, %p\n", extra->classDefine, classdefinescanner);
  return extra->classDefine->DefineField(name);
};
const char* DefineFieldType(void* classdefinescanner, int type) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineFieldType(type);
};
const char* DefineFieldCategory(void* classdefinescanner, int cate) {
  ScanExtra* extra = (ScanExtra*)classdefinescanner;            // the first field in scan is extra
  return extra->classDefine->DefineFieldCategory(cate);
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
