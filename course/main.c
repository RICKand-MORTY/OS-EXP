#include"schedule.h"
int main()
{
    int choice = 0;
    printf("请选择算法：1.先来先服务算法（FCFS）2.最短寻道时间优先算法（SSTF）3.扫描算法（SCAN）4.循环扫描算法（CSCAN）\n");
    printf("请输入序号：");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SSTF();
        break;
    case 3:
        SCAN();
        break;
    case 4:
        CSCAN();
        break;
    default:
        printf("输入有误!\n");
        break;
    }
}