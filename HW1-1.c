//Collatz conjecture with fork() and wait()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for fork()
#include <sys/types.h>  
#include <sys/wait.h>


void collatz(int n)
{

    int count = 0;
    while(n != 1)
    {
        //輸出格式
        if(n == 1){
          printf("%d", n);
        }
        else{
          printf("%d, ", n);
        }
        
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
        
    }
    printf("The number of steps is %d", count);
}

int main()
{
    int n;
    int count = 0;
    pid_t pid;
    pid_t child_pid;
    int status, i;

    scanf("%d", &n);
    if(n < 1){
      printf("Please not input less than 1 \n");
    }
    
    // 建立子行程
    pid = fork();
    //collatz(n);

    if (pid == 0) {
        printf("Child process! \n");
        collatz(n);
    } 
    else if (pid > 0) {
        // 父行程
        printf("Parent process! \n");
        sleep(1);
        printf("This is the parent process, wait for child...\n");
        child_pid = wait(&status);
        i = WEXITSTATUS(status);
        printf("child's pid =%d . exit status=%d \n", child_pid, i);
    } 
    else {
        // 錯誤
        printf("Error! \n");
    }

    printf(" End! \n");

    return 0;
}