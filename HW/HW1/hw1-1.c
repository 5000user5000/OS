//Collatz conjecture with fork() and wait()
//使用fork()讓子行程執行Collatz , 父行程wait()直到子行程完成
//此程式是在colab環境(ubuntu)下執行

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork()
#include <sys/types.h>  
#include <sys/wait.h>


void collatz(int n)
{

    int count = 0;
    //先輸出第一個數字
    printf("%d,", n);
    while(n != 1)
    {
        
        
        //計算
        if(n % 2 == 0)
        {
            n = n / 2;
            count++;
        }
        else
        {
            n = 3 * n + 1;
            count++;
        }

        //輸出格式 (最後一個,也就是n==1時，後面不用加逗號)
        if(n == 1){
          printf("%d", n);
        }
        else{
          printf("%d, ", n);
        }
        
    }
    printf("The number of steps is %d \n", count);
}

int main()
{
    int n;
    int count = 0;
    pid_t pid;
    pid_t child_pid;
    int status, i;

    scanf("%d", &n);
    //輸出必大於等於1
    if(n < 1){
      printf("Please not input less than 1 \n");
    }
    
    // 建立子行程
    pid = fork();

    if (pid == 0) {
        printf("Child process! \n");
        collatz(n); //讓子行程執行此collatz
    } 
    else if (pid > 0) {
        // 父行程
        printf("This is the parent process, wait for child...\n");
        //等待子行程的完成
        child_pid = wait(&status);
        i = WEXITSTATUS(status);
        printf("This is the parent process,and child's pid =%d . exit status=%d \n", child_pid, i);
    } 
    else {
        // 錯誤
        printf("Error! \n");
    }

    printf("End! \n");

    return 0;
}

/*
範例輸出:

25
This is the parent process, wait for child...
Child process! 
25,76, 38, 19, 58, 29, 88, 44, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1The number of steps is 23 
End! 
This is the parent process,and child's pid =8361 . exit status=0 
End!     
*/



