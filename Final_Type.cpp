#include "stdafx.h"
#include "Final_Type.h"

/*function to decide if a bone voxel is N3/N4 initial type*/
int Is_N34(int ***temp, int i, int j, int k)
{
	if((temp[i][j][k] == 3) || (temp[i][j][k] == 4) || (temp[i][j][k] == 16) || (temp[i][j][k] == 17))
		return 1;
	else 
		return 0;
}

void Final_Type(int ***matrix, int ***temp, int ***type, int i, int j, int k)
{
	int sum = 0;
	int a,b,c;
	int Asp, N34;
	
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
			{
				//if(type[i-1+a][j-1+b][k-1+c]>0)
				//{
					temp[a][b][c] = type[i-1+a][j-1+b][k-1+c];
				//}
				//else 
					//temp[a][b][c] = 0;
			}

	sum = !!matrix[i-1][j-1][k-1] + !!matrix[i-1][j-1][k] + !!matrix[i-1][j-1][k+1]
		 +!!matrix[i-1][j][k-1]   + !!matrix[i-1][j][k]   + !!matrix[i-1][j][k+1]
		 +!!matrix[i-1][j+1][k-1] + !!matrix[i-1][j+1][k] + !!matrix[i-1][j+1][k+1]
		 +!!matrix[i][j-1][k-1]   + !!matrix[i][j-1][k]	  + !!matrix[i][j-1][k+1]
		 +!!matrix[i][j][k-1]							  + !!matrix[i][j][k+1]
		 +!!matrix[i][j+1][k-1]   + !!matrix[i][j+1][k]   + !!matrix[i][j+1][k+1]
		 +!!matrix[i+1][j-1][k-1] + !!matrix[i+1][j-1][k] + !!matrix[i+1][j-1][k+1]
		 +!!matrix[i+1][j][k-1]   + !!matrix[i+1][j][k]   + !!matrix[i+1][j][k+1]
		 +!!matrix[i+1][j+1][k-1] + !!matrix[i+1][j+1][k] + !!matrix[i+1][j+1][k+1];

	if(type[i][j][k] == 1)
	{
		type[i][j][k] = 8;
		return;
	}

	else if(type[i][j][k] == 2)
	{
		if(sum ==1)
			type[i][j][k] = 5;		//CE-type
//		else if(sum <3)
//			type[i][j][k][4] = 7;
//		else if(sum >=3)
		else
			type[i][j][k] = 1;		//SE-type
		return;
	}
	
	else if(type[i][j][k] == 3)
	{
		type[i][j][k] = 16;
		return;
	}

	else if(type[i][j][k] == 4)
	{
		type[i][j][k] = 17;
		return;
	}

	else if(type[i][j][k] == 5)
	{
		type[i][j][k] = 7;			//CC-type
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if((matrix[i-1+a][j-1+b][k-1+c] > 0) && (a!=1 || b!=1 || c!=1) && (Is_N34(temp, a, b, c) == 0))
						type[i][j][k] = 2;			//S-type
				}
			}
		}
		return;
	}

	else if(type[i][j][k] == 6)
	{
		Asp = 0;
		N34 = 0;
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if((matrix[i-1+a][j-1+b][k-1+c] > 0) && (a!=1 || b!=1 || c!=1))
					{
						Asp++;
						if(Is_N34(temp, a, b, c)==1)
							N34++;
					}
				}
			}
		}
		if(Asp == N34)
			type[i][j][k] = 7;
		else if(N34 == 0)
			type[i][j][k] = 2;
		else if(Asp > N34)
			type[i][j][k] = 4;

		return;
	}

	else if(type[i][j][k] == 7)
	{
		Asp = 0;
		N34 = 0;
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if((matrix[i-1+a][j-1+b][k-1+c] > 0)&& (a!=1 || b!=1 || c!=1))
					{
						Asp++;
						if(Is_N34(temp, a, b, c))
							N34++;
					}
				}
			}
		}
		if(Asp == N34)
			type[i][j][k] = 7;
		else if(N34 == 0)
			type[i][j][k] = 2;
		else if(Asp > N34)
			type[i][j][k] = 4;
		return;
	}

	else if(type[i][j][k] == 8)
	{
		Asp = 0;
		N34 = 0;
		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if((matrix[i-1+a][j-1+b][k-1+c] > 0) && (a!=1 || b!=1 || c!=1))
					{
						Asp++;
						if(Is_N34(temp, a, b, c))
							N34++;
					}
				}
			}
		}
		if(Asp == N34)
			type[i][j][k] = 7;
		else if(N34==0)
			type[i][j][k] = 2;
		else if(Asp > N34)
			type[i][j][k] = 4;

		return;
	}
}

void SS_Extention(int ***type, int i, int j, int k)
{

}

int Distance(int i, int j, int k, int ii, int jj, int kk)
{
	if((i - ii) * (i - ii) + (j - jj) * (j - jj) + (k - kk) * (k - kk) == 1)
		return 1;
	else if((i - ii) * (i - ii) + (j - jj) * (j - jj) + (k - kk) * (k - kk) == 2)
		return 2;
	else if((i - ii) * (i - ii) + (j - jj) * (j - jj) + (k - kk) * (k - kk) == 3)
		return 3;
	else
		return INF;
}

void Is_SCType(int ***type, int i, int j, int k)
{
	int a, b, c;
	int d = 3;
	int SC_i = 0, SC_j = 0, SC_k = 0;

	if(type[i][j][k] == 2 || type[i][j][k] == 3 || type[i][j][k] == 1)
	{
		/*for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if((a!= 1 && b!= 1 && c!=1) && (type[i-1+a][j-1+b][k-1+c] == 4 || type[i-1+a][j-1+b][k-1+c] == 3))
						return;
				}
			}
		}*/

		for(a=0; a<=2; a++)
		{
			for(b=0; b<=2; b++)
			{
				for(c=0; c<=2; c++)
				{
					if(type[i-1+a][j-1+b][k-1+c] == 6 || type[i-1+a][j-1+b][k-1+c] == 7)
					{
						if(Distance(i, j, k, i-1+a, j-1+b, k-1+c)<=d)
						{
							SC_i = i-1+a;
							SC_j = j-1+b;
							SC_k = k-1+c;
							d = Distance(i, j, k, i-1+a, j-1+b, k-1+c);
						}
					}
							
				}
			}
		}

		type[SC_i][SC_j][SC_k] = 4;
	}
}



		


