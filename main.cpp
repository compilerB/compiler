#include <stdio.h>
#include <stdlib.h>
#include "lex.h" 
FILE *fp_in, *fp_out;

typedef struct node
{
    char ch;
    struct node *next;
    struct node *prev;
} node;

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

void print(node *current)   //將所有linked list 列印出來，用於檢查
{
    while(current != NULL)
    {
        printf("c",current->ch);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
	
	
	fp_in = fopen(argv[1], "rb");
	fp_out = fopen(argv[2], "wb");
	
	if(fp_in == NULL) {
		printf("Open file error.\n");
		return 0;
	}
	char ch;
    	node *head = (node *)malloc(sizeof(node));
    	head->next = NULL;
   	head->prev = NULL;

    	while((ch = getc(fp_in)) != EOF)
    	{
        	if(ch != '\n')      //決定是否要存換行
            		insert(head,ch);
    	}
    	print(head->next);

	fclose(fp_in);
	fclose(fp_out);
	return 0;
}
		
