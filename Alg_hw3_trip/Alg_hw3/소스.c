#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void main() {
	int numofstu=0;
	int* moneypaid;
	int avg, sum =0;
	int moneyget=0;
	int output=0;
	

	printf("put numebr of student");
	scanf_s("%d", &numofstu);

	moneypaid = (int*)malloc(sizeof(int) * numofstu);

	printf("put the money that they paid");
	for (int i = 0; i < numofstu; i++) {
		scanf_s("%d", &moneypaid[i]);
		sum += moneypaid[i];
	}

	//what is average?

	avg = sum / numofstu;

	if (avg % 10 != 0) {
		int i = 0;
		int extra = avg % 10;
		avg = avg - extra + 10;
	}
	for (int i = 0; i < numofstu; i++) {
		if (moneypaid[i] > avg)moneyget += moneypaid[i] - avg;
	}
	output = moneyget;


	printf("output : \%d", output);
	free(moneypaid);
	
}