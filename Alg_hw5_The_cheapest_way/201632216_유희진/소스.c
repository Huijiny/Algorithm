#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int height;
int width;

typedef struct {
	int row;
	int col;
}index;
typedef struct {
	int num;
	int index;
}tofindindex;

int** openFile(char* fileName) {
	FILE* tmp;
	int** arr=NULL;

	tmp = fopen(fileName, "r");
	if (tmp == NULL) {
		printf("Error in open Files");
	}
	if (fscanf(tmp, "%d %d", &height, &width) > 0) {

		arr = (int**)malloc(sizeof(int*) * height);
		for (int i = 0; i < height; i++) {
			arr[i] = (int*)malloc(sizeof(int) * width);
		}
	}
	

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fscanf(tmp, "%d", &arr[i][j]);
		}
	}
	

	fclose(tmp);

	return arr;
	
}
int compare(const void* a, const void* b)
{
	int num1 = *(int*)a;  
	int num2 = *(int*)b;    

	if (num1 < num2)   
		return -1;      

	if (num1 > num2)    
		return 1;      

	return 0;    
}
int compareindex(const void* a, const void* b)
{
	tofindindex num1 = *(tofindindex*)a;
	tofindindex num2 = *(tofindindex*)b;

	return num1.num > num2.num;
}
int findminimum(int a, int b, int c) {
	//세 값중 최솟값찾기
	int tmp[3] = { a,b,c };
	qsort(tmp, 3, sizeof(int), compare);
	
	return tmp[0];
	
}

int findminimumindex(int a, int b, int c) {
	//세 값중 최솟값찾기
	tofindindex tmp[3];
	
		tmp[0].index = 1;
		tmp[0].num = a;
		tmp[1].index = 2;
		tmp[1].num = b;
		tmp[2].index = 3;
		tmp[2].num = c;
	
	int index;
	qsort(tmp, 3, sizeof(tofindindex), compareindex);

	return tmp[0].index;

}


void findTheCheapestPath(int** arr, int** cp) {
	index indx[20];
	int min ;
	int minIndex;
	int col;
	int row;
		min = cp[0][width-1];
		for (int i = 1; i < height; i++) {
			if (min > cp[i][width-1]) {
				min = cp[i][width-1];
				indx[width-1].row = width-1;
				indx[width-1].col = i;
			
		}
	}//맨 마지막 열 중 가장 작은 값 구하기

		row = indx[width-1].row;
		col = indx[width-1].col;
		printf("The cheapest cost : %d\n\n\n", cp[col][row]);
		

		//역행하며 셋 중 작은 값 찾아내기
		for (int j = width - 2; j >= 0; j--) {
			if (col == 0) {
				minIndex = findminimumindex(cp[height- 1][j], cp[col][j], cp[col + 1][j]);
			}
			else if (col == height - 1) {
				minIndex = findminimumindex(cp[col - 1][j], cp[col][j], cp[0][j]);
			}
			else {
				minIndex = findminimumindex(cp[col - 1][j], cp[col][j], cp[col + 1][j]);
			}
			
			if (minIndex == 1) {//첫번째값이 젤 작은값이면 첫번째 인덱스를 저장
				if (col == 0) {
					indx[j].col = height - 1;
				}
				else {
					indx[j].col = col - 1;					
				}
				indx[j].row = j ;
			}
			else if (minIndex == 2) {//두번째값이 젤 작은 값이면 두번째 인덱스 저장
				indx[j].col = col;
				indx[j].row = j ;
			}
			else {//세번째값이 젤 작은 값이면 세번째 인덱스 저장
				if (col == height - 1) {
					indx[j].col = 0;
				}
				else {
					indx[j].col = col + 1;
				}
				indx[j].row = j;

			}
			row = indx[j].row;
			col = indx[j].col;

	}
		printf("The cheapest path : ");
	
	for (int i = width; i > 0; i--) {
		int col = indx[width - i].col;
		int row = indx[width - i].row;
		printf("%d ", arr[col][row]);
	}
}
void findThePath(int** arr) {
	int** cp = NULL;
	
	cp = (int**)malloc(sizeof(int*) * height);
	for (int i = 0; i < height; i++) {
		cp[i] = (int*)malloc(sizeof(int) * width);
	}
	for (int i = 0; i <height; i++) {
		for (int j = 0; j <1; j++) {
			cp[i][j] = arr[i][j];
		}
	}
	for (int j = 1; j < width; j++) {
		for (int i = 0; i < height; i++) {
			if (i == 0) {
				cp[i][j] = findminimum(cp[height - 1][j-1], cp[i][j-1], cp[i + 1][j - 1]) + arr[i][j];
			}
			else if (i == height - 1) {
				cp[i][j] = findminimum(cp[i - 1][j - 1], cp[i][j-1], cp[0][j-1]) + arr[i][j];
			}
			else {
				cp[i][j] = findminimum(cp[i - 1][j - 1], cp[i][j-1], cp[i + 1][j -1]) + arr[i][j];
			}
		}
	}
	/*
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d ", cp[i][j]);
		}
		printf("\n");
	}
	*/
	
	findTheCheapestPath(arr, cp);

	
}

void main() {
	int** arr= NULL;
	
	arr = openFile("input.txt");
	findThePath(arr);


	
}

