#include <stdio.h>
#include <stdlib.h>

//3�� data set�� ���� �� 
int n = 0;
int i = 0;//ū ���� ���������� �� Ƚ�� Ȯ�ο�
int getmaxindex(int testCase[], int check);
int issorted(int* arr, int lenth);
void flip(int spatusNum, int testCase[]);

int main() {
	//int testCase[n] = { 3,1,5,2,4 };
	int* data;
	//int numberOfData=0;
	int spatus;
	int top = 0;//�����Ҵ��ؼ� 5 �ڸ� ä���
	
	//dataset�ޱ�

	printf("���� ������ũ�� ���� : ");
	scanf_s("%d", &n);
	top = n ;
	data = (int*)malloc(sizeof(int) * n);
	printf("������ũ�� ���� : ");
	for (int i = 0; i < n; i++) {
		scanf_s("%d", &data[i]);

	}

	//print original one 
	for (int j = 0; j < n; j++) {
		printf(" %d ", data[j]);
	}

	//dataset ��Ʈ���� Ȯ�� �� flip����. 
	while (issorted(data, n)==0) {

		spatus = getmaxindex(data, i)+1;
		
		if (getmaxindex(data, i) == i) {
			i++;
		}
		else if (spatus == top) { //max���� top�� ������ �־��� ���� ��ü���� flip
			i++;
			if (i == n) break;
			flip(i, data); //i(���� ū ���� ���������� ���ִ� ) ���� testCase�� ������
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

int getmaxindex(int testCase[], int check) {//max���� ã�Ƴ� �� �ε����� ������ �Լ�
	int maxIndex;
	int max;
	int i = check+1;

	max = testCase[check];
	maxIndex = check;

	for (i; i < n; i++) {//���� ū �� Ȯ�ε� ������ ���������� �����鼭 max�� ã��
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

	if (spatus == 0)//flip(0)�� �ø��������� ����.
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


