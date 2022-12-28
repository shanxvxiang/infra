#ifndef __RAYMON_SHAN_LOCKS_HPP
#define __RAYMON_SHAN_LOCKS_HPP

#include "infra.hpp"

class MutexLock {
  pthread_mutex_t mutex;
public:
  MutexLock() {
    pthread_mutex_init(&mutex, NULL);
  }
  ~MutexLock() {
    pthread_mutex_destroy(&mutex);
  }
  void operator ++(int) {
    pthread_mutex_lock(&mutex);
  }
  void operator --(int) {
    pthread_mutex_unlock(&mutex);
  }
};

#endif  // __RAYMON_SHAN_LOCKS_HPP
