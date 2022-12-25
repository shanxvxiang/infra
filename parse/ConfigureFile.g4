grammar ConfigureFile;

fragment ESCCHAR    
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
    | '\\X' HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT
    | '\\u' HEXDIGIT HEXDIGIT
    | '\\U' HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT
    ;

KEYWORD
    : [a-zA-Z_][a-zA-Z0-9_]*;
    
INT 
    : [0-9]+;
HEXINT
    : '0' ('x'|'X') HEXDIGIT+;

HEXDIGIT
    : [0-9a-fA-F];
STRING    
    : '"' (~["\\] | ESCCHAR )*? '"'
    | '\'' (~['\\] | ESCCHAR )*? '\'';
    
IPADDRESS
    : INT '.' INT '.' INT '.' INT (':' INT)?;
    
SAPCE     
    : [ \t\r\n]+ -> skip;
COMMENT   
    : '//' .*? '\n' -> skip;
MULCOMMENT
    : '/*' .*? '*/' -> skip;

allConfig 
    : oneLine*;
oneLine   
    : KEYWORD '=' INT (',' INT)* ';'                       # AssignInt
    | KEYWORD '=' STRING ';'                             # AssignString
    ;
          

