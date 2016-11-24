#include "stdafx.h"
#include "Primary_Thinning.h"
#include "Final_Thinning.h"

/************************************************************************************************
*			definition 1								*				
*	during an iterationa black pt is an s-open point if at least one s_point		*
*	of N(p) is white before	the iteration							*
************************************************************************************************/				

int Is_sopen_pt(int ***matrix, int i, int j, int k, int thr) /*return 1 when the pt is a sopen pt*/
{
	if(matrix[i-1][j][k] < thr || matrix[i+1][j][k] < thr || matrix[i][j-1][k] < thr || 
	   matrix[i][j+1][k] < thr || matrix[i][j][k-1] < thr || matrix[i][j][k+1] < thr)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}


/************************************************************************************************
*			definition 2								*
*	during an iteration a black point is an e-open point if p is not a s-open point and 	*
*	an e-point e(a,b,p) is white while the points f1(a,p), f1(b,p) are black b4 the 	*
* 	iteration										*
************************************************************************************************/
int Is_eopen_pt(int ***matrix, int i, int j, int k, int thr)
{
	if(Is_sopen_pt(matrix, i, j, k, thr)==0)
	{
		if(matrix[i+1][j+1][k] <thr && matrix[i+2][j][k] >=thr && matrix[i][j+2][k] >=thr) 
		{
			return 1;
		}
		else if(matrix[i+1][j-1][k] <thr && matrix[i+2][j][k] >=thr && matrix[i][j-2][k] >=thr) 
		{
			return 1;
		}
		else if(matrix[i-1][j+1][k] <thr && matrix[i-2][j][k] >=thr && matrix[i][j+2][k] >=thr) 
		{
			return 1;
		}
		else if(matrix[i-1][j-1][k] <thr && matrix[i-2][j][k] >=thr && matrix[i][j-2][k] >=thr) 
		{
			return 1;
		}
		else if(matrix[i+1][j][k+1] <thr && matrix[i+2][j][k] >=thr && matrix[i][j][k+2] >=thr) 
		{
			return 1;
		}
		else if(matrix[i+1][j][k-1] <thr && matrix[i+2][j][k] >=thr && matrix[i][j][k-2]>=thr) 
		{
			return 1;
		}
		else if(matrix[i-1][j][k+1] <thr && matrix[i-2][j][k] >=thr && matrix[i][j][k+2]>=thr) 
		{
			return 1;
		}
		else if(matrix[i-1][j][k-1] <thr && matrix[i-2][j][k] >=thr && matrix[i][j][k-2] >=thr) 
		{
			return 1;
		}
		else if(matrix[i][j+1][k+1] <thr && matrix[i][j+2][k] >=thr && matrix[i][j][k+2] >=thr) 
		{
			return 1;
		}
		else if(matrix[i][j+1][k-1] <thr && matrix[i][j+2][k] >=thr && matrix[i][j][k-2] >=thr) 
		{
			return 1;
		}
		else if(matrix[i][j-1][k+1] <thr && matrix[i][j-2][k] >=thr && matrix[i][j][k+2] >=thr) 
		{
			return 1;
		}
		else if(matrix[i][j-1][k-1] <thr && matrix[i][j-2][k] >=thr && matrix[i][j][k-2] >=thr) 
		{
			return 1;
		}
		else 
			return 0;
	}
	else
		return 0;
}

/************************************************************************************************
*			definition 3								*
*	during an iteration a black pt p is a v_open pt if p is neither an s_open pt nor an	*
*	e_open pt and a v-pt v(a,b,c,p) is white while the points f1(a,p), f1(b,p), f1(c,p)	*
*	are black before the iteration								*
************************************************************************************************/
int Is_vopen_pt(int ***matrix, int i, int j, int k, int thr)
{
	if(Is_sopen_pt(matrix, i, j, k, thr)==0 && Is_eopen_pt(matrix, i, j, k, thr)==0)
	{
		if(matrix[i+1][j+1][k+1] <thr && matrix[i+2][j][k] >=thr && 
			matrix[i][j+2][k] >=thr && matrix[i][j][k+2] >=thr) 
			return 1;
		else if(matrix[i+1][j+1][k-1] <thr && matrix[i+2][j][k] >=thr && 
			matrix[i][j+2][k] >=thr && matrix[i][j][k-2] >=thr) 
			return 1;
		else if(matrix[i+1][j-1][k+1] <thr && matrix[i+2][j][k] >=thr && 
			matrix[i][j-2][k] >=thr && matrix[i][j][k+2] >=thr) 
			return 1;
		else if(matrix[i+1][j-1][k-1] <thr && matrix[i+2][j][k] >=thr && 
			matrix[i][j-2][k] >=thr && matrix[i][j][k-2] >=thr) 
			return 1;
		else if(matrix[i-1][j+1][k+1] <thr && matrix[i-2][j][k] >=thr && 
			matrix[i][j+2][k] >=thr && matrix[i][j][k+2] >=thr) 
			return 1;
		else if(matrix[i-1][j+1][k-1] <thr && matrix[i-2][j][k] >=thr && 
			matrix[i][j+2][k] >=thr && matrix[i][j][k-2] >=thr) 
			return 1;
		else if(matrix[i-1][j-1][k+1] <thr && matrix[i-2][j][k] >=thr && 
			matrix[i][j-2][k] >=thr && matrix[i][j][k+2] >=thr) 
			return 1;
		else if(matrix[i-1][j-1][k-1] <thr && matrix[i-2][j][k] >=thr && 
			matrix[i][j-2][k] >=thr && matrix[i][j][k-2] >=thr) 
			return 1;
		else 
			return 0;
	}
	else 
		return 0;
}


