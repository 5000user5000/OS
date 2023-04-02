//file-copy using ordinary pipes
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <unistd.h> // for fork()
#include <string.h> // for memset()
#include <fcntl.h> // for open() ，O_RDWR|O_CREAT|O_APPEND

#define size 100

int main(int argc, char *argv[]) {
    int fd[2]; // 管道，fd[0]為讀取端，fd[1]為寫入端
    char readBuff[size]; //讀檔的暫存區
    pipe(fd); // 創建管道

    // 檢查參數數量
    if( argc != 3 ) 
    {
        printf("錯誤，指令格式應為 filecopy input.txt copy.txt\n");
        exit(1);
    }


    
    int fileOpen = open(argv[1], 0); // 0表示只用讀寫模式打開
    int fileCopy = open(argv[2], O_RDWR|O_CREAT|O_APPEND, 0666);//可讀寫模式|文件不存在則創建文件|追加內容都放在文件末尾|權限，文件所有者可讀寫，其他用戶可讀寫
    
    // 檢查文件是否打開成功
    if (fileOpen == -1 || fileCopy == -1) {
        printf("打開文件失敗\n");
        exit(1);
    }



    pid_t pid = fork(); // 創建子行程
    
    if (pid == 0) { // 子行程
        close(fd[1]); // 關閉寫入端
         while(read(fd[0], readBuff, sizeof(readBuff)) > 0) { // 從讀取端讀取內容
            write(fileCopy, readBuff, strlen(readBuff) - 1); // 將內容寫入文件
        }
        close(fd[0]); // 關閉讀取端
        close(fileOpen); // 關閉文件
        
    } else { // 父行程
        close(fd[0]); // 關閉讀取端，因爲我們只需要寫入端，否則會阻塞
        while(read(fileOpen, readBuff, sizeof(readBuff)) > 0) { // 從文件讀取內容
            write(fd[1], readBuff, strlen(readBuff) - 1); // 將內容寫入管道
            memset(readBuff, 0, sizeof(readBuff)); // 清空暫存區
        }
        close(fd[1]); // 關閉讀取端
        close(fileCopy); // 關閉文件

    }

    return 0;
}
/*
指令格式：.
gcc hw1-3.c -o filecopy
echo "Hello World" > input.txt
./filecopy input.txt copy.txt
cat copy.txt

*/



