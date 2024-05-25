#include <stdio.h>
#include "big_number.h"
int main() {
    BigNumber* bn1 = CreateBN("5");
    BigNumber* bn2 = CreateBN("-1");

    if (!bn1 || !bn2) {
        printf("Error creating BigNumber instances.\n");
        return 1;
    }

    BigNumber* sum = SumBN(bn1, bn2);
    if (sum) {
        printf("Sum: ");
        PrintBN(sum);
    }
    else {
        printf("Sum failed.\n");
    }

    BigNumber* diff = SubtractBN(bn1, bn2);
    if (diff) {
        printf("Difference: ");
        PrintBN(diff);
    }
    else {
        printf("Difference failed.\n");
    }

    BigNumber* prod = MultiplyBN(bn1, bn2);
    if (prod) {
        printf("Product: ");
        PrintBN(prod);
    }
    else {
        printf("Product failed.\n");
    }

   // BigNumber* quotient = DivideBN(bn2, bn1);
    //if (quotient) {
    //    printf("Quotient: ");
   //     PrintBN(quotient);
   // }
    //else {
    //    printf("Quotient failed.\n");
   // }

    // Освобождение памяти для всех созданных BigNumber
    //DeleteBN(&bn1);
   // DeleteBN(&bn2);
    //DeleteBN(&sum);
    //DeleteBN(&diff);
    //DeleteBN(&prod);
   // DeleteBN(&quotient);

    return 0;
}

