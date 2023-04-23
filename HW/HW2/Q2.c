//hw2作業2，使用multithreaded的方式，把數列使用merge sort排序

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define MAX 1000
int count = 0; //輸入的數字個數
int num[MAX]; //輸入的數字
int ans[MAX]; //排序後的數字
int flag = 1; //判斷是subset1還是subset2

//傳送用的參數
typedef struct 
{
    int subset1[MAX], subset2[MAX];
} parameter;

//subset1, subset2排序
void *sort(void *arg)
{
    int i, j;
    int temp;
    int *num = (int *)arg;
    int len;
    
    //subset 長度，如果flag是1，就是subset1，長度是count/2，如果flag是0，就是subset2，長度是count-count/2
    if(flag)
    {
        len = count / 2;
        flag = 0;
    }
    else
    {
        len = count - count / 2;
    }

    //bubble sort
    for(i = 0; i < len; i++)
    {
        for(j = i + 1; j < len; j++)
        {
            if(num[i] > num[j])
            {
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
    }
    return NULL;
}

//合併 subset1 , subset2
void *merge(void *arg)
{
    parameter *param = (parameter *)arg;
    
    //兩個 subset
    int *subset1 = param->subset1;
    int *subset2 = param->subset2;
    //各自的長度
    int len1 = count/2;
    int len2 = count - len1;
    
    //兩個 subset 的 index 和 ans 的 index
    int i=0, j=0;
    int ans_idx = 0;

    //merge，如果subset1的數字小於subset2的，就先放subset1的，如果subset1的數字大於subset2的，就先放subset2的，如果相等，就先放subset1的
    while(i<len1 && j<len2)
    {
        if(subset1[i] < subset2[j])
        {
            ans[ans_idx++] = subset1[i++];
        }
        else if(subset1[i] > subset2[j])
        {
            ans[ans_idx++] = subset2[j++];
        }
        else{
            ans[ans_idx++] = subset1[i++]; 
        }
    }
    
    //如果subset1還有數字，就把subset1的數字放進ans
    while(i < len1) {
        ans[ans_idx++] = subset1[i++];
    }
    //同上
    while(j < len2) {
        ans[ans_idx++] = subset2[j++];
    }

    return NULL;
}

int main()
{
    char str[MAX];
    char *token;
    pthread_t t1, t2, t3;
    int half;
    parameter *param = (parameter *)malloc(sizeof(parameter));

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

    half = count / 2;
    
    //將數字分成兩個subset
    for (int i = 0; i < half; i++) {
        param->subset1[i] = num[i];
    }

    for (int i = half; i < count; i++) {
        param->subset2[i-half] = num[i];
    }
    
    //建立thread，執行sort，並等待thread結束
    pthread_create(&t1, NULL, sort, param->subset1);
    pthread_create(&t2, NULL, sort, param->subset2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //建立thread，執行merge，並等待thread結束
    pthread_create(&t3, NULL, merge, param);
    pthread_join(t3, NULL);

    //輸出排序後的數字
    for(int i = 0; i < count; i++)
    {
        printf("%d ", ans[i]);
    }
    
    free(param);

    return 0;
}