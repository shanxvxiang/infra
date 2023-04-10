#ifndef __RAYMON_SHAN_GM_ENCRYPTION_HPP
#define __RAYMON_SHAN_GM_ENCRYPTION_HPP

#include "infra.hpp"

class ValueType {
public:
  virtual unsigned char* GetAddress() = 0;
  virtual int GetLength() = 0;
};

class None : public ValueType {
public:
  None() {};
  unsigned char* GetAddress() {
    return NULL;
  };
  int GetLength() {
    return 0;
  };
};

class String : public ValueType {
public:
  std::string val;
public:
  String() {};
  String(const std::string& str) {
    val = str;
  };
  String& operator = (const char* str) {
    val = str;
    return *this;
  };

  String& operator = (String& that) {
    val = that.val;
    return *this;
  };
  unsigned char* GetAddress() {
    return (unsigned char*)val.c_str();
  };
  int GetLength() {
    return val.length();
  };
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
  bool operator <= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) <= 0);
  };
  bool operator < (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) < 0);
  };
  bool operator >= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) >= 0);
  };
  bool operator > (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) > 0);
  };
  int Compare(Hash256& that) {
    return memcmp(val, that.val, sizeof(long) * 4);
  };
  unsigned char* GetAddress() {
    return (unsigned char*)val;
  };
  void PrintHash(int len = 0) {
    unsigned char *uc = (unsigned char*)val;
    if (len == 0) len = 32;
    for(int i = 0; i < len; i++) {
      printf("%02X", *uc++);
    }
    // printf("\n");
  };
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
#endif  // __RAYMON_SHAN_GM_ENCRYPTION_HPP
