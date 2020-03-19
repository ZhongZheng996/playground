#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50

typedef struct{
	int i;
	int j;
	int di;
}Box;

typedef struct{
	double data[MaxSize];
	int top;
}SqStack;

typedef struct{
	char data[MaxSize];
	int top;
}SqStack1;

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



bool Push(SqStack* &S,double e)
{
	if(S->top==MaxSize-1) return false;
	
	S->top++;
	S->data[S->top] = e;
	return true;
}

bool Pop(SqStack* &S, double&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

bool GetTop(SqStack* S,double&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	return true;
		
}


void InitStack1(SqStack1* &S)
{
	S = (SqStack1*)malloc(sizeof(SqStack1));
	S->top = -1;
}

void DestroyStack1(SqStack1* &S)
{
	free(S);	
}



bool StackEmpty1(SqStack1* S)
{
	return(S->top==-1);
}



bool Push1(SqStack1* &S,char e)
{
	if(S->top==MaxSize-1) return false;
	
	S->top++;
	S->data[S->top] = e;
	return true;
}

bool Pop1(SqStack1* &S, char&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	S->top--;
	return true;
}

bool GetTop1(SqStack1* S,char&e){
	if(S->top==-1) return false;
	e = S->data[S->top];
	return true;
		
}


// 算术表达式->后缀表达式->结果


void trans(char* exp, char postexp[])
{
	char e;
	SqStack1 *Optr;
	InitStack1(Optr);
	int i=0;

	while((*exp)!='\0')
	{
		switch(*exp)
		{
		case '(': 
			Push1(Optr,'(');
			exp++;
			break;
		case ')':
			Pop1(Optr,e);
			while(e!='(')
			{
				postexp[i]=e;
				i++;
				Pop1(Optr,e);
			}
			exp++;
			break;
		case '+':
		case '-':
			while(!StackEmpty1(Optr))
			{
				GetTop1(Optr,e);
				if(e!='(')
				{
					Pop1(Optr,e);
					postexp[i] = e;
					i++;
				}
				else
					break;
			}
			Push1(Optr,*exp);
			exp++;
			break;
		case '*':
		case '/':
			while(!StackEmpty1(Optr))
			{
				GetTop1(Optr,e);
				if(e=='*'||e=='/')
				{
					Pop1(Optr,e);
					postexp[i] = e;
					i++;
					
				}
				else
					break;
			}
			Push1(Optr,*exp);
			exp++;
			break;
		default:
			while(*exp>='0'&&*exp<='9')
			{
				postexp[i] = *exp;
				i++;
				exp++;
			}
			postexp[i]='#';
			i++;
			break;
		}

	}
	while(!StackEmpty1(Optr))
	{	
		Pop1(Optr,e);
		postexp[i++] = e;
	}
	postexp[i++] = '\0';
	DestroyStack1(Optr);
}




double compvalue(char postexp[])
{
	double a,b,c,d,e;
	SqStack *Opnd;
	InitStack(Opnd);
	while(*postexp != '\0')
	{
		switch(*postexp)
		{
		case '+':
			Pop(Opnd,a);
			Pop(Opnd,b);
			c = b+a;
			Push(Opnd,c);
			postexp++;
			break;
		case '-':
			Pop(Opnd,a);
			Pop(Opnd,b);
			c = b-a;
			Push(Opnd,c);
			postexp++;
			break;
		case '*':
			Pop(Opnd,a);
			Pop(Opnd,b);
			c = b*a;
			Push(Opnd,c);
			postexp++;
			break;
		case '/':
			Pop(Opnd,a);
			Pop(Opnd,b);
			c = b/a;
			Push(Opnd,c);
			postexp++;	
			break;
		default:
			d = 0;
			while(*postexp>='0'&&*postexp<='9')
			{
				d = 10*d + ((*postexp)-'0');
				postexp++;
			}
			Push(Opnd,d);
			postexp++;
			break;
		}
		
	}
	GetTop(Opnd,e);
	DestroyStack(Opnd);
	return e;
} 


int main()
{
	char exp[]="(5-2)*(((3+5)/2)+4)";
	char postexp[MaxSize];
	trans(exp,postexp);
	printf("中缀表达式:%s\n",exp);
	printf("后缀表达式:%s\n",postexp);
	printf("表达式的值:%f\n",compvalue(postexp));
	return 0;

}
