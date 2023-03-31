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

## hw1-3 <br>
使用unix pipe的方式，先讓子程序把源文件的內容寫入pipe，再讓父程序從pipe把內容寫入副本。
但副本會出現亂碼，尚未解決，應該是input.txt會多留一行空白出現問題。

> gcc -o filecopy  hw1-3.c <br>
> echo "Hello World" > input.txt
>./filecopy input.txt copy.txt
> cat copy.txt
