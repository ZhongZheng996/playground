//用循环队列解决排队问题 
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 50
typedef struct
{
	int data[MaxSize];
	int front;
	int rear;
 } SqQueue;
 
void InitQueue(SqQueue* &q)

{
	
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = 0; 
} 
  
void DestroyQueue(SqQueue* &q)
{
	free(q);
}
  
bool QueueEmpty(SqQueue* q)
{
	return(q->front == q->rear);
}
  
bool enQueue(SqQueue* &q, int e)
{
	if((q->rear+1)%MaxSize == q->front)
		return false;
  	
	q->rear = (q->rear+1)%MaxSize;
	q->data[q->rear] = e;
	return true;
}
  
bool deQueue(SqQueue* &q, int&e)
{
	if(q->front == q->rear)
		return false;
	q->front = (q->front+1)%MaxSize;
	e = q->data[q->front];
	
}
  
void number(int n)
{
	int i,e;
	SqQueue *q;
	InitQueue(q);
	for(i=1;i<=n;i++)
		enQueue(q,i);
	while(!QueueEmpty(q))
	{
		 
		deQueue(q,e);
		printf("%d ",e);
  		if(!QueueEmpty(q))
  		{
  			deQueue(q,e);
  			enQueue(q,e);
		}
  	}
  	DestroyQueue(q);

}
  
int main()
{
	int i,n=8;
	for(i=1;i<=n;i++)
		printf("%d ",i);
	printf("\n");
	number(n);
	return 0;
}
