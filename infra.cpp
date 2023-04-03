#include "include/infra.hpp"

#ifndef __RAYMON_SHAN_FOR_L_Y

typedef class SM3Hash _Hash;
#include "include/gmencryption.hpp"

#include "include/signalhandle.hpp"
#include "include/vectormap.hpp"
#include "include/configurefile.hpp"
#include "include/treedefine.hpp"
#include "include/datafiletype.hpp"
#include "include/classdefine.hpp"
#include "include/voucher.hpp"

#endif  // __RAYMON_SHAN_FOR_L_Y

//typedef class LinkedNode <String, String, SM3Hash, Hash256> StringNode;
//typedef class NodeList<String, String, SM3Hash, Hash256> StringList;
//String K("abc");
//String V("aasdfsdfds242dfadfasdfdsfdsaf");

typedef class LinkedNode <String, String, SM3Hash, Hash256> StringNode;
typedef class NodeList<String, String, SM3Hash, Hash256> StringList;
typedef class HashListMap<String, String, SM3Hash, Hash256> StringHash;

volatile int wwait = 1;
int addsize = 100000;
StringNode *node;
StringList list;
StringHash hash(1000);

void* TestList(void*) {
  do {} while (wwait);
  
  VoucherDetail vd;
  for (int i = 0; i < addsize; i++) {
    vd.money = i;
//    printf("%d, %d\n", ThreadStartInfo.threadID, i);
//    InsertVoucherDetail(&bdn, new VoucherDetailNode(KN, vd));
  }

  return NULL;
};

int main(int, char **) {
  TimeSpend tspend;
  int ret, ret1, ret2;
  //  void* retv;

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  //  pthread_t t1 = ThreadInfo::CreateThread("test", TestList, (void*)0xaaa);
  //  pthread_t t2 = ThreadInfo::CreateThread("errrr", TestList, (void*)0xbbb);
  //  pthread_t t3 = ThreadInfo::CreateThread("test", TestList, (void*)0xccc);

  wwait = 0;
  tspend.TimeStart();
  String a1 ("a1");
  String a2 ("a2");
  String a3 ("a3");
  String a4 ("a4");
  String a5 ("a5");
  
  hash.FindOrInsert(new StringNode(a1, a1));
  hash.FindOrInsert(new StringNode(a2, a1));
  hash.FindOrInsert(new StringNode(a3, a1));
  hash.FindOrInsert(new StringNode(a4, a1));
  hash.FindOrInsert(new StringNode(a5, a1));

  list.PrintList();

  //  pthread_join(t1, &retv);
  //  pthread_join(t2, &retv);
  //  pthread_join(t3, &retv);
  ret1 = tspend.TimeClick();
  
  // ret = bdn.value.voucherDetailList->Size();
  ret2 = tspend.TimeClick();
  //  printf("money: %ld\n", bdn.value.money.money);

//  printf("size: %d, time1: %d, time2: %d\n", ret, ret1, ret2);
  //  list.PrintList();
  
  /*
  LogDirectly *gLogDirectly = new LogDirectly();
  ThreadInfo *gThreadInfo = new ThreadInfo();
  SignalHandle *gSignalHandle = new SignalHandle();
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  gLogDirectly->SetLogFileParameter();

  ClassDefine *gClassDefine = new ClassDefine();


  delete gSignalHandle;
  delete gThreadInfo;
  delete gLogDirectly;
  delete gClassDefine;
  delete gConfigureFile;
  */



  return 0;
}


