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
 * @brief Создает большое число из строки
 * @param number Строка, представляющая целое число
 * @return Указатель на созданное большое число или NULL, если произошла ошибка
 */
BigNumber* CreateBN(const char* number);

/**
 * @brief Удаляет большое число и освобождает память
 * @param bn Двойной указатель на большое число, которое нужно удалить
 */
void DeleteBN(BigNumber** bn);

/**
 * @brief Выводит большое число на консоль
 * @param bn Указатель на большое число, которое нужно вывести
 */
void PrintBN(const BigNumber* bn);

/**
 * @brief Складывает два больших числа
 * @param a Указатель на первое большое число
 * @param b Указатель на второе большое число
 * @return Указатель на результат сложения или NULL, если произошла ошибка
 */
BigNumber* AddBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief Вычитает одно большое число из другого
 * @param a Указатель на уменьшаемое большое число
 * @param b Указатель на вычитаемое большое число
 * @return Указатель на результат вычитания или NULL, если произошла ошибка
 */
BigNumber* SubtractBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief Умножает два больших числа
 * @param a Указатель на первое большое число
 * @param b Указатель на второе большое число
 * @return Указатель на результат умножения или NULL, если произошла ошибка
 */
BigNumber* MultiplyBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief Делит одно большое число на другое
 * @param a Указатель на делимое большое число
 * @param b Указатель на делитель большое число
 * @return Указатель на результат деления или NULL, если произошла ошибка
 */
BigNumber* DivideBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief Сравнивает два больших числа
 * @param a Указатель на первое большое число
 * @param b Указатель на второе большое число
 * @return Положительное значение, если a больше b, отрицательное значение, если a меньше b, и 0, если они равны
 */
int CompareBN(const BigNumber* a, const BigNumber* b);

/**
 * @brief Сдвигает большое число влево на заданное количество позиций
 * @param bn Указатель на большое число
 * @param shifts Количество позиций для сдвига
 * @return Указатель на результат сдвига или NULL, если произошла ошибка
 */
BigNumber* ShiftLeftBN(const BigNumber* bn, size_t shifts);

/**
 * @brief Копирует большое число
 * @param bn Указатель на большое число для копирования
 * @return Указатель на копию большого числа или NULL, если произошла ошибка
 */
BigNumber* CopyBN(const BigNumber* bn);

/**
 * @brief Проверяет, является ли большое число равным нулю
 * @param bn Указатель на большое число
 * @return true, если большое число равно нулю, иначе false
 */
bool IsZeroBN(const BigNumber* bn);



