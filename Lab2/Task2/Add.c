
#include "deRigorich.h"

#include <math.h>

/* Произошла ли ошибка в ходе вычислений */
bool err;

/* Находит i-й элемент ряда */
double GetRowElem(double x, int i) {
    double tmp = pow(-1.0L, i-1) * pow(x, 2*i-1) / fact_float(2*i-1);
    if (!finite(tmp)) {
        err = true;
    }
	return tmp;
}

/* Находит сумму первых n элементов ряда */
double RowSin(double x, int n) {
	double t = 0.0L;
	for ( ; n > 0; n--) {
		t += GetRowElem(x, n);
	}
	if (!finite(t)) {
        err = true;
    }
	return t;
}

/* Находит N такое, что сумма ряда находится в e-окрестности */
int GetSinRowN(double x, double e) {
	int n = 1;
	double sum = x;
	while (absf(sum - sin(x)) > e) {
		n++;
		sum += GetRowElem(x, n);
        if (err || !finite(sum) || n > 1e6) {
            err = true;
            break;
        }
	}
	return n;
}

int main(void) {
    do {
        err = false;
        printf("Enter x: ");
        double x = StringReadFloat(stdin);
        StringIgnore(stdin);
        printf("Enter epsilon: ");
        double e = StringReadFloat(stdin);
        int n = GetSinRowN(x, e);
        if (!err) {
            double sum = RowSin(x, n);
            if (!err) {
                printf("sin(x) = %.15f = %.15f +- %.15f; n = %d\n", sin(x), sum, e, n);
            }
        }
    } while (err && printf("Calculation error!\nPlease enter others variables\n\n"));
	return 0;
}