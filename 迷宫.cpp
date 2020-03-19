#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50

typedef struct{
	int i;
	int j;
	int di;
}Box;

typedef struct{
	Box data[MaxSize];
	int top;
}SqStack;

int mg[10][10] = {
				{1,1,1,1,1,1,1,1,1},{1,0,0,1,0,0,0,1,0,1},
				{1,0,0,1,0,0,0,1,0,1},{1,0,0,0,0,1,1,0,0,1},
				{1,0,1,1,1,0,0,0,0,1},{1,0,0,0,1,0,0,0,0,1},
				{1,0,1,0,0,0,1,0,0,1},{1,0,1,1,1,0,1,1,0,1},
				{1,1,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1}
				};

void InitStack(SqStack* &S)
{
	S = (SqStack*)malloc(sizeof(SqStack));
	S->top = -1;
}

void DestroyStack(SqStack* &S)
{
	free(S);	
}



bool StackEmpty(SqStack* S)
{
	return(S->top==-1);
}



bool Push(SqStack* &S,Box e)
{
	if(S->top==MaxSize-1) return false;
	
	S->top++;
	S->data[S->top] = e;
	return true;
}

bool Pop(SqStack* &S, Box&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

bool GetTop(SqStack* S,Box&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	return true;
		
}

bool mgpath(int xi, int yi, int xe,int ye)
{
	Box path[MaxSize],e;
	bool find;
	int k;
	int i1,j1,d1,i,j;
	SqStack *st;
	InitStack(st);
	e.i = xi;
	e.j = yi;
	e.di = -1;
	mg[xi][yi] = -1;
	Push(st,e);
	while(!StackEmpty(st))
	{
		GetTop(st,e);
		i = e.i;
		j = e.j;
		d1 = e.di;
		if(i == xe && j == ye)
		{
			k=0;
			while(!StackEmpty(st))
			{
				Pop(st,e);
				path[k] = e;	
				k++;
			}
			while(k>=1)
			{
				k--;
				printf("(%d,%d)\n",path[k].i,path[k].j);
			}
			DestroyStack(st);
			return true;
		}
		
		
		find = false;
		while(d1<4&&!find)
		{	
			d1++;
			switch(d1)
			{
			case 0: i1 = i-1; j1 = j;break;
			case 1: i1 = i; j1 = j+1;break;
			case 2: i1 = i+1; j1 = j; break;
			case 3: i1 = i; j1 = j-1; break; 
				
			}
			if(mg[i1][j1] == 0) find = true;
		}
		if(find)
		{
			st->data[st->top].di = d1; 
			e.i = i1;
			e.j = j1;
			e.di = -1;
			Push(st,e);
			mg[i1][j1] = -1;
		}
		else
		{
			Pop(st,e);
			mg[e.i][e.j] = 0;
		}
	}
	DestroyStack(st);
	return false;
}


int main()
{
	if(!mgpath(1,1,8,8))
		printf("No path!\n");
	return 0;
}



