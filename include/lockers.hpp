#ifndef __RAYMON_SHAN_LOCKS_HPP
#define __RAYMON_SHAN_LOCKS_HPP

#include "systeminclude.hpp"

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

class SpinLock {
  struct spinlock spin;
public:
  SpinLock() {
    spin_lock_init(spin);
  }
  ~SpinLock() {
  }
  void operator ++(int) {
    spin_lock(&spin);
  }
  void operator --(int) {
    spin_unlock(&spin);    
  }
};

#endif  // __RAYMON_SHAN_LOCKS_HPP
