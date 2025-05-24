/*  已知活动总费用为totalCost，共有n个人参与活动，但每个人参与活动的时间不一样
    用float数组time表示每个人参与的时间
    time[0] = 1     表示第1个人参与了1个小时
    time[1] = 1.5   表示第2个人参与了1.5个小时
    ...
    time[n] = 2     表示第n个人参与了2个小时
    使用数组大小为n的数组 sharedCost 存储每个人分摊的费用
    请补充如下函数，让每个人公平的分摊活动费用
*/
#include <stdio.h>
#include <stdlib.h>

struct personTag {
    unsigned idx;
    float time;
    float cost;
};

int compare(const void *a, const void *b)
{
    struct personTag *person1 = (struct personTag*)a;
    struct personTag *person2 = (struct personTag*)b;
    return person1->time > person2->time;
}

float *getSharedActivityCost(float *time, unsigned n, float totalCost)
{
    float *sharedCost = (float*)malloc(n * sizeof(float));
    struct personTag *person = (struct personTag*)malloc(n * sizeof(struct personTag));

    for (int i = 0; i < n; i++) {
        person[i].idx = i;
        person[i].time = time[i];
    }

    qsort(person, n, sizeof(struct personTag), compare);

    printf("After qsort:\n");
    for (int i = 0; i < n; i++) {
        printf("time[%u]: %.1f", person[i].idx, person[i].time);
        if (i != n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    float totalTime = person[n - 1].time;

    printf("TotalTime: %.2f\n", totalTime);

    float *periodCost = (float*)malloc(n * sizeof(float));
    periodCost[0] = ((person[0].time / totalTime) * totalCost) / n;
    for (int i = 1; i < n; i++) {
        periodCost[i] = (((person[i].time - person[i - 1].time) / totalTime) * totalCost) / (n - i);
    }

    printf("PeriodCost:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f", periodCost[i]);
        if (i != n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    for (int i = 0; i < n; i++) {
        person[i].cost = 0;
        for (int j = 0; j <= i; j++) {
            person[i].cost += periodCost[j];
        }
    }
    for (int i = 0; i < n; i++) {
        sharedCost[person[i].idx] = person[i].cost;
    }

    return sharedCost;
}

void test_getSharedActivityCost() {
    float totalCost = 100.0;
    float time[] = {1.0, 1.5, 2.0};
    unsigned n = sizeof(time) / sizeof(time[0]);

    float *sharedCost = getSharedActivityCost(time, n, totalCost);

    printf("Total cost: %.2f\n", totalCost);
    printf("Time: ");
    for (unsigned i = 0; i < n; i++) {
        printf("%.2f ", time[i]);
    }
    printf("\nShared cost:\n");

    for (unsigned i = 0; i < n; i++) {
        printf("Person %u: %.2f\n", i + 1, sharedCost[i]);
    }

    free(sharedCost);
}

int main() {
    test_getSharedActivityCost();
    return 0;
}