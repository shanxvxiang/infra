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
    | '\\X' HEXDIGIT HEXDIGIT HEXDIGIT HEXDIGIT
    | '\\u' HEXDIGIT HEXDIGIT
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
    : '0' ('x'|'X') HEXDIGIT+;
fragment DECDIGIT
    : [0-9];
fragment HEXDIGIT
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

allConfigFile 
    : oneConfigLine*;
oneConfigLine   
    : KEYWORD '=' INT (',' INT)* ';'                           # AssignInt
    | KEYWORD '=' STRING (',' STRING)* ';'                     # AssignString
    | KEYWORD '=' IPADDRESS (',' IPADDRESS)* ';'               # AssignIpAddress
    ;
          

