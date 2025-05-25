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

typedef struct SharedCostPersonTag {
    unsigned idx;
    float time;
    float cost;
} SharedCostPerson;

int compare(const void *a, const void *b)
{
    SharedCostPerson *person1 = (SharedCostPerson*)a;
    SharedCostPerson *person2 = (SharedCostPerson*)b;
    return (person1->time > person2->time) - (person1->time < person2->time);
}

float *getSharedActivityCost(float totalCost, SharedCostPerson *person, unsigned n)
{
    qsort(person, n, sizeof(SharedCostPerson), compare);

    printf("After qsort:\n");
    for (int i = 0; i < n; i++) {
        printf("person[%u]", person[i].idx + 1);
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

    float *sharedCost = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        sharedCost[person[i].idx] = person[i].cost;
    }

    free(periodCost);
    return sharedCost;
}

void UiEntry(float *totalCost, SharedCostPerson **person, unsigned *num)
{
    unsigned tempNum;
    float tempTotalCost;
    printf("This is a program calculating shared cost.\n");
    printf("\n");
    printf("Total cost of the badminton activity: ");
    scanf("%f", &tempTotalCost);
    printf("Total number of people participating the badminton activity: ");
    scanf("%u", &tempNum);
    printf("\n");

    SharedCostPerson *tempPerson = (SharedCostPerson*)malloc(tempNum * sizeof(SharedCostPerson));

    for (unsigned i = 0; i < tempNum; i++) {
        printf("---- Person %2u ----\n", i + 1);
        tempPerson[i].idx = i;

        printf("The participating time is: ");
        scanf("%f", &tempPerson[i].time);
    }
    printf("\n");

    *totalCost = tempTotalCost;
    *person = tempPerson;
    *num = tempNum;
}

int main()
{
    float totalCost = 0;
    SharedCostPerson *person = NULL;
    unsigned num = 0;

    UiEntry(&totalCost, &person, &num);

    float *sharedCost = getSharedActivityCost(totalCost, person, num);

    printf("\nShared cost:\n");
    for (unsigned i = 0; i < num; i++) {
        printf("Person[%u]: %.2f\n", i + 1, sharedCost[i]);
    }
    
    free(person);
    free(sharedCost);
    return 0;
}