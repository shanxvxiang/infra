#ifndef __RAYMON_SHAN_GM_ENCRYPTION_HPP
#define __RAYMON_SHAN_GM_ENCRYPTION_HPP

#include "infra.hpp"

class ValueType {
public:
  virtual unsigned char* GetAddress() = 0;
  virtual int GetLength() = 0;
};

class String : public ValueType {
public:
  std::string val;
public:
  String() {};
  String(const std::string& str) {
    val = str;
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
  }
  bool operator != (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) != 0);
  }
  bool operator <= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) <= 0);
  }
  bool operator < (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) < 0);
  }
  bool operator >= (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) >= 0);
  }
  bool operator > (Hash256& that) {
    return (memcmp(val, that.val, sizeof(long) * 4) > 0);
  }
  unsigned char* GetAddress() {
    return (unsigned char*)val;
  }
};

class SM3_Hash {
public:
  SM3_Hash() {};

  static unsigned char* Digest(unsigned char *detail, int len, unsigned char* hashvalue) {
    sm3_digest(detail, len, hashvalue);
    return hashvalue;
  };
  static void PrintHash(unsigned char* hashvalue) {
    for(int i = 0; i < 256/8; i++) {
      unsigned char c = hashvalue[i];
      printf("%02X", c);
    }
    printf("\n");
  }
};


#endif  // __RAYMON_SHAN_GM_ENCRYPTION_HPP
