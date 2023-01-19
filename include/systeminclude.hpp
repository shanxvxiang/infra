#ifndef __RAYMON_SHAN_SYSTEM_INCLUDE_HPP
#define __RAYMON_SHAN_SYSTEM_INCLUDE_HPP

#include <bits/stdc++.h>

#include <execinfo.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>

#include <arpa/inet.h>

// #include <linux/spinlock.h>

#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>


// GLOBAL VARS
#ifndef __RAYMON_SHAN_FOR_L_Y
#define EXTERN
#else   // __RAYMON_SHAN_FOR_L_Y
#define EXTERN extern
#endif  // __RAYMON_SHAN_FOR_L_Y

EXTERN std::string LogPath;
EXTERN int LogFileLines;
EXTERN int LogFileLevel;
EXTERN int LogTermLevel;

EXTERN std::string DataDefineFile;



#endif  // __RAYMON_SHAN_SYSTEM_INCLUDE_HPP
