整數四則運算 syntax
**************
包含 
1. +, -, *, / 
2. 變數、整數  
*****************************
":="此符號為"定義為"  
"ADDSUB"，為"+","-"  
"MULDIV"，為"*","/"  
END := 一個句子的結束  
INT := 整數  
VAR := 變數  
ASSIGN := "="  
LPAREN := "("  
RPAREN := ")"  
UNKNOWN := else case  
SPACE := 空白  
NUL := 空值  
********
*syntax  
stat -> END | exp END  
exp -> VAR ASSIGN term  
term -> op ADDSUB term | factor  
factor -> op MULDIV term | base  
base -> LPAREN term RPAREN | op  
op -> VAR | INT  
************************************
First Set   
First(stat) = {END, First(exp)} = {END, VAR}  
First(exp) = {VAR}  
First(term) = {First(op), First(factor)} = {LPAREN, VAR, INT}  
First(factor) = {First(op), First(base)} = {LPAREN, VAR, INT}  
First(base) = {LPAREN, First(op)} = {LPAREN, VAR, INT}  
First(op) = {VAR, INT}  
**************************************
Follow Set (未使用)  
Follow(stat) = {$}   
Follow(exp) = {END}  
Follow(term) = Follow(factor) U {END, RPAREN}  
Follow(factor) = Follow(term)  
Follow(base) = Follow(factor)  
Follow(op) = {ADDSUB, MULDIV} U Follow(base) = {ADDSUB, MULDIV} U Follow(factor)  
**************************************
![image](https://user-images.githubusercontent.com/43271915/120911157-5efebe00-c6b7-11eb-8f6d-c13af357abdf.png)  
****************************************
