#include "stdafx.h"
#include "Shape_Point.h"

int set1(int ***matrix, int i, int j, int k, int thr)
{
	if((matrix[i+1][j+1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr) && 
	(matrix[i+1][j][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i-1][j][k+1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k] >=thr || matrix[i][j+1][k] >=thr || matrix[i-1][j+1][k] >=thr)&&
	(matrix[i+1][j-1][k] >=thr || matrix[i][j-1][k] >=thr || matrix[i-1][j-1][k] >=thr ) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr)&&
	(matrix[i+1][j][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i-1][j][k-1] >=thr) && 
	(matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr))  
	{
		return 1; // when each line contains at least one black point before the iteration/
	}
	else 
	{
		return 0;
	}
} //when a,d = Pe, Pw


int set2(int ***matrix, int i, int j, int k, int thr)
{
	if((matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr) && 
	(matrix[i+1][j][k+1] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr) && 
	(matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr) &&
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr)&&
	(matrix[i-1][j][k+1] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j][k-1] >=thr) && 
	(matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		return 1;
	}
	else
	{ 
		return 0;
	}
} //when a,d = Pt, Pb 

int set3(int ***matrix, int i, int j, int k, int thr)
{
	if((matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j-1][k] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr) && 
	(matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr) &&
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i-1][j+1][k] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j-1][k] >=thr) && 
	(matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 

		return 1;
	else
		 return 0;
}//when a,d = Pn, Ps 


/*int set1(int ***matrix, int i, int j, int k, int thr)
{
	if((!!(matrix[i+1][j+1][k+1]-thr+1) + !!(matrix[i][j+1][k+1]-thr+1) +!!(matrix[i-1][j+1][k+1]-thr+1)<3) && 
	(!!(matrix[i+1][j+1][k+1]-thr+1) + !!(matrix[i][j+1][k+1]-thr+1) +!!(matrix[i-1][j+1][k+1]-thr+1)>0) &&
	(!!(matrix[i+1][j][k+1] -thr+1) + !!(matrix[i][j][k+1] -thr+1) + !!( matrix[i-1][j][k+1] -thr+1)<3) && 
	(!!(matrix[i+1][j][k+1] -thr+1) + !!(matrix[i][j][k+1] -thr+1) + !!( matrix[i-1][j][k+1] -thr+1)>0) && 
	(!!(matrix[i+1][j-1][k+1] -thr+1) + !!(matrix[i][j-1][k+1]-thr+1) +!!( matrix[i-1][j-1][k+1] -thr+1)<3) && 
	(!!(matrix[i+1][j-1][k+1] -thr+1) + !!(matrix[i][j-1][k+1]-thr+1) +!!( matrix[i-1][j-1][k+1] -thr+1)>0) && 
	(!!(matrix[i+1][j+1][k] -thr+1) + !!(matrix[i][j+1][k]-thr+1) +!!( matrix[i-1][j+1][k] -thr+1)<3) && 
	(!!(matrix[i+1][j+1][k] -thr+1) + !!(matrix[i][j+1][k]-thr+1) +!!( matrix[i-1][j+1][k] -thr+1)>0) && 
	(!!(matrix[i+1][j-1][k] -thr+1) + !!(matrix[i][j-1][k]-thr+1) +!!( matrix[i-1][j-1][k] -thr+1)<3) && 
	(!!(matrix[i+1][j-1][k] -thr+1) + !!(matrix[i][j-1][k]-thr+1) +!!( matrix[i-1][j-1][k] -thr+1)>0) && 
	(!!(matrix[i+1][j+1][k-1] -thr+1) + !!(matrix[i][j+1][k-1]-thr+1) +!!( matrix[i-1][j+1][k-1] -thr+1)<3) && 
	(!!(matrix[i+1][j+1][k-1] -thr+1) + !!(matrix[i][j+1][k-1]-thr+1) +!!( matrix[i-1][j+1][k-1] -thr+1)>0) && 
	(!!(matrix[i+1][j][k-1] -thr+1) + !!(matrix[i][j][k-1]-thr+1) +!!( matrix[i-1][j][k-1] -thr+1)<3) && 
	(!!(matrix[i+1][j][k-1] -thr+1) + !!(matrix[i][j][k-1]-thr+1) +!!( matrix[i-1][j][k-1] -thr+1)>0) && 
	(!!(matrix[i+1][j-1][k-1] -thr+1) + !!(matrix[i][j-1][k-1]-thr+1) +!!( matrix[i-1][j-1][k-1] -thr+1)<3) && 
	(!!(matrix[i+1][j-1][k-1] -thr+1) + !!(matrix[i][j-1][k-1]-thr+1) +!!( matrix[i-1][j-1][k-1] -thr+1)<0)) 
	{
		return 1; // when each line contains at least one black point before the iteration/
	}
	else 
	{
		return 0;
	}
} //when a,d = Pe, Pw


int set2(int ***matrix, int i, int j, int k, int thr)
{
	if((!!(matrix[i+1][j+1][k+1]-thr+1) + !!(matrix[i+1][j+1][k]-thr+1) +!!(matrix[i+1][j+1][k-1]-thr+1)<3) && 
	(!!(matrix[i+1][j+1][k+1]-thr+1) + !!(matrix[i+1][j+1][k]-thr+1) +!!(matrix[i+1][j+1][k-1]-thr+1)>0) &&
	(!!(matrix[i+1][j][k+1]-thr+1) + !!(matrix[i+1][j][k]-thr+1) +!!(matrix[i+1][j][k-1]-thr+1)<3) &&
	(!!(matrix[i+1][j][k+1]-thr+1) + !!(matrix[i+1][j][k]-thr+1) +!!(matrix[i+1][j][k-1]-thr+1)>0) &&
	(!!(matrix[i+1][j-1][k+1]-thr+1) + !!(matrix[i+1][j-1][k]-thr+1) +!!(matrix[i+1][j-1][k-1]-thr+1)<3) &&
	(!!(matrix[i+1][j-1][k+1]-thr+1) + !!(matrix[i+1][j-1][k]-thr+1) +!!(matrix[i+1][j-1][k-1]-thr+1)>0) &&
	(!!(matrix[i][j+1][k+1]-thr+1) + !!(matrix[i][j+1][k]-thr+1) +!!(matrix[i][j+1][k-1]-thr+1)<3) &&
	(!!(matrix[i][j+1][k+1]-thr+1) + !!(matrix[i][j+1][k]-thr+1) +!!(matrix[i][j+1][k-1]-thr+1)>0) &&
	(!!(matrix[i][j-1][k+1]-thr+1) + !!(matrix[i][j-1][k]-thr+1) +!!(matrix[i][j-1][k-1]-thr+1)<3) &&
	(!!(matrix[i][j-1][k+1]-thr+1) + !!(matrix[i][j-1][k]-thr+1) +!!(matrix[i][j-1][k-1]-thr+1)>0) &&
	(!!(matrix[i][j-1][k+1]-thr+1) + !!(matrix[i][j-1][k]-thr+1) +!!(matrix[i][j-1][k-1]-thr+1)<3) &&
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr)&&
	(matrix[i-1][j][k+1] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j][k-1] >=thr) && 
	(matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		return 1;
	}
	else
	{ 
		return 0;
	}
} //when a,d = Pt, Pb 

int set3(int ***matrix, int i, int j, int k, int thr)
{
	if((matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j-1][k] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr) && 
	(matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr) &&
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i-1][j+1][k] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j-1][k] >=thr) && 
	(matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 

		return 1;
	else
		 return 0;
}//when a,d = Pn, Ps */

int Shape_Point(int ***matrix, int i, int j, int k, int thr) /*return 1 when it's a shape point, return 0 when it's not a shape pt*/
{
	//group 1, 1
/*	if(matrix[i+1][j+1][k] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j-1][k] <thr && matrix[i][j+1][k] <thr && matrix[i-1][j+1][k] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i-2][j+1][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] <thr && matrix[i-2][j-2][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr && matrix[i+1][j-2][k] <thr)
			return 1;

		else if(matrix[i][j-1][k] <thr && matrix[i-2][j+1][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] <thr && matrix[i-2][j-2][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr)
		    return 1;

		else if(matrix[i-1][j][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] <thr && matrix[i-2][j-2][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr && matrix[i+1][j-2][k] <thr)
			return 1;

		else if(matrix[i-2][j+1][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] < thr && matrix[i-1][j-1][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr && matrix[i+1][j-2][k] <thr)
		    return 1;

		else if(matrix[i-2][j+1][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] < thr && matrix[i-1][j-1][k] <thr && matrix[i][j-1][k] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-1][j-1][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr && matrix[i+1][j-2][k] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j-1][k] <thr && matrix[i-2][j-2][k] <thr && matrix[i-1][j-2][k] <thr && matrix[i][j-2][k] <thr && matrix[i][j-1][k] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-1][j-1][k] <thr && matrix[i][j-1][k] <thr)
		     return 1;
	} 

	//group1,2
	if(matrix[i+1][j][k+1] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j][k-1] <thr && matrix[i][j][k+1] <thr && matrix[i-1][j][k+1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i-2][j][k+1] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] <thr && matrix[i-2][j][k-2] <thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i+1][j][k-2] <thr)
			return 1;
		
		else if(matrix[i][j][k-1] <thr && matrix[i-2][j][k+1] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] <thr && matrix[i-2][j][k-2] <thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] <thr && matrix[i-2][j][k-2] <thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i+1][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k-1] <thr && matrix[i-2][j][k+1] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] < thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i+1][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i-2][j][k+1] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-1][j][k-1] <thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i+1][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i][j][k-1] <thr && matrix[i-2][j][k] <thr && matrix[i-2][j][k-1] <thr && matrix[i-2][j][k-2] <thr && matrix[i-1][j][k-2] <thr && matrix[i][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i-1][j][k] <thr && matrix[i-1][j][k-1] <thr && matrix[i][j][k-1] <thr)
		     return 1;
		
	}

	//group1,3
	if(matrix[i][j+1][k+1] <thr && matrix[i][j+1][k] <thr && matrix[i][j+1][k-1] <thr && matrix[i][j][k+1] <thr && matrix[i][j-1][k+1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i][j-2][k+1] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] <thr && matrix[i][j-2][k-2] <thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i][j+1][k-2] <thr)
			return 1;
		
		else if(matrix[i][j][k-1] <thr && matrix[i][j-2][k+1] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] <thr && matrix[i][j-2][k-2] <thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] <thr && matrix[i][j-2][k-2] <thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i][j+1][k-2] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k-1] <thr && matrix[i][j-2][k+1] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] < thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i][j+1][k-2] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i][j-2][k+1] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k] <thr && matrix[i][j-1][k-1] <thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr && matrix[i][j+1][k-2] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k] <thr && matrix[i][j][k-1] <thr && matrix[i][j-2][k] <thr && matrix[i][j-2][k-1] <thr && matrix[i][j-2][k-2] <thr && matrix[i][j-1][k-2] <thr && matrix[i][j][k-2] <thr)
		    return 1;
		
		else if(matrix[i][j-1][k] <thr && matrix[i][j-1][k-1] <thr && matrix[i][j][k-1] <thr)
		     return 1;
		
	} 

	//group2,4
	if(matrix[i+1][j+1][k] <thr && matrix[i][j+1][k] <thr && matrix[i-1][j+1][k] <thr && matrix[i-1][j][k] <thr && matrix[i-1][j-1][k] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+2][j-2][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i-1][j-2][k] < thr)
			return 1;
		
		else if(matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+2][j-2][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i][j-1][k] < thr)
			return 1;
		
		else if(matrix[i+1][j][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+2][j-2][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i-1][j-2][k] < thr)
			return 1;

		else if(matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i-1][j-2][k] < thr)
			return 1;

		else if(matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i][j-1][k] < thr)
			return 1;

		else if(matrix[i+1][j][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i-1][j-2][k] < thr)
			return 1;
		
		else if(matrix[i+1][j][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr && matrix[i+2][j-2][k] < thr && matrix[i+1][j-2][k] < thr && matrix[i][j-2][k] < thr && matrix[i][j-1][k] < thr)
			return 1;

		else if(matrix[i+1][j][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i][j-1][k] < thr)
			return 1 ;
	}

	//group2,5
	if(matrix[i+1][j][k+1] <thr && matrix[i][j][k+1] <thr && matrix[i-1][j][k+1] <thr && matrix[i-1][j][k] <thr && matrix[i-1][j][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+2][j][k-2] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i-1][j][k-2] < thr)
			return 1;
		
		else if(matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+2][j][k-2] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j][k-1] < thr)
			return 1;
		
		else if(matrix[i+1][j][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+2][j][k-2] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i-1][j][k-2] < thr)
			return 1;

		else if(matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+1][j][k-1] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i-1][j][k-2] < thr)
			return 1;

		else if(matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+1][j][k-1] < thr && matrix[i][j][k-1] < thr)
			return 1;

		else if(matrix[i+1][j][k] < thr && matrix[i+1][j][k-1] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i-1][j][k-2] < thr)
			return 1;
		
		else if(matrix[i+1][j][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr && matrix[i+2][j][k-2] < thr && matrix[i+1][j][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j][k-2] < thr)
			return 1;

		else if(matrix[i+1][j][k] < thr && matrix[i+1][j][k-1] < thr && matrix[i][j][k-1] < thr)
			return 1 ;
	}

	//group2,6
	if(matrix[i][j+1][k+1] <thr && matrix[i][j][k+1] <thr && matrix[i][j-1][k+1] <thr && matrix[i][j-1][k] <thr && matrix[i][j-1][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+2][k-2] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j-1][k-2] < thr)
			return 1;
		
		else if(matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+2][k-2] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j][k-1] < thr)
			return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+2][k-2] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j-1][k-2] < thr)
			return 1;

		else if(matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j-1][k-2] < thr)
			return 1;

		else if(matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j][k-1] < thr)
			return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j-1][k-2] < thr)
			return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr && matrix[i][j+2][k-2] < thr && matrix[i][j+1][k-2] < thr && matrix[i][j][k-2] < thr && matrix[i][j][k-1] < thr)
			return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j][k-1] < thr)
			return 1 ;
	}

	//group3,7
	if(matrix[i-1][j+1][k] <thr && matrix[i-1][j][k] <thr && matrix[i-1][j-1][k] <thr && matrix[i][j-1][k] <thr && matrix[i+1][j-1][k] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i-1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+2][j+2][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr)
			return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+2][j+2][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr)
		    return 1;

		else if(matrix[i-1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+2][j+2][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+1][j][k] < thr)
			return 1;

		else if(matrix[i-1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr)
		    return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j-1][k] < thr)
		    return 1;
		
		else if(matrix[i-1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i+1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i+1][j+2][k] < thr && matrix[i+2][j+2][k] < thr && matrix[i+2][j+1][k] < thr && matrix[i+2][j][k] < thr && matrix[i+1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i+1][j][k] < thr)
		     return 1;
	} 

	//group3,8
	if(matrix[i-1][j][k+1] <thr && matrix[i-1][j][k] <thr && matrix[i-1][j][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i+1][j][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i-1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+2][j][k+2] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr)
			return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+2][j][k+2] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr)
		    return 1;

		else if(matrix[i-1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+2][j][k+2] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+1][j][k] < thr)
			return 1;

		else if(matrix[i-1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+1][j][k+1] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr)
		    return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i+1][j][k+1] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+2][j][k-1] < thr)
		    return 1;
		
		else if(matrix[i-1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+1][j][k+1] < thr && matrix[i+1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i+1][j][k+2] < thr && matrix[i+2][j][k+2] < thr && matrix[i+2][j][k+1] < thr && matrix[i+2][j][k] < thr && matrix[i+1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i+1][j][k+1] < thr && matrix[i+1][j][k] < thr)
		     return 1;
	} 

	//group3,9
	if(matrix[i][j-1][k+1] <thr && matrix[i][j-1][k] <thr && matrix[i][j-1][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i][j+1][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >= thr || matrix[i+1][j+1][k] >= thr || matrix[i+1][j+1][k-1] >= thr || matrix[i+1][j][k+1] >= thr || matrix[i+1][j][k] >= thr || matrix[i+1][j][k-1] >= thr || matrix[i+1][j-1][k+1] >= thr || matrix[i+1][j-1][k] >= thr || matrix[i+1][j-1][k-1] >= thr) && 
	(matrix[i-1][j+1][k+1] >= thr || matrix[i-1][j+1][k] >= thr || matrix[i-1][j+1][k-1] >= thr || matrix[i-1][j][k+1] >= thr || matrix[i-1][j][k] >= thr || matrix[i-1][j][k-1] >= thr || matrix[i-1][j-1][k+1] >= thr || matrix[i-1][j-1][k] >= thr || matrix[i-1][j-1][k-1] >= thr)) 
	{
		if(matrix[i][j-1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+2][k+2] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr)
			return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+2][k+2] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr)
		    return 1;

		else if(matrix[i][j-1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+2][k+2] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+1][k] < thr)
			return 1;

		else if(matrix[i][j-1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr)
		    return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+2][k-1] < thr)
		    return 1;
		
		else if(matrix[i][j-1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+1][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i][j+1][k+2] < thr && matrix[i][j+2][k+2] < thr && matrix[i][j+2][k+1] < thr && matrix[i][j+2][k] < thr && matrix[i][j+1][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+1][k] < thr)
		     return 1;
	} 

	//group4,10
	if(matrix[i+1][j+1][k] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j-1][k] <thr && matrix[i][j-1][k] <thr && matrix[i-1][j-1][k] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i+1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-2][j+2][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j-1][k] < thr)
			return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-2][j+2][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j-1][k] < thr)
		    return 1;

		else if(matrix[i+1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-2][j+2][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-1][j][k] < thr)
			return 1;

		else if(matrix[i+1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j-1][k] < thr)
		    return 1;

		else if(matrix[i][j+1][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j-1][k] < thr)
		    return 1;
		
		else if(matrix[i+1][j+2][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i][j+2][k] < thr && matrix[i-1][j+2][k] < thr && matrix[i-2][j+2][k] < thr && matrix[i-2][j+1][k] < thr && matrix[i-2][j][k] < thr && matrix[i-1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j+1][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr)
		     return 1;
	} 

	//group4,11
	if(matrix[i+1][j][k+1] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i-1][j][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
	{
		if(matrix[i+1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-2][j][k+2] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j][k-1] < thr)
			return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-2][j][k+2] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j][k-1] < thr)
		    return 1;

		else if(matrix[i+1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-2][j][k+2] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-1][j][k] < thr)
			return 1;

		else if(matrix[i+1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-1][j][k+1] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j][k-1] < thr)
		    return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i-1][j][k+1] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-2][j][k-1] < thr)
		    return 1;
		
		else if(matrix[i+1][j][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-1][j][k+1] < thr && matrix[i-1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i-1][j][k+2] < thr && matrix[i-2][j][k+2] < thr && matrix[i-2][j][k+1] < thr && matrix[i-2][j][k] < thr && matrix[i-1][j][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i-1][j][k+1] < thr && matrix[i-1][j][k] < thr)
		     return 1;
	} 

	//group4,12
	if(matrix[i][j+1][k+1] <thr && matrix[i][j+1][k] <thr && matrix[i][j+1][k-1] <thr && matrix[i][j][k-1] <thr && matrix[i][j-1][k-1] <thr && 
	(matrix[i+1][j+1][k+1] >= thr || matrix[i+1][j+1][k] >= thr || matrix[i+1][j+1][k-1] >= thr || matrix[i+1][j][k+1] >= thr || matrix[i+1][j][k] >= thr || matrix[i+1][j][k-1] >= thr || matrix[i+1][j-1][k+1] >= thr || matrix[i+1][j-1][k] >= thr || matrix[i+1][j-1][k-1] >= thr) && 
	(matrix[i-1][j+1][k+1] >= thr || matrix[i-1][j+1][k] >= thr || matrix[i-1][j+1][k-1] >= thr || matrix[i-1][j][k+1] >= thr || matrix[i-1][j][k] >= thr || matrix[i-1][j][k-1] >= thr || matrix[i-1][j-1][k+1] >= thr || matrix[i-1][j-1][k] >= thr || matrix[i-1][j-1][k-1] >= thr)) 
	{
		if(matrix[i][j+1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-2][k+2] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-2][k-1] < thr)
			return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-2][k+2] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-2][k-1] < thr)
		    return 1;

		else if(matrix[i][j+1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-2][k+2] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-1][k] < thr)
			return 1;

		else if(matrix[i][j+1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-2][k-1] < thr)
		    return 1;

		else if(matrix[i][j][k+1] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-2][k-1] < thr)
		    return 1;
		
		else if(matrix[i][j+1][k+2] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j-1][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j][k+2] < thr && matrix[i][j-1][k+2] < thr && matrix[i][j-2][k+2] < thr && matrix[i][j-2][k+1] < thr && matrix[i][j-2][k] < thr && matrix[i][j-1][k] < thr)
		    return 1;
		
		else if(matrix[i][j][k+1] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j-1][k] < thr)
		     return 1;
	} */

/***************condition 1*********************************************************************************
* if there exist two opposite s-points a,d =N(p) such that EM(a,d,p) contains a 6-closed path of white pts *
*encircling p and each of surface(a,p) and surface(d,p) contains at least one black pt b4 the iteration    *
*surface(a,p) is the surface k+1, surface(d,p) is the surface k-1					   *
***********************************************************************************************************/
	if(matrix[i+1][j+1][k] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j-1][k] <thr && matrix[i][j+1][k] <thr && matrix[i][j-1][k] <thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr && matrix[i-1][j-1][k] < thr && 
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j][k+1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j-1][k+1] >=thr) && 
	(matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i][j][k-1] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
		return 1;

	if(matrix[i+1][j][k+1] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j][k-1] <thr && matrix[i][j][k+1] <thr && matrix[i][j][k-1] <thr && matrix[i-1][j][k+1] < thr && matrix[i-1][j][k] < thr && matrix[i-1][j][k-1] < thr &&
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i][j+1][k+1] >=thr || matrix[i][j+1][k] >=thr || matrix[i][j+1][k-1] >=thr || matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr) && 
	(matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr || matrix[i][j-1][k+1] >=thr || matrix[i][j-1][k] >=thr || matrix[i][j-1][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
		return 1;

	if(matrix[i][j+1][k+1] <thr && matrix[i][j+1][k] <thr && matrix[i][j+1][k-1] <thr && matrix[i][j][k+1] <thr && matrix[i][j][k-1] <thr && matrix[i][j-1][k+1] < thr && matrix[i][j-1][k] < thr && matrix[i][j-1][k-1] < thr &&
	(matrix[i+1][j+1][k+1] >=thr || matrix[i+1][j+1][k] >=thr || matrix[i+1][j+1][k-1] >=thr || matrix[i+1][j][k+1] >=thr || matrix[i+1][j][k] >=thr || matrix[i+1][j][k-1] >=thr || matrix[i+1][j-1][k+1] >=thr || matrix[i+1][j-1][k] >=thr || matrix[i+1][j-1][k-1] >=thr) && 
	(matrix[i-1][j+1][k+1] >=thr || matrix[i-1][j+1][k] >=thr || matrix[i-1][j+1][k-1] >=thr || matrix[i-1][j][k+1] >=thr || matrix[i-1][j][k] >=thr || matrix[i-1][j][k-1] >=thr || matrix[i-1][j-1][k+1] >=thr || matrix[i-1][j-1][k] >=thr || matrix[i-1][j-1][k-1] >=thr)) 
		return 1;
	

/****condition 2*********************************/
/*if there exist a pair of opposite s-points (a,d) such that d={pb,ps,pw}, a is white, d or f1(d,p) is white 
and each of the sets{ e(a,b,p),b,e(b,d,p)},{e(a,c,p),c,e(c,d,p)},{e(a,e,p),e,e(d,e,p)},{e(a,f,p),f,e(d,f,p)}
{v(a,b,c,p),e(b,c,p),v(b,c,d,p)},{v(a,b,f,p),e(b,f,p),v(b,d,f,p)},{v(a,c,e,p),e(c,e,p),v(c,d,e,p)},{v(a,e,f,p),
e(e,f,p),v(d,e,f,p)} contains at least one black pt before the iteration*/
/************************************************/

	if(matrix[i+1][j][k] <thr && (matrix[i-1][j][k] <thr || matrix[i-2][j][k] <thr) && set1(matrix, i, j, k, thr)==1)
	//if(matrix[i+1][j][k] <thr && matrix[i-1][j][k] <thr && set1(matrix, i, j, k, thr)==1)
		return 1;

	if(matrix[i][j][k+1] <thr && (matrix[i][j][k-1] <thr || matrix[i][j][k-2] <thr) && set2(matrix, i, j, k, thr)==1)
	//if(matrix[i][j][k+1] <thr && matrix[i][j][k-1] <thr && set2(matrix, i, j, k, thr)==1)
		return 1;

	if(matrix[i][j+1][k] <thr && (matrix[i][j-1][k] <thr || matrix[i][j-2][k] <thr) && set3(matrix, i, j, k, thr)==1)
	//if(matrix[i][j+1][k] <thr && matrix[i][j-1][k] <thr && set3(matrix, i, j, k, thr)==1)
		return 1;

	return 0;
}

