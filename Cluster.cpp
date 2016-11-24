#include "stdafx.h"
#include "Cluster.h"

int labelmax(int *label_nums, int num)
{
	int max = 0;
	int label = 0;
	int i;
	for (i=1; i<=num; i++)
	{
		if(label_nums[i] > max)
		{
			max = label_nums[i];
			label = i;
		}
	}

	return label;
}

int labelmax2(int *label_nums, int num, int max)
{
	int max2 = 0;
	int label = 0;
	int i;
	for (i=1; i<=num; i++)
	{
		if(label_nums[i] > max2 && i!=max)
		{
			max2 = label_nums[i];
			label = i;
		}
	}

	return label;
}

int neighbormin(int *neighbor)
{
	int min = 99999;
	int i;
	for (i=0; i<13; i++)
	{
		if(neighbor[i] <= min && neighbor[i] != 0)
			min = neighbor[i];
	}
	
	return min;
}

int neighbormin2(int *neighbor)
{
	int min = 99999;
	int i;
	for (i=0; i<3; i++)
	{
		if(neighbor[i] <= min && neighbor[i] != 0)
			min = neighbor[i];
	}
	
	return min;
}

int hoshen_kopelman (int ***matrix, int *size, BOOL m_bDebugmode)
{
	int *labels, *label_nums, *final_labels, label_min, label_max, cluster_num, i, j, k, m;
	int voxel_num = 0;
	int *neighbor;
//	int i,j,k;

	if(m_bDebugmode == TRUE)
	{	
		for (i=0; i<size[0]+4; i++)
		{
			for (j=0; j<size[1]+4; j++)
			{
				for(k=0; k<size[2]+4; k++)
				{
					if(i < 2+5 || j < 2+5 || k < 2+5 || i > size[0]+1-5 || j > size[1]+1-5 || k > size[2]+1-5)
					{
						matrix[i][j][k] = 0;
					}
					else
					{
						if(matrix[i][j][k] >= 0)
						{
							voxel_num++;
							matrix[i][j][k] = 1;
						}
						else
						{
							matrix[i][j][k] = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		for (i=0; i<size[0]+4; i++)
		{
			for (j=0; j<size[1]+4; j++)
			{
				for(k=0; k<size[2]+4; k++)
				{
					if(i < 2 || j < 2 || k < 2 || i > size[0]+1 || j > size[1]+1 || k > size[2]+1)
					{
						matrix[i][j][k] = 0;
					}
					if(matrix[i][j][k] > 0)
					{
						voxel_num++;
					}
				}
			}
		}
	}

	labels = (int*)malloc(sizeof(int) * voxel_num);
	neighbor = (int*)malloc(sizeof(int) * 13);
		
	// we'll use element 0 of the labels array to record the maximum label we've used so far. 

	labels[0] = 0; 
  
	// scan the matrix 
  
	for (k=2; k<size[2]+2; k++)
	{
		for (j=2; j<size[1]+2; j++)
		{
			for(i=2; i<size[0]+2; i++)
			{
				if (matrix[i][j][k]>0)
				{
					neighbor[0] =  matrix[i-1][j-1][k] ;
					neighbor[1] =  matrix[i-1][j][k] ;
					neighbor[2] =  matrix[i+1][j-1][k] ;
					neighbor[3] =  matrix[i][j-1][k] ;
					neighbor[4] =  matrix[i-1][j+1][k-1] ;
					neighbor[5] =  matrix[i-1][j][k-1] ;
					neighbor[6] =  matrix[i-1][j-1][k-1] ;
					neighbor[7] =  matrix[i][j+1][k-1] ;
					neighbor[8] =  matrix[i][j][k-1] ;
					neighbor[9] =  matrix[i][j-1][k-1] ;
					neighbor[10] =  matrix[i+1][j+1][k-1] ;
					neighbor[11] =  matrix[i+1][j][k-1] ;
					neighbor[12] =  matrix[i+1][j-1][k-1] ;

					switch (!!neighbor[0] + !!neighbor[1] + !!neighbor[2] + !!neighbor[3] + !!neighbor[4] + !!neighbor[5] + !!neighbor[6] 
						   +!!neighbor[7] + !!neighbor[8] + !!neighbor[9] + !!neighbor[10] + !!neighbor[11] + !!neighbor[12] )
					{
						case 0: // new cluster 
							labels[0] ++;                      // make the new label number
							labels[ labels[0] ] = 1;		   // no known alias yet (label[x]=1)
							matrix[i][j][k] = labels[0];          // apply this label to this position 
							break;

						case 1: // same cluster 
							// whichever is nonzero is labelled
							for (m=0; m<=12; m++)
							{
								if(neighbor[m] != 0)
								{
									label_max = neighbor[m];
								}
							}
							while(labels[label_max] < 0)
							{
								label_max = (-1)*labels[label_max];
							}
							matrix[i][j][k] = label_max;       
							labels[label_max]++;
							break;

						case 2: // two clusters //
						case 3:
						case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
							while(labels[neighbor[0]] < 0)
							{
								neighbor[0] = (-1)*labels[neighbor[0]];
							}
							while(labels[neighbor[1]] < 0) 
							{
								neighbor[1] = (-1)*labels[neighbor[1]];
							}
							while(labels[neighbor[2]] < 0) 
							{
								neighbor[2] = (-1)*labels[neighbor[2]];
							}
							while(labels[neighbor[3]] < 0) 
							{
								neighbor[3] = (-1)*labels[neighbor[3]];
							}
							while(labels[neighbor[4]] < 0) 
							{
								neighbor[4] = (-1)*labels[neighbor[4]];
							}
							while(labels[neighbor[5]] < 0) 
							{
								neighbor[5] = (-1)*labels[neighbor[5]];
							}
							while(labels[neighbor[6]] < 0) 
							{
								neighbor[6] = (-1)*labels[neighbor[6]];
							}
							while(labels[neighbor[7]] < 0) 
							{
								neighbor[7] = (-1)*labels[neighbor[7]];
							}
							while(labels[neighbor[8]] < 0) 
							{
								neighbor[8] = (-1)*labels[neighbor[8]];
							}
							while(labels[neighbor[9]] < 0) 
							{
								neighbor[9] = (-1)*labels[neighbor[9]];
							}
							while(labels[neighbor[10]] < 0) 
							{
								neighbor[10] = (-1)*labels[neighbor[10]];
							}
							while(labels[neighbor[11]] < 0) 
							{
								neighbor[11] = (-1)*labels[neighbor[11]];
							}
							while(labels[neighbor[12]] < 0) 
							{
								neighbor[12] = (-1)*labels[neighbor[12]];
							}
						
							label_min = neighbormin(neighbor);
							matrix[i][j][k] = label_min;
							labels[label_min]++;
							
							for (m=0; m<13; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[label_min] += labels[neighbor[m]]; 
								}
							}

							for (m=0; m<13; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[neighbor[m]] = (-1)*label_min;
								}
							}
							break;
						default:
							break;

					}
				}
			}
		}
	}
  
	// renumber the labels so that they're continuous
	cluster_num = 0;
	label_nums = (int*)malloc(sizeof(int)*(labels[0]+1));
	label_nums[0] = 0;		//use label_nums[0] as the total element numbers
	final_labels = (int*)malloc(sizeof(int)*(labels[0]+1));

	for (i=1; i<=labels[0]; i++)
	{
		if (labels[i] > 0)
		{
			cluster_num ++;
			final_labels[i] = cluster_num;
			label_nums[cluster_num] = labels[i];
			label_nums[0] =label_nums[0]+ label_nums[cluster_num];
		}
	}
	// apply the relabeling to the matrix 
  
	labels[0] = 0;
	final_labels[0] = 0;	
	label_max = labelmax(label_nums, cluster_num);

	for (i=2; i<size[0]+2; i++)
	{
		for (j=2; j<size[1]+2; j++)
		{
			for (k=2; k<size[2]+2; k++)
			{
				if(matrix[i][j][k] != 0)
				{
					while(labels[ matrix[i][j][k] ]  < 0)
					{
						matrix[i][j][k] = (-1)*labels[ matrix[i][j][k] ];
					}
					matrix[i][j][k] = final_labels[ matrix[i][j][k] ];
					
					if(matrix[i][j][k] == label_max)
						matrix[i][j][k] = 1;
					else
						matrix[i][j][k] = 0;
				}
			}
		}
	}
  	
	free(labels);
	free(label_nums);
	free(neighbor);	
	free(final_labels);
	return cluster_num;
	//return 0;
}

int HKcluster4S (int ***matrix, int *size)
{
	int *labels, *label_nums, *final_labels, label_min, label_max, cluster_num, i, j, k, m;
	int voxel_num = 0;
	int *neighbor;
//	int i,j,k;

	for (i=2; i<size[0]+2; i++)
	{
		for (j=2; j<size[1]+2; j++)
		{
			for(k=2; k<size[2]+2; k++)
			{
				if(matrix[i][j][k] > 0)
				{
					voxel_num++;
				}
			}
		}
	}

	labels = (int*)malloc(sizeof(int) * (voxel_num+1));
	neighbor = (int*)malloc(sizeof(int) * 13);
		
	// we'll use element 0 of the labels array to record the maximum label we've used so far. 

	labels[0] = 0; 
  
	// scan the matrix 
  
	for (k=2; k<size[2]+2; k++)
	{
		for (j=2; j<size[1]+2; j++)
		{
			for(i=2; i<size[0]+2; i++)
			{
				if (matrix[i][j][k]>0)
				{
					neighbor[0] =  matrix[i-1][j-1][k] ;
					neighbor[1] =  matrix[i-1][j][k] ;
					neighbor[2] =  matrix[i+1][j-1][k] ;
					neighbor[3] =  matrix[i][j-1][k] ;
					neighbor[4] =  matrix[i-1][j+1][k-1] ;
					neighbor[5] =  matrix[i-1][j][k-1] ;
					neighbor[6] =  matrix[i-1][j-1][k-1] ;
					neighbor[7] =  matrix[i][j+1][k-1] ;
					neighbor[8] =  matrix[i][j][k-1] ;
					neighbor[9] =  matrix[i][j-1][k-1] ;
					neighbor[10] =  matrix[i+1][j+1][k-1] ;
					neighbor[11] =  matrix[i+1][j][k-1] ;
					neighbor[12] =  matrix[i+1][j-1][k-1] ;

					switch (!!neighbor[0] + !!neighbor[1] + !!neighbor[2] + !!neighbor[3] + !!neighbor[4] + !!neighbor[5] + !!neighbor[6] 
						   +!!neighbor[7] + !!neighbor[8] + !!neighbor[9] + !!neighbor[10] + !!neighbor[11] + !!neighbor[12] )
					{
						case 0: // new cluster 
							labels[0] ++;                      // make the new label number
							labels[ labels[0] ] = 1;		   // no known alias yet (label[x]=1)
							matrix[i][j][k] = labels[0];          // apply this label to this position 
							break;

						case 1: // same cluster 
							// whichever is nonzero is labelled
							for (m=0; m<=12; m++)
							{
								if(neighbor[m] != 0)
								{
									label_max = neighbor[m];
								}
							}
							while(labels[label_max] < 0)
							{
								label_max = (-1)*labels[label_max];
							}
							matrix[i][j][k] = label_max;       
							labels[label_max]++;
							break;

						case 2: // two clusters //
						case 3:
						case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
							while(labels[neighbor[0]] < 0)
							{
								neighbor[0] = (-1)*labels[neighbor[0]];
							}
							while(labels[neighbor[1]] < 0) 
							{
								neighbor[1] = (-1)*labels[neighbor[1]];
							}
							while(labels[neighbor[2]] < 0) 
							{
								neighbor[2] = (-1)*labels[neighbor[2]];
							}
							while(labels[neighbor[3]] < 0) 
							{
								neighbor[3] = (-1)*labels[neighbor[3]];
							}
							while(labels[neighbor[4]] < 0) 
							{
								neighbor[4] = (-1)*labels[neighbor[4]];
							}
							while(labels[neighbor[5]] < 0) 
							{
								neighbor[5] = (-1)*labels[neighbor[5]];
							}
							while(labels[neighbor[6]] < 0) 
							{
								neighbor[6] = (-1)*labels[neighbor[6]];
							}
							while(labels[neighbor[7]] < 0) 
							{
								neighbor[7] = (-1)*labels[neighbor[7]];
							}
							while(labels[neighbor[8]] < 0) 
							{
								neighbor[8] = (-1)*labels[neighbor[8]];
							}
							while(labels[neighbor[9]] < 0) 
							{
								neighbor[9] = (-1)*labels[neighbor[9]];
							}
							while(labels[neighbor[10]] < 0) 
							{
								neighbor[10] = (-1)*labels[neighbor[10]];
							}
							while(labels[neighbor[11]] < 0) 
							{
								neighbor[11] = (-1)*labels[neighbor[11]];
							}
							while(labels[neighbor[12]] < 0) 
							{
								neighbor[12] = (-1)*labels[neighbor[12]];
							}
						
							label_min = neighbormin(neighbor);
							matrix[i][j][k] = label_min;
							labels[label_min]++;
							
							for (m=0; m<13; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[label_min] += labels[neighbor[m]]; 
								}
							}

							for (m=0; m<13; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[neighbor[m]] = (-1)*label_min;
								}
							}
							break;
						default:
							break;

					}
				}
			}
		}
	}
  
	// renumber the labels so that they're continuous
	cluster_num = 0;
	label_nums = (int*)malloc(sizeof(int)*(labels[0]+1));
	label_nums[0] = 0;		//use label_nums[0] as the total element numbers
	final_labels = (int*)malloc(sizeof(int)*(labels[0]+1));

	for (i=1; i<=labels[0]; i++)
	{
		if (labels[i] > 0)
		{
			cluster_num ++;
			final_labels[i] = cluster_num;
			label_nums[cluster_num] = labels[i];
			label_nums[0] =label_nums[0]+ label_nums[cluster_num];
		}
	}
	// apply the relabeling to the matrix 
    
	labels[0] = 0;
	final_labels[0] = 0;	
	label_max = labelmax(label_nums, cluster_num);

	for (i=2; i<size[0]+2; i++)
	{
		for (j=2; j<size[1]+2; j++)
		{
			for (k=2; k<size[2]+2; k++)
			{
				if(matrix[i][j][k] != 0)
				{
					while(labels[ matrix[i][j][k] ]  < 0)
					{
						matrix[i][j][k] = (-1)*labels[ matrix[i][j][k] ];
					}
					matrix[i][j][k] = final_labels[ matrix[i][j][k] ];

				}
			}
		}
	}
  	
	free(labels);
	free(label_nums);
	free(neighbor);	
	free(final_labels);
	return cluster_num;
	//return 0;
}

//3-1-2006
int hoshen_kopelman2 (int ***matrix, int *size)
{
	int *labels, *label_nums, *final_labels, label_min, label_max, label_max2, cluster_num, i, j, k, m;
	int voxel_num = 0;
	int *neighbor;
//	int i,j,k;

	for (i=0; i<size[0]+4; i++)
	{
		for (j=0; j<size[1]+4; j++)
		{
			for(k=0; k<size[2]+4; k++)
			{
				if(i < 2 || j < 2 || k < 2 || i > size[0]+1 || j > size[1]+1 || k > size[2]+1)
				{
					matrix[i][j][k] = 1;
					voxel_num++;
				}
				if(i < 1 || j < 1 || k < 1 || i > size[0]+2 || j > size[1]+2 || k > size[2]+2)
				{
					matrix[i][j][k] = 0;
					voxel_num--;
				}
				else if(matrix[i][j][k] == 0)
				{
					matrix[i][j][k] = 1;
					voxel_num++;
				}
				else
					matrix[i][j][k] = 0;
			}
		}
	}
	

	labels = (int*)malloc(sizeof(int) * voxel_num);
	neighbor = (int*)malloc(sizeof(int) * 3);
		
	// we'll use element 0 of the labels array to record the maximum label we've used so far. 

	labels[0] = 0; 
  
	// scan the matrix 
  
	for (k=1; k<size[2]+3; k++)
	{
		for (j=1; j<size[1]+3; j++)
		{
			for(i=1; i<size[0]+3; i++)
			{
				if (matrix[i][j][k]>0)
				{
					neighbor[0] =  matrix[i-1][j][k] ;
					neighbor[1] =  matrix[i][j-1][k] ;
					neighbor[2] =  matrix[i][j][k-1] ;

					switch (!!neighbor[0] + !!neighbor[1] + !!neighbor[2])
					{
						case 0: // new cluster 
							labels[0] ++;                      // make the new label number
							labels[ labels[0] ] = 1;		   // no known alias yet (label[x]=1)
							matrix[i][j][k] = labels[0];          // apply this label to this position 
							break;

						case 1: // same cluster 
							// whichever is nonzero is labelled
							for (m=0; m<=2; m++)
							{
								if(neighbor[m] != 0)
								{
									label_max = neighbor[m];
								}
							}
							while(labels[label_max] < 0)
							{
								label_max = (-1)*labels[label_max];
							}
							matrix[i][j][k] = label_max;       
							labels[label_max]++;
							break;

						case 2: // two clusters //
						case 3:
							while(labels[neighbor[0]] < 0)
							{
								neighbor[0] = (-1)*labels[neighbor[0]];
							}
							while(labels[neighbor[1]] < 0) 
							{
								neighbor[1] = (-1)*labels[neighbor[1]];
							}
							while(labels[neighbor[2]] < 0) 
							{
								neighbor[2] = (-1)*labels[neighbor[2]];
							}
					
							label_min = neighbormin2(neighbor);
							matrix[i][j][k] = label_min;
							labels[label_min]++;
							
							for (m=0; m<3; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[label_min] += labels[neighbor[m]]; 
								}
							}

							for (m=0; m<3; m++)
							{
								if(neighbor[m] != label_min && neighbor[m] != 0)
								{
									labels[neighbor[m]] = (-1)*label_min;
								}
							}
							break;
						default:
							break;

					}
				}
			}
		}
	}
  
	// renumber the labels so that they're continuous
	cluster_num = 0;
	label_nums = (int*)malloc(sizeof(int)*(1+labels[0]));
	label_nums[0] = 0;		//use label_nums[0] as the total element numbers
	final_labels = (int*)malloc(sizeof(int)*(1+labels[0]));

	for (i=1; i<=labels[0]; i++)
	{
		if (labels[i] > 0)
		{
			cluster_num ++;
			final_labels[i] = cluster_num;
			label_nums[cluster_num] = labels[i];
			label_nums[0] =label_nums[0]+ label_nums[cluster_num];
		}
	}
	// apply the relabeling to the matrix 
  
	labels[0] = 0;
	final_labels[0] = 0;	
	label_max = labelmax(label_nums, cluster_num);
	label_max2 = labelmax2(label_nums, cluster_num, label_max);

	if(label_nums[label_max2] < (size[0]*size[1]+size[1]*size[2]+size[2]*size[0])*2)
		label_max2 = 0;

	for (i=1; i<size[0]+3; i++)
	{
		for (j=1; j<size[1]+3; j++)
		{
			for (k=1; k<size[2]+3; k++)
			{
				if(matrix[i][j][k] != 0)
				{
					while(labels[ matrix[i][j][k] ]  < 0)
					{
						matrix[i][j][k] = (-1)*labels[ matrix[i][j][k] ];
					}
					matrix[i][j][k] = final_labels[ matrix[i][j][k] ];
					
					if(matrix[i][j][k] == label_max ||matrix[i][j][k] == label_max2)
						matrix[i][j][k] = 0;
					else
						matrix[i][j][k] = 1;
				}
				else
					matrix[i][j][k] = 1;
			}
		}
	}
  	
	free(labels);
	free(label_nums);
	free(neighbor);	
	free(final_labels);
	return cluster_num;
	//return 0;
}