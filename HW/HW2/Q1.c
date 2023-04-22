//hw2作業，使用multithreaded的方式，把輸入的多個數字，一個算平均，一個找最大值，一個找最小值

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAX 1000

double num[MAX];
int count = 0; //輸入的數字個數
double max = 0;
double min = 0;
double sum = 0;
double avg = 0;

//補充的部分
double median = 0;
double std = 0;



void *get_max(void *arg)
{
    int i;
    max = num[0];
    for(i = 0; i < count; i++)
    {
        if(num[i] > max)
            max = num[i];
    }
    //printf("max = %d, min = %d", max, min);
    return NULL;
}

void *get_min(void *arg)
{
    int i;
    min = num[0];
    for(i = 0; i < count; i++)
    {
        if(num[i] < min)
            min = num[i];
    }
    //printf("max = %d, min = %d", max, min);
    return NULL;
}

void *get_avg(void *arg)
{
    int i;
    for(i = 0; i < count; i++)
    {
        sum += num[i];
    }
    avg = sum / count;
    //printf("avg = %d ", avg);
    return NULL;
}

//計算中位數
void *get_median(void *arg)
{
    int i;
    double temp;

    //暴力排序
    for(i = 0; i < count; i++)
    {
        for(int j = i + 1; j < count; j++)
        {
            if(num[i] > num[j])
            {
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }

    //計算中位數
    if(count % 2 == 0)
        median = (num[count / 2] + num[count / 2 - 1]) / 2;
    else
        median = num[count / 2];


    return NULL;
}

//計算標準差
void *get_std(void *arg)
{
    int i;
    double temp = 0;
    for(i = 0; i < count; i++)
    {
        temp += (num[i] - avg) * (num[i] - avg);
    }
    std = sqrt(temp / count);
    return NULL;
}




int main()
{
    int i;
    char str[MAX];
    char *token;
    pthread_t t1, t2, t3;
    pthread_t t4, t5; //補充的部分
    
    //輸入數字(空格隔開)
    printf("Please input numbers: ");
    fgets(str, MAX, stdin);

    //將輸入的數字轉成int存入陣列
    token = strtok(str, " ");
    while(token != NULL)
    {
        num[count] = atoi(token);
        count++;
        token = strtok(NULL, " ");
    }
    
    //建立thread
    pthread_create(&t1, NULL, get_max, NULL);
    pthread_create(&t2, NULL, get_min, NULL);
    pthread_create(&t3, NULL, get_avg, NULL);

    //等待thread結束
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    //補充的部分
    pthread_create(&t4, NULL, get_median, NULL);
    pthread_create(&t5, NULL, get_std, NULL);
    //等待結束，因為標準差要用到平均值，所以要等平均值算完才能算
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    //輸出結果
    printf("The average value is %.2f \n", avg);
    printf("The minimum value is %.2f \n", min);
    printf("The maximum value is %.2f \n", max);
    printf("The median value is %.2f \n", median);
    printf("The standard deviation is %.2f \n", std);


    return 0;
}