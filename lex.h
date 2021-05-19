#ifndef __LEX__H
#define __LEX__H
#define MAXLEN 256
typedef enum {
UNKNOWN, END, INT, VAR, ADDSUB, MULDIV, ASSIGN,LPAREN, RPAREN
} Token;

#endif 
