#include "stdafx.h"
#include "Final_Thinning.h"
#include "Simple_Point.h"

int Is_single_26(int ***temp) /*by deciding if it's NOT 26 connected for plane axis_k (current iteration)*/
{
	int temp2[3][3][3];
	int i,j,k;

	for(i=0; i<=2; i++)
	{
		for(j=0; j<=2; j++)
		{
			for(k=0; k<=2; k++)
			{
				if(temp[i][j][k]>=0)
					temp2[i][j][k] = 1;
				else 
					temp2[i][j][k] = 0;
			}
		}
	}

	if(temp2[0][1][1]+temp2[1][2][1]+temp2[2][1][1]+temp2[1][0][1] == 4)	//create tunnel
		return 0;
	
	else if(temp2[0][1][1]+temp2[1][2][1]+temp2[2][1][1]+temp2[1][0][1] == 3)
		return 1;

	else if(temp2[0][1][1]+temp2[1][2][1]+temp2[2][1][1]+temp2[1][0][1] == 2)
	{
		if(temp2[0][1][1]+temp2[1][2][1] == 2)
		{
			if(temp2[2][0][1]!=1)
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[1][2][1]+temp2[2][1][1] == 2)
		{
			if(temp2[0][0][1]!=1)
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[2][1][1]+temp2[1][0][1] == 2)
		{
			if(temp2[0][2][1]!=1)
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[1][0][1]+temp2[0][1][1] == 2)
		{
			if(temp2[2][2][1]!=1)
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp[0][1][1]+temp[2][1][1] == 2)
			return 0;
		else if(temp[1][0][1]+temp[1][2][1] == 2)
			return 0;
		else
			return 0;
	}

	else if(temp2[0][1][1]+temp2[1][2][1]+temp2[2][1][1]+temp2[1][0][1] == 1)
	{
		if(temp2[0][1][1]==1)
		{
			if((temp2[2][0][1]!=1) && (temp2[2][2][1]!=1))
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[1][2][1]==1)
		{
			if((temp2[0][0][1]!=1) && (temp2[2][0][1]!=1))      //////////////////////////////////////////////////11-16-2005
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[2][1][1]==1)
		{
			if((temp2[0][0][1]!=1) && (temp2[0][2][1]!=1))
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else if(temp2[1][0][1]==1)
		{
			if((temp2[0][2][1]!=1) && (temp2[2][2][1]!=1))
				return 1;
			else
				return 0;		//not single 26-component in M(a,d,p)
		}
		else 
			return 0;
	}
	else if(temp2[0][1][1]+temp2[1][2][1]+temp2[2][1][1]+temp2[1][0][1] == 0)
	{
		if(temp2[0][0][1]+temp2[0][2][1]+temp2[2][2][1]+temp2[2][0][1] <= 1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}



/************************************************************************************************
*			thick(a,d,p)								*
*	thick(a,d,p)=1 if a is white while b,c,d are black b4 iteration				*
*	and also ///f1(d,p) are white b4 iteration///							*
*	which means p has at least 3 black non-opposite s-points				*
*   only for before iteration																*
************************************************************************************************/
int thick(int ***temp, int thr)   
{
	if(temp[1][1][2]<thr && (temp[2][1][1]>=thr || temp[0][1][1]>=thr) && (temp[1][2][1]>=thr || temp[1][0][1]>=thr) && 
		(temp[1][1][0]>=thr)) 
		return 1;
	else 
		return 0;
}

/****************************************************************************************
*			condition 3							*
*	during an iteration a point p satisfies condition 3 if each middle plane 	*
*	M(a,d,p) of N(p) holds that -- either all e-points in M(a,d,p) are black	*
*	b4 the iteration or the current black points of M(a,d,p) generate single 	*
*	26-component without any tunnel	.						*
*	the black points of the middle plane M(a,d,p) generate a tunnel if and only	*
*	if all the s-points of N(p) belonging to M(a,d,p) are currently black		*
****************************************************************************************/

int Is_cond3(int ***matrix, int ***temp, int i, int j, int k, int thr)
{
	int mid_k, mid_i, mid_j;
	mid_k=0; mid_i=0; mid_j=0; 

	int a,b,c;
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
				temp[a][b][c] = matrix[i-1+a][j-1+b][k-1+c];
	
	if((temp[2][2][1]>=thr && temp[2][0][1]>=thr && temp[0][2][1]>=thr && temp[0][0][1]>=thr) || Is_single_26(temp)==1 ) 
		mid_k = 1; 
	else 
		mid_k = 0;

	axis_j_90(temp);
	if((temp[2][2][1]>=thr && temp[2][0][1]>=thr && temp[0][2][1]>=thr && temp[0][0][1]>=thr) || Is_single_26(temp)==1 ) 
		mid_i = 1; 
	else
		mid_i = 0;

	axis_i_90(temp);
	if((temp[2][2][1]>=thr && temp[2][0][1]>=thr && temp[0][2][1]>=thr && temp[0][0][1]>=thr) || Is_single_26(temp)==1 ) 
		mid_j = 1; 
	else 
		mid_j = 0;

	if(mid_k==1 && mid_i==1 && mid_j==1) 
		return 1;
	else 
		return 0;
}

/************************************************************************************************
*			condition 4								*
*	a point P satisfies condition 4 if thick (a,d,p) where d<{Pb,Ps,Pw}, is true		*
*	and also f1(d,p) is white before iteration						*
*	and the current black points of each of M(b,e,p) and M(c,f,p) generate single		*
*	26-component without any tunnel								*
*	tunnel are generate if all s-point of M are currently black				*
************************************************************************************************/
int Is_cond4(int ***matrix, int ***temp, int i, int j, int k, int thr)
{
	int mid_ad, mid_be, mid_cf;
	int thick_ad, thick_be, thick_cf, thick_da, thick_eb, thick_fc;
	thick_ad = thick_be = thick_cf = thick_da = thick_eb = thick_fc = 0;
	mid_ad = mid_be = mid_cf = 0;

	int a,b,c;
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
				temp[a][b][c] = matrix[i-1+a][j-1+b][k-1+c];

	//for a,d = Pt, Pb, opposite s-point in k-axis
	if(thick(temp, thr)==1 && matrix[i][j][k-2] < thr) 
		thick_ad = 1;

	//for a,d = Pt, Pb, opposite s-point in k-axis
	axis_i_90(temp);
	axis_i_90(temp);
	
	if(thick(temp, thr)==1 && matrix[i][j][k+2] < thr) 
		thick_da = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j-2][k] < thr)
		thick_be = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j+2][k] < thr)
		thick_eb = 1;

	axis_i_90(temp); 
	axis_i_90(temp); 
	axis_i_90(temp); 

	/*for opposite s-point in i-axis*/
	axis_j_90(temp);

	if(thick(temp, thr)==1 && matrix[i-2][j][k] < thr)
		thick_cf = 1;


	/*for opposite s-point in i-axis*/
	axis_j_90(temp); 
	axis_j_90(temp); 

	if(thick(temp, thr)==1 && matrix[i+2][j][k] < thr)
		thick_fc = 1;

	axis_j_90(temp); 

	//for ad middle plate
	if(Is_single_26(temp)==1) 
		mid_ad=1;

	//for be middle plate
	axis_i_90(temp); 
	if(Is_single_26(temp)==1) 
		mid_be=1;

	//for cf middle plate
	axis_j_90(temp); 
	if(Is_single_26(temp)==1) 
		mid_cf=1;
	
	if((thick_ad == 1 || thick_da == 1) && (mid_be == 1 && mid_cf == 1))
		return 1;
	else if((thick_be == 1 || thick_eb == 1) && (mid_ad == 1 && mid_cf == 1))
		return 1;
	else if((thick_cf == 1 || thick_fc == 1) && (mid_ad == 1 && mid_be == 1))
		return 1;
	else
		return 0;
}

/************************************************************************************************
*	cond 5											*
*	a point p satisfies cond 5 if thick(a,d,p), thick(b,e,p) where d,e<{Pb,Ps,Pw} are true	*
*	and the current black points of M(c,f,p) generate single 26 component without		*
*	any tunnel (currently black)								*
************************************************************************************************/
int Is_cond5(int ***matrix, int ***temp, int i, int j, int k, int thr)
{
	int thick_ad, thick_be, thick_cf, thick_da, thick_eb, thick_fc;
	int mid_be=0;
	int mid_cf=0;
	int mid_ad=0;

	thick_ad=0; thick_be=0; thick_cf=0;
	thick_da=0; thick_eb=0; thick_fc=0;


	int a,b,c;
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
				temp[a][b][c] = matrix[i-1+a][j-1+b][k-1+c];

	
	//for a,d = Pt, Pb, opposite s-point in k-axis
	if(thick(temp, thr)==1 && matrix[i][j][k-2] < thr) 
		thick_ad = 1;

	//for a,d = Pt, Pb, opposite s-point in k-axis
	axis_i_90(temp);
	axis_i_90(temp);
	
	if(thick(temp, thr)==1 && matrix[i][j][k+2] < thr) 
		thick_da = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j-2][k] < thr)
		thick_be = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j+2][k] < thr)
		thick_eb = 1;

	axis_i_90(temp); 
	axis_i_90(temp); 
	axis_i_90(temp); 

	/*for opposite s-point in i-axis*/
	axis_j_90(temp);

	if(thick(temp, thr)==1 && matrix[i-2][j][k] < thr)
		thick_cf = 1;


	/*for opposite s-point in i-axis*/
	axis_j_90(temp); 
	axis_j_90(temp); 

	if(thick(temp, thr)==1 && matrix[i+2][j][k] < thr)
		thick_fc = 1;

	axis_j_90(temp); 

	//for ad middle plate
	if(Is_single_26(temp)==1) 
		mid_ad=1;

	//for be middle plate
	axis_i_90(temp); 
	if(Is_single_26(temp)==1) 
		mid_be=1;

	//for cf middle plate
	axis_j_90(temp); 
	if(Is_single_26(temp)==1) 
		mid_cf=1;

	if((thick_ad == 1 || thick_da == 1) && (thick_be == 1 || thick_eb == 1) && mid_cf==1) 
		return 1;
	
	else if((thick_ad==1 || thick_da == 1) && (thick_cf == 1 && thick_fc == 1) && mid_be==1) 
		return 1;
	
	else if((thick_be==1 || thick_eb == 1) && (thick_cf==1 || thick_fc == 1) && mid_ad==1) 
		return 1;
	
	else 
		return 0;

}


/************************************************************************************************
*	cond 6											*
*	a point p satisfies cond 6 if thick(a,d,p) thick (b,e,p) and thick(c,f,p) where 	*
*	d,e,f <{Pb,Ps,Pw} are true								*
************************************************************************************************/
int Is_cond6(int ***matrix, int ***temp, int i, int j, int k, int thr)
{
	int thick_ad, thick_be, thick_cf, thick_da, thick_eb, thick_fc;
	thick_ad=0; thick_be=0; thick_cf=0;
	thick_da=0; thick_eb=0; thick_fc=0;

	int a,b,c;
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
				temp[a][b][c] = matrix[i-1+a][j-1+b][k-1+c];

	//for a,d = Pt, Pb, opposite s-point in k-axis
	if(thick(temp, thr)==1 && matrix[i][j][k-2] < thr) 
		thick_ad = 1;

	//for a,d = Pt, Pb, opposite s-point in k-axis
	axis_i_90(temp);
	axis_i_90(temp);
	
	if(thick(temp, thr)==1 && matrix[i][j][k+2] < thr) 
		thick_da = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j-2][k] < thr)
		thick_be = 1;

	/*for opposite s-point in j-axis*/
	axis_i_90(temp); 
	axis_i_90(temp); 

	if(thick(temp, thr)==1 && matrix[i][j+2][k] < thr)
		thick_eb = 1;

	axis_i_90(temp); 
	axis_i_90(temp); 
	axis_i_90(temp); 

	/*for opposite s-point in i-axis*/
	axis_j_90(temp);

	if(thick(temp, thr)==1 && matrix[i-2][j][k] < thr)
		thick_cf = 1;


	/*for opposite s-point in i-axis*/
	axis_j_90(temp); 
	axis_j_90(temp); 

	if(thick(temp, thr)==1 && matrix[i+2][j][k] < thr)
		thick_fc = 1;


	if((thick_ad == 1 || thick_da == 1) && (thick_be == 1 || thick_eb == 1) && (thick_cf == 1 || thick_fc == 1)) 
		return 1; 

	else 
		return 0;
}

