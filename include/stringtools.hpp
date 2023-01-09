#ifndef __RAYMON_SHAN_STRING_TOOLS_HPP
#define __RAYMON_SHAN_STRING_TOOLS_HPP

#include "infra.hpp"

char tohex [128] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
  0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 10, 11, 12, 13, 14, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

int ToHex(std::string str) {
  int result = 0;
  const char *now = str.c_str() + 2;            // remove 0x
  while (*now)
    result = result * 16 + tohex[(int)*now++];
  return result;
}

int ToHex(char *str) {
  int result = 0;
  const char *now = str + 2;
  while (*now)
    result = result * 16 + tohex[(int)*now++];
  return result;
}

char ToHex(char a, char b) {
  return (tohex[(int)a] << 4) + tohex[(int)b];
}

int StoI(std::string str) {
  if (str.compare(0, 2, "0x")) return stoi(str);
  else return ToHex(str);
}

int StoI(char *str) {
  if (str[0]!='0' || str[1]!='x') return atoi(str);
  else return ToHex(str);
}

const char* RightOfSlash(const char *str) {
  return strrchr(str,'/')?strrchr(str,'/')+1:str;
}

// the input string following the lexer
/*
HEXDIGIT
    : [0-9a-fA-F];

ESCCHAR    
    : '\\\''
    | '\\"'
    | '\\?'
    | '\\\\'
    | '\\a'
    | '\\b'
    | '\\f'
    | '\\n'
    | '\\r'
    | '\\t'
    | '\\v'
    | '\\x' HEXDIGIT HEXDIGIT
    | '\\X' HEXDIGIT HEXDIGIT
    ;

STRING    
    : '"' (~["\\] | ESCCHAR )*? '"'
    | '\'' (~['\\] | ESCCHAR )*? '\'';
*/
bool RemoveEscapeChar(std::string &str) {
  int slen = str.size();
  char *dnow = (char*)str.c_str();
  char *snow = dnow + 1;
  char *send = dnow + slen - 1;

  while (snow < send) {
    if (*snow != '\\') {
      *dnow++ = *snow++;
    } else {
      snow++;
      switch(*snow) {
      case '\'':
	*dnow++ = '\''; break;
      case '"' :
	*dnow++ = '"';  break;
      case '?' :
	*dnow++ = '?';  break;
      case '\\':
	*dnow++ = '\\'; break;
      case 'a' :
	*dnow++ = '\a'; break;
      case 'b' :
	*dnow++ = '\b'; break;
      case 'f' :
	*dnow++ = '\f'; break;
      case 'n' :
	*dnow++ = '\n'; break;
      case 'r' :
	*dnow++ = '\r'; break;
      case 't' :
	*dnow++ = '\t'; break;
      case 'v' :
	*dnow++ = '\v'; break;
      case 'x' :
      case 'X' :
	*dnow++ = ToHex(*(snow+1), *(snow+2));
	snow += 2; break;
      }
      snow++;
    }
  }
  str.erase(slen - (send - dnow) - 1);
  return true;
}

bool RemoveEscapeChar(char *str) {
  int slen = strlen(str);
  char *dnow = str;
  char *snow = dnow + 1;
  char *send = dnow + slen - 1;

  while (snow < send) {
    if (*snow != '\\') {
      *dnow++ = *snow++;
    } else {
      snow++;
      switch(*snow) {
      case '\'':
	*dnow++ = '\''; break;
      case '"' :
	*dnow++ = '"';  break;
      case '?' :
	*dnow++ = '?';  break;
      case '\\':
	*dnow++ = '\\'; break;
      case 'a' :
	*dnow++ = '\a'; break;
      case 'b' :
	*dnow++ = '\b'; break;
      case 'f' :
	*dnow++ = '\f'; break;
      case 'n' :
	*dnow++ = '\n'; break;
      case 'r' :
	*dnow++ = '\r'; break;
      case 't' :
	*dnow++ = '\t'; break;
      case 'v' :
	*dnow++ = '\v'; break;
      case 'x' :
      case 'X' :
	*dnow++ = ToHex(*(snow+1), *(snow+2));
	snow += 2; break;
      }
      snow++;
    }
  }
  
  *dnow = 0;
  return true;
}

#endif // __RAYMON_SHAN_STRING_TOOLS_HPP
