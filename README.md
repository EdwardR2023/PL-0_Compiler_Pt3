# PL-0_Compiler_Pt3
Merging of PL-0_Compiler Pt1 and Pt2





Appendix B:
EBNF of tiny PL/0:
program ::= block "." .
block ::= const-declaration var-declaration statement.
constdeclaration ::= [ “const” ident "=" number {"," ident "=" number} “;"].
var-declaration ::= [ "var" ident {"," ident} “;"].
statement ::= [ ident ":=" expression
| "begin" statement { ";" statement } "end"
| "if" condition "then" statement "fi"
| "while" condition "do" statement
| "read" ident
| "write" expression
| empty ] .
condition ::= "odd" expression
| expression rel-op expression.
rel-op ::= "="|“<>"|"<"|"<="|">"|">=“.
expression ::= term { ("+"|"-") term}.
term ::= factor {("*"|"/") factor}.
factor ::= ident | number | "(" expression ")“.
number ::= digit {digit}.
ident ::= letter {letter | digit}.
digit ;;= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9“.
letter ::= "a" | "b" | ... | "y" | "z" | "A" | "B" | ... |"Y" | "Z".
Based on Wirth’s definition for EBNF we have the following rule:
[ ] means an optional item.

Appendix C:
Error messages for the tiny PL/0 Parser:
 program must end with period
 const, var, and read keywords must be followed by identifier
 symbol name has already been declared
 constants must be assigned with =
 constants must be assigned an integer value
 constant and variable declarations must be followed by a semicolon
 undeclared identifier
 only variable values may be altered
 assignment statements must use :=
 begin must be followed by end
 if must be followed by then
 while must be followed by do
 condition must contain comparison operator
 right parenthesis must follow left parenthesis
 arithmetic equations must contain operands, parentheses, numbers, or symbols
{ } means repeat 0 or more times.
Terminal symbols are enclosed in quote marks.
A period is used to indicate the end of the definition of a syntactic class.
