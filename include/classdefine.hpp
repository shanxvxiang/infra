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
  String pendName;
public:
  TreeNode *classTreeRoot;
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
    pendName = "";
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

  const char* DefineClass(const char* name, const char* base, const char* summary) {
    // TODO not found class
    ClassNode *node;
    pendName = name;
    if (base) {
      node = allClassHash.Find(String(base));
      if (node) pendingInheritClass = node->value;
    }
    if (summary) {
      node = allClassHash.Find(String(summary));
      if (node) pendingAggregationClass = node->value;
    }
    return 0;
  };

  const char* EndofDefineClass() {
    ClassNode *node;
    DataClass *newclass =
      new DataClass(pendName, pendingInheritClass, pendingAggregationClass, pendFieldList);
    //    newclass->Display();
    node = new ClassNode(pendName, newclass);
    allClassHash.FindOrInsert(node);
    RenewPendingClass();
    return 0;
  }
};

#define ClassDefineFunc ((classdefineguts_t*)classdefinescanner)->yyextra_r->classDefine

const char* DefineField(void* classdefinescanner, const char* name) {
  return ClassDefineFunc->DefineField(name);
};
const char* DefineFieldType(void* classdefinescanner, int type) {
  return ClassDefineFunc->DefineFieldType(type);
};
const char* DefineFieldCategory(void* classdefinescanner, int cate) {
  return ClassDefineFunc->DefineFieldCategory(cate);
}
const char* DefineClass(void* classdefinescanner, const char* name, const char* base, const char* summary) {
  return ClassDefineFunc->DefineClass(name, base, summary);  
}
const char* EndofDefineClass(void* classdefinescanner) {
  return ClassDefineFunc->EndofDefineClass();
};



ClassHash ClassDefine::allClassHash(CLASS_HASH_BUCKET_NUMBER);    // 128

#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
