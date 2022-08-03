// https://leetcode.cn/problems/k-th-smallest-in-lexicographical-order/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctime>

unsigned int string_to_int(const char *str);

void process_func(const int MAX_VALUE, int k);

void loop_find_solution(unsigned int n, unsigned int k);

int main(int argc, char *argv[])
{
    // const unsigned int SIZE = string_to_int(argv[1]);
    // const unsigned int k = string_to_int(argv[2]);

    unsigned int SIZE = 957747794;
    unsigned int k = 366107483;
    // process_func(SIZE, k);

    loop_find_solution(SIZE, k);

    return 0;
}
unsigned int mini_k_solution(unsigned int current_value, unsigned int current_index, const unsigned int max_value, const unsigned int target_index)
{
    bool find = false;

    while (!find)
    {
        if (current_index == target_index)
        {
            break;
        }

        // first go deeper
        if (current_value * 10 <= max_value)
        {
            current_value = current_value * 10;
            current_index++;
        }
        else
        {
            // go upper
            while (9 == (current_value % 10) || current_value + 1 > max_value)
            {
                current_value /= 10;
            }

            current_value++;
            current_index++;
        }
    }

    return current_value;
}

void loop_find_solution(unsigned int n, unsigned int k)
{
    time_t start = time(nullptr);

    unsigned int result = mini_k_solution(1, 1, n, k);

    time_t end = time(nullptr);
    printf("%u; time consume %f\n", result, difftime(end, start));
}

int str_compare(const void *p1, const void *p2)
{
    return strcmp((const char *)p1, (const char *)p2);
}

unsigned int string_to_int(const char *str)
{
    unsigned int sum = 0;
    int i = 0;

    while (str[i])
    {
        sum = (sum * 10) + (str[i] - '0');
        i++;
    }

    return sum;
}

int int_len(int value)
{
    int tmp = value;
    int len = 0;
    while (tmp)
    {
        len += 1;
        tmp /= 10;
    }

    return len;
}

void process_func(const int MAX_VALUE, int k)
{
    time_t start = time(nullptr);

    const int SIZE = MAX_VALUE;
    const int MAX_NUM_LEN = 11;

    char *p = new char[(unsigned int)(SIZE * MAX_NUM_LEN * sizeof(char))]();
    char(*parray)[MAX_NUM_LEN] = (char(*)[MAX_NUM_LEN])p;

    for (int i = 0; i < SIZE; i++)
    {
        int string_len = int_len(i + 1);

        for (int j = 0; j < string_len; j++)
        {
            parray[i][string_len - j - 1] = '0' + (((i + 1) / int(pow(10, j))) % 10);
        }

        parray[i][string_len] = 0;
    }

    qsort((void *)parray, SIZE, MAX_NUM_LEN * sizeof(char), str_compare);

    time_t end = time(nullptr);

    printf("%s; time consume %f\n", parray[k - 1], difftime(end, start));
}