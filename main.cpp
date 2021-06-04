#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include<cstring>
#include<ctype.h>
#define strMember(ch, set) (strchr(set, ch) != NULL)
FILE *fp_in, *fp_out;

/*** 0601版 錯誤則跳出  ***/

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

int parencount=0;


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

void parsing(Node *current);

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

Node *insert_N(Node *current, char ch[], Token token)  //加入字元
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
    return current;
}


void print(node *current)   //將所有linked list 列印出來，用於檢查
{
    while(current != NULL)
    {
        printf("c",current->ch);
        current = current->next;
    }
}

void print_N(Node *current)   //將所有linked list 列印出來，用於檢查
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

void delete_SPACE(Node *current)
{
    while(current->next!=NULL)
    {
        if(current->token==10)
        {
            if(current->prev==NULL)
            {
                (current->next)->prev=current->prev;
                free(current);
            }
            else
            {
                (current->prev)->next=current->next;
                (current->next)->prev=current->prev;
                free(current);
            }
        }
        current=current->next;
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

void lexer(node *current,Node *head_N)
{
    Token PreToken=NUL;   //前一個字元的Token
    Token CurToken=NUL;   //當前字元的Token
    Node *temp;           //暫存現在加入的點
    char tempstr[20]="";  //暫存字串的陣列
    char zerostr[20]="";  //清空暫存字串用的陣列
    char cur_char[1];     //暫存當前字元的陣列

    while (current != NULL)  //儲存讀入字元的Linked List節點不為空
    {
        cur_char[0]=current->ch;          //從儲存讀入字元的Linked List讀字元出來
        CurToken=getToken(cur_char[0]);   //取得當前字元的Token

        if(PreToken==NUL)        //前一個Token是空的代表是第一個
        {
            //第一個不能是(數字、+-*/、=)
            if(CurToken == 2)
            {
                printf("Can't start with a number\n");
                printf("%s\n",cur_char);
                exit(0);
//                printf("EXIT\n");
            }
            else if(CurToken == 4||CurToken==5)
            {
                printf("Can't start with an operator\n");
                printf("%s\n",cur_char);
                exit(0);
//                printf("EXIT\n");
            }
            else if(CurToken == 6)
            {
                printf("Can't start with an assign\n");
                printf("%s\n",cur_char);
                exit(0);
//                printf("EXIT\n");
            }
            strcat(tempstr,cur_char);   //將這個字元先放進Temp裡面
            PreToken = CurToken;        //當前字元Token存入前一個Token
            CurToken = NUL;             //當前字元Token清空
        }
        else //P.T.!=NULL
        {
            if(PreToken == CurToken)
            {
                if(CurToken == 4||CurToken==5)  //eg. ++ -- +- -+ ** // */ /*
                {
                    printf("Two Consecutive Operator Error\n");
                    printf("%s %s\n",tempstr,cur_char);
//                    temp = insert_N(head_N,tempstr,PreToken);
//                    parsing(temp);
//                    strcpy(tempstr,zerostr);
//                    strcat(tempstr,cur_char);
                    exit(0);
//                    printf("EXIT\n");
                }
                else if(CurToken==6)   // eg. ==
                {
                    printf("Two Assign In a Row\n");
                    printf("%s %s\n",tempstr,cur_char);
                    exit(0);
//                    printf("EXIT\n");
                }
                else if(CurToken==7||CurToken==8)  //左括、右括分開儲存
                {
                    temp = insert_N(head_N,tempstr,PreToken);
                    parsing(temp);
                    strcpy(tempstr,zerostr);
                    strcat(tempstr,cur_char);
                }
                else
                {
                    strcat(tempstr,cur_char);
                }
            }
            else if(PreToken == 3 && CurToken == 2)  //變數以英文開頭，後面可以接數字
            {
                CurToken = PreToken;
                strcat(tempstr,cur_char);
            }
            else  //P.T.!=C.T.
            {
                temp = insert_N(head_N,tempstr,PreToken);
                parsing(temp);
                strcpy(tempstr,zerostr);
                strcat(tempstr,cur_char);
            }
            PreToken=CurToken;
            CurToken=NUL;
        }
        current = current->next;
    }
    //需要多跑一次，處理最後一個字元
    if(PreToken == CurToken)
    {
        if(CurToken == 4||CurToken==5)  //eg. ++ -- +- -+ ** // */ /*
        {
            printf("Two Consecutive Operator Error\n");
            printf("%s %s\n",tempstr,cur_char);
            exit(0);
//            printf("EXIT\n");
        }
        else if(CurToken==6)
        {
            printf("Two Assign In a Row\n"); //eg. ==
            printf("%s %s\n",tempstr,cur_char);
            exit(0);
//            printf("EXIT\n");
        }
        else if(CurToken==7||CurToken==8) //左括、右括分開儲存
        {
            temp = insert_N(head_N,tempstr,PreToken);
            parsing(temp);
            strcpy(tempstr,zerostr);
            strcat(tempstr,cur_char);
        }
        else
        {
            strcat(tempstr,cur_char);
        }
    }
    else if(PreToken == 3 && CurToken == 2) //變數以英文開頭，後面可以接數字
    {
        CurToken = PreToken;
        strcat(tempstr,cur_char);
    }
    else  //P.T.!=C.T.
    {
        temp = insert_N(head_N,tempstr,PreToken);
        parsing(temp);
        strcpy(tempstr,zerostr);
        strcat(tempstr,cur_char);
    }
    PreToken=CurToken;
    CurToken=NUL;
}

void parsing(Node *current)
{
    bool assigflag=false;   //assign flag，每一行只能有一個等於
    Node *temp;
    temp=current->prev;     //看前一個字串的Token
    if(temp->token==10)     //遇到空白再往前看
    {
        temp=temp->prev;
    }
    switch(current->token)  //根據當前存入之字串Token，判斷是否合法
    {
    case 0: //UNKNOWN

        printf("Unknown Input Error\n");
        printf("%s\n",current->data);
        exit(0);
//        printf("EXIT\n");
        break;

    case 1: //END

        if (temp->token ==4||temp->token ==5) // eg. *\n
        {

            printf("Operator End Error\n");
            printf("%s\n",temp->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if (temp->token ==6 ) // eg. =\n
        {

            printf("Assign End Error\n");
            printf("%s\n",temp->data);
            exit(0);
//            printf("EXIT\n");

        }
        if(parencount!=0)  //括號不成對
        {
            printf("Unpaired Parentheses Error\n");
            exit(0);
//            printf("EXIT\n");
        }
        assigflag=false;
        parencount = 0;
        break;

    case 2: //INT

        if(temp->token==2||temp->token ==3)  //eg. a1 4 || 15 3
        {
            printf("Two Consecutive Term Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==8)  //eg. (15)2
        {
            printf("Hidden Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==1)  //每行開頭不能是數字
        {
            printf("Can't start with a number\n");
            printf("%s\n",current->data);
                exit(0);
//            printf("EXIT\n");
        }
        break;

    case 3: //VAR

        if(temp->token==2||temp->token ==3) //eg. 4 a1  || a1 a3
        {
            printf("Two Consecutive Term Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==8) //eg. (15)a2
        {
            printf("Hidden Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        break;

    case 4: //ADDSUB

        if(temp->token== 7)  //eg. (+
        {
            printf("Left Parentheses Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token == 5) //eg. *+
        {
            printf("Two Consecutive Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==1)   //每行開頭不能是 +-
        {
            printf("Can't start with an operator\n");
            printf("%s\n",current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token == 6) //eg. =+
        {
            printf("Assign Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        break;

    case 5: //MULDIV

        if(temp->token==7)       //eg. (*
        {
            printf("Left Parentheses Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==4)  //eg. -/
        {
            printf("Two Consecutive Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==1)  //每行開頭不能是 */
        {
            printf("Can't start with an operator\n");
            printf("%s\n",current->data);
                exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token == 6) //eg. =*
        {
            printf("Assign Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        break;

    case 6: //ASSIGN

        if(temp->token==7)  //eg. (=
        {
            printf("Left Parentheses Assign Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==4||temp->token ==5)  //eg. -=
        {
            printf("Operator Assign Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==1) //每行開頭不能是 =
        {
            printf("Can't start with an assign\n");
            printf("%s\n",current->data);
            exit(0);
//            printf("EXIT\n");
        }
        if(assigflag)  //Only one assign in a row
        {
            printf("Two Assigns In a Row\n");
            exit(0);
//            printf("EXIT\n");
        }
        assigflag=true;
        break;

    case 7: //LPAREN

        if(temp->token==2||temp->token ==3)       // eg. 3(6) || a2(5)
        {
            printf("Hidden Operator Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        parencount++;
        break;

    case 8: //RPAREN

        parencount--;
        if(parencount<0) //判斷括號不成對
        {
            printf("Extra Right Parentheses\n");
            exit(0);
//            printf("EXIT\n");
        }
        if(temp->token==4||temp->token ==5)  //eg. +)
        {
            printf("Operator Right Parentheses Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==6)  //eg. =)
        {
            printf("Assign Right Parentheses Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        else if(temp->token==7)  //eg. ()
        {
            printf("Nothing in Parentheses Error\n");
            printf("%s %s\n",temp->data,current->data);
            exit(0);
//            printf("EXIT\n");
        }
        break;

    case 9: //NUL
//        printf("Case NUL\n");
        break;
    case 10: //SPACE
//            printf("Case SPACE\n");
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

    while((ch = getc(fp_in)) != EOF)
    {
//      if(ch != '\n')      //決定是否要存換行
        insert(head,ch);
    }
    insert(head,'\n');

    // print(head->next);
    lexer(head->next,head_N);

    //delete_SPACE(head_N->next);
    printf("\n**********\n");
    print_N(head_N->next);
    
    listdivide(head_N->next);

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
