#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t size;
    bool is_negative;
    unsigned char* digits;
} BigNumber;

BigNumber* CreateBN(const char* number);
void DeleteBN(BigNumber** bn);
void PrintBN(const BigNumber* bn);
int CompareBN(const BigNumber* bn1, const BigNumber* bn2);
BigNumber* SumBN(const BigNumber* bn1, const BigNumber* bn2);
BigNumber* SubtractBN(const BigNumber* bn1, const BigNumber* bn2);
BigNumber* MultiplyBN(const BigNumber* bn1, const BigNumber* bn2);
BigNumber* DivideBN(const BigNumber* bn1, const BigNumber* bn2);


