#include<stdio.h>
#include<conio.h>
#include<math.h>
#define MAX 100
int i,j,n=0;
float sum=0;
void mode(float *p);
float mean(float *p);
float median(float *p);
float stdDeviation(float mean,float *p);
void main()
{
	clrscr();
	int op;
	float numbers[MAX];

	printf("***********************Stat Calculator********************\n\n");
	do
	{
		printf("Select an operation\n\t1-Mode\n\t2-Mean\n\t3-Median\n\t4-Standard Deviation\nop : ");
		scanf("%d", &op);
		if((op<1)||(op>4))
			printf("\nwrong input, enter again\n");
	}
	while((op<1)||(op>4));

	printf("\nEnter the values, one per line\nTo stop, enter -1\n");

	for(i=0;i<MAX;i++)
	{
		scanf("%f", &numbers[i]);
		if(numbers[i]==-1)
			break;
		n++;
	}
	switch(op)
	{
		case 1:
			mode(numbers);
			break;
		case 2:
			float mn;
			mn = mean(numbers);
			printf("\nThe mean of values : %0.2f", mn);
			break;
		case 3:
			printf("\nThe median of values : %0.2f", median(numbers));
			break;
		case 4:
			printf("\nThe standard deviation of values : %0.6f",stdDeviation(mean(numbers),numbers));
			break;
	}
	getch();
}
void mode(float *p)
{
	float big;
	int x,k=0;
	float count=1;
	float b[MAX];
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if((*(p+i))==(*(p+j)))
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
	printf("\nThe mode of values : %0.0f \nIt has occured %0.0f times", *(p+x), b[x]);
}
float mean(float *p)
{
	float mean;
	for(i=0;i<n;i++)
		sum+=(*p++);
	mean = sum/(float)n;
	printf("\nThe sum of values  : %0.2f", sum);
	printf("\nNo of values       : %d", n);
	return mean;
}
float median(float *p)
{
	int mid,r;
	mid =(n+1)/2;
	r=n%2;
	if(r==0)
		return ( (*(p+mid)) + (*(p+(mid-1))) )/2;
	else
		return  *(p+(mid-1));
}
float stdDeviation(float mean,float *p)
{
	float deviation,sumsqr,variance,stdDiv;
	for(i=0;i<n;i++)
	{
		deviation=(*p++)-mean;
		sumsqr+=deviation*deviation;
	}
	variance=sumsqr/(float)n;
	stdDiv=sqrt(variance);
	return stdDiv;
}