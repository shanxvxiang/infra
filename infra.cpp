
#include "include/infra.hpp"



int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  infra::ThreadInfo *gThreadInfo = new infra::ThreadInfo;
  infra::LogDirectly *gLogDirectly = new infra::LogDirectly(LEVEL_LOG_TRAC);
  infra::ConfigureFile *gConfigureFile = new infra::ConfigureFile((char*)__MY_PROGRAM ".conf");
  //gLogDirectly->LogFileHandle();

  int LogLevel = 0;
  std::any ll = LogLevel;
  char *ret = infra::ConfigureFile::GetSingleConfigureParameter(TOSTRING(LogLevel), ll);
  std::cout << ret << std::endl;
  delete gConfigureFile;
  delete gLogDirectly;
  delete gThreadInfo;


  return 0;

}

