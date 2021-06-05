#ifndef __LEX__H
#define __LEX__H
#define MAXLEN 256
typedef enum {
UNKNOWN, END, INT, VAR, ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN, NUL, SPACE
} Token;
#define strMember(ch, set) (strchr(set, ch) != NULL)

#endif 
