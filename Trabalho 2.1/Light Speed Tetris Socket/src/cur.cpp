#include"../include/cur.h"
#include<cstdio>
#include<cstdlib>

void Cur::moveCur(const int x,const int y)
{
	int i;
	for(i = 0; i < y; i++)
		printf("\33[2C");
	for(i = 0; i < x; i++)
		printf("\33[1B");
}
void Cur::saveCur()
{
	printf("\33[s");	
}
void Cur::resumeCur()
{
	printf("\33[u");
}
