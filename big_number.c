#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
bool IsZeroBN(const BigNumber* bn) 
{
    if (bn == NULL) return true;

    for (size_t i = 0; i < bn->size; ++i) {
        if (bn->digits[i] != 0) return false;
    }
    return true;
}

BigNumber* CreateBN(const char* number) 
{
    if (number == NULL || strlen(number) == 0 || !IsIntString(number))
        return NULL;

    BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
    if (bn == NULL)
        return NULL;

    size_t size = strlen(number);
    if (*number == '-') 
    {
        bn->size = size - 1;
        bn->is_negative = true;
        number++;
    }
    else 
    {
        bn->size = size;
        bn->is_negative = false;
    }

    bn->digits = (unsigned char*)calloc(bn->size, sizeof(unsigned char));
    if (bn->digits == NULL)
    {
        free(bn);
        return NULL;
    }

    for (size_t i = 0; i < bn->size; ++i)
        bn->digits[i] = number[i] - '0';

    return bn;
}

void DeleteBN(BigNumber** bn)
{
    if (bn == NULL || *bn == NULL)
        return;

    free((*bn)->digits);
    (*bn)->digits = NULL;

    free(*bn);
    *bn = NULL;
}

void PrintBN(const BigNumber* bn)
{
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

BigNumber* AddBN(const BigNumber* a, const BigNumber* b)
{
    if (a == NULL || b == NULL)
        return NULL;

    if (a->is_negative && !b->is_negative) 
    {
        BigNumber* neg_a = CopyBN(a);
        neg_a->is_negative = false;
        BigNumber* result = SubtractBN(b, neg_a);
        DeleteBN(&neg_a);
        return result;
    }

    if (!a->is_negative && b->is_negative) 
    {
        BigNumber* neg_b = CopyBN(b);
        neg_b->is_negative = false;
        BigNumber* result = SubtractBN(a, neg_b);
        DeleteBN(&neg_b);
        return result;
    }

    size_t max_size = (a->size > b->size ? a->size : b->size) + 1;
    unsigned char* result_digits = (unsigned char*)calloc(max_size, sizeof(unsigned char));
    if (result_digits == NULL)
        return NULL;

    size_t a_index = a->size;
    size_t b_index = b->size;
    size_t res_index = max_size;

    int carry = 0;
    while (a_index > 0 || b_index > 0 || carry > 0)
    {
        int sum = carry;
        if (a_index > 0) sum += a->digits[--a_index];
        if (b_index > 0) sum += b->digits[--b_index];
        result_digits[--res_index] = sum % 10;
        carry = sum / 10;
    }

    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
    {
        free(result_digits);
        return NULL;
    }

    result->size = max_size;
    result->is_negative = a->is_negative;
    result->digits = result_digits;

    while (result->size > 1 && result->digits[0] == 0) 
    {
        my_memmove(result->digits, result->digits + 1, --result->size);
    }

    return result;
}

BigNumber* SubtractBN(const BigNumber* a, const BigNumber* b) 
{
    if (a == NULL || b == NULL)
        return NULL;

    if (a->is_negative && !b->is_negative)
    {
        BigNumber* neg_a = CopyBN(a);
        neg_a->is_negative = false;
        BigNumber* result = AddBN(neg_a, b);
        result->is_negative = true;
        DeleteBN(&neg_a);
        return result;
    }
    if (!a->is_negative && b->is_negative)
    {
        BigNumber* neg_b = CopyBN(b);
        neg_b->is_negative = false;
        BigNumber* result = AddBN(a, neg_b);
        DeleteBN(&neg_b);
        return result;
    }
    if (CompareBN(a, b) < 0)
    {
        BigNumber* result = SubtractBN(b, a);
        result->is_negative = !a->is_negative;
        return result;
    }
    size_t max_size = a->size;
    unsigned char* result_digits = (unsigned char*)calloc(max_size, sizeof(unsigned char));
    if (result_digits == NULL)
        return NULL;

    size_t a_index = a->size;
    size_t b_index = b->size;
    size_t res_index = max_size;

    int borrow = 0;
    while (a_index > 0 || b_index > 0)
    {
        int diff = borrow + (a_index > 0 ? a->digits[--a_index] : 0) - (b_index > 0 ? b->digits[--b_index] : 0);
        if (diff < 0) 
        {
            diff += 10;
            borrow = -1;
        }
        else {
            borrow = 0;
        }
        result_digits[--res_index] = diff;
    }

    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
    {
        free(result_digits);
        return NULL;
    }
    result->size = max_size;
    result->is_negative = a->is_negative;
    result->digits = result_digits;

    while (result->size > 1 && result->digits[0] == 0) 
    {
        my_memmove(result->digits, result->digits + 1, --result->size);
    }

    return result;
}

BigNumber* MultiplyBN(const BigNumber* a, const BigNumber* b) 
{
    if (a == NULL || b == NULL)
        return NULL;

    size_t result_size = a->size + b->size;
    unsigned char* result_digits = (unsigned char*)calloc(result_size, sizeof(unsigned char));
    if (result_digits == NULL)
        return NULL;

    for (size_t i = 0; i < a->size; ++i)
    {
        for (size_t j = 0; j < b->size; ++j) 
        {
            result_digits[i + j + 1] += a->digits[i] * b->digits[j];
        }
    }

    int carry = 0;
    for (size_t i = result_size; i > 0; --i) 
    {
        result_digits[i - 1] += carry;
        carry = result_digits[i - 1] / 10;
        result_digits[i - 1] %= 10;
    }

    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL) {
        free(result_digits);
        return NULL;
    }
    result->size = result_size;
    result->is_negative = a->is_negative != b->is_negative;
    result->digits = result_digits;

    while (result->size > 1 && result->digits[0] == 0) {
        my_memmove(result->digits, result->digits + 1, --result->size);
    }

    return result;
}
BigNumber* DivideBN(const BigNumber* a, const BigNumber* b)
{
    if (a == NULL || b == NULL || IsZeroBN(b)) {
        printf("Error: Division by zero or invalid input.\n");
        return NULL;
    }

    BigNumber* quotient = CreateBN("0");
    if (quotient == NULL) {
        printf("Error: Failed to create quotient.\n");
        return NULL;
    }

    BigNumber* remainder = CopyBN(a);
    if (remainder == NULL) {
        printf("Error: Failed to copy numerator.\n");
        DeleteBN(&quotient);
        return NULL;
    }

    while (CompareBN(remainder, b) >= 0)
    {
        size_t shift = remainder->size - b->size;
        BigNumber* shifted_b = ShiftLeftBN(b, shift);
        if (shifted_b == NULL) {
            printf("Error: Failed to shift divisor.\n");
            DeleteBN(&quotient);
            DeleteBN(&remainder);
            return NULL;
        }

        BigNumber* one = CreateBN("1");
        if (one == NULL) {
            printf("Error: Failed to create one.\n");
            DeleteBN(&quotient);
            DeleteBN(&remainder);
            DeleteBN(&shifted_b);
            return NULL;
        }

        BigNumber* one_shifted = ShiftLeftBN(one, shift);
        DeleteBN(&one);
        if (one_shifted == NULL) {
            printf("Error: Failed to shift one.\n");
            DeleteBN(&quotient);
            DeleteBN(&remainder);
            DeleteBN(&shifted_b);
            return NULL;
        }

        while (CompareBN(remainder, shifted_b) >= 0) {
            BigNumber* new_remainder = SubtractBN(remainder, shifted_b);
            if (new_remainder == NULL) {
                printf("Error: Failed to subtract shifted divisor from remainder.\n");
                DeleteBN(&quotient);
                DeleteBN(&remainder);
                DeleteBN(&shifted_b);
                DeleteBN(&one_shifted);
                return NULL;
            }
            DeleteBN(&remainder);
            remainder = new_remainder;

            BigNumber* new_quotient = AddBN(quotient, one_shifted);
            if (new_quotient == NULL) {
                printf("Error: Failed to add to quotient.\n");
                DeleteBN(&quotient);
                DeleteBN(&remainder);
                DeleteBN(&shifted_b);
                DeleteBN(&one_shifted);
                return NULL;
            }
            DeleteBN(&quotient);
            quotient = new_quotient;
        }

        DeleteBN(&shifted_b);
        DeleteBN(&one_shifted);
    }

    quotient->is_negative = a->is_negative != b->is_negative;
    DeleteBN(&remainder);
    return quotient;
}

int CompareBN(const BigNumber* a, const BigNumber* b) 
{
    if (a->size != b->size)
        return (int)(a->size - b->size);

    for (size_t i = 0; i < a->size; ++i) {
        if (a->digits[i] != b->digits[i])
            return (int)(a->digits[i] - b->digits[i]);
    }

    return 0;
}

BigNumber* ShiftLeftBN(const BigNumber* bn, size_t shifts) 
{
    if (bn == NULL || shifts == 0)
        return CopyBN(bn);

    BigNumber* result = (BigNumber*)malloc(sizeof(BigNumber));
    if (result == NULL)
        return NULL;

    result->size = bn->size + shifts;
    result->is_negative = bn->is_negative;
    result->digits = (unsigned char*)calloc(result->size, sizeof(unsigned char));
    if (result->digits == NULL) {
        free(result);
        return NULL;
    }

    my_memcpy(result->digits, bn->digits, bn->size);

    return result;
}

BigNumber* CopyBN(const BigNumber* bn) 
{
    if (bn == NULL)
        return NULL;

    BigNumber* copy = (BigNumber*)malloc(sizeof(BigNumber));
    if (copy == NULL)
        return NULL;

    copy->size = bn->size;
    copy->is_negative = bn->is_negative;
    copy->digits = (unsigned char*)malloc(copy->size * sizeof(unsigned char));
    if (copy->digits == NULL) {
        free(copy);
        return NULL;
    }
    my_memcpy(copy->digits, bn->digits, copy->size);

    return copy;
}