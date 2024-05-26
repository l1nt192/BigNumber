#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
/**
 * @brief ���������, �������� �� ������ ����� ������
 * @param str ������� ������
 * @return true, ���� ������ ������������ ����� ����� �����, ����� false
 */
bool IsIntString(const char* str);
/**
 * @brief �������� n ���� �� ��������� � ����������.
 * @param dest ��������� �� ����� ����������, ���� ����� ����������� ������.
 * @param src ��������� �� ��������, ������ ����� ����������� ������.
 * @param n ���������� ����, ������� ����� �����������.
 * @return ��������� �� ����� ���������� (dest).
 */
void* my_memcpy(void* dest, const void* src, size_t n);
/**
 * @brief ���������� n ���� �� ��������� � ����������, ��������� ����������� ���������� �������� ������.
 * @param dest ��������� �� ����� ����������, ���� ����� ���������� ������.
 * @param src ��������� �� ��������, ������ ����� ���������� ������.
 * @param n ���������� ����, ������� ����� ����������.
 * @return ��������� �� ����� ���������� (dest).
 */
void* my_memmove(void* dest, const void* src, size_t n);
