grammar Puml;
// https://github.com/p-indriunas/antlr4-puml/blob/510514bba33bb1f4f77cacc075f917b022d17fd5/src/main/antlr4/puml.g4
// found another version puml.g4

GBK
    : [\u8140-\uFE4F]; 
TYPE
    : 'String' | 'Int' | 'Percent' | 'Money' | 'Hash' | 'Time' ;
IDENTIFIER
    : ([a-zA-Z_]|GBK)([a-zA-Z0-9_]|GBK)*;
   
COMMENT   
    : '//' .*? '\n' -> skip;
MULTICOMMENT
    : '/*' .*? '*/' -> skip;
SAPCE     
    : [ \t\r\n]+ -> skip;

allPUMLFile 
    : (classLine | relationLine)* ;

classLine 
    :  'class' IDENTIFIER ('base' IDENTIFIER)? '{'
       (attributeLine)*
       '}'                                   # DefineClass
    ;

attributeLine 
    : TYPE IDENTIFIER                     # DefineAttribute
    | IDENTIFIER ':' TYPE                 # DefineAttribute
    ;

relationLine 
    : IDENTIFIER '--|>' IDENTIFIER        # Generalization
    | IDENTIFIER '--o'  IDENTIFIER        # Aggregation
    ;


