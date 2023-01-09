
#include "include/infra.hpp"

int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  ThreadInfo *gThreadInfo = new ThreadInfo;
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  //  LogDirectly *gLogDirectly = new LogDirectly();
  SignalHandle *gSignalHandle = new SignalHandle();

  //  ClassDefine *gClassDefine = new ClassDefine();

  gConfigureFile->IteratorParameter();
  
  //  delete gClassDefine;
  delete gSignalHandle;
  //  delete gLogDirectly;
  delete gConfigureFile;
  delete gThreadInfo;

  return 0;

}


