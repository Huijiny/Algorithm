#include <stdio.h>
#include <stdlib.h>

//3개 data set에 대한 것 
int n = 0;
int i = 0;//큰 수가 마지막으로 간 횟수 확인용
int getmaxindex(int testCase[], int check);
int issorted(int* arr, int lenth);
void flip(int spatusNum, int testCase[]);

int main() {
	//int testCase[n] = { 3,1,5,2,4 };
	int* data;
	//int numberOfData=0;
	int spatus;
	int top = 0;//동적할당해서 5 자리 채우기
	
	//dataset받기

	printf("받을 팬케이크의 갯수 : ");
	scanf_s("%d", &n);
	top = n ;
	data = (int*)malloc(sizeof(int) * n);
	printf("팬케이크의 지름 : ");
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &data[i]);

	}

	//print original one 
	for (int j = 0; j < n; j++) {
		printf(" %d ", data[j]);
	}

	//dataset 소트여부 확인 후 flip결정. 
	while (issorted(data, n)==0) {

		spatus = getmaxindex(data, i)+1;
		
		if (getmaxindex(data, i) == i) {
			i++;
		}
		else if (spatus == top) { //max값이 top에 있으면 주어진 범위 전체에서 flip
			i++;
			if (i == n) break;
			flip(i, data); //i(가장 큰 수가 마지막으로 들어가있는 ) 부터 testCase를 리버스
		}
		else
			flip(spatus, data);

	}
	flip(0, data);
	free(data);
	return 0;
}

int issorted(int* arr, int lenth) {

	int i, j;

	for (i = 0; i < lenth; i++) {
		for (j = i + 1; j < lenth; j++) {
			if (arr[i] < arr[j]) {
				return 0;
			}
		}
	}
	return 1;
	

}

int getmaxindex(int testCase[], int check) {//max값을 찾아내 그 인덱스를 보내는 함수
	int maxIndex;
	int max;
	int i = check+1;

	max = testCase[check];
	maxIndex = check;

	for (i; i < n; i++) {//가장 큰 수 확인된 곳부터 맨위에까지 돌리면서 max값 찾기
		if (max <= testCase[i]) {
			max = testCase[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

void flip(int spatusNum, int testCase[]) {

	int spatus = spatusNum;
	int size = n;

	if (spatus == 0)//flip(0)면 플립하지말고 종료.
		printf(" -----> flip(0)");
	
	else {//flip

		for (int i = 0; i <= (n - (spatusNum - 1)) / 2; i++) {
			int temp;

			temp = testCase[spatusNum - 1];
			testCase[spatusNum - 1] = testCase[size - 1];
			testCase[size - 1] = temp;
			spatusNum++;
			size--;
		}

		printf("  flip(%d) ----->", spatus);
		for (int i = 0; i < n; i++) {
			printf(" %d ", testCase[i]);
		}
	}
	
}


