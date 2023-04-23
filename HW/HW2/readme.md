# 使用教學
## Q1 <br>
hw2作業，使用multithreaded的方式，首先輸入的多個數字，接著分成多個thread，一個算平均，一個找最大值，一個找最小值<br>
並額外做了中位數、(母體)標準差的計算。使用的變數型態為double，不是 int 。所以輸出的格式會是取小數兩位。<br>
> gcc -o Q1 Q1.c -lpthread -lm <br>
> ./Q1 <br>
> 任意輸入一串整數，注意用空格隔開就好，例如: 90 81 78 95 79 72 85

附註:如果是使用colab的話，先把 Q1.c放到檔案區，之後上兩個指令前頭都加上'!' <br>
補充: "-lpthread" 是為了使用<pthread.h>，而 "-lm" 是為了使用 <math.h>

## Q2 <br>
使用multithreaded去做merge sort，首先輸入的多個數字，把數字大致均分成2個subset，接著生成2個thread，各自去把分到的subset sort，完成後再生成1個thread去merge，最後由parent輸出結果<br>
> gcc -o Q2 Q2.c -lpthread <br>
> ./Q2 <br>
> 任意輸入一串整數，注意用空格隔開就好，例如: 90 81 78 95 79 72 85