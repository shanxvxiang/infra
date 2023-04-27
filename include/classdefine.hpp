#ifndef __RAYMON_SHAN_CLASS_DEFINE_HPP
#define __RAYMON_SHAN_CLASS_DEFINE_HPP

#include "infraall.hpp"

struct classdefineguts_t {
  ScanExtra* yyextra_r;
};

typedef class LinkedNode<String, DataClass*, SM3Hash, Hash256> ClassNode;
typedef class NodeList<String, DataClass*, SM3Hash, Hash256> ClassList;
typedef class HashListMap<String, DataClass*, SM3Hash, Hash256> ClassHash;

typedef class TreeNode<SM3Hash, Hash256> ClassTree;

int DoClassDefineFileParse(FILE* in, struct ScanExtra* extra);
int DoClassDefineMemoryParse(char* buffer, int length, struct ScanExtra* extra);

class ClassDefine {
  ScanExtra scanExtra;
  FILE *classdefinein;
  int pendingFieldCategory;
  int pendingFieldType;
  int pendingFieldOffset;
  DataClass *pendingInheritClass;
  DataClass *pendingAggregationClass;
  DataClass *nowDataClass;
  DataField *pendFieldList;
  DataField *pendFieldOrder;
  DataField *nowFieldOrder;
  char *nowFieldBuffer;
  ClassTree **nowTreeNode;
  String pendName;
public:
  ClassTree *classTreeRoot;
  static ClassHash allClassHash;

public:
  void RenewPendingField(void) {
    pendingFieldCategory = 0;
    pendingFieldType = 0;

  };
  void RenewPendingClass(void) {
    RenewPendingField();
    pendingFieldOffset = 0;
    pendingInheritClass = NULL;
    pendingAggregationClass = NULL;
    pendFieldList = NULL;
    pendName = "";
    nowTreeNode = NULL;
    classTreeRoot = NULL;
  };
  void ChainFieldList(DataField *field) {
    DataField **pnext = &pendFieldList;
    while (*pnext != NULL) pnext = &((*pnext)->nextField);
    *pnext = field;
    //    printf("add chain %p\n", field);
  };
  void RemoveFieldList(DataField *list) {                 // for value field order use
    DataField *pnext = list, *nnext;
    while (pnext != NULL) {
      nnext = pnext;
      pnext = pnext->nextField;
      //      printf("in delete %p\n", nnext);
      delete nnext;
    }
    pendFieldList = NULL;
  };
  DataField* FindDataField(std::string &name, DataField *list) {
    while (list != NULL) {
      if (list->fieldName.compare(name) == 0) return list;
      list = list->nextField;
    }
    return NULL;
  };

  ClassDefine() {
    const char *ret;
    GetSingleConfigSegment(ret, DataDefineFile, "string");
    classdefinein = fopen(DataDefineFile.c_str(), "r");
    if (!classdefinein) {
      _LOG_CRIT("%s, <%s>", ERROR_INVALID_CLASSFILE, DataDefineFile.c_str());
      exit(1);
    }
    RenewPendingClass();
    scanExtra.fileName = DataDefineFile;
    scanExtra.classDefine = this;
    DoClassDefineFileParse(classdefinein, &scanExtra);    // READ CLASS DEFINE and VALUE
  };

  ClassDefine(char *buffer, int length) {
    RenewPendingClass();
    scanExtra.fileName = DataDefineFile;
    scanExtra.classDefine = this;
    DoClassDefineMemoryParse(buffer, length, &scanExtra);
  };  

  const char* DefineField(const char* name) {
    DataField *newfield = new DataField(pendingFieldCategory, pendingFieldType, pendingFieldOffset, name);
    pendingFieldOffset += FIELDOFFSET[pendingFieldType - T_STRING];
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
  };

  const char* DefineValueOrder(char *name, int isfirst) {
    //    printf("in value order %s, %d\n", name, isfirst);
    if (isfirst) {
      RemoveFieldList(pendFieldList);
    }
    DataField *newfield = new DataField(pendingFieldCategory, pendingFieldType, 0, name);
    ChainFieldList(newfield);
    RenewPendingField();
    return 0;
  };
  const char* DefineClassValue(char *name, int defaultorder) {
    DataField *field;
    DataField *order, *now;

    // TODO: verify class name
    nowDataClass = ClassDefine::allClassHash.Find(String(name))->value;
    field = nowDataClass->fieldList;
    nowTreeNode = &(nowDataClass->dataList);
    if (!defaultorder) {
      
      // TODO: confirm field in class
      pendFieldOrder = order = pendFieldList;
      while (order != NULL) {
	now = FindDataField(order->fieldName, field);
	if (now) {
	  order->fieldCategory = now->fieldCategory;
	  order->fieldType = now->fieldType;
	  order->fieldOffset = now->fieldOffset;
	}
	order = order->nextField;
      }
      //      printf("set order pending %p\n", pendFieldList);
      nowFieldOrder = pendFieldList;
    } else {
      //      printf("set order field %p\n", field);
      pendFieldOrder = field;
    }

    return 0;
  };
  const char* DefineFieldValue(char *name, int isfirst) {
    if (isfirst) {
      nowFieldOrder = pendFieldOrder;
      nowFieldBuffer = (char*)malloc(nowDataClass->fieldLength);
      //      printf("buffer size %d\n", nowDataClass->fieldLength);
    } else {
      nowFieldOrder = nowFieldOrder->nextField;

    }

    if (!nowFieldOrder) {

	// TODO: value number less than field
      return 0;
    }
    
    if (nowFieldOrder->fieldType == T_STRING) {
      String strval(name);
      //      printf("IN fieldvalue %p, %d\n", nowFieldBuffer, nowFieldOrder->fieldOffset);
      memcpy(nowFieldBuffer + nowFieldOrder->fieldOffset, &strval, sizeof(String));

    } else if (nowFieldOrder->fieldType == T_INT) {
      Int intval(atoi(name));
      memcpy(nowFieldBuffer + nowFieldOrder->fieldOffset, &intval, sizeof(Int));
    }
    return 0;
  };
  const char* DefineFieldLine(int linemode) {
    if (nowFieldOrder->nextField) {
    // TODO: verify field number      
      printf("in error field number \n");
    }

    ClassTree *now = new ClassTree();
    now->fieldBuffer = nowFieldBuffer;
    now->InsertNode(nowTreeNode);
    
    // TODO: doing mode
    return 0;
  };
  const char* DefineValueLevel(int level) {
    return 0;
  };
  const char* EndofValueClass() {
            RemoveFieldList(pendFieldList); 
    return 0;
  };
  
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
};
const char* DefineClass(void* classdefinescanner, const char* name, const char* base, const char* summary) {
  return ClassDefineFunc->DefineClass(name, base, summary);  
};
const char* EndofDefineClass(void* classdefinescanner) {
  return ClassDefineFunc->EndofDefineClass();
};


const char* DefineValueOrder(void* classdefinescanner, char* name, int isfirst) {
  return ClassDefineFunc->DefineValueOrder(name, isfirst);  
};
const char* DefineClassValue(void* classdefinescanner, char *name, int defaultorder) {
    return ClassDefineFunc->DefineClassValue(name, defaultorder); 
};
const char* DefineFieldValue(void* classdefinescanner, char *name, int isfirst) {
  return ClassDefineFunc->DefineFieldValue(name, isfirst);  
};
const char* DefineFieldLine(void* classdefinescanner, int linemode) {
  return ClassDefineFunc->DefineFieldLine(linemode);
};
const char* DefineValueLevel(void* classdefinescanner, int level) {
  return ClassDefineFunc->DefineValueLevel(level);
};
const char* EndofValueClass(void* classdefinescanner) {
  return ClassDefineFunc->EndofValueClass();
};


ClassHash ClassDefine::allClassHash(CLASS_HASH_BUCKET_NUMBER);    // 128

#endif  // __RAYMON_SHAN_CLASS_DEFINE_HPP
