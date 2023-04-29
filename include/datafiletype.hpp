#ifndef __RAYMON_SHAN_DATAFILE_TYPE_HPP
#define __RAYMON_SHAN_DATAFILE_TYPE_HPP

#include "infraall.hpp"

// depend classdefine.y
// %token T_STRING T_INT T_DOUBLE T_MONEY T_HASH T_TIME
int FIELDOFFSET[T_TIME - T_STRING + 1] = {sizeof(String), sizeof(Int)};

typedef class TreeNode<SM3Hash, Hash256> ClassTree;
typedef int (*ComFunc)(char*, char*);

class DataField {
public:
  int fieldCategory;            // key, unique, essential, attribute
  int fieldType;                // string, int, double, money, hash, time
  int fieldOffset;
  DataField *nextField;
  std::string fieldName;
  ComFunc cmpField;
  
public:
  DataField() {
    fieldCategory = 0;
    fieldType = 0;
    nextField = NULL;
  };
  DataField(int category, int type, int offset, const char *name) {
    fieldCategory = category;
    fieldType = type;
    fieldOffset = offset;
    fieldName = name;
    nextField = NULL;
    if (type == T_STRING) cmpField = CompareString;
    else if (type == T_INT) cmpField = CompareInt;
    else cmpField = NULL;
  };
  void Display(void) {
    printf("FIELD %s, %d, %d, %d\n", fieldName.c_str(), fieldCategory, fieldType, fieldOffset);
  };

  static int CompareString(char *val1, char *val2) {
    return String::Compare((String*)val1, (String*)val2);
  }
  static int CompareInt(char *val1, char *val2) {
    return Int::Compare((Int*)val1, (Int*)val2);
  }
};

class DataClass {
public:
  String className;
  DataClass *inheritClass;
  DataClass *aggregationClass;
  DataField *fieldList;
  ClassTree valueVirtualRoot;
  int fieldLength;

  ComFunc cmpField;
  int keyOffset;
public:
  DataClass(String &name, DataClass *inherit, DataClass *aggregation, DataField *field) {
    inheritClass = inherit;
    aggregationClass = aggregation;
    fieldList = field;
    className = name;
    valueVirtualRoot.parent = valueVirtualRoot.child = valueVirtualRoot.brother = NULL;

    fieldLength = 0;
    DataField *next = fieldList;
    while (next != NULL) {
      if (next->fieldCategory == K_KEY) {
	cmpField = next->cmpField;
	keyOffset = fieldLength;
      }
      fieldLength += FIELDOFFSET[next->fieldType - T_STRING];
      next = next->nextField;
    }
  };
  void FreeAllFieldList(DataField *field) {
    DataField *next = field;
    DataField *now;
    while (next != NULL)  {
      now = next;
      next = next->nextField;
      delete now;
    }
  };
  ~DataClass() {
    FreeAllFieldList(fieldList);    
  };
  
  void Display(void) {
    printf("CLASS %s, size:%d\n", className.GetAddress(), fieldLength);
    DataField **pnext = &fieldList;
    while (*pnext != NULL) {
      (*pnext)->Display();
      pnext = &((*pnext)->nextField);
    }
    return;
  };
  void DisplayValue(void) {
    return DisplayValue(fieldList, valueVirtualRoot.child);
  };
  void DisplayValue(DataField *field, ClassTree *value) {
    value->TraversalNode();
    return;
  };
};

/*
聚合关系（Aggregation） 树木 --o 森林
泛化关系（Generalization） 继承类 --|> 基类
实现关系（Realization）   实现 ..|> 接口
组合关系 Composition      部件 --* 整体 
 */
//struct 

#endif  // __RAYMON_SHAN_DATAFILE_TYPE_HPP


