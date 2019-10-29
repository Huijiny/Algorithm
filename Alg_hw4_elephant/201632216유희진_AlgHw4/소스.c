#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y)) 

int cnt;
int length;
typedef struct {
	int index;
	int weight;
	int smart;
}elephant;


void openFile(char* fileName, elephant arr[]) {
	FILE* tmp;
	int i = 1;

	tmp = fopen(fileName, "r");
	if (tmp == NULL) {
		printf("Error in open Files");
	}

	while (fscanf(tmp, "%d %d", &arr[i].weight, &arr[i].smart) > 0) {
		arr[i].index = i;
		i++;
	}
	cnt = i;
	
	fclose(tmp);
}


void LCS(elephant arr[]) {

	
	int** cur;
	int indx[10];
	int indexup = 0;
	int total = 0;
	int cmpr = 0;

	cur = (int**)malloc(sizeof(int*) * cnt );
	for (int i = 0; i < cnt;i++) {
		cur[i] = (int*)malloc(sizeof(int) * cnt );
		memset(cur[i], 0,sizeof(int*)*cnt);
	}
	

	for (int i = 1; i < cnt; i++) {
		for (int j = 1; j < cnt; j++) {
			if (arr[i].weight<arr[j].weight && arr[i].smart>arr[j].smart) {
				cur[i][j] = cur[i - 1][j - 1] + 1;
			}
			else {
				cur[i][j] = MAX(cur[i][j - 1], cur[i - 1][j]);
			}
		}
	}

	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < cnt; j++) {
			printf("%d", cur[i][j]);
		}
		printf("\n");
		
	}
	printf("length : %d\n", cur[cnt-1][cnt-1]);


}

void bubblesort(elephant list[]) {
	elephant tmp;

	for (int i = 1; i < cnt; i++) {
		for (int j = i+1; j < cnt; j++) {
			if (list[i].smart < list[j].smart) {//스마트로 내림차순
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			else if (list[i].smart == list[j].smart) {//스마트가 같으면 웨이트로 오름차순
				if (list[i].weight > list[j].weight) {
					tmp = list[i];
					list[i] = list[j];
					list[j] = tmp;
				}
			}
		}
	}
}


int main() {
	elephant list[100] = { 0 };

	openFile("elephants information.txt", list);
	

	
	LCS(list);
	
	bubblesort(list);
}

