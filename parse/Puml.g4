grammar Puml;

// https://github.com/p-indriunas/antlr4-puml/blob/510514bba33bb1f4f77cacc075f917b022d17fd5/src/main/antlr4/puml.g4
// found another version puml.g4

TYPE
    : 'String' | 'Int' | 'Percent' | 'Money' | 'Hash' ;
IDENTIFIER
    : [a-zA-Z][a-zA-Z0-9_]*;
   
COMMENT   
    : '\'' .*? '\n' -> skip;
MULTICOMMENT
    : '/\'' .*? '\'/' -> skip;
SAPCE     
    : [ \t\r\n]+ -> skip;

allPUMLFile :
    '@startuml'
    (classLine | relationLine)* 
    '@enduml';

classLine :
    'class' IDENTIFIER '{'
    (attributeLine)*
    '}'                                 # DefineClass
    ;

attributeLine 
    : TYPE IDENTIFIER                    # DefineAttribute
    | IDENTIFIER ':' TYPE                # DefineAttribute
    ;

relationLine 
    : IDENTIFIER '--|>' IDENTIFIER        # Generalization
    | IDENTIFIER '--o'  IDENTIFIER        # Aggregation
    ;


