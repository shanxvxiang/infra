#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infra.hpp"

struct classdefineguts_t {
  ScanExtra* yyextra_r;
};
class ClassDefine;

class AllClassMap {
  
};

int DoClassDefineParse(FILE* in, struct ScanExtra* extra);

class ClassDefine {
  ScanExtra scanExtra;
  FILE *classdefinein;
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

  ClassDefine() {
    const char *ret;
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
    DoClassDefineParse(classdefinein, &scanExtra);
  };

  const char* DefineField(const char* name) {
    DataField *newfield = new DataField(pendingFieldCategory, pendingFieldType, name);
    ChainFieldList(newfield);
    RenewPendingField();
    return 0;
  };
  const char* DefineFieldType(int type) {
    pendingFieldType = type;
    return 0;
  };
  const char* DefineFieldCategory(int cate) {
    pendingFieldCategory = cate;
    return 0;
  };
  const char* DefineClass(const char* name) {
    DataClass *newclass = new DataClass(name, NULL, NULL, pendFieldList);
    RenewPendingClass();
    
    printf("in DefineClass:%s \n", name);
    return 0;
  };
  const char* DefineInheritClass(const char* name, const char* base) {
    RenewPendingClass();
    printf("in DefineInheritClass:%s base:%s \n", name, base);
    return 0;
  };
  const char* DefineAggregationClass(const char* name, const char* summary) {
    RenewPendingClass();
    printf("in DefineAggregationClass:%s aggr:%s \n", name, summary);
    return 0;
  };
  const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary) {
    RenewPendingClass();
    printf("in DefineInheritAggregationClass:%s base:%s aggr:%s \n", name, base, summary);
    return 0;
  };
};

const char* DefineField(void* classdefinescanner, const char* name) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineField(name);
};
const char* DefineFieldType(void* classdefinescanner, int type) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineFieldType(type);
};
const char* DefineFieldCategory(void* classdefinescanner, int cate) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineFieldCategory(cate);
}
const char* DefineClass(void* classdefinescanner, const char* name) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineClass(name);
};
const char* DefineInheritClass(void* classdefinescanner, const char* name, const char* base) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineInheritClass(name, base);
};
const char* DefineAggregationClass(void* classdefinescanner, const char* name, const char* summary) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineAggregationClass(name, summary);    
  return 0;  
};
const char* DefineInheritAggregationClass(void* classdefinescanner,
					  const char* name, const char* base, const char* summary) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineInheritAggregationClass(name, base, summary);  
}


#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
