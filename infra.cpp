#include "include/infra.hpp"

int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);

  LogDirectly *gLogDirectly = new LogDirectly();
  ThreadInfo *gThreadInfo = new ThreadInfo();
  SignalHandle *gSignalHandle = new SignalHandle();
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  gLogDirectly->SetLogFileParameter();

  ClassDefine *gClassDefine = new ClassDefine();
  // gConfigureFile->IteratorParameter();
  uint8_t testbuf[] = "abc";
  uint8_t dgst[32];

  // TestInsertNode(3,10000);
  sm3_digest(testbuf, 3, dgst);
  for (int i=0; i<32; i++) printf("%x", dgst[i]);
  printf("\n");
  
  delete gClassDefine;
  delete gConfigureFile;
  delete gSignalHandle;
  delete gThreadInfo;
  delete gLogDirectly;
  return 0;

}


