#include <stddef.h>
#include <stdbool.h>
#include "my_string.h"
// BigNumber structure
typedef struct {
    size_t size;
    bool is_negative;
    unsigned char* digits;
} BigNumber;


/**
 * @brief ������� ������� ����� �� ������
 * @param number ������, �������������� ����� �����
 * @return ��������� �� ��������� ������� ����� ��� NULL, ���� ��������� ������
 */
BigNumber* CreateBN(const char* number);

/**
 * @brief ������� ������� ����� � ����������� ������
 * @param bn ������� ��������� �� ������� �����, ������� ����� �������
 */
void DeleteBN(BigNumber** bn);

/**
 * @brief ������� ������� ����� �� �������
 * @param bn ��������� �� ������� �����, ������� ����� �������
 */
void PrintBN(const BigNumber* bn);

/**
 * @brief ���������� ��� ������� �����
 * @param a ��������� �� ������ ������� �����
 * @param b ��������� �� ������ ������� �����
 * @return ��������� �� ��������� �������� ��� NULL, ���� ��������� ������
 */
BigNumber* AddBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief �������� ���� ������� ����� �� �������
 * @param a ��������� �� ����������� ������� �����
 * @param b ��������� �� ���������� ������� �����
 * @return ��������� �� ��������� ��������� ��� NULL, ���� ��������� ������
 */
BigNumber* SubtractBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief �������� ��� ������� �����
 * @param a ��������� �� ������ ������� �����
 * @param b ��������� �� ������ ������� �����
 * @return ��������� �� ��������� ��������� ��� NULL, ���� ��������� ������
 */
BigNumber* MultiplyBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief ����� ���� ������� ����� �� ������
 * @param a ��������� �� ������� ������� �����
 * @param b ��������� �� �������� ������� �����
 * @return ��������� �� ��������� ������� ��� NULL, ���� ��������� ������
 */
BigNumber* DivideBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief ���������� ��� ������� �����
 * @param a ��������� �� ������ ������� �����
 * @param b ��������� �� ������ ������� �����
 * @return ������������� ��������, ���� a ������ b, ������������� ��������, ���� a ������ b, � 0, ���� ��� �����
 */
int CompareBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief �������� ������� ����� ����� �� �������� ���������� �������
 * @param bn ��������� �� ������� �����
 * @param shifts ���������� ������� ��� ������
 * @return ��������� �� ��������� ������ ��� NULL, ���� ��������� ������
 */
BigNumber* ShiftLeftBN(const BigNumber* bn, size_t shifts);

/**
 * @brief �������� ������� �����
 * @param bn ��������� �� ������� ����� ��� �����������
 * @return ��������� �� ����� �������� ����� ��� NULL, ���� ��������� ������
 */
BigNumber* CopyBN(const BigNumber* bn);

/**
 * @brief ���������, �������� �� ������� ����� ������ ����
 * @param bn ��������� �� ������� �����
 * @return true, ���� ������� ����� ����� ����, ����� false
 */
bool IsZeroBN(const BigNumber* bn);



