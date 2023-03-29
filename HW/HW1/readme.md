# 使用教學
## hw1-1 <br>
使用fork()，讓子程序跑考拉茲猜想(Collatz conjecture)的運算。
> gcc test -o hw1-1.c <br>
> ./test

附註:如果是使用collab的話，先把 hw1-1.c放到檔案區，之後上兩個指令前頭都加上'!' <br>
補充: gcc 是 c的編譯器 ， test是編譯出的exe，也就是會生成 test.exe ，-o 是 output ， hw1-1.c 是源代碼


## hw1-2 <br>
hw1-1的延伸，使用share memory的方式把子程序的運算結果傳給父程序來打印。

> gcc test -o hw1-1.c  -lrt <br>
> ./test

附註:這個-lrt選項可以讓編譯器使用POSIX實時庫，這個庫包含了shm_open和shm_unlink等需要的函數。
