#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <ctype.h>
#include "lex.h"
FILE *fp_in, *fp_out;

/*** 0605ver  ***/

char End[] = {13,10};
char Int[] = "|0|1|2|3|4|5|6|7|8|9|";
char Var[] = "|A|a|B|b|C|c|D|d|E|e|F|f|G|g|H|h|I|i|J|j|K|k|L|l|M|m|N|n|O|o|P|p|Q|q|R|r|S|s|T|t|U|u|V|v|W|w|X|x|Y|y|Z|z|";
char Addsub[] = "|+|-|";
char Muldiv[] = "|*|/|";
char Assign[] = "=";
char Lparen[] = "(";
char Rparen[] = ")";
char Space[] = " ";

int parenCount=0;


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

void listdivide(Node *head_parser)
{

    Node *process;
    Node *temp;

    process = NULL;
    temp = NULL;

    Node *firstn_parser;
    firstn_parser = NULL;
    Node *h_parser = (Node *)malloc(sizeof(Node));
    h_parser->next = NULL;
    h_parser->prev = NULL;

    if(head_parser == NULL)
    {
        printf("Warning: There is nothing!!");
    }

    process = head_parser;

    firstn_parser = h_parser;

    while(process != NULL)
    {
        while(process->data != "\n")
        {
            if(process->token == 10)
            {
                process = process->next;
            }
            else
            {
                h_parser->next = (Node *)malloc(sizeof(Node));
                h_parser = h_parser->next;
                strcpy(h_parser->data, process->data);
                h_parser->token = process->token;
                h_parser->next = NULL;
                process = process->next;
                printf("data:%s\n", h_parser->data);
                printf("token:%d\n", h_parser->token);
            }
        }
        if(process->token == END)
        {
            h_parser->next = (Node *)malloc(sizeof(Node));
            h_parser = h_parser->next;
            strcpy(h_parser->data, process->data);
            h_parser->token = process->token;
            h_parser->next = NULL;
            process = process->next;
            printf("data:%s\n", h_parser->data);
            printf("token:%d\n", h_parser->token);
        }
        //**********************parse(firstn_parser->next);*********************
        h_parser = firstn_parser->next;
        while(h_parser->next != NULL)
        {
            temp = h_parser->next;
            free(h_parser);
            h_parser = temp;
            temp = NULL;
        }
        free(h_parser);
        h_parser = firstn_parser;
    }
    head_parser = NULL;
    process = NULL;
}

void preParsing(Node *current);

void insert(node *current, char ch)
{
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (node *)malloc(sizeof(node));
    (current->next)->prev = current;
    current = current->next;
    current->ch = ch;
    current->next = NULL;
}

Node *insert_N(Node *current, char ch[], Token token)
{
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (Node *)malloc(sizeof(Node));
    (current->next)->prev = current;
    current = current->next;
    strcpy(current->data,ch);
    current->token = token;
    current->next = NULL;
    return current;
}


void print(node *current)
{
    while (current != NULL)
    {
        printf("c",current->ch);
        current = current->next;
    }
}

void print_N(Node *current)
{
    while (current != NULL)
    {
        if (current->token == 1)
        {
            printf("String = %s , Token = %d\n",current->data,current->token);
        }
        else
        {
            printf("String = %s , Token = %d\n",current->data,current->token);
        }
        current = current->next;
    }
}

Token getToken(char c)
{
    if (strMember(c, Int))
        return INT;

    else if (strMember(c, Var))
        return VAR;

    else if (strMember(c, Addsub))
        return ADDSUB;

    else if (strMember(c, Muldiv))
        return MULDIV;

    else if (strMember(c, Assign))
        return ASSIGN;

    else if (strMember(c, Lparen))
        return LPAREN;

    else if (strMember(c, Rparen))
        return RPAREN;

    else if (strMember(c, Space))
        return SPACE;

    else if (strMember(c, End))
        return END;

    else
        return UNKNOWN;

}
void printError(int n)
{
    switch(n)
    {
    case 0:
        printf("Can't start with a number\n");
        break;
    case 1:
        printf("Can't start with an operator\n");
        break;
    case 2:
        printf("Can't start with an assign\n");
        break;
    case 3:
        printf("Two Consecutive Operator Error\n");
        break;
    case 4:
        printf("Two Assign In a Row\n");
        break;
    case 5:
        printf("Unknown Input Error\n");
        break;
    case 6:
        printf("Operator End Error\n");
        break;
    case 7:
        printf("Assign End Error\n");
        break;
    case 8:
        printf("Unpaired Parentheses Error\n");
        break;
    case 9:
        printf("Two Consecutive Term Error\n");
        break;
    case 10:
        printf("Hidden Operator Error\n");
        break;
    case 11:
        printf("Left Parentheses Operator Error\n");
        break;
    case 12:
        printf("Assign Operator Error\n");
        break;
    case 13:
        printf("Left Parentheses Assign Error\n");
        break;
    case 14:
        printf("Operator Assign Error\n");
        break;
    case 15:
        printf("Extra Right Parentheses\n");
        break;
    case 16:
        printf("Operator Right Parentheses Error\n");
        break;
    case 17:
        printf("Assign Right Parentheses Error\n");
        break;
    case 18:
        printf("Nothing in Parentheses Error\n");
        break;
    }
}

void lexer(node *current,Node *head_N)
{
    Token preToken=NUL;
    Token curToken=NUL;
    Node *temp;
    char tempStr[20]="";
    char zeroStr[20]="";
    char curChar[1];

    while (current != NULL)
    {
        curChar[0]=current->ch;
        curToken=getToken(curChar[0]);

        if (preToken==NUL)
        {
            if (curToken == 2)
            {
                printError(0);
                printf("%s\n",curChar);
                exit(0);
            }
            else if (curToken == 4||curToken==5)
            {
                printError(1);
                printf("%s\n",curChar);
                exit(0);
            }
            else if (curToken == 6)
            {
                printError(2);
                printf("%s\n",curChar);
                exit(0);
            }
            strcat(tempStr,curChar);
            preToken = curToken;
            curToken = NUL;
        }
        else
        {
            if (preToken == curToken)
            {
                if (curToken == 4||curToken==5)
                {
                    printError(3);
                    printf("%s %s\n",tempStr,curChar);
                    exit(0);
                }
                else if (curToken==6)
                {
                    printError(4);
                    printf("%s %s\n",tempStr,curChar);
                    exit(0);
                }
                else if (curToken==7||curToken==8)
                {
                    temp = insert_N(head_N,tempStr,preToken);
                    preParsing(temp);
                    strcpy(tempStr,zeroStr);
                    strcat(tempStr,curChar);
                }
                else
                {
                    strcat(tempStr,curChar);
                }
            }
            else if (preToken == 3 && curToken == 2)
            {
                curToken = preToken;
                strcat(tempStr,curChar);
            }
            else
            {
                if (preToken!=10)
                {
                    temp = insert_N(head_N,tempStr,preToken);
                    preParsing(temp);
                }
                strcpy(tempStr,zeroStr);
                strcat(tempStr,curChar);
            }
            preToken=curToken;
            curToken=NUL;
        }
        current = current->next;
    }
    if (preToken == curToken)
    {
        if (curToken == 4||curToken==5)
        {
            printError(3);
            printf("%s %s\n",tempStr,curChar);
            exit(0);
        }
        else if (curToken==6)
        {
            printError(4);
            printf("%s %s\n",tempStr,curChar);
            exit(0);
        }
        else if (curToken==7||curToken==8)
        {
            temp = insert_N(head_N,tempStr,preToken);
            preParsing(temp);
            strcpy(tempStr,zeroStr);
            strcat(tempStr,curChar);
        }
        else
        {
            strcat(tempStr,curChar);
        }
    }
    else if (preToken == 3 && curToken == 2)
    {
        curToken = preToken;
        strcat(tempStr,curChar);
    }
    else
    {
        if (preToken!=10)
        {
            temp = insert_N(head_N,tempStr,preToken);
            preParsing(temp);
        }
        strcpy(tempStr,zeroStr);
        strcat(tempStr,curChar);
    }
    preToken=curToken;
    curToken=NUL;
}

void preParsing(Node *current)
{
    bool assignFlag=false;
    Node *temp;
    temp=current->prev;

    if (temp->token==10)
    {
        temp=temp->prev;
    }
    switch(current->token)
    {
    case 0: //UNKNOWN

        printError(5);
        printf("%s\n",current->data);
        exit(0);
        break;

    case 1: //END

        if (temp->token ==4||temp->token ==5)
        {
            printError(6);
            printf("%s\n",temp->data);
            exit(0);
        }
        else if (temp->token ==6 )
        {
            printError(7);
            printf("%s\n",temp->data);
            exit(0);
        }
        if (parenCount!=0)
        {
            printError(8);
            exit(0);
        }
        assignFlag=false;
        parenCount = 0;
        break;

    case 2: //INT

        if (temp->token==2||temp->token ==3)
        {
            printError(9);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==8)
        {
            printError(10);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==1)
        {
            printError(0);
            printf("%s\n",current->data);
            exit(0);
        }
        break;

    case 3: //VAR

        if (temp->token==2||temp->token ==3)
        {
            printError(9);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==8)
        {
            printError(10);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        break;

    case 4: //ADDSUB

        if (temp->token== 7)
        {
            printError(11);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token == 5)
        {
            printError(3);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==1)
        {
            printError(1);
            printf("%s\n",current->data);
            exit(0);
        }
        else if (temp->token == 6)
        {
            printError(12);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        break;

    case 5: //MULDIV

        if (temp->token==7)
        {
            printError(11);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==4)
        {
            printError(3);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==1)
        {
            printError(1);
            printf("%s\n",current->data);
            exit(0);
        }
        else if (temp->token == 6)
        {
            printError(12);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        break;

    case 6: //ASSIGN

        if (temp->token==7)
        {
            printError(13);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==4||temp->token ==5)
        {
            printError(14);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==1)
        {
            printError(2);
            printf("%s\n",current->data);
            exit(0);
        }
        if (assignFlag)
        {
            printError(4);
            exit(0);
        }
        assignFlag=true;
        break;

    case 7: //LPAREN

        if (temp->token==2||temp->token ==3)
        {
            printError(10);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        parenCount++;
        break;

    case 8: //RPAREN

        parenCount--;
        if (parenCount<0)
        {
            printError(15);
            exit(0);
        }
        if (temp->token==4||temp->token ==5)
        {
            printError(16);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==6)
        {
            printError(17);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        else if (temp->token==7)
        {
            printError(18);
            printf("%s %s\n",temp->data,current->data);
            exit(0);
        }
        break;

    case 9: //NUL
        break;
    case 10: //SPACE
        break;
    }

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

    Node *head_N = (Node *)malloc(sizeof(Node));
    head_N->next = NULL;
    head_N->prev = NULL;
    if((ch = getc(fp_in)) == EOF)
    {
        printf("Warning: Nothing in input file!!");
        exit(0);
    }
    else
    {
        insert(head,ch);
    }
    while((ch = getc(fp_in)) != EOF)
    {
        insert(head,ch);
    }
    insert(head,'\n');
    lexer(head->next,head_N);

    printf("\n**********\n");
    print_N(head_N->next);

    listdivide(head_N->next);
    
    free(head);
    free(head_N);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
