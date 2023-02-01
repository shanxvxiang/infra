#ifndef __RAYMON_SHAN_DATAFILE_TYPE_HPP
#define __RAYMON_SHAN_DATAFILE_TYPE_HPP

#include "infra.hpp"

class DataField {
public:
  int fieldCategory;            // unique, essential, attribute
  int fieldType;                // string, int, percent, money, hash, time
  DataField *nextField;
  std::string fieldName;
public:
  DataField() {
    fieldCategory = 0;
    fieldType = 0;
    nextField = NULL;
  };
  DataField(int category, int type, const char *name) {
    fieldCategory = category;
    fieldType = type;
    fieldName = name;
    nextField = NULL;    
  };
  void Display(void) {
    printf("FIELD %s, %d, %d\n", fieldName.c_str(), fieldCategory, fieldType);
  };
};

class DataClass {
public:
  std::string className;
  DataClass *inheritClass;
  DataClass *aggregationClass;
  DataField *fieldList;
  TreeNode  *dataList;
public:
  DataClass(const char *name, DataClass *inherit, DataClass *aggregation, DataField *field) {
    inheritClass = inherit;
    aggregationClass = aggregation;
    fieldList = field;
    className = name;
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
  
  void TravelClass(void) {
    printf("CLASS %s\n", className.c_str());
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


