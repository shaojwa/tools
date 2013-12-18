
#include <stdio.h>
#include <stdlib.h>

int binasearch(int *buf, int n, int tag);

int buf[] = {1, 3, 7, 9, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

int main(void)
{
    int index = 0, hit, count = 0;
    int len = sizeof(buf) / sizeof(int);
    printf("**** len of buf = %d ****\n", len);
    for(index = 0; index < 60; index++)
    {
        hit = binasearch(buf, len, index);
        if (-1 != hit)
        {
            printf("yes: tag = %d, index = %d, buf[index] = %d\n",
                index, hit, buf[hit]);
            count++;
        }
        else
        {
            printf("no: unfound: %d\n", index);
        }
    }
    printf("**** count = %d ****\n", count);
}

int binasearch(int *buf, int n, int tag)
{
    int left = 0, right = n - 1, mid = left + ((right - left) >> 1);
    do
    {
        if (tag == buf[mid])
            return mid;
        else if(tag < buf[mid])
            right = mid - 1;
        else 
            left = mid + 1;
        mid = left + ((right - left) >> 1);
    }while(left <= right);
    return -1;
}