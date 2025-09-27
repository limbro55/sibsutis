#include <stdio.h>
#include <math.h>

int main() {
    double s = 0;
    for (double i = 0.1; i < 2; i += 0.2){
	s += log(i);
}
    printf("%.3lf\n", s);
}
