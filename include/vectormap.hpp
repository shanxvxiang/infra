#ifndef __RAYMON_SHAN_VECTOR_MAP_HPP
#define __RAYMON_SHAN_VECTOR_MAP_HPP

#include "infra.hpp"

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH >
class Node
{
private:
  HASH hash;
  KEY key;
  VALUE value;
public:
  Node(KEY& k, VALUE& v) {
    key = k;
    value = v;
    HASHCLASS::Digest(key.GetAddress(), key.GetLength(), hash.GetAddress());
  }
  void PrintHash() {
    HASHCLASS::PrintHash(hash.GetAddress());
  }
};

typedef class Node <String, String, SM3_Hash, Hash256> StringNode;





#endif  // __RAYMON_SHAN_VECTOR_MAP_HPP
