grammar Expr;
/*prog:	expr EOF ;
expr:	expr ('*'|'/') expr
    |	expr ('+'|'-') expr
    |	INT
    |	'(' expr ')'
    ;
NEWLINE : [\r\n]+ -> skip;
INT     : [0-9]+ ;*/

// lexer grammar NClexer;      /*注意词法文件前为lexer grammar*/
ID : [a-zA-Z]+;
INT: [0-9]+;
NEWLINE : '\r'?'\n' ;
WS : [ \t]+ ->skip;
MUL : '*';
DIV : '/';
ADD : '+';
SUB : '-';

/*开启Visitor模式 根据不同 # Label 会自动生成对应的方法*/
prog:   stat+;
stat:   expr NEWLINE                    # printExpr
    |   ID '=' expr NEWLINE             # assign
    |   NEWLINE                         # blank
    ;
expr:   expr op=('*'|'/') expr          # MulDiv           /* 优先匹配乘除法 */
    |   expr op=('+'|'-') expr          # AddSub
    |   INT                             # int
    |   ID                              # id
    |   '(' expr ')'                    # parens
    ;
