grammar ConfigureFile;

/*
// this is sample for esc char
@members {
StringBuilder buf = new StringBuilder(); // can't make locals in lexer rules
}
STR :   '"'
        (   '\\'
            (   'r'     {buf.append('\r');}
            |   'n'     {buf.append('\n');}
            |   't'     {buf.append('\t');}
            |   '\\'    {buf.append('\\');}
            |   '"'     {buf.append('"');}
            )
        |   ~('\\'|'"') {buf.append((char)_input.LA(-1));}
        )*
        '"'
        {setText(buf.toString()); buf.setLength(0); System.out.println(getText());}
    ;
*/

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
    | '\\X' HEXDIGIT HEXDIGIT
    | '\\u' HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT
    | '\\U' HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT
    ;

KEYWORD
    : [a-zA-Z_][a-zA-Z0-9_]*;
    
INT
    : DECINT
    | HEXINT;
fragment DECINT 
    : ('-')? DECDIGIT+;
fragment HEXINT
    : '0x' HEXDIGIT+;
fragment DECDIGIT
    : [0-9];
fragment HEXDIGIT
    : [0-9a-fA-F];
    
STRING    
    : '"' (~["\\] | ESCCHAR )*? '"'
    | '\'' (~['\\] | ESCCHAR )*? '\'';
    

IPADDRESS
    : INT '.' INT '.' INT '.' INT ':' INT;
    
COMMENT   
    : '//' .*? '\n' -> skip;
MULTICOMMENT
    : '/*' .*? '*/' -> skip;
SAPCE     
    : [ \t\r\n]+ -> skip;
SEGMENTNOTE
    : '[' KEYWORD ']' -> skip;

allConfigFile 
    : oneConfigLine*;
oneConfigLine   
    : KEYWORD '=' INT ';'                           # AssignInt
    | KEYWORD '=' STRING ';'                     # AssignString
    | KEYWORD '=' IPADDRESS ';'               # AssignIpAddress
    ;
          

