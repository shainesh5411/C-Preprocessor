#include<stdio.h>
// Object-like macros
#define MAX 100
#define PI 3.14

/* Function-like macros */
#define SQUARE(x) ((x) * (x))
#define ADD(a,b) ((a) + (b))
#define AREA(r) (PI * (r) * (r))

int main()
{
    int arr[MAX > 10 ? 10 : 5];

    int a = 10;
    int b = 20;

    int sum = ADD(a,b);
    int square = SQUARE(5);

    float radius = 5;
    float area = AREA(radius);

    float nested = SQUARE(PI);

    printf("Sum = %d\n", sum);
    printf("Square = %d\n", square);
    printf("Area = %f\n", area);
    printf("Nested = %f\n", nested);

    return 0;
}
