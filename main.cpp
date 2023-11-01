#define MAT_OPERATION

#include <iostream>
#include "Mat.h"
using namespace std;

int main()
{
    srand(4247);
    float data[] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    MAT a = MAT(3,3);
    MAT b = MAT(3,3);
    MAT c = MAT(3,3);
    mat_rand(a,1,2);
    a.print_mat();
    mat_rand(b,1,2);
    b.print_mat();

    mat_sum(c,a,b);
    c.print_mat();

    mat_dot(c,a,b);
    c.print_mat();

    mat_mul(c,a,b);
    c.print_mat();
    a.deallocate();
    b.deallocate();
    c.getRow(1).print_mat();
    c.getCol(1).print_mat();
    c.clone().print_mat();
    return 0;
}
