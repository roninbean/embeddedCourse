#include <stdio.h>
#include <math.h>

int main() {
    double a, z1, z2;

    printf("Enter 'a': ");
    scanf("%lf", &a);

    // given equations:
    z1 = 2 * pow(sin(3 * M_PI - 2 * a), 2) * pow(cos(5 * M_PI + 2 * a), 2);
    z2 = 0.25 - 0.25 * sin(5 * M_PI / 2 - 8 * a);

    printf("z1 = %f\n", z1);
    printf("z2 = %f\n", z2);

    return 0;
}