#include "include/infraall.hpp"

//typedef class LinkedNode <String, String, SM3Hash, Hash256> StringNode;
//typedef class NodeList<String, String, SM3Hash, Hash256> StringList;
//String K("abc");
//String V("aasdfsdfds242dfadfasdfdsfdsaf");

typedef class LinkedNode<String, String, SM3Hash, Hash256> StringNode;
typedef class NodeList<String, String, SM3Hash, Hash256> StringList;
typedef class HashListMap<String, String, SM3Hash, Hash256> StringHash;

volatile int wwait = 1;
int addsize = 100000;
StringNode *node;
StringList list;
StringHash hash(7);

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

char classdefine[] = "class 行政区划 {\n"
"  unique string 区划名称;\n"
"  unique string 区划代码;\n"
"};\n"
"class 地址 inherit 行政区划 {\n"
"  attribute string 具体地址;\n"
"};";


int main(int, char **) {
  TimeSpend tspend;

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  LogDirectly *gLogDirectly = new LogDirectly();
  ThreadInfo *gThreadInfo = new ThreadInfo();
  SignalHandle *gSignalHandle = new SignalHandle();
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  gLogDirectly->SetLogFileParameter();

//  ClassDefine *gClassDefine = new ClassDefine(classdefine, strlen(classdefine));
  ClassDefine *gClassDefine = new ClassDefine();

  ClassNode *node = NULL;
  do {
    node = ClassDefine::allClassHash.GetNext(node);
    if (node) {
      node->value->Display();
    }
  } while (node);
  

  delete gSignalHandle;
  delete gThreadInfo;
  delete gLogDirectly;
  delete gClassDefine;
  delete gConfigureFile;

  // printf("%ld, %ld, %ld\n", sizeof(ValueType), sizeof(String), sizeof(std::string));
  return 0;
}

int main_hashtest(int, char **) {
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

  StringNode* retnode = NULL;
  do {
    retnode = hash.GetNext(retnode);
    if (retnode) retnode->PrintHash();
    printf("\n");
  } while (retnode != NULL);

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


