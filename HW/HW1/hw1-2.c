#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for fork()
#include <sys/wait.h>


#define SHM_SIZE 1024  // 共享記憶體區域的大小
char* collatz(int n)
{
    int count = 0;
    char* str = malloc(1000);
    str[0] = '\0';  // 初始化字串
    sprintf(str, "%d, ", n);  // 將第一個數字加入字串中
    while (n != 1)
    {
        // 計算下一個數字
        if (n % 2 == 0)
        {
            n = n / 2;
            count++;
        }
        else
        {
            n = 3 * n + 1;
            count++;
        }

        // 加入數字到字串中
        if (n == 1)
            sprintf(str + strlen(str), "%d\n", n);  // 如果是最後一個數字，換行
        else
            sprintf(str + strlen(str), "%d, ", n);  // 如果不是最後一個數字，加上逗號和空格
    }
    printf("The number of steps is %d\n", count);
    return str;
}

int main() {

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


    const char *name = "/myshm";  // 共享記憶體區域的名稱
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);  // 創建共享記憶體區域
    if (fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(fd, SHM_SIZE) == -1) {  // 設置共享記憶體區域的大小
        perror("ftruncate");
        exit(1);
    }

    void *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {  // 將共享記憶體區域映射到進程地址空間中
        perror("mmap");
        exit(1);
    }
    

    // 建立子行程
    pid = fork();
    const char *msg ;

    if (pid == 0) {
        printf("Child process!\n");
        char* str = collatz(n);  // 讓子行程執行此collatz
        // 向共享記憶體區域中寫入數據
        sprintf(ptr, "%s", str);
        free(str);  // 釋放動態分配的記憶體
        exit(0);  // 子行程執行完畢，直接退出
    } 
    else{
        // 父行程
        printf("This is the parent process, wait for child...\n");
        //等待子行程的完成
        child_pid = wait(&status);
        i = WEXITSTATUS(status);
        printf("This is the parent process,and child's pid =%d . exit status=%d \n", child_pid, i);
         // 從共享內存區域中讀取數據
        printf("%s\n", (char *) ptr);

       if (munmap(ptr, SHM_SIZE) == -1) {  // 解除映射關係
        perror("munmap");
        exit(1);
        }

        if (shm_unlink(name) == -1) {  // 刪除共享記憶體區域
            perror("shm_unlink");
            exit(1);
        }
    
    
    } 
    


    return 0;
}

/*
輸出範例:
輸入:25
This is the parent process, wait for child...
Child process!
The number of steps is 23
This is the parent process,and child's pid =3732 . exit status=0 
25, 76, 38, 19, 58, 29, 88, 44, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
*/
