#include "stdafx.h"
#include "Arc_Thinning.h"

/************************************************************************************************
*			definition 7								*				
*	during an iterationa black pt is an s-open-surface point if the points a , e(a,b,p), b,		*
*	e(b,d,p), d are all white before the iteration							*
************************************************************************************************/				

int Is_sopen_surface_pt(int ***matrix, int i, int j, int k, int thr)	/*return 1 when the pt is a s_open_surface pt*/
{
	if(matrix[i-1][j][k] < thr && matrix[i-1][j-1][k] < thr && matrix[i][j-1][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i+1][j][k] < thr)
		return 1;

	else if(matrix[i][j-1][k] < thr && matrix[i+1][j-1][k] < thr && matrix[i+1][j][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i][j+1][k] < thr)
		return 1;
	
	else if(matrix[i+1][j][k] < thr && matrix[i+1][j+1][k] < thr && matrix[i][j+1][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr)
		return 1;

	else if(matrix[i][j+1][k] < thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr && matrix[i-1][j-1][k] < thr && matrix[i][j-1][k] < thr)
		return 1;

	else if(matrix[i][j-1][k] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j][k+1] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+1][k] < thr)
		return 1;

	else if(matrix[i][j][k+1] < thr && matrix[i][j+1][k+1] < thr && matrix[i][j+1][k] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j][k-1] < thr)
		return 1;

	else if(matrix[i][j+1][k] < thr && matrix[i][j+1][k-1] < thr && matrix[i][j][k-1] < thr && matrix[i][j-1][k-1] < thr && matrix[i][j-1][k] < thr)
		return 1;

	else if(matrix[i][j][k-1] < thr && matrix[i][j-1][k-1] < thr && matrix[i][j-1][k] < thr && matrix[i][j-1][k+1] < thr && matrix[i][j][k+1] < thr)
		return 1;

	else if(matrix[i][j][k-1] < thr && matrix[i-1][j][k-1] < thr && matrix[i-1][j][k] < thr && matrix[i-1][j][k+1] < thr && matrix[i][j][k+1] < thr)
		return 1;

	else if(matrix[i-1][j][k] < thr && matrix[i-1][j][k+1] < thr && matrix[i][j][k+1] < thr && matrix[i+1][j][k+1] < thr && matrix[i+1][j][k] < thr)
		return 1;

	else if(matrix[i][j][k+1] < thr && matrix[i+1][j][k+1] < thr && matrix[i+1][j][k] < thr && matrix[i+1][j][k-1] < thr && matrix[i][j][k-1] < thr)
		return 1;

	else if(matrix[i+1][j][k] < thr && matrix[i+1][j][k-1] < thr && matrix[i][j][k-1] < thr && matrix[i-1][j][k-1] < thr && matrix[i-1][j][k] < thr)
		return 1;

	else
		return 0;

}


/************************************************************************************************
*			definition 8								*
*	during an iteration a point p is an e-open-surface point if it is not an s-open-surface point
*   and at least one point from each sets {a}, {e(a,b,p), e(a,c,p)}, {v(a,b,c,p)}, {e(b,c,p)},
*   {v(b,c,d,p)}, {e(b,d,p), e(c,d,p)}, {d} is white while each of the sets {f2(a,b,p)}, f3(a,b,p),
*   f2(b,a,p), f1(b,p), f2(b,d,p), f3(b,d,p), f2(d,b,p)} and {f2(a,c,p), f3(a,c,p), f2(c,a,p), f1(c,p),
*   f2(c,d,p), f3(c,d,p), f2(d,c,p)} contains at least one black point before the iteration.
************************************************************************************************/
int Is_eopen_surface_pt(int ***matrix, int i, int j, int k, int thr)
{
	if(!Is_sopen_surface_pt(matrix, i, j, k, thr))
	{
		/*********************************************************************************/
		if((matrix[i-1][j][k] < thr && matrix[i-1][j-1][k+1] < thr && matrix[i][j-1][k+1] < thr && 
		   matrix[i+1][j-1][k+1] < thr && matrix[i+1][j][k] < thr &&
		   (matrix[i-1][j-1][k] < thr || matrix[i-1][j][k+1] < thr) && (matrix[i+1][j-1][k] < thr || matrix[i+1][j][k+1] <thr)) &&
			
		  (matrix[i-2][j-1][k] >= thr || matrix[i-2][j-2][k] >= thr || matrix[i-1][j-2][k] >= thr ||
		   matrix[i][j-2][k] >= thr || matrix[i+1][j-2][k] >= thr || matrix[i+2][j-2][k] >= thr || matrix[i+2][j-1][k] >= thr) &&
			   
		  (matrix[i-2][j][k+1] >= thr || matrix[i-2][j][k+2] >= thr || matrix[i-1][j][k+2] >= thr || 
		   matrix[i][j][k+2] >= thr || matrix[i+1][j][k+2] >= thr || matrix[i+2][j][k+2] >= thr || matrix[i+2][j][k+1] >= thr))
				  
				  return 1;
		/*********************************************************************************/
		else if((matrix[i-1][j][k] < thr && matrix[i-1][j+1][k+1] < thr && matrix[i][j+1][k+1] < thr && 
				matrix[i+1][j+1][k+1] < thr && matrix[i+1][j][k] < thr &&
				(matrix[i-1][j+1][k] < thr || matrix[i-1][j][k+1] < thr) && (matrix[i+1][j+1][k] < thr || matrix[i+1][j][k+1] < thr)) &&
			
				(matrix[i-2][j+1][k] >= thr || matrix[i-2][j+2][k] >= thr || matrix[i-1][j+2][k] >= thr ||
				 matrix[i][j+2][k] >= thr || matrix[i+1][j+2][k] >= thr || matrix[i+2][j+2][k] >= thr || matrix[i+2][j+1][k] >= thr) &&
			   
				(matrix[i-2][j][k+1] >= thr || matrix[i-2][j][k+2] >= thr || matrix[i-1][j][k+2] >= thr || 
				 matrix[i][j][k+2] >= thr || matrix[i+1][j][k+2] >= thr || matrix[i+2][j][k+2] >= thr || matrix[i+2][j][k+1] >= thr))
				  
				  return 1;
		/*********************************************************************************/
		else if((matrix[i-1][j][k] < thr && matrix[i-1][j+1][k-1] < thr && matrix[i][j+1][k-1] < thr && 
				matrix[i+1][j+1][k-1] < thr && matrix[i+1][j][k] < thr &&
				(matrix[i+1][j+1][k] < thr || matrix[i+1][j][k-1] < thr) && (matrix[i-1][j+1][k] < thr || matrix[i-1][j][k-1] < thr)) &&
			
				(matrix[i-2][j+1][k] >= thr || matrix[i-2][j+2][k] >= thr || matrix[i-1][j+2][k] >= thr ||
			     matrix[i][j+2][k] >= thr || matrix[i+1][j+2][k] >= thr || matrix[i+2][j+2][k] >= thr || matrix[i+2][j+1][k] >= thr) &&
			   
				(matrix[i-2][j][k-1] >= thr || matrix[i-2][j][k-2] >= thr || matrix[i-1][j][k-2] >= thr || 
				 matrix[i][j][k-2] >= thr || matrix[i+1][j][k-2] >= thr || matrix[i+2][j][k-2] >= thr || matrix[i+2][j][k-1] >= thr))
				  
				  return 1;
		/*********************************************************************************/
		else if((matrix[i-1][j][k] < thr && matrix[i-1][j-1][k-1] < thr && matrix[i][j-1][k-1] < thr && 
				matrix[i+1][j-1][k-1] < thr && matrix[i+1][j][k] < thr &&
				(matrix[i-1][j-1][k] < thr || matrix[i-1][j][k-1] < thr) && (matrix[i+1][j][k-1] < thr || matrix[i+1][j-1][k] < thr)) &&
			
				(matrix[i-2][j-1][k] >= thr || matrix[i-2][j-2][k] >= thr || matrix[i-1][j-2][k] >= thr ||
			     matrix[i][j-2][k] >= thr || matrix[i+1][j-2][k] >= thr || matrix[i+2][j-2][k] >= thr || matrix[i+2][j-1][k] >= thr) &&
			   
			    (matrix[i-2][j][k-1] >= thr || matrix[i-2][j][k-2] >= thr || matrix[i-1][j][k-2] >= thr || 
				 matrix[i][j][k-2] >= thr || matrix[i+1][j][k-2] >= thr || matrix[i+2][j][k-2] >= thr || matrix[i+2][j][k-1] >= thr))
				  
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j][k+1] < thr && matrix[i-1][j-1][k+1] < thr && matrix[i-1][j-1][k] < thr && 
				matrix[i-1][j-1][k-1] < thr && matrix[i][j][k-1] < thr &&
				(matrix[i-1][j][k+1] < thr || matrix[i][j-1][k+1] < thr) && (matrix[i-1][j][k-1] < thr || matrix[i][j-1][k-1] < thr)) &&
			
				(matrix[i-1][j][k+2] >= thr || matrix[i-2][j][k+2] >= thr || matrix[i-2][j][k+1] >= thr ||
				 matrix[i-2][j][k] >= thr || matrix[i-2][j][k-1] >= thr || matrix[i-2][j][k-2] >= thr || matrix[i-1][j][k-2] >= thr) &&
			   
			    (matrix[i][j-1][k+2] >= thr || matrix[i][j-2][k+2] >= thr || matrix[i][j-2][k+1] >= thr || 
				 matrix[i][j-2][k] >= thr || matrix[i][j-2][k-1] >= thr || matrix[i][j-2][k-2] >= thr || matrix[i][j-1][k-2] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j][k+1] < thr && matrix[i+1][j-1][k+1] < thr && matrix[i+1][j-1][k] < thr && 
				matrix[i+1][j-1][k-1] < thr && matrix[i][j][k-1] < thr &&
				(matrix[i+1][j][k+1] < thr || matrix[i][j-1][k+1] < thr) && (matrix[i+1][j][k-1] < thr || matrix[i][j-1][k-1] < thr)) &&
			
				(matrix[i+1][j][k+2] >= thr || matrix[i+2][j][k+2] >= thr || matrix[i+2][j][k+1] >= thr ||
				 matrix[i+2][j][k] >= thr || matrix[i+2][j][k-1] >= thr || matrix[i+2][j][k-2] >= thr || matrix[i+1][j][k-2] >= thr) &&
			   
			    (matrix[i][j-1][k+2] >= thr || matrix[i][j-2][k+2] >= thr || matrix[i][j-2][k+1] >= thr || 
				 matrix[i][j-2][k] >= thr || matrix[i][j-2][k-1] >= thr || matrix[i][j-2][k-2] >= thr || matrix[i][j-1][k-2] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j][k+1] < thr && matrix[i+1][j+1][k+1] < thr && matrix[i+1][j+1][k] < thr && 
				matrix[i+1][j+1][k-1] < thr && matrix[i][j][k-1] < thr &&
				(matrix[i+1][j][k+1] < thr || matrix[i][j+1][k+1] < thr) && (matrix[i+1][j][k-1] < thr || matrix[i][j+1][k-1] < thr)) &&
			
		        (matrix[i+1][j][k+2] >= thr || matrix[i+2][j][k+2] >= thr || matrix[i+2][j][k+1] >= thr ||
			     matrix[i+2][j][k] >= thr || matrix[i+2][j][k-1] >= thr || matrix[i+2][j][k-2] >= thr || matrix[i+1][j][k-2] >= thr) &&
			   
			    (matrix[i][j+1][k+2] >= thr || matrix[i][j+2][k+2] >= thr || matrix[i][j+2][k+1] >= thr || 
				 matrix[i][j+2][k] >= thr || matrix[i][j+2][k-1] >= thr || matrix[i][j+2][k-2] >= thr || matrix[i][j+1][k-2] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j][k+1] < thr && matrix[i-1][j+1][k+1] < thr && matrix[i-1][j+1][k] < thr && 
				matrix[i-1][j+1][k-1] < thr && matrix[i][j][k-1] < thr &&
				(matrix[i-1][j][k+1] < thr || matrix[i][j+1][k+1] < thr) && (matrix[i-1][j][k-1] < thr || matrix[i][j+1][k-1] < thr)) &&
			
		        (matrix[i-1][j][k+2] >= thr || matrix[i-2][j][k+2] >= thr || matrix[i-2][j][k+1] >= thr ||
			     matrix[i-2][j][k] >= thr || matrix[i-2][j][k-1] >= thr || matrix[i-2][j][k-2] >= thr || matrix[i-1][j][k-2] >= thr) &&
			   
			    (matrix[i][j+1][k+2] >= thr || matrix[i][j+2][k+2] >= thr || matrix[i][j+2][k+1] >= thr || 
				 matrix[i][j+2][k] >= thr || matrix[i][j+2][k-1] >= thr || matrix[i][j+2][k-2] >= thr || matrix[i][j+1][k-2] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j-1][k] < thr && matrix[i-1][j-1][k+1] < thr && matrix[i-1][j][k+1] < thr && 
				matrix[i-1][j+1][k+1] < thr && matrix[i][j+1][k] < thr &&
				(matrix[i-1][j-1][k] < thr || matrix[i][j-1][k+1] < thr) && (matrix[i-1][j+1][k] < thr || matrix[i][j+1][k+1] < thr)) &&
			
		        (matrix[i-1][j-2][k] >= thr || matrix[i-2][j-2][k] >= thr || matrix[i-2][j-1][k] >= thr ||
			     matrix[i-2][j][k] >= thr || matrix[i-2][j+1][k] >= thr || matrix[i-2][j+2][k] >= thr || matrix[i-1][j+2][k] >= thr) &&
			   
			    (matrix[i][j-2][k+1] >= thr || matrix[i][j-2][k+2] >= thr || matrix[i][j-1][k+2] >= thr || 
				 matrix[i][j][k+2] >= thr || matrix[i][j+1][k+2] >= thr || matrix[i][j+2][k+2] >= thr || matrix[i][j+2][k+1] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j-1][k] < thr && matrix[i+1][j-1][k+1] < thr && matrix[i+1][j][k+1] < thr && 
				matrix[i+1][j+1][k+1] < thr && matrix[i][j+1][k] < thr &&
				(matrix[i+1][j-1][k] < thr || matrix[i][j-1][k+1] < thr) && (matrix[i+1][j+1][k] < thr || matrix[i][j+1][k+1] < thr)) &&
			
				(matrix[i+1][j-2][k] >= thr || matrix[i+2][j-2][k] >= thr || matrix[i+2][j-1][k] >= thr ||
			     matrix[i+2][j][k] >= thr || matrix[i+2][j+1][k] >= thr || matrix[i+2][j+2][k] >= thr || matrix[i+1][j+2][k] >= thr) &&
			   
			    (matrix[i][j-2][k+1] >= thr || matrix[i][j-2][k+2] >= thr || matrix[i][j-1][k+2] >= thr || 
				 matrix[i][j][k+2] >= thr || matrix[i][j+1][k+2] >= thr || matrix[i][j+2][k+2] >= thr || matrix[i][j+2][k+1] >= thr))
			
				  return 1;
		/*********************************************************************************///
		else if((matrix[i][j-1][k] < thr && matrix[i+1][j-1][k-1] < thr && matrix[i+1][j][k-1] < thr && 
				matrix[i+1][j+1][k-1] < thr && matrix[i][j+1][k] < thr &&
				(matrix[i+1][j-1][k] < thr || matrix[i][j-1][k-1] < thr) && (matrix[i+1][j+1][k] < thr || matrix[i][j+1][k-1] < thr)) &&
			
		        (matrix[i+1][j-2][k] >= thr || matrix[i+2][j-2][k] >= thr || matrix[i+2][j-1][k] >= thr ||
			     matrix[i+2][j][k] >= thr || matrix[i+2][j+1][k] >= thr || matrix[i+2][j+2][k] >= thr || matrix[i+1][j+2][k] >= thr) &&
			   
			    (matrix[i][j-2][k-1] >= thr || matrix[i][j-2][k-2] >= thr || matrix[i][j-1][k-2] >= thr || 
				 matrix[i][j][k-2] >= thr || matrix[i][j+1][k-2] >= thr || matrix[i][j+2][k-2] >= thr || matrix[i][j+2][k-1] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else if((matrix[i][j-1][k] < thr && matrix[i-1][j-1][k-1] < thr && matrix[i-1][j][k-1] < thr && 
				matrix[i-1][j+1][k-1] < thr && matrix[i][j+1][k] < thr &&
				(matrix[i-1][j-1][k] < thr || matrix[i][j-1][k-1] < thr) && (matrix[i-1][j+1][k] < thr || matrix[i][j+1][k-1] < thr)) &&
			
				(matrix[i-1][j-2][k] >= thr || matrix[i-2][j-2][k] >= thr || matrix[i-2][j-1][k] >= thr ||
			     matrix[i-2][j][k] >= thr || matrix[i-2][j+1][k] >= thr || matrix[i-2][j+2][k] >= thr || matrix[i-1][j+2][k] >= thr) &&
			   
			    (matrix[i][j-2][k-1] >= thr || matrix[i][j-2][k-2] >= thr || matrix[i][j-1][k-2] >= thr || 
				 matrix[i][j][k-2] >= thr || matrix[i][j+1][k-2] >= thr || matrix[i][j+2][k-2] >= thr || matrix[i][j+2][k-1] >= thr))
			
				  return 1;
		/*********************************************************************************/
		else
			return 0;
	}
	else
		return 0;
	
}

/************************************************************************************************
*			definition 9								*
*	A black point is an arc-shape point if it satisfies Condition 1							*
************************************************************************************************/
int Arc_Shape_Point(int ***matrix, int i, int j, int k, int thr) /*return 1 when it's an arc shape point, return 0 when it's not a shape pt*/
{
	/***************condition 1*********************************************************************************
	* if there exist two opposite s-points a,d =N(p) such that EM(a,d,p) contains a 6-closed path of white pts *
	*encircling p and each of surface(a,p) and surface(d,p) contains at least one black pt b4 the iteration    *
	*surface(a,p) is the surface k+1, surface(d,p) is the surface k-1					   *
	***********************************************************************************************************/
//group 1, 1
	if(matrix[i+1][j+1][k] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j-1][k] <thr && matrix[i][j+1][k] <thr && matrix[i-1][j+1][k] <thr && 
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
	} 
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


/*	if(matrix[i+1][j+1][k] <thr && matrix[i+1][j][k] <thr && matrix[i+1][j-1][k] <thr && matrix[i][j+1][k] <thr && matrix[i][j-1][k] <thr && matrix[i-1][j+1][k] < thr && matrix[i-1][j][k] < thr && matrix[i-1][j-1][k] < thr && 
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
		return 1;*/

	return 0;
}

/************************************************************************************************
*			definition 10								*
*	A black point is an arc-erodable point if: (i) every middle plane of N(p) contains at least
*	one currently black point, and (ii) p is a simple point							*
************************************************************************************************/

/*in arc_erodable_point, only check (i)*/
int Arc_Erodable_Point(int ***matrix, int i, int j, int k) /*return 1 when it's an arc shape-erodable-point, return 0 when it's not a shape pt*/
{
	if((matrix[i-1][j-1][k] >= 0 || matrix[i-1][j][k] >= 0 || matrix[i-1][j+1][k] >=0 || matrix[i][j-1][k] >=0 || 
	   matrix[i][j+1][k] >=0 || matrix[i+1][j-1][k] >=0 || matrix[i+1][j][k] >=0 || matrix[i+1][j+1][k] >=0) &&
		
	   (matrix[i][j-1][k-1] >= 0 || matrix[i][j-1][k] >= 0 || matrix[i][j-1][k+1] >=0 || matrix[i][j][k-1] >=0 || 
		matrix[i][j][k+1] >=0 || matrix[i][j+1][k-1] >=0 || matrix[i][j+1][k] >=0 || matrix[i][j+1][k+1] >=0) &&
			
	   (matrix[i-1][j][k-1] >= 0 || matrix[i-1][j][k] >= 0 || matrix[i-1][j][k+1] >=0 || matrix[i][j][k-1] >=0 || 
		matrix[i][j][k+1] >=0 || matrix[i+1][j][k-1] >=0 || matrix[i+1][j][k] >=0 || matrix[i+1][j][k+1] >=0))
				
		return 1;
	else 
		return 0;

}

