#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int time;
	int panalty;
	int index;
}clothes;

void algorithm(clothes dress[], int num);

void main() {
	clothes* dress;

	int num,i = 0;

	scanf("%d", &num);

	dress = (clothes*)malloc(sizeof(clothes) * num);
	
	while (i != num ) {
		scanf(" %d %d", &dress[i].time, &dress[i].panalty);
		dress[i].index = i+1;
		i++;
	}

	algorithm(dress,num);
}

void algorithm(clothes dress[],int number) {
	int tmp1;
	int tmp2;
	int tmp3;
	int num=number;

	for (int i = 0; i < num; i++) {
		for (int j = i+1; j < num; j++) {
			if (dress[i].time * dress[j].panalty > dress[j].time * dress[i].panalty) {
				tmp1 = dress[i].time;
				tmp2 = dress[i].panalty;
				tmp3 = dress[i].index;

				dress[i].time = dress[j].time;
				dress[i].panalty = dress[j].panalty;
				dress[i].index = dress[j].index;

				dress[j].time = tmp1;
				dress[j].panalty = tmp2;
				dress[j].index = tmp3;
			}
		}
	}

	for (int i =0; i <num; i++) {
		printf("%d ", dress[i].index);
	}

	free(dress);
	
}