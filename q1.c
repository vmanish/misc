#include <stdio.h>

void foo(float A[6][6], float b[6], double c[6]) {
	int i, j;
	for (i=0; i<6; i++) {
		c[i] = 0.0f;
		for(j=0; j < 6; j++) {
			c[i] += A[i][j]*b[j];
		}
	}
}


int main() {
	int i=0;
	float F[6][6] = {{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f},
					{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f},
					{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f},
					{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f},
					{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f},
					{1.0f,2.0f,3.0f,4.0f,5.0f,6.0f}
					};
	float x[6] = {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
	double y[6];
	foo(F, x, y);

	for (i=0; i< 6 ; i++) {
		printf("%f ", y[i]);
	}

	return 0;
}