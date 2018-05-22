#include<stdio.h>
#include<stdlib.h>

void main()

{
int number;
printf("Enter a number");
scanf("%d", &number);
printf("sequence is :\n");
printf("%d\n", number);

do
{
if(number%2!=0)
{
number = number (number*3)+1;
}
elseif(number%2==0)
{
number = (number)/2;
}
printf("%d\n", number);
}
while(number!=1);
}