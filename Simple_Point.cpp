#include "stdafx.h"
#include "Simple_Point.h"
#include "Look_up_tabel.h"

//for debug saha's lookup table
#define SAHA_TABLE

extern int	tab3b[16],
			tab4a[16],
			tab4b[128],
			tab5[4096],
			tab6[4096][2];

/*function to rotate the cube around axis_k by 90 degree clockwise*/
void axis_k_90(int ***temp)
{
	int temp2[3][3][3];

	temp2[2][2][2] = temp[0][2][2];
	temp2[2][1][2] = temp[1][2][2];
	temp2[2][0][2] = temp[2][2][2];
	temp2[1][2][2] = temp[0][1][2];
	temp2[1][1][2] = temp[1][1][2];
	temp2[1][0][2] = temp[2][1][2];
	temp2[0][2][2] = temp[0][0][2];
	temp2[0][1][2] = temp[1][0][2];
	temp2[0][0][2] = temp[2][0][2];

	temp2[2][2][1] = temp[0][2][1];
	temp2[2][1][1] = temp[1][2][1];
	temp2[2][0][1] = temp[2][2][1];
	temp2[1][2][1] = temp[0][1][1];
	temp2[1][1][1] = temp[1][1][1];
	temp2[1][0][1] = temp[2][1][1];
	temp2[0][2][1] = temp[0][0][1];
	temp2[0][1][1] = temp[1][0][1];
	temp2[0][0][1] = temp[2][0][1];

	temp2[2][2][0] = temp[0][2][0];
	temp2[2][1][0] = temp[1][2][0];
	temp2[2][0][0] = temp[2][2][0];
	temp2[1][2][0] = temp[0][1][0];
	temp2[1][1][0] = temp[1][1][0];
	temp2[1][0][0] = temp[2][1][0];
	temp2[0][2][0] = temp[0][0][0];
	temp2[0][1][0] = temp[1][0][0];
	temp2[0][0][0] = temp[2][0][0];

	/******************************************************/

	temp[2][2][2] =	temp2[2][2][2];
	temp[2][1][2] =	temp2[2][1][2];
	temp[2][0][2] =	temp2[2][0][2];
	temp[1][2][2] =	temp2[1][2][2];
	temp[1][1][2] =	temp2[1][1][2];
	temp[1][0][2] =	temp2[1][0][2];
	temp[0][2][2] =	temp2[0][2][2];
	temp[0][1][2] =	temp2[0][1][2];
	temp[0][0][2] =	temp2[0][0][2];

	temp[2][2][1] =	temp2[2][2][1];
	temp[2][1][1] =	temp2[2][1][1];
	temp[2][0][1] =	temp2[2][0][1];
	temp[1][2][1] =	temp2[1][2][1];
	temp[1][1][1] =	temp2[1][1][1];
	temp[1][0][1] =	temp2[1][0][1];
	temp[0][2][1] =	temp2[0][2][1];
	temp[0][1][1] =	temp2[0][1][1];
	temp[0][0][1] =	temp2[0][0][1];

	temp[2][2][0] =	temp2[2][2][0];
	temp[2][1][0] =	temp2[2][1][0];
	temp[2][0][0] =	temp2[2][0][0];
	temp[1][2][0] =	temp2[1][2][0];
	temp[1][1][0] =	temp2[1][1][0];
	temp[1][0][0] =	temp2[1][0][0];
	temp[0][2][0] =	temp2[0][2][0];
	temp[0][1][0] =	temp2[0][1][0];
	temp[0][0][0] =	temp2[0][0][0];
}

void axis_j_90(int ***temp)
{ /*clock-wise*/
	int temp2[3][3][3];

	temp2[2][2][2] = temp[2][2][0];
	temp2[2][2][1] = temp[1][2][0];
	temp2[2][2][0] = temp[0][2][0];
	temp2[1][2][2] = temp[2][2][1];
	temp2[1][2][1] = temp[1][2][1];
	temp2[1][2][0] = temp[0][2][1];
	temp2[0][2][2] = temp[2][2][2];
	temp2[0][2][1] = temp[1][2][2];
	temp2[0][2][0] = temp[0][2][2];

	temp2[2][1][2] = temp[2][1][0];
	temp2[2][1][1] = temp[1][1][0];
	temp2[2][1][0] = temp[0][1][0];
	temp2[1][1][2] = temp[2][1][1];
	temp2[1][1][1] = temp[1][1][1];
	temp2[1][1][0] = temp[0][1][1];
	temp2[0][1][2] = temp[2][1][2];
	temp2[0][1][1] = temp[1][1][2];
	temp2[0][1][0] = temp[0][1][2];

	temp2[2][0][2] = temp[2][0][0];
	temp2[2][0][1] = temp[1][0][0];
	temp2[2][0][0] = temp[0][0][0];
	temp2[1][0][2] = temp[2][0][1];
	temp2[1][0][1] = temp[1][0][1];
	temp2[1][0][0] = temp[0][0][1];
	temp2[0][0][2] = temp[2][0][2];
	temp2[0][0][1] = temp[1][0][2];
	temp2[0][0][0] = temp[0][0][2];
		
	/******************************************************/

	temp[2][2][2] =	temp2[2][2][2];
	temp[2][1][2] =	temp2[2][1][2];
	temp[2][0][2] =	temp2[2][0][2];
	temp[1][2][2] =	temp2[1][2][2];
	temp[1][1][2] =	temp2[1][1][2];
	temp[1][0][2] =	temp2[1][0][2];
	temp[0][2][2] =	temp2[0][2][2];
	temp[0][1][2] =	temp2[0][1][2];
	temp[0][0][2] =	temp2[0][0][2];

	temp[2][2][1] =	temp2[2][2][1];
	temp[2][1][1] =	temp2[2][1][1];
	temp[2][0][1] =	temp2[2][0][1];
	temp[1][2][1] =	temp2[1][2][1];
	temp[1][1][1] =	temp2[1][1][1];
	temp[1][0][1] =	temp2[1][0][1];
	temp[0][2][1] =	temp2[0][2][1];
	temp[0][1][1] =	temp2[0][1][1];
	temp[0][0][1] =	temp2[0][0][1];

	temp[2][2][0] =	temp2[2][2][0];
	temp[2][1][0] =	temp2[2][1][0];
	temp[2][0][0] =	temp2[2][0][0];
	temp[1][2][0] =	temp2[1][2][0];
	temp[1][1][0] =	temp2[1][1][0];
	temp[1][0][0] =	temp2[1][0][0];
	temp[0][2][0] =	temp2[0][2][0];
	temp[0][1][0] =	temp2[0][1][0];
	temp[0][0][0] =	temp2[0][0][0];


}


void axis_i_90(int ***temp)
{
/*clock-wise*/
	int temp2[3][3][3];

	temp2[2][2][2] = temp[2][0][2];
	temp2[2][2][1] = temp[2][1][2];
	temp2[2][2][0] = temp[2][2][2];
	temp2[2][1][2] = temp[2][0][1];
	temp2[2][1][1] = temp[2][1][1];
	temp2[2][1][0] = temp[2][2][1];
	temp2[2][0][2] = temp[2][0][0];
	temp2[2][0][1] = temp[2][1][0];
	temp2[2][0][0] = temp[2][2][0];

	temp2[1][2][2] = temp[1][0][2];
	temp2[1][2][1] = temp[1][1][2];
	temp2[1][2][0] = temp[1][2][2];
	temp2[1][1][2] = temp[1][0][1];
	temp2[1][1][1] = temp[1][1][1];
	temp2[1][1][0] = temp[1][2][1];
	temp2[1][0][2] = temp[1][0][0];
	temp2[1][0][1] = temp[1][1][0];
	temp2[1][0][0] = temp[1][2][0];

	temp2[0][2][2] = temp[0][0][2];
	temp2[0][2][1] = temp[0][1][2];
	temp2[0][2][0] = temp[0][2][2];
	temp2[0][1][2] = temp[0][0][1];
	temp2[0][1][1] = temp[0][1][1];
	temp2[0][1][0] = temp[0][2][1];
	temp2[0][0][2] = temp[0][0][0];
	temp2[0][0][1] = temp[0][1][0];
	temp2[0][0][0] = temp[0][2][0];

	/******************************************************/

	temp[2][2][2] =	temp2[2][2][2];
	temp[2][1][2] =	temp2[2][1][2];
	temp[2][0][2] =	temp2[2][0][2];
	temp[1][2][2] =	temp2[1][2][2];
	temp[1][1][2] =	temp2[1][1][2];
	temp[1][0][2] =	temp2[1][0][2];
	temp[0][2][2] =	temp2[0][2][2];
	temp[0][1][2] =	temp2[0][1][2];
	temp[0][0][2] =	temp2[0][0][2];

	temp[2][2][1] =	temp2[2][2][1];
	temp[2][1][1] =	temp2[2][1][1];
	temp[2][0][1] =	temp2[2][0][1];
	temp[1][2][1] =	temp2[1][2][1];
	temp[1][1][1] =	temp2[1][1][1];
	temp[1][0][1] =	temp2[1][0][1];
	temp[0][2][1] =	temp2[0][2][1];
	temp[0][1][1] =	temp2[0][1][1];
	temp[0][0][1] =	temp2[0][0][1];

	temp[2][2][0] =	temp2[2][2][0];
	temp[2][1][0] =	temp2[2][1][0];
	temp[2][0][0] =	temp2[2][0][0];
	temp[1][2][0] =	temp2[1][2][0];
	temp[1][1][0] =	temp2[1][1][0];
	temp[1][0][0] =	temp2[1][0][0];
	temp[0][2][0] =	temp2[0][2][0];
	temp[0][1][0] =	temp2[0][1][0];
	temp[0][0][0] =	temp2[0][0][0];

}


int Simple_Point(int ***matrix, int ***temp, int i, int j, int k)	//non-simle point return 1
{

	int number_objects = 0;
	int number_tunnels = 0;

	int config;
	int index;
	int isolated_vpoints;
	
	int m;

	int a,b,c;
	for(a=0; a<=2; a++)
		for(b=0; b<=2; b++)
			for(c=0; c<=2; c++)
			{
				if(matrix[i-1+a][j-1+b][k-1+c] < 0)
					temp[a][b][c] = 0;
				else
					temp[a][b][c] = 1;
			}

	int sum = temp[1][1][2] + temp[1][1][0] + temp[1][2][1]+
			  temp[1][0][1] + temp[2][1][1] + temp[0][1][1];

	if(sum==0)
	{
		//if all the e-points are white
		if((temp[2][1][0] + temp[1][2][0] + temp[0][1][0] + temp[1][0][0] + temp[2][0][1] + temp[2][2][1] + 
			temp[0][2][1] + temp[0][0][1] + temp[1][0][2] + temp[2][1][2] + temp[1][2][2] + temp[0][1][2])==0)
		{
			number_objects = (temp[2][2][2] + temp[2][2][0] + temp[2][0][2] + temp[2][0][0]
				+ temp[0][2][2] + temp[0][2][0] + temp[0][0][2] + temp[0][0][0]);
			number_tunnels = 0;
		}
		else	//at least one e-point is black, then the best way is to count the nubmer of objects by program 
		{
			//the configure of v-point

			config = 0;
			config = config | temp[2][2][2];
			config = config | (temp[2][0][2] << 1);
			config = config | (temp[0][0][2] << 2);
			config = config | (temp[0][2][2] << 3);
			config = config | (temp[2][2][0] << 4);
			config = config | (temp[2][0][0] << 5);
			config = config | (temp[0][0][0] << 6);
			config = config | (temp[0][2][0] << 7);

			//the configure of effective points

			index = 0;
			index = index | temp[2][2][1];
			index = index | (temp[2][0][1] << 1);
			index = index | (temp[0][2][1] << 2);
			index = index | (temp[0][0][1] << 3);
			index = index | (temp[1][2][2] << 4);
			index = index | (temp[2][1][2] << 5);
			index = index | (temp[1][0][2] << 6);
			index = index | (temp[0][1][2] << 7);
			index = index | (temp[1][2][0] << 8);
			index = index | (temp[2][1][0] << 9);
			index = index | (temp[1][0][0] << 10);
			index = index | (temp[0][1][0] << 11);
			
			isolated_vpoints = config & tab6[index][1];
			m=0;
			while (isolated_vpoints != 0)
			{
				if (isolated_vpoints % 2)
					m = m + 1;
				isolated_vpoints = isolated_vpoints  / 2;
			}

			number_objects = (tab6[index][0] & 0x0f) +m;
			number_tunnels = (tab6[index][0] & 0xf0) >> 4;
		}

		if(number_objects==1 && number_tunnels ==0)
			return 0;
		else
			return 1;
	}
		
	if(sum==1)
	{

		/*****one s-point is black, criteria is (i,j,k-1)*****/
		if(temp[1][0][1]==1)
		{
			axis_i_90(temp);
			axis_i_90(temp);
			axis_i_90(temp);
		}
		else if(temp[2][1][1]==1)
		{
			axis_j_90(temp);
			axis_j_90(temp);
			axis_j_90(temp);
		}
		else if(temp[1][2][1]==1)
		{
			axis_i_90(temp);
		}
		else if(temp[0][1][1]==1)
		{
			axis_j_90(temp);
		}
		else if(temp[1][1][2]==1)
		{
			axis_j_90(temp);
			axis_j_90(temp);
		}
			
		index = 0;
		index = index | temp[2][2][1];
		index = index | (temp[2][0][1] << 1);
		index = index | (temp[0][2][1] << 2);
		index = index | (temp[0][0][1] << 3);
		index = index | (temp[2][2][2] << 4);
		index = index | (temp[2][1][2] << 5);
		index = index | (temp[2][0][2] << 6);
		index = index | (temp[1][0][2] << 7);
		index = index | (temp[0][0][2] << 8);
		index = index | (temp[0][1][2] << 9);
		index = index | (temp[0][2][2] << 10);
		index = index | (temp[1][2][2] << 11);  
		if(index == 0)
			index = 0;

		number_objects = tab5[index] & 0x0f;
		number_tunnels = (tab5[index] & 0xf0) >> 4;
		if(number_objects==1 && number_tunnels ==0)
			return 0;
		else
			return 1;
	}
	

	if(sum ==2)
	{
		/******two opposite s-points are black, criteria is (i, j, k+1) and (i, j, k-1)******/
		if((temp[2][1][1] + temp[0][1][1])==2 || (temp[1][2][1] + temp[1][0][1])==2 || (temp[1][1][2] + temp[1][1][0])==2)
		{
			if((temp[1][2][1] + temp[1][0][1])==2) //j-axis
			{
				axis_i_90(temp);
			}
			else if((temp[2][1][1] + temp[0][1][1])==2)
			{
				axis_j_90(temp);
			}
			index = 0;
			index = index | temp[2][2][1];
			index = index | (temp[2][0][1] << 1);
			index = index | (temp[0][2][1] << 2);
			index = index | (temp[0][0][1] << 3);

			number_objects = tab4a[index] & 0x0f;
			number_tunnels = (tab4a[index] & 0xf0) >> 4;
		}
		else /******two unopposite s-points are black, criteria is (i, j-1, k) and (i+1, j, k)******/
		{
			if(temp[2][1][1]==1 && temp[1][2][1]==1)
			{
				axis_k_90(temp);
			}
			else if(temp[2][1][1]==1 && temp[1][1][2]==1)
			{
				axis_i_90(temp);
				axis_i_90(temp);
				axis_i_90(temp);
			}
			else if(temp[2][1][1]==1 && temp[1][1][0]==1)
			{
				axis_i_90(temp);
			}
			else if(temp[0][1][1]==1 && temp[1][2][1]==1)
			{
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[0][1][1]==1 && temp[1][0][1]==1)
			{
				axis_k_90(temp);
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[0][1][1]==1 && temp[1][1][2]==1)
			{
				axis_i_90(temp);
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[0][1][1]==1 && temp[1][1][0]==1)
			{
				axis_j_90(temp);
				axis_i_90(temp);
			}
			else if(temp[1][0][1]==1 && temp[1][1][2]==1)
			{
				axis_j_90(temp);
				axis_j_90(temp);
				axis_j_90(temp);
			}
			else if(temp[1][0][1]==1 && temp[1][1][0]==1)
			{
				axis_j_90(temp);
			}
			else if(temp[1][2][1]==1 && temp[1][1][2]==1)
			{
				axis_j_90(temp);
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[1][2][1]==1 && temp[1][1][0]==1)
			{
				axis_k_90(temp);
				axis_i_90(temp);
			}
			/*the point is rotated to (temp[2][1][1]==1 && temp[1][0][1]==1)*/
			index = 0;
			index = index | temp[0][2][2];
			index = index | (temp[0][2][0] << 1);
			index = index | (temp[0][2][1] << 2);
			index = index | (temp[0][1][2] << 3);
			index = index | (temp[1][2][2] << 4);
			index = index | (temp[0][1][0] << 5);
			index = index | (temp[1][2][0] << 6);
		
			number_objects = tab4b[index] & 0x0f;
			number_tunnels = (tab4b[index] & 0xf0) >> 4;
		}

		if(number_objects==1 && number_tunnels ==0)
			return 0;
		else
			return 1;

	}
		
	if(sum ==3)
	{
		if((temp[2][1][1] + temp[0][1][1])==1 && (temp[1][2][1] + temp[1][0][1])==1 && (temp[1][1][2] + temp[1][1][0])==1)
		{
			//3 non opposite s-points are black
			//the effective voxel number = 4
			if(temp[2][1][1]==1 && temp[1][2][1]==1 && temp[1][1][0]==1)
			{
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[2][1][1]==1 && temp[1][1][0]==1 && temp[1][0][1]==1)
			{
				axis_k_90(temp);
			}
			else if(temp[1][1][0]==1 && temp[1][2][1]==1 && temp[0][1][1]==1)
			{
				axis_k_90(temp);
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[1][1][2]==1 && temp[2][1][1]==1 && temp[1][2][1]==1)
			{
				axis_i_90(temp);
				axis_k_90(temp);
				axis_k_90(temp);
			}
			else if(temp[1][1][2]==1 && temp[1][2][1]==1 && temp[0][1][1]==1)
			{
				axis_i_90(temp);
				axis_i_90(temp);
			}
			else if(temp[1][1][2]==1 && temp[0][1][1]==1 && temp[1][0][1]==1)
			{
				axis_j_90(temp);
			}
			else if(temp[1][1][2]==1 && temp[1][0][1]==1 && temp[2][1][1]==1)
			{
				axis_j_90(temp);
				axis_j_90(temp);
			}
			//now the point is rotated to (temp[1][1][0]==1 && temp[1][0][1]==1 && temp[0][1][1]==1)
			index = 0;
			index = index | temp[2][2][2];
			index = index | (temp[1][2][2]<<1);
			index = index | (temp[2][1][2]<<2);
			index = index | (temp[2][2][1]<<3);

			number_objects = tab3b[index] & 0x0f;
			number_tunnels = (tab3b[index] & 0xf0) >> 4;
		}
		else
		{
			//two opposite s-points and another s-point are black
			if(temp[1][1][2]==1 && temp[1][1][0]==1)	//oppposite s-points in k-axis are black
			{	
				if(temp[1][0][1]) 
				{
					if(temp[2][2][1] + temp[0][2][1] == 2)
						number_tunnels = 2; /*****if both effective pts are white, then it's simple pt*****/
					else if(temp[2][2][1] + temp[0][2][1] == 1)
						number_tunnels = 1;
					else 
						number_tunnels = 0;
				}
		
				else if(temp[2][1][1])
				{
					if(temp[0][0][1] + temp[0][2][1] == 2)
						number_tunnels = 2;
					else if(temp[0][0][1] + temp[0][2][1] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
	
				else if(temp[1][2][1])
				{
					if(temp[2][0][1] + temp[0][0][1] == 2)
						number_tunnels = 2;
					else if(temp[2][0][1] + temp[0][0][1] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[0][1][1])
				{
					if(temp[2][0][1] + temp[2][2][1] == 2)
						number_tunnels = 2;
					else if(temp[2][0][1] + temp[2][2][1] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			}

			/****** opposites s-points in i-axis are black *******/
			else if(temp[2][1][1]==1 && temp[0][1][1]==1)
			{
				if(temp[1][0][1])
				{
					if(temp[1][2][0] + temp[1][2][2] == 2) 
						number_tunnels = 2;
					else if(temp[1][2][0] + temp[1][2][2] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][1][2])
				{
					if(temp[1][0][0] + temp[1][2][0] == 2)
						number_tunnels = 2;
					else if(temp[1][0][0] + temp[1][2][0] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][2][1])
				{
					if(temp[1][0][2] + temp[1][0][0] == 2)
						number_tunnels = 2;
					else if(temp[1][0][2] + temp[1][0][0] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][1][0])
				{
					if(temp[1][0][2] + temp[1][2][2]==2)
						number_tunnels = 2;
					else if(temp[1][0][2] + temp[1][2][2]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			}
		
			/*******the opposite s-points in j-axis are black ********/
			else if(temp[1][2][1]==1 && temp[1][0][1]==1)
			{
				if(temp[1][1][2])
				{
					if(temp[2][1][0] + temp[0][1][0] == 2)
						number_tunnels = 2;
					else if(temp[2][1][0] + temp[0][1][0] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
		
				else if(temp[0][1][1])
				{
					if(temp[2][1][2] + temp[2][1][0] == 2)
						number_tunnels = 2;
					else if(temp[2][1][2] + temp[2][1][0] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][1][0])
				{
					if(temp[2][1][2] + temp[0][1][2] == 2)///////////////////////////////////////////////////////11-16-2005
						number_tunnels = 2;
					else if(temp[2][1][2] + temp[0][1][2] == 1)////////////////////////////////////////
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[2][1][1])
				{
					if(temp[0][1][2] + temp[0][1][0] == 2)
						number_tunnels = 2;
					else if(temp[0][1][2] + temp[0][1][0] == 1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			}
						/*in this case, the number of objects will always be 1*/
			number_objects = 1;
		}
		if(number_objects==1 && number_tunnels ==0)
			return 0;
		else
			return 1;
	}
		

	if(sum ==4)
	{
		if((temp[2][1][1]+temp[0][1][1]+temp[1][2][1]+temp[1][0][1] == 4) || (temp[1][2][1]+temp[1][0][1]+temp[1][1][2]+temp[1][1][0] == 4) || (temp[1][1][2]+temp[1][1][0]+temp[2][1][1]+temp[0][1][1] == 4))
		{
			//two pairs of opposite s-points are black
			number_objects = 1;
			number_tunnels = 1;
		}
		else		/************ one pair of opposite s-points and two other nonopposite s-points are black ************/
		{
			if(temp[2][1][1]==1 && temp[0][1][1]==1)
			/************ opposite s-points in i-axis are black ****************/
			{
				if(temp[1][2][1]==1 && temp[1][1][2]==1)
				{
					if(temp[1][0][0]==1)
						number_tunnels = 1; 
					else
						number_tunnels = 0;
				}

				else if(temp[1][2][1]==1 && temp[1][1][0]==1)
				{
					if(temp[1][0][2]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][0][1]==1 && temp[1][1][2]==1)
				{
					if(temp[1][2][0]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[1][0][1]==1 && temp[1][1][0]==1)
				{
					if(temp[1][2][2]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			}
			
			/************** opposite s-points in j-axis are black ****************/
			else if(temp[1][2][1]==1 && temp[1][0][1]==1)
			{
				if(temp[2][1][1]==1 && temp[1][1][2]==1)
				{
					if(temp[0][1][0]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[2][1][1]==1 && temp[1][1][0]==1)
				{
					if(temp[0][1][2]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			
				else if(temp[0][1][1]==1 && temp[1][1][2]==1)
				{
					if(temp[2][1][0]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[0][1][1]==1 && temp[1][1][0]==1)
				{
					if(temp[2][1][2]==1) 
						number_tunnels = 1;
					else 
						number_tunnels = 0;
				}
			}

			/***************** opposite s-points in k-axis are black ******************/
			else if(temp[1][1][2]==1 && temp[1][1][0]==1)
			{
				if(temp[2][1][1]==1 && temp[1][2][1]==1)
				{
					if(temp[0][0][1]==1) 
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[2][1][1]==1 && temp[1][0][1]==1)
				{
					if(temp[0][2][1]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			
				else if(temp[0][1][1]==1 && temp[1][2][1]==1)
				{
					if(temp[2][0][1]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}

				else if(temp[0][1][1]==1 && temp[1][0][1]==1)
				{
					if(temp[2][2][1]==1)
						number_tunnels = 1;
					else
						number_tunnels = 0;
				}
			}
			number_objects = 1;
		}
		if(number_objects==1 && number_tunnels ==0)
			return 0;
		else
			return 1;
	}

	else if(sum==5)
	{
		return 0;				//////////////////////////////////11-16-2005
	}

	else if(sum==6)
	{
		return 1;				//////////////////////////////////11-16-2005
	}

	return 0;

}