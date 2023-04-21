#ifndef __RAYMON_SHAN_VOUCHER_HPP
#define __RAYMON_SHAN_VOUCHER_HPP

#include "infraall.hpp"
//#include "vectormap.hpp"
//#include "gmencryption.hpp"

typedef __int128_t int128;

class SmallMoney {

public:
  volatile long money;
public:
  SmallMoney() { money = 0; };
  SmallMoney(long m) { money = m; };

  void operator = (long m) {
    money = m;
  };
  long operator += (SmallMoney m) {
    return __sync_add_and_fetch(&money, m.money);
  };
  long operator -= (SmallMoney m) {
    return __sync_sub_and_fetch(&money, m.money);    
  };  

  bool operator == (SmallMoney m) {
    return (money == m.money);
  };
  bool operator != (SmallMoney m) {
    return (money != m.money);
  };
  bool operator < (SmallMoney m) {
    return (money < m.money);
  };
  bool operator <= (SmallMoney m) {
    return (money <= m.money);
  };
  bool operator > (SmallMoney m) {
    return (money > m.money);
  };
  bool operator >= (SmallMoney m) {
    return (money >= m.money);
  };

};

class Voucher;
class VoucherDetail;
class Balance;
class BalanceDetail;


typedef class LinkedNode<None, Voucher, NoneHash, None> VoucherNode;
typedef class NodeList<None, Voucher, NoneHash, None> VoucherList;
typedef class LinkedNode<None, Balance, NoneHash, None> BalanceNode;
typedef class NodeList<None, Balance, NoneHash, None> BalanceList;

typedef class LinkedNode<None, VoucherDetail, NoneHash, None> VoucherDetailNode;
typedef class NodeList<None, VoucherDetail, NoneHash, None> VoucherDetailList;
typedef class LinkedNode<String, BalanceDetail, SM3Hash, Hash256> BalanceDetailNode;
typedef class NodeList<String, BalanceDetail, SM3Hash, Hash256> BalanceDetailList;

class VoucherDetail {
public:
  BalanceDetailNode *balanceNode;   // sum of VoucherDetail is BalancdDetail
  VoucherNode *voucher;
  SmallMoney money;
};

class Voucher {
  // DATE
  // PEOPLE
  // SIGN
  int detailNumber;
  VoucherDetailNode voucherNode[];
};

None Not_None;
VoucherDetail Not_Voucher; 

class BalanceDetail {
public:
  Balance *balance;
  SmallMoney money;
  VoucherDetailList *voucherDetailList;
  // BASE_INFO [number]
public:
  BalanceDetail() {
    voucherDetailList = new VoucherDetailList();
  }
  
};

class Balance {
  BalanceDetailList balanceDetailList(None, BalanceDetail*);
  
};

bool InsertVoucherDetail(BalanceDetailNode *bn, VoucherDetailNode *vn) {
  vn->value.balanceNode = bn;
  bn->value.money += vn->value.money;
  bn->value.voucherDetailList->InsertAhead(vn);
  return true;
};


#endif  // __RAYMON_SHAN_VOUCHER_HPP
