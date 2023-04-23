#ifndef __RAYMON_SHAN_DATAFILE_TYPE_HPP
#define __RAYMON_SHAN_DATAFILE_TYPE_HPP

#include "infraall.hpp"

class DataField {
public:
  int fieldCategory;            // unique, essential, attribute
  int fieldType;                // string, int, percent, money, hash, time
  int fieldOffset;
  DataField *nextField;
  std::string fieldName;
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
  };
  void Display(void) {
    printf("FIELD %s, %d, %d, %d\n", fieldName.c_str(), fieldCategory, fieldType, fieldOffset);
  };
};

class DataClass {
public:
  String className;
  DataClass *inheritClass;
  DataClass *aggregationClass;
  DataField *fieldList;
  TreeNode  *dataList;
  int fieldLength;
public:
  DataClass(String &name, DataClass *inherit, DataClass *aggregation, DataField *field) {
    inheritClass = inherit;
    aggregationClass = aggregation;
    fieldList = field;
    className = name;

    fieldLength = 0;
    DataField *next = fieldList;
    while (next != NULL) {
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
  }
  
  void Display(void) {
    printf("CLASS %s, size:%d\n", className.GetAddress(), fieldLength);
    DataField **pnext = &fieldList;
    while (*pnext != NULL) {
      (*pnext)->Display();
      pnext = &((*pnext)->nextField);
    }
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


