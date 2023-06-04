#include "memory.h"

int (*alloc_func)(int,int);

int main()
{
    int choice;
    int mode;
    printf("选择动态分区分配算法：1.首次适应 2.循环首次适应 3.最佳适应 4.最坏适应\n");
    printf("请输入:");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        alloc_func = first_fit;
        mode = 1;
        break;
    case 2:
        alloc_func = cyclic_first_fit;
        mode =2;
        break;
    case 3:
        alloc_func = first_fit;
        mode = 3;
        break;
    case 4:
        alloc_func = first_fit;
        mode = 4;
        break;
    default:
        printf("输入有误！\n");
        return 0;
        break;
    }
    initial();
    int choice2 = 2;
    while(choice2 <= 4 && choice2 > 0)
    {
        printf("输入要进行的操作");
        printf("（1.分配内存，2.内存释放，3.退出程序）：");
        scanf("%d", &choice2);
        switch(choice2)
        {
        case 1:
            alloc_memory(alloc_func);
            show_memory();
            break;
        case 2:
            free_memory(mode);
            show_memory();
            break;
        default:
            printf("程序已退出！");
            return 0;
        }
    }
}