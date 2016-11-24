#include "stdafx.h"
#include "Recover.h"
#define MAXNUM 9999

void Recover(int ***type, int i, int j, int k, int *m_iSize)
{
	int a,b,c;
	float pro = 0;
	int sum = 0;
	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(type[i-1+a][j-1+b][k-1+c] > 0)
				{
					pro += type[i-1+a][j-1+b][k-1+c];
					sum ++;
				}
			}
		}
	}

	if(sum == 0)
		type[i][j][k] = -MAXNUM-1;

	pro = pro/sum;
	
	type[i][j][k] = pro;
}

int RecoverConnection(int ***type, int ***Matrix, int i, int j, int k)
{
	int registry[26][2];
	int a,b,c;
	int count;

	for(a=0; a<26; a++)
	{
		registry[a][0] = 0;
		registry[a][1] = 0;
	}

	count = 0;

	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(type[i-1+a][j-1+b][k-1+c] >0 && Matrix[i-1+a][j-1+b][k-1+c] > 0 && !(a==1 && b==1 && c==1))
				{
					while(registry[count][0]!=0 && registry[count][0]!=type[i-1+a][j-1+b][k-1+c])
					{
						count++;
					}
					registry[count][0] = type[i-1+a][j-1+b][k-1+c];
					registry[count][1]++;
				}
			}
		}
	}

	int max = 0;
	for(a=0; a<26; a++)
	{
		if(registry[a][1]>registry[max][1])
			max = a;
	}
	return registry[max][0];
}


int PrimaryRecover(int ***type, int ***Matrix, int i, int j, int k, int l)
{
	int a,b,c;
	int tra = MAXNUM;
	int count = 0;

	for(a=0; a<=2; a++)
	{
		for(b=0; b<=2; b++)
		{
			for(c=0; c<=2; c++)
			{
				if(type[i-1+a][j-1+b][k-1+c] >0 && Matrix[i-1+a][j-1+b][k-1+c] > 0 && !(a==1 && b==1 && c==1))
				{
					if(count==0)
					{
						tra = type[i-1+a][j-1+b][k-1+c];
						count = 1;
					}
					else if(tra != type[i-1+a][j-1+b][k-1+c])
					{
						return 0;
					}
				}
			}
		}
	}
	if(tra == MAXNUM)
	{
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if(type[i-1+a][j-1+b][k-1+c] == l && !(a==1 && b==1 && c==1))
					{
						return tra;
					}
				}
			}
		}
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if(type[i-1+a][j-1+b][k-1+c] == -MAXNUM-1 && !(a==1 && b==1 && c==1))
					{
						type[i-1+a][j-1+b][k-1+c] = (int)RecoverConnection(type, Matrix, i-1+a, j-1+b, k-1+c);
						Matrix[i-1+a][j-1+b][k-1+c] = type[i-1+a][j-1+b][k-1+c];
						return tra;
					}
				}
			}
		}	
	}
	return tra;
}