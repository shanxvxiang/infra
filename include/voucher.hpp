#ifndef __RAYMON_SHAN_VOUCHER_HPP
#define __RAYMON_SHAN_VOUCHER_HPP

#include "infra.hpp"
#include "vectormap.hpp"
#include "gmencryption.hpp"

typedef __int128_t int128;

class SmallMoney {

private:
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

typedef class LinkedNode<None, VoucherDetail*, NoneHash, None> VoucherDetailNode;
typedef class NodeList<None, VoucherDetail*, NoneHash, None> VoucherDetailList;
typedef class LinkedNode<None, BalanceDetail*, NoneHash, None> BalanceDetailNode;
typedef class NodeList<None, BalanceDetail*, NoneHash, None> BalanceDetailList;


class VoucherDetail {
public:
  BalanceDetail *balanceDetail;
  Voucher *voucher;
  SmallMoney money;
};

class Voucher {
  // DATE
  // PEOPLE
  // SIGN
  int detailNumber;
  VoucherDetail voucherDetail[];
};

None Not_None;
VoucherDetail *Not_Voucher = NULL; 

class BalanceDetail {
  Balance *balance;
  SmallMoney money;
  VoucherDetailList *voucherDetailList;
  // BASE_INFO [number]
public:
  BalanceDetail() {
    voucherDetailList = new VoucherDetailList(Not_None, Not_Voucher);
  }
  bool operator += (VoucherDetail *vd) {
    vd->balanceDetail = this;
    money += vd->money;
    voucherDetailList->InsertAhead(new VoucherDetailNode(Not_None, vd));
    return true;
  }
};

class Balance {
  BalanceDetailList balanceDetailList(None, BalanceDetail*);
  
};

#endif  // __RAYMON_SHAN_VOUCHER_HPP
