/*ANIL AKBULUT HW8 Finding Island Coordinates and Island Number*/
			/*Number:151044029*/
#include <stdio.h> /* I used this library*/
#include <sys/resource.h>/* I used this library*/
#define ROW_COLUMN 512 /* I defined the size of the square matrix*/
void island_coordinat(int matrix[][ROW_COLUMN], int i, int j, int row, int column) /* recursive function */
{
	matrix[i][j]=0; /* I gave the value '0' to element*/
	if(i>=1)  /*check overflow status*/
	{
		if(matrix[i-1][j] == 1)  /*I checked the upper element.*/
		{
			island_coordinat(matrix, i-1, j, row, column); /* I called the recursive function */
		}
	}
	if(i<ROW_COLUMN) /*check overflow status*/
	{
		if(matrix[i+1][j]==1) /*I checked the bottom element.*/
		{
			island_coordinat(matrix, i+1, j, row, column);/* I called the recursive function */
		}
	}
	if(j>=1 && matrix[i][j-1]==1)  /*I checked the left element.*/
	{
		island_coordinat(matrix, i, j-1, row, column);/* I called the recursive function */
	}
	if(j<ROW_COLUMN && matrix[i][j+1]==1)  /*I checked the right element.*/
	{
		island_coordinat(matrix, i, j+1, row, column);/* I called the recursive function */
	}
}
int main(void)
{
	FILE *fp,*fp2; /*File pointers*/
	int matrix[ROW_COLUMN][ROW_COLUMN]; /*Two dimensional map(matrix)*/
	int i=0,j=0,island_count = 0,k=1,temp; /*variables*/
	int row=ROW_COLUMN;/*variables*/
	int column=ROW_COLUMN;/*variables*/
	int water_level;/* water level in input.txt*/
	const rlim_t kStackSize = 16 * 1024 * 1024; /* min stack size = 16 MB*/
	struct rlimit rl;
	int result;
	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0){
		if (rl.rlim_cur < kStackSize){
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0){
				fprintf(stderr, "setrlimit returned result = %d\n", result);
			}
		}
	}
	fp = fopen("input.txt", "r"); /*File read operator*/
	fp2 = fopen("output1.txt", "w+");/*File read operator*/
	fscanf(fp , "%d" , &water_level); /*water level in file assigned to variable*/
	while(fscanf(fp , "%d" , &matrix[i][j]) != EOF) /* map information with while loop assigned to two dimension matrix*/
	{
		j++;
		if (j==ROW_COLUMN) /*at the end of the line, the i value is increased and j is set to 0*/
		{
			j=0;
			i++;
		}
	}
	for(i=0;i<ROW_COLUMN ;i++) /*This loop changed elements of matrix*/
	{
		for(j=0;j<ROW_COLUMN ;j++)
		{
			if(matrix[i][j]<water_level)
			{
				matrix[i][j]=0;/*If the land part is lower than the water level, a value of 0 is assigned.*/
			}
			else matrix[i][j]=1;/*If the land part is higher than the water level, a value of 1 is assigned.*/
		}
	}
	fprintf(fp2, "    ");/*There is a space at the beginning of the file to write the number of islands*/
    for(i=0; i<ROW_COLUMN; i++) /*This loop scans the map*/
    {
        for(j=0; j<ROW_COLUMN; j++)
        {
            if(matrix[i][j] == 1) /*If the piece of land enters the condition*/
            {
                island_count++; /*Island count updated*/
                island_coordinat(matrix, i, j, row, column);/*This function is called up repeatedly for each island.*/
                fprintf(fp2, "%d %d\n",i,j);/*The first coordinate of the island part was printed to the file*/
            }
        }
    }
    rewind(fp2);/*Moves the cursor to the first line*/
	fprintf(fp2,"%d\n",island_count); /*I printed the island number*/
	fclose(fp); /*close input.txt*/
	fclose(fp2); /*close output.txt*/
	fp=fopen("output1.txt","r");
	fp2=fopen("output.txt","w+");
	fscanf(fp , "%d " , &temp);
	fprintf(fp2, "%d\n",temp);
	i=1;
	while(fscanf(fp , "%d" , &temp) != EOF) /* prints the total number of islands and coordinates to output.txt file*/
	{
		if(i%2==0){
			fprintf(fp2, "%d\n",temp);
		}
		else{
			fprintf(fp2, "%d ",temp);
		}
		i++;
	}
	remove("output1.txt");
 	fclose(fp);
 	fclose(fp2);
	return 0;
}