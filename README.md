整數四則運算 syntax

包含 
1. + - * / = ( )
2. 變數

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

*syntax
 stat := END | exp END
 exp := term exp_tail
 exp_tail := ADDSUB term | ε
 term := factor term_tail
 term_tail := MULDIV factor term_tail | ε
 factor := INT | ADDSUB INT | ADDSUB VAR | VAR ASSIGN exp | VAR | LPAREN exp RPAREN
