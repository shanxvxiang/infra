#ifndef __RAYMON_SHAN_INFRA_HPP
#define __RAYMON_SHAN_INFRA_HPP

#include <any>
#include <iostream>
#include <map>
#include <typeinfo>

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

//#include <linux/spinlock.h>

#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>

#include "../parse/configfile.bison.hpp"
#include "../parse/classdefine.bison.hpp"

std::string LogPath;
int LogFileLines;
int LogFileLevel;
int LogTermLevel = 6;

std::string DataDefineFile;

#include "raymoncommon.hpp"
#include "errormessage.hpp"
#include "stringtools.hpp"
#include "lockers.hpp"
#include "threadinfo.hpp"
#include "logdirectly.hpp"

#include "configurefile.hpp"

#include "signalhandle.hpp"
#include "classdefine.hpp"

#include "datafiletype.hpp"

#endif  // __RAYMON_SHAN_INFRA_HPP

