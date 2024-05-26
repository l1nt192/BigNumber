#include <stdio.h>
#include "big_number.h"

int main() {
    BigNumber* bn1 = CreateBN("55");
    BigNumber* bn2 = CreateBN("15");
    BigNumber* sum = AddBN(bn1, bn2);
    printf("Sum: ");
    PrintBN(sum);
    DeleteBN(&sum);
    BigNumber* diff = SubtractBN(bn1, bn2);
    printf("Difference: ");
    PrintBN(diff);
    DeleteBN(&diff);
    BigNumber* prod = MultiplyBN(bn1, bn2);
    printf("Product: ");
    PrintBN(prod);
    DeleteBN(&prod);
    if (!IsZeroBN(bn2)) 
    {
        BigNumber* quot = DivideBN(bn1, bn2);
        printf("Quotient: ");
        PrintBN(quot);
        DeleteBN(&quot);
    }
    else 
    {
        printf("Division by zero is not allowed.\n");
    }
    DeleteBN(&bn1);
    DeleteBN(&bn2);

    return 0;
}
