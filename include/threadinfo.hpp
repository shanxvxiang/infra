#ifndef __RAYMON_SHAN_THREAD_INFO_HPP
#define __RAYMON_SHAN_THREAD_INFO_HPP

#include "infra.hpp"

struct threadStartInfo {
  char threadName[SMALL_CHAR_LENGTH];
  void *(*threadFunc)(void *);
  void *threadArg;
  unsigned int threadID;
};

#ifndef __RAYMON_SHAN_FOR_L_Y
thread_local threadStartInfo ThreadStartInfo;
#else  // __RAYMON_SHAN_FOR_L_Y
extern thread_local threadStartInfo ThreadStartInfo;
#endif // __RAYMON_SHAN_FOR_L_Y

void *InitializeThread(void *arg);

class ThreadInfo {
public:
  ThreadInfo() {
    strncpy(ThreadStartInfo.threadName, "MAIN", SMALL_CHAR_LENGTH - 1);
    ThreadStartInfo.threadID = syscall(SYS_gettid);
  };
  static MutexLocker serializeMutex;

  static pthread_t CreateThread(const char *tname, void *(*func)(void *), void *arg) {
    pthread_t tid;
    static threadStartInfo startInfo;

    serializeMutex++;
    strncpy(startInfo.threadName, tname, SMALL_CHAR_LENGTH - 1);
    startInfo.threadFunc = func;
    startInfo.threadArg = arg;
    pthread_create(&tid, NULL, InitializeThread, &startInfo);
    return tid;
  };
};

#ifndef __RAYMON_SHAN_FOR_L_Y

void* InitializeThread(void *arg)
{
  memcpy(&ThreadStartInfo, arg, sizeof(threadStartInfo));
  ThreadInfo::serializeMutex--;

  ThreadStartInfo.threadID = syscall(SYS_gettid);
  return ThreadStartInfo.threadFunc(ThreadStartInfo.threadArg);
}

MutexLocker ThreadInfo::serializeMutex;

#endif // __RAYMON_SHAN_FOR_L_Y

#endif  // __RAYMON_SHAN_THREAD_INFO_HPP

