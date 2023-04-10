#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infraall.hpp"

struct classdefineguts_t {
  ScanExtra* yyextra_r;
};

typedef class LinkedNode<String, DataClass*, SM3Hash, Hash256> ClassNode;
typedef class NodeList<String, DataClass*, SM3Hash, Hash256> ClassList;
typedef class HashListMap<String, DataClass*, SM3Hash, Hash256> ClassHash;

int DoClassDefineFileParse(FILE* in, struct ScanExtra* extra);
int DoClassDefineMemoryParse(char* buffer, int length, struct ScanExtra* extra);

class ClassDefine {
  ScanExtra scanExtra;
  FILE *classdefinein;
  int pendingFieldCategory;
  int pendingFieldType;
  DataClass *pendingInheritClass;
  DataClass *pendingAggregationClass;
  DataField *pendFieldList;
public:
  static ClassHash allClassHash;

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
    DoClassDefineFileParse(classdefinein, &scanExtra);
  };

  ClassDefine(char *buffer, int length) {
    RenewPendingField();
    RenewPendingClass();
    scanExtra.fileName = DataDefineFile;
    scanExtra.classDefine = this;
    DoClassDefineMemoryParse(buffer, length, &scanExtra);
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

  const char* DefineInheritAggregationClass(const char* name, const char* base, const char* summary) {
    ClassNode *node;
    DataClass *inhe = NULL, *aggr = NULL;
    if (base) {
      node = allClassHash.Find(String(base));
      if (node) inhe = node->value;
    }
    if (summary) {
      node = allClassHash.Find(String(summary));
      if (node) aggr = node->value;
    }
    
    DataClass *newclass = new DataClass(name, inhe, aggr, pendFieldList);
    node = new ClassNode(String(name), newclass);
    allClassHash.FindOrInsert(node);
    RenewPendingClass();
    //    printf("in DefineInheritAggregationClass:%s base:%s aggr:%s \n", name, base, summary);
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
  return extra->classDefine->DefineInheritAggregationClass(name, NULL, NULL);
};
const char* DefineInheritClass(void* classdefinescanner, const char* name, const char* base) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineInheritAggregationClass(name, base, NULL);
};
const char* DefineAggregationClass(void* classdefinescanner, const char* name, const char* summary) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineInheritAggregationClass(name, NULL, summary);    
};
const char* DefineInheritAggregationClass(void* classdefinescanner,
					  const char* name, const char* base, const char* summary) {
  ScanExtra* extra = ((classdefineguts_t*)classdefinescanner)->yyextra_r;
  return extra->classDefine->DefineInheritAggregationClass(name, base, summary);  
}


ClassHash ClassDefine::allClassHash(CLASS_HASH_BUCKET_NUMBER);    // 128

#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
