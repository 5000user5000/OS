# 使用教學
## hw1-1 <br>
使用fork()，讓子程序跑考拉茲猜想(Collatz conjecture)的運算。
> gcc -o  test hw1-1.c <br>
> ./test 25

附註:如果是使用colab的話，先把 hw1-1.c放到檔案區，之後上兩個指令前頭都加上'!' <br>
補充: gcc 是 c的編譯器 ， test是編譯出的exe，也就是會生成 test.exe ，-o 是 output ， hw1-1.c 是源代碼


## hw1-2 <br>
hw1-1的延伸，使用share memory的方式把子程序的運算結果傳給父程序來打印。

> gcc -o test2 hw1-2.c  -lrt <br>
> ./test2 25

附註:這個-lrt選項可以讓編譯器使用POSIX實時庫，這個庫包含了shm_open和shm_unlink等需要的函數。

## hw1-3 <br>
使用unix pipe的方式，先讓子程序把源文件的內容寫入pipe，再讓父程序從pipe把內容寫入副本。<br>
之前副本會出現亂碼，已經解決，把 write(fileCopy, readBuff, size); 的 size 改成 strlen(readBuff)。

> gcc -o filecopy  hw1-3.c <br>
> echo "Hello World" > input.txt <br>
>./filecopy input.txt copy.txt <br>
> cat copy.txt
