#include <stdio.h>
#pragma warning(disable:4996)

void main() {

	int pearls;
	int num1;
	int dol1;
	int num2;
	int dol2;

	scanf("%d", &pearls);
	
	scanf("%d", &dol1);
	scanf("%d", &num1);
	
	scanf("%d", &dol2);
	scanf("%d", &num2);
	


	int cheaperone = 0;
	int nextone = 0;
	int first = dol1/num1 ;
	int second = dol2 / num2;
	if (first > second) {
		cheaperone = num2;
		nextone = num1;
	}
	else {
		cheaperone = num1;
		nextone = num2;
	}

	int maxnumberofpearls = pearls / cheaperone;

	if (pearls % cheaperone == 0) {
		printf("%d %d", cheaperone, maxnumberofpearls);
	}
	else {
		for (int i = 1; i < maxnumberofpearls; i++) {

			if ((cheaperone * (maxnumberofpearls - i)) + (nextone * i) == pearls) {

				printf("%d 달러짜리 %d개  %d달러짜리  %d개", cheaperone, maxnumberofpearls - i, cheaperone, i);
				break;
			}


		}
		printf("failed");

	}
}