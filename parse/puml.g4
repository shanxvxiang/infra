grammar puml;

ATTRIBUTE
    : [a-zA-Z_][a-zA-Z0-9_]*;
TYPE
    : 'String' | 'Int' | 'Percent' | 'Money' | 'Hash' ;
CLASSNAME
    : [a-zA-Z_][a-zA-Z0-9_]*;
    
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
    'class' CLASSNAME '{'
    (attributeLine)*
    '}'                                 # DefineClass
    ;

attributeLine 
    : TYPE ATTRIBUTE                    # DefineTypeAttribute
    | ATTRIBUTE ':' TYPE                # DefineAttributeType
    ;

relationLine 
    : CLASSNAME '--|>' CLASSNAME        # Generalization
    | CLASSNAME '--o'  CLASSNAME        # Aggregation
    ;


