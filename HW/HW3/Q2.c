#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 // 執行緒數量
#define POINTS_PER_THREAD 1000  // 每個執行緒產生的點數

int total_points = 0; // 總點數
int points_in_circle = 0; // 圓內點數
pthread_mutex_t mutex; // 互斥鎖

// 產生隨機點
void *generate_points(void *arg) {
    int i;
    int local_points_in_circle = 0;

    for (i = 0; i < POINTS_PER_THREAD; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            local_points_in_circle++;
        }
    }

    pthread_mutex_lock(&mutex); //上鎖
    // critical section
    points_in_circle += local_points_in_circle;
    total_points += POINTS_PER_THREAD;
    pthread_mutex_unlock(&mutex); //解鎖

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex, NULL);

    // 建立執行緒
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, generate_points, NULL);
    }

    // 等待執行緒結束
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 刪除互斥鎖
    pthread_mutex_destroy(&mutex);

    // 計算 pi
    double pi = 4.0 * (double)points_in_circle / total_points;
    printf("Estimated value of pi: %f\n", pi);

    return 0;
}
