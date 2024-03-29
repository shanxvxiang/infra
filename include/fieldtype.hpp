#ifndef __RAYMON_SHAN_FILED_TYPE_HPP
#define __RAYMON_SHAN_FILED_TYPE_HPP

#include "infra.hpp"

class ValueType {
public:
  //  virtual unsigned char* GetAddress() = 0;
  //  virtual int GetLength() = 0;
  //  virtual int GetSize() = 0;  
};

class None : public ValueType {
public:
  None() {};
  unsigned char* GetAddress() {
    return NULL;
  };
  int GetLength() {            // for string is strlen
    return 0;
  };
  int GetSize() {              // is sizeof()
    return 0;
  }
};

class Hash256 {
public:
  unsigned long val[4];
public:
  Hash256() {};
  Hash256& operator = (Hash256& that) {
    memcpy(val, that.val, sizeof(long) * 4);
    return *this;
  };
  bool operator == (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) == 0);
  };
  bool operator != (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) != 0);
  };
  bool operator > (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) > 0);
  };
  bool operator >= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) >= 0);
  };
  bool operator < (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) < 0);
  };  
  bool operator <= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) <= 0);
  };

  int Compare(Hash256& that) {
    return memcmp(val, that.val, sizeof(long) * 4);
  };
  unsigned char* GetAddress() {
    return (unsigned char*)val;
  };
  void Display(int len = 0) {
    unsigned char *uc = (unsigned char*)val;
    if (len == 0) len = 32;
    for(int i = 0; i < len; i++) {
      printf("%02X", *uc++);
    }
    // printf("\n");
  };
};

class String : public ValueType {
public:
  std::string val;
public:
  String() {};
  String(const std::string &str) {
    val = str;
  };
  String& operator = (const char *str) {
    val = str;
    return *this;
  };
  String& operator = (String &that) {
    val = that.val;
    return *this;
  };
  bool operator == (String &that) {
    return val.compare(that.val) == 0;
  };
  bool operator != (String &that) {
    return val.compare(that.val) != 0;
  };  
  bool operator > (String &that) {
    return val.compare(that.val) > 0;
  };
  bool operator >= (String &that) {
    return val.compare(that.val) >= 0;
  };
  bool operator < (String &that) {
    return val.compare(that.val) < 0;
  };
  bool operator <= (String &that) {
    return val.compare(that.val) <= 0;
  };

  unsigned char* GetAddress() {
    return (unsigned char*)val.c_str();
  };
  int GetLength() {
    return val.length();
  };
  int GetSize() {
    return sizeof(String);
  };
  void Display() {
    printf("%s", val.c_str());
  };
  static int Compare(String *val1, String *val2) {
    return val1->val.compare(val2->val);
  };
  
  template< typename... Args >
  static std::string Format(const char* format, Args... args) {
    int length = std::snprintf(nullptr, 0, format, args...);
    if (length <= 0) {
        return "";
    }
    char* buf = new char[length + 1];
    std::snprintf(buf, length + 1, format, args...);

    std::string str(buf);
    delete[] buf;
    return std::move(str);
  };
};

class Int : public ValueType {
public:
  long val;
public:
  Int() {
    val = 0;
  };
  Int(long i) {
    val = i;
  };
  Int& operator = (long i) {
    val = i;
    return *this;
  };
  Int& operator = (Int &that) {
    val = that.val;
    return *this;
  };
  bool operator == (Int &that) {
    return val == that.val;
  };
  bool operator != (Int &that) {
    return val != that.val;
  };  
  bool operator > (Int &that) {
    return val > that.val;
  };
  bool operator >= (Int &that) {
    return val >= that.val;
  };
  bool operator < (Int &that) {
    return val < that.val;
  };
  bool operator <= (Int &that) {
    return val <= that.val;
  };
  static int Compare(Int *val1, Int *val2) {
    if (val1->val == val2->val) return 0;
    else if (val1->val > val2->val) return 1;
    else return -1;
  }
  
  unsigned char* GetAddress() {
    return (unsigned char*)(&val);
  };
  int GetLength() {
    return sizeof(Int);
  };
  int GetSize() {
    return sizeof(Int);
  };
   void Display() {
  	printf("%ld", val);
  }
};

class SM3Hash {
public:
  SM3Hash() {};

  static unsigned char* Digest(unsigned char *detail, int len, unsigned char* hashvalue) {
    sm3_digest(detail, len, hashvalue);
    return hashvalue;
  };
};

class NoneHash {
public:
  NoneHash() {};
  static unsigned char* Digest(unsigned char*, int, unsigned char*) {
    return NULL;
  }
  static void PrintHash(unsigned char*) {
    printf("None\n");
  };
};

#endif  // __RAYMON_SHAN_FILED_TYPE_HPP

