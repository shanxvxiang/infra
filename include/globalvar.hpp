#ifndef __RAYMON_SHAN_GLOBAL_VAR_HPP
#define __RAYMON_SHAN_GLOBAL_VAR_HPP

#include "infra.hpp"

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

#endif  // __RAYMON_SHAN_GLOBAL_VAR_HPP
