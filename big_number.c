#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

BigNumber* CreateBN(const char* number) {
    if (number == NULL || strlen(number) == 0 || !IsIntString(number))
        return NULL;

    BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
    if (bn == NULL)
        return NULL;

    size_t size = strlen(number);
    if (*number == '-') {
        bn->size = size - 1;
        bn->is_negative = true;
        number++;
    }
    else {
        bn->size = size;
        bn->is_negative = false;
    }

    bn->digits = (unsigned char*)calloc(bn->size, sizeof(unsigned char));
    if (bn->digits == NULL) {
        free(bn);
        return NULL;
    }

    for (size_t i = 0; i < bn->size; ++i)
        bn->digits[i] = number[i] - '0';

    return bn;
}

void DeleteBN(BigNumber** bn) {
    if (bn == NULL || *bn == NULL)
        return;
    free((*bn)->digits);
    free(*bn);
    *bn = NULL;
}

void PrintBN(const BigNumber* bn) {
    if (bn == NULL) {
        printf("BigNumber is empty!\n");
        return;
    }

    if (bn->is_negative)
        printf("-");

    for (size_t i = 0; i < bn->size; ++i)
        printf("%u", bn->digits[i]);

    printf("\n");
}

int CompareBN(const BigNumber* bn1, const BigNumber* bn2) {
    if (bn1 == NULL || bn2 == NULL) {
        return 2;   // Indicate invalid comparison
    }

    // Compare based on sizes
    if (bn1->size > bn2->size) {
        return 1;
    }
    else if (bn1->size < bn2->size) {
        return -1;
    }

    // Compare based on individual digit values
    for (size_t i = 0; i < bn1->size; ++i) {
        if (bn1->digits[i] > bn2->digits[i]) {
            return 1;
        }
        else if (bn1->digits[i] < bn2->digits[i]) {
            return -1;
        }
    }

    return 0;  // Both numbers are equal
}

BigNumber* SumBN(const BigNumber* bn1, const BigNumber* bn2) {
    if (bn1 == NULL || bn2 == NULL) {
        return NULL;
    }

    // Если одно из чисел нулевое, вернем копию другого числа
    if (bn1->size == 1 && bn1->digits[0] == 0) {
        return CreateBN(bn2->is_negative ? "-" : "");
    }
    else if (bn2->size == 1 && bn2->digits[0] == 0) {
        return CreateBN(bn1->is_negative ? "-" : "");
    }

    // Если знаки чисел разные, приведем задачу к вычитанию
    if (bn1->is_negative != bn2->is_negative) {
        if (bn1->is_negative) {
            BigNumber* neg_bn1 = CreateBN(bn1->digits[0] == 0 ? bn1->digits + 1 : bn1->digits);
            BigNumber* result = SubtractBN(neg_bn1, bn2);
            DeleteBN(&neg_bn1);
            return result;
        }
        else {
            BigNumber* neg_bn2 = CreateBN(bn2->digits[0] == 0 ? bn2->digits + 1 : bn2->digits);
            BigNumber* result = SubtractBN(bn1, neg_bn2);
            DeleteBN(&neg_bn2);
            return result;
        }
    }

    // Если знаки одинаковые, складываем числа по модулю
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    result->size = (bn1->size > bn2->size ? bn1->size : bn2->size) + 1;
    result->digits = (unsigned char*)calloc(result->size, sizeof(unsigned char));
    if (result->digits == NULL) {
        free(result);
        return NULL;
    }

    int carry = 0;
    int sign = bn1->is_negative ? -1 : 1;

    for (int i = 0; i < result->size; ++i) {
        int digit_sum = carry;
        if (i < bn1->size)
            digit_sum += sign * bn1->digits[bn1->size - 1 - i];
        if (i < bn2->size)
            digit_sum += sign * bn2->digits[bn2->size - 1 - i];

        if (digit_sum < 0) {
            digit_sum += 10;
            carry = -1;
        }
        else {
            carry = digit_sum / 10;
        }

        result->digits[result->size - 1 - i] = abs(digit_sum) % 10;
    }

    // Определяем знак результата
    result->is_negative = carry < 0;
    if (result->is_negative) {
        for (int i = 0; i < result->size; ++i) {
            result->digits[i] = 9 - result->digits[i];
        }
        if (result->digits[result->size - 1] != 0) {
            result->digits[result->size - 1] = 10 - result->digits[result->size - 1];
        }
        else {
            int i = result->size - 2;
            while (result->digits[i] == 0 && i >= 0) {
                result->digits[i] = 9;
                --i;
            }
            if (i >= 0)
                result->digits[i] -= 1;
        }
    }

    // Удаляем ведущие нули
    size_t first_non_zero = 0;
    while (first_non_zero < result->size && result->digits[first_non_zero] == 0) {
        first_non_zero++;
    }

    if (first_non_zero == result->size) {
        result->size = 1;
    }
    else if (first_non_zero > 0) {
        for (size_t i = first_non_zero; i < result->size; ++i) {
            result->digits[i - first_non_zero] = result->digits[i];
        }
        result->size -= first_non_zero;
    }

    return result;
}


BigNumber* SubtractBN(const BigNumber* bn1, const BigNumber* bn2) {
    if (bn1 == NULL || bn2 == NULL) {
        return NULL;
    }

    if (bn1->size == 1 && bn1->digits[0] == 0) {
        BigNumber* neg_bn2 = CreateBN(bn2->digits[0] == 0 ? bn2->digits + 1 : bn2->digits);
        neg_bn2->is_negative = !bn2->is_negative;
        return neg_bn2;
    } else if (bn2->size == 1 && bn2->digits[0] == 0) {
        return CreateBN(bn1->digits[0] == 0 ? bn1->digits + 1 : bn1->digits);
    }

    // Если знаки чисел разные, приводим задачу к сложению
    if (bn1->is_negative != bn2->is_negative)
    {
        BigNumber* neg_bn2 = CreateBN(bn2->digits[0] == 0 ? bn2->digits + 1 : bn2->digits);
        neg_bn2->is_negative = !bn2->is_negative;
        BigNumber* result = SumBN(bn1, neg_bn2);
        DeleteBN(&neg_bn2);
        return result;
    }
    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    result->size = (bn1->size > bn2->size ? bn1->size : bn2->size) + 1;
    result->digits = (unsigned char*)calloc(result->size, sizeof(unsigned char));
    if (result->digits == NULL) {
        free(result);
        return NULL;
    }

    int borrow = 0;
    int sign = bn1->is_negative ? -1 : 1;

    for (int i = 0; i < result->size; ++i) {
        int digit_sub = borrow;
        if (i < bn1->size)
            digit_sub += sign * bn1->digits[bn1->size - 1 - i];
        if (i < bn2->size)
            digit_sub -= sign * bn2->digits[bn2->size - 1 - i];

        if (digit_sub < 0) {
            digit_sub += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        result->digits[result->size - 1 - i] = abs(digit_sub) % 10;
    }

    // Определяем знак результата
    result->is_negative = borrow < 0;
    if (result->is_negative) {
        for (int i = 0; i < result->size; ++i) {
            result->digits[i] = 9 - result->digits[i];
        }
        if (result->digits[result->size - 1] != 0) {
            result->digits[result->size - 1] = 10 - result->digits[result->size - 1];
        } else {
            int i = result->size - 2;
            while (result->digits[i] == 0 && i >= 0) {
                result->digits[i] = 9;
                --i;
            }
            if (i >= 0)
                result->digits[i] -= 1;
        }
    }

    // Удаляем ведущие нули
    size_t first_non_zero = 0;
    while (first_non_zero < result->size && result->digits[first_non_zero] == 0) {
        first_non_zero++;
    }

    if (first_non_zero == result->size) {
        result->size = 1;
    } else if (first_non_zero > 0) {
        for (size_t i = first_non_zero; i < result->size; ++i) {
            result->digits[i - first_non_zero] = result->digits[i];
        }
        result->size -= first_non_zero;
    }

    return result;
}
BigNumber* MultiplyBN(const BigNumber* bn1, const BigNumber* bn2) 
{
    if (bn1 == NULL || bn2 == NULL) {
        return NULL;
    }

    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    result->size = bn1->size + bn2->size;
    result->digits = (unsigned char*)calloc(result->size, sizeof(unsigned char));
    if (result->digits == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < bn1->size; ++i) {
        int carry = 0;
        for (int j = 0; j < bn2->size; ++j) {
            int mul = bn1->digits[bn1->size - 1 - i] * bn2->digits[bn2->size - 1 - j] + carry + result->digits[result->size - 1 - (i + j)];
            carry = mul / 10;
            result->digits[result->size - 1 - (i + j)] = mul % 10;
        }
        result->digits[result->size - 1 - (i + bn2->size)] += carry;
    }

    // Удаляем ведущие нули
    size_t first_non_zero = 0;
    while (first_non_zero < result->size && result->digits[first_non_zero] == 0) {
        first_non_zero++;
    }

    if (first_non_zero == result->size) {
        result->size = 1;
    }
    else if (first_non_zero > 0) {
        for (size_t i = first_non_zero; i < result->size; ++i) {
            result->digits[i - first_non_zero] = result->digits[i];
        }
        result->size -= first_non_zero;
    }

    result->is_negative = bn1->is_negative != bn2->is_negative;

    return result;
}





