#include <stdio.h>
int x;
int tmp;
int y;
int a;
int b;
int d;

int Extended_Euclid(int a, int b) {
	if (b == 0) {
		a = a;
		x = 1;
		y = 0;
		return y;
	}
	
	d = gcd(a, b);
	Extended_Euclid(b, a % b);
	tmp = x;
	x = y;
	y = tmp - ((int)(a / b) * y);
}

int gcd(int a, int b) {
	int gcd = 0;
	for (int i = 1; i <= a; i++) {
		if (a % i == 0 && b % i == 0) {
			gcd=i;
		}
	}
	return gcd;
}
void main() {
	scanf_s("%d %d", &a, &b);
	Extended_Euclid(a, b);
	printf("%d %d %d", d, x, y);

}