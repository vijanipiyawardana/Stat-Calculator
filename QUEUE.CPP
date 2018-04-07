//stat calculator
//including header files
#include<stdio.h>
//#include<conio.h>
#include<math.h>
//#include<iostream.h>
#define MAX 100
//declaring global variables
int TRUE =1;
int FALSE = 0;
int i,j,n=0;            //n : no of values, i,j : for 'for' loops
float sum,mn;           //sum : sum of values, mn : mean of values
//defining class
class Queue
{
	//members  (definition)
	private:
		struct Numbers             //structure of an element in the queue
		{
			float no;          	//to hold the value
			Numbers *next;     	//to hold next element of the queue
		};
		Numbers *in;               //pointer to refer tail of the queue
		Numbers *out;              //pointer to refer head of the queue
	public:
		Queue(void);               //constructor
		void enqueue(float);       //method for input values
		float dequeue();           //method for output values
		int isempty();             //to check whether the data structure is empty or not
		void mode();               //to find mode
		float summation();         //to find sum
		float mean(float);         //to find mean
		float median();            //to find median
		float stdDeviation(float); //to find standard deviation
}
//method declaration
Queue :: Queue(void)                             //constructor initializes in and out pointers
{
	in=NULL;
	out=NULL;
}
int Queue :: isempty()
{
	if(out==NULL)
		return TRUE;                     //if out refers to none queue is empty
	else
		return FALSE;
}
void Queue :: enqueue(float newNum)              //parameter to catch a new number
{
	Numbers *tmp=new Numbers;                //tmp points to a new element
	if(tmp==NULL)
		printf("\nNo more memory to allocate\n");
	else
	{
		(*tmp).no=newNum;                //assigning new number to the element
		(*tmp).next=NULL;                //new element refers to none
		if(in!=NULL)                     //if it's not the first element of the queue
		{
			(*in).next=tmp;          //new element is refered by the current tail
			in=(*in).next;           //and new element becomes tail
		}
		if(out==NULL)                    //if it's the first element of the queue both in and out refer it
		{
			in=tmp;
			out=tmp;
		}
	}
	return;
}
float Queue :: dequeue(void)                     //returns a float value
{
	Numbers *tmp;                            //a pointer to assist
	float topVal;                            //variable to hold the value
	topVal=(*out).no;                        //it is assigned by the value in first element of the queue
	tmp=(*out).next;                         //tmp refers next element
	delete(out);                             //deleting first element (release memory)
	out=tmp;                                 //the next element becomes as first element
	return(topVal);                          //returns the value taken
}
float Queue :: summation()
{
	Numbers *tmp;
	tmp=out;                                 //pointer tmp initialized with first element's address
	while(tmp!=NULL)                         //find sum of values in the queue
	{
		sum+=((*tmp).no);
		tmp=(*tmp).next;
	}
	return sum;
}
void Queue :: mode()
{
	float big;
	int x,k=0;
	float count=1;
	float b[MAX];
	Numbers *curr,*prev;
	prev=out;
	//while loop like : take i th number and compare it with others from i+1, then i increases by 1 and do the same upto end of queue.
	while(prev!=NULL)
	{
		curr=(*prev).next;
		while(curr!=NULL)
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
	//array b contains no of times of each value occured
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
	float md;
	curr=out;
	prev=NULL;
	for(j=1;j<=x;j++)                         //this loop find the correct element having mode
	{
		prev=curr;
		curr=(*curr).next;
	}
	md=(*curr).no;
	printf("\nThe mode of values : %0.2f \nIt has occured %0.0f times", md,b[x]);
}
float Queue :: mean(float sum)                   //parameter to take sum
{
	mn=sum/n;                                //mean = sum/(no of values)
	return(mn);                              //returns mean
}
float Queue :: median()
{
	float median,m1,m2;
	int mid,r;
	Numbers *curr,*prev;
	curr=out;
	mid=(n+1)/2;                             //to find middle element
	r=n%2;
	if(r==0)                                 //if no of values is even, there are 2 middle values
	{
		for(i=1; i<=mid; i++)            //find these 2 values
		{
			prev=curr;
			curr=(*curr).next;
		}
		m1=(*prev).no;
		m2=(*curr).no;
		median=(m1+m2)/2;                //and take their average as median
	}
	else                                     //if no of values is odd there is exactly 1 value in the middle
	{
		for(i=1; i<=(mid-1); i++)        //find that value
		{
			prev=curr;
			curr=(*curr).next;
		}
		median=(*curr).no;               //take it as median
	}
	return median;
}
float Queue :: stdDeviation(float mn)            //parameter to take mean of values
{
	float deviation,sumsqr,variance,stdDiv;
	Numbers *tmp;                            //temporary pointer
	tmp=out;                                 //it refers the head of queue
	while(tmp!=NULL)                         //until end of queue
	{
		deviation=((*tmp).no)-mn;        //find deviation (by mean) of each values
		sumsqr+=deviation*deviation;     //taking sum of squres of each deviations
		tmp=(*tmp).next;
	}
	variance=sumsqr/(float)n;                //find variance
	stdDiv=sqrt(variance);                   //take square root of variance as std.deviation, math.h is needed
	printf("\nPopulation Standard Variance  : %0.6f", variance);
	return stdDiv;
}
//main method
int main()
{
	//clrscr();
	int op;
	float newNum;
	char again;
	Queue newQueue;                          //declaring object from Queue class, constructor is called
	printf("***********************STATISTICS CALCULATOR***********************\n\n");
	//selecting an operation
	do
	{
		printf("Select an operation\n\t1-Mode\n\t2-Mean\n\t3-Median\n\t4-Standard Deviation\nop : ");
		scanf("%d", &op);
		if((op<1)||(op>4))
			printf("\nwrong input, enter again\n");
	}
	while((op<1)||(op>4));
	//enqueue values one by one
	printf("\nEnter as many digits as you wish, one per line\nTo stop, enter -1\n\n");
	while(1)
	{
		printf("Input a number :");
		scanf("%f", &newNum);                 //take a value from the user
		if(newNum==-1)                        //if user entered -1 come out of the loop
			break;
		else                                  //else
		{
			n++;                          //taking no of values  (counter)
			newQueue.enqueue(newNum);     //passing new value to the queue
		}
	}
	switch(op)
	{
		//calling relevant methods and having results of operations
		case 1:
			newQueue.mode();
			break;
		case 2:
			sum=newQueue.summation();
			printf("\nSum of values  : %0.2f", sum);
			printf("\nNo of values   : %d", n);
			printf("\nMean of values : %0.2f", newQueue.mean(sum));
			break;
		case 3:
			printf("\nMedian is : %0.2f",newQueue.median());
			//printf("Do you want to use calculator again? (Y/N) :");
			//scanf("%s", &again);
			//if((again=='Y')||(again=='y'))
			//main();
			//else if((again=='N')||(again=='n'))
			//printf("\nThank you for using statistics calculator\nPress any key to exit");
			break;
		case 4:
			sum=newQueue.summation();
			mn=newQueue.mean(sum);
			printf("\nSum of values                 : %0.6f", sum);
			printf("\nMean of values                :  %0.6f", mn);
			float stdD=newQueue.stdDeviation(mn);
			printf("\nPopulation Standard Deviation :  %0.6f",stdD);
			break;
	}
	printf("\n\nAll Numbers entered :\n");
	while(!newQueue.isempty())
	{
		printf("%0.0f ", newQueue.dequeue());
	}
	//to continue calculator as you wish
	printf("\n\nDo you want to use statistics calculator again? (Y/N) :");
	scanf("%s", &again);
	if((again=='Y')||(again=='y'))
	{
		sum=0;
		mn=0;
		n=0;
		main();
	}
	else if((again=='N')||(again=='n'))
		printf("\nThank you for using statistics calculator\nPress any key to exit");
	//getch();
    return 0;
}
