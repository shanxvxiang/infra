#ifndef __RAYMON_SHAN_GM_ENCRYPTION_HPP
#define __RAYMON_SHAN_GM_ENCRYPTION_HPP

#include "infra.hpp"

class SM3_Hash {
  uint8_t hash[256/8];

#ifdef  _WITH_TEST_NODE  
  char hashid;
#endif  // _WITH_TEST_NODE
  
public:
  SM3_Hash() {};

#ifdef  _WITH_TEST_NODE  
  SM3_Hash(char id) { hashid = id; };
  void Print(void) {
    printf("%c", hashid);
  }
#endif  // _WITH_TEST_NODE

  void Digest(const unsigned char *detail, int len) {
    sm3_digest(detail, len, hash);
  }

  void Digest(const unsigned char *detail) {
    Digest(detail, strlen((const char*)detail));
    return;
  }
};


#endif  // __RAYMON_SHAN_GM_ENCRYPTION_HPP
