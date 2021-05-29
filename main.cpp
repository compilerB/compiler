#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
FILE *fp_in, *fp_out;

// char UNKNOWN[] = "else case";
char End[] = {13,10};
char Int[] = "|0|1|2|3|4|5|6|7|8|9|";
char Var[] = "|A|a|B|b|C|c|D|d|E|e|F|f|G|g|H|h|I|i|J|j|K|k|L|l|M|m|N|n|O|o|P|p|Q|q|R|r|S|s|T|t|U|u|V|v|W|w|X|x|Y|y|Z|z|";
char Addsub[] = "|+|-|";
char Muldiv[] = "|*|/|";
char Assign[] = "=";
char Lparen[] = "(";
char Rparen[] = ")";
char Space[] = " ";

typedef struct node
{
char ch;
struct node *next;
struct node *prev;
} node;

typedef struct Node
{
char data[20];
Token token;
struct Node *next;
struct Node *prev;
} Node;

void insert(node *current, char ch) //加入字元
{

while(current->next != NULL)
{
    current = current->next;
}

current->next = (node *)malloc(sizeof(node));
(current->next)->prev = current;
current = current->next;
current->ch = ch;
current->next = NULL;
}

void insert_N(Node *current, char ch[], Token token) //加入字元
{

while(current->next != NULL)
{
    current = current->next;
}

current->next = (Node *)malloc(sizeof(Node));
(current->next)->prev = current;
current = current->next;
strcpy(current->data,ch);
current->token = token;
current->next = NULL;
}

void print(node *current) //將所有linked list 列印出來，用於檢查
{
while(current != NULL)
{
printf("c",current->ch);
current = current->next;
}
}

void print_N(Node *current) //將所有linked list 列印出來，用於檢查
{
while(current != NULL)
{
if(current->token == 1)
printf("String = %s , Token = %d\n",current->data,current->token);
else
printf("String = %s , Token = %d\n",current->data,current->token);
current = current->next;
}
}

Token getToken(char c)//取得Token
{
if(strMember(c, Int))
return INT;

else if(strMember(c, Var))
    return VAR;

else if(strMember(c, Addsub))
    return ADDSUB;

else if(strMember(c, Muldiv))
    return MULDIV;

else if(strMember(c, Assign))
    return ASSIGN;

else if(strMember(c, Lparen))
    return LPAREN;

else if(strMember(c, Rparen))
    return RPAREN;

else if(strMember(c, Space))
    return SPACE;

else if(strMember(c, End))
    return END;
    
else
    return UNKNOWN;
}

void lexical(node *current)
{
Token PreToken=NUL;
Token CurToken=NUL;
char tempstr[20]="";
char zerostr[20]="";
char cur_char[1];

Node *head_N = (Node *)malloc(sizeof(Node));
head_N->next = NULL;
head_N->prev = NULL;

while (current != NULL)
{
    cur_char[0]=current->ch;
    CurToken=getToken(cur_char[0]);
    if(PreToken==NUL)
    {
        strcat(tempstr,cur_char);
        PreToken = CurToken;
        CurToken = NUL;
    }
    else //P.T.!=NULL
    {
        if(PreToken == CurToken)
        {
            strcat(tempstr,cur_char);
        }
        else if(PreToken == 3 && CurToken == 2)
        {
            CurToken = PreToken;
            strcat(tempstr,cur_char);
        }
        else  //P.T.!=N.T.
        {

            insert_N(head_N,tempstr,PreToken);

            strcpy(tempstr,zerostr);

            strcat(tempstr,cur_char);

        }
        PreToken=CurToken;
        CurToken=NUL;

    }
    current = current->next;
}

if(PreToken == CurToken)
{
    strcat(tempstr,cur_char);
}
else //P.T.!=N.T.
{

    insert_N(head_N,tempstr,PreToken);

    strcpy(tempstr,zerostr);

    strcat(tempstr,cur_char);

}
PreToken=CurToken;
CurToken=NUL;

printf("Print Node\n");
print_N(head_N->next);
}

int main(int argc, char *argv[])
{

fp_in = fopen(argv[1], "rb");
fp_out = fopen(argv[2], "wb");

if(fp_in == NULL)
{
    printf("Open file error.\n");
    return 0;
}
char ch;
node *head = (node *)malloc(sizeof(node));
head->next = NULL;
head->prev = NULL;

while((ch = getc(fp_in)) != EOF)
{
// if(ch != '\n') //決定是否要存換行
insert(head,ch);
}

// print(head->next);
lexical(head->next);

fclose(fp_in);
fclose(fp_out);
return 0;
}
