
#include "C:\BSUIR\C\deRigorich\deRigorich.h"

int main(void) {
	printf("Enter four-digit number:\n");
	int a = StringReadInt(stdin, 1000, 9999);
	int b = a / 100 + (a % 100) * 100;
	printf("%d -> %d\n", a, b);
	return 0;
}