#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<iostream.h>
#define MAX 100
int TRUE =1;
int FALSE = 0;
int i,j,n=0;
float sum,mn;
class Queue
{
	private:
		struct Numbers
		{
			float no;
			Numbers *next;
		};
		Numbers *in;
		Numbers *out;
	public:
		Queue(void);
		void enqueue(float);
		float dequeue();
		int isempty();
		//void mode();
		void mode(float *p);
		float summation();
		float mean(float);
		float median();
		float stdDeviation(float);
}

Queue :: Queue(void)
{
	in=NULL;
	out=NULL;
}
int Queue :: isempty()
{
	if(out==NULL)
		return TRUE;
	else
		return FALSE;
}
void Queue :: enqueue(float newNum)
{
	Numbers *tmp=new Numbers;
	if(tmp==NULL)
		printf("\nNo more memory to allocate\n");
	else
	{
		(*tmp).no=newNum;
		(*tmp).next=NULL;
		if(in!=NULL)
		{
			(*in).next=tmp;
			in=(*in).next;
		}
		if(out==NULL)
		{
			in=tmp;
			out=tmp;
		}
	}
	return;
}
float Queue :: dequeue(void)
{
	Numbers *tmp;
	float topVal;
	topVal=(*out).no;
	tmp=(*out).next;
	delete(out);
	out=tmp;
	return(topVal);
}
float Queue :: summation()
{
	Numbers *tmp;
	tmp=out;
	while(tmp!=NULL)
	{
		sum+=((*tmp).no);
		tmp=(*tmp).next;
	}
	return sum;
}
/*void Queue :: mode()
{
	float big;
	float count=1;
	int x,k=0;
	float b[MAX];
	Numbers *curr,*prev;
	prev=out;
	curr=(*prev).next;
	while(((*prev).next)!=NULL)
	{
		while(((*curr).next)!=NULL)
		{
			if(  ((*prev).no)  ==  ((*curr).no)  )
			count++;
			curr=(*curr).next;
		}
		b[k]=count;
		k++;
		count=1;
		prev=(*prev).next;
	}
	big=b[0];
	x=0;
	for(int i=1;i<n;i++)
	{
		if(big<b[i])
		{
			big=b[i];
			x=i;
		}
	}
	printf("\nx is : %d", x);
	printf("\nn is : %d", n);
	float md;
	curr=out;
	prev=NULL;
	for(int j=1;j<x;j++)
	{
		prev=curr;
		curr=(*curr).next;
	}
	md=(*curr).no;
	printf("\nThe mode of values : %0.2f \n It has occured %d times", md,b[x]);
}*/
void Queue :: mode(float *p)
{
	float big;
	int x,k=0;
	float count=1;
	float b[MAX];
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if((*(p+i)) == (*(p+j)))
			count++;
		}
		b[k]=count;
		k++;
		count=1;
	}
	big=b[0];
	x=0;
	for(i=1;i<n;i++)
	{
		if(big<b[i])
		{
			big=b[i];
			x=i;
		}
	}
	printf("\nThe mode of values : %0.0f\nIt has occured %0.0f times", *(p+x), b[x]);
}
float Queue :: mean(float sum)
{
	mn=sum/n;
	return(mn);
}
float Queue :: median()
{
	float median,m1,m2;
	int mid,r;
	Numbers *curr,*prev;
	curr=out;
	mid=(n+1)/2;
	r=n%2;
	if(r==0)
	{
		for(i=1; i<=mid; i++)
		{
			prev=curr;
			curr=(*curr).next;
		}
		m1=(*prev).no;
		m2=(*curr).no;
		median=(m1+m2)/2;
	}
	else
	{
		for(i=1; i<=(mid-1); i++)
		{
			prev=curr;
			curr=(*curr).next;
		}
		median=(*curr).no;
	}
	return median;
}
float Queue :: stdDeviation(float mn)
{
	float deviation,sumsqr,variance,stdDiv;
	Numbers *tmp;
	tmp=out;
	while(tmp!=NULL)
	{
		deviation=((*tmp).no)-mn;
		sumsqr+=deviation*deviation;
		tmp=(*tmp).next;
	}
	variance=sumsqr/(float)n;
	stdDiv=sqrt(variance);
	return stdDiv;
}
void main()
{
	clrscr();
	int op;
	float newNum;
	Queue newQueue;
	printf("***********************Stat Calculator********************\n\n");
	do
	{
		printf("Select an operation\n\t1-Mode\n\t2-Mean\n\t3-Median\n\t4-Standard Deviation\nop : ");
		scanf("%d", &op);
		if((op<1)||(op>4))
			printf("\nwrong input, enter again\n");
	}
	while((op<1)||(op>4));

	printf("Enter as many digits as you wish, one per line\nTo stop, enter -1\n\n");
	while(1)
	{
		printf("Input a number :");
		scanf("%f", &newNum);
		if(newNum==-1)
			break;
		else
		{
			n++;
			newQueue.enqueue(newNum);
		}
	}

	/*printf("\nAll Numbers entered :\n");

	while(!newQueue.isempty())
	{
		printf("%0.0f ", newQueue.dequeue());
	}*/

	switch(op)
	{
		case 1:
			float numArray[MAX];
			i=0;
			while(!newQueue.isempty())
			{
				numArray[i]=newQueue.dequeue();
				i++;
			}
			newQueue.mode(numArray);
			break;
		case 2:
			sum=newQueue.summation();
			printf("\nSum of values  : %0.2f", sum);
			printf("\nNo of values   : %d", n);
			printf("\nMean of values : %0.2f", newQueue.mean(sum));
			break;
		case 3:
			printf("\nMedian is : %0.2f",newQueue.median());
			break;
		case 4:
			sum=newQueue.summation();
			mn=newQueue.mean(sum);
			printf("\nStandard deviation is : %0.6f",newQueue.stdDeviation(mn));
			break;
	}
	getch();
}