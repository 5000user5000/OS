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
    printf("%d, ", n);
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
          printf("%d \n", n);
        }
        else{
          printf("%d, ", n);
        }
        
    }
    printf("The number of steps is %d \n", count);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
      printf("Please give a correct command，like ./test 25");
      exit(1);
    }
    
    int n = atoi(argv[1]); //char轉成int。附註:第二個參數才是數字，第一個是指令本身。
    int count = 0;
    pid_t pid;
    pid_t child_pid;
    int status, i;

    //scanf("%d", &n);
    //輸出必大於等於1
    if(n < 1){
      printf("Please not input less than 1 \n");
      exit(1);
    }
    
    // 建立子行程
    pid = fork();

    if (pid == 0) {
        printf("Child process! pid = 0 \n");
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
    
    if(pid==0){
        printf("child End! \n");
    }
    
    
    else{
        printf("Parent End! \n");
    }

    return 0;
}
