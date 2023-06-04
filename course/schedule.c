#include <stdio.h>
#include <stdlib.h>
#define N   9

typedef struct _disk
{
    int visit;          //visit number
    int distance;
    int flag;           //indicate if visited
}Disk;

typedef struct _num
{
    int num;
    int flag;       //indicate if visited
}Num;

int abs_cal(int a, int b)
{
    if(a > b)
        return a - b;
    else
        return b - a;
}

int test_visit(Disk arr[])
{
    for(int i = 0; i < N ;i++)
    {
        if(arr[i].flag == 0)
        {
            return 1;
        }
    }
    return 0;
}

int test_out(int where, Disk arr[])
{
    for(int i = 0; i < N;i++)
    {
        if(arr[i].flag == 0)
        {
            if(arr[i].visit >= where)
            {
                return 1;
            }
        }
    }
    return -1;
}

int test_in(int where, Disk arr[])
{
    for(int i = 0; i < N;i++)
    {
        if(arr[i].flag == 0)
        {
            if(arr[i].visit <= where)
            {
                return 1;
            }
        }
    }
    return -1;
}

int find_smallest(int where, Disk arr[])
{
    int min = 0;
    int min_index = 0;
    for(int i = 0;i < N;i++)
    {
        if(arr[i].flag == 0)
        {
            if(arr[i].visit < where)
            {
                min = arr[i].visit;
                min_index = i;
                break;
            }
        }
    }
    for(int i = 0;i < N;i++)
    {
        if(arr[i].flag == 0)
        {
            if(arr[i].visit < min)
            {
                min = arr[i].visit;
                min_index = i;
            }
        }
    }
    return min_index;
}

void FCFS()
{
    int num[N];
    int where = 0;
    float average = 0;
    Disk result[N];   
    printf("输入%d个磁道号:",N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&num[i]);
    }
    printf("输入起始磁道号:");
    scanf("%d",&where);
    printf("磁道号  移动距离\n");
    for(int i = 0;i < N;i++)
    {
        //calculate moving distance
        result[i].visit = num[i];
        result[i].distance = abs_cal(where, num[i]);
        where = num[i];
        average += result[i].distance;
        printf("%-10d%-10d\n",result[i].visit,result[i].distance);
    }
    average = average / (N*1.0);
    printf("平均寻道长度为:%f\n",average);
}

void SSTF()
{
    Disk num[N];
    int where = 0;
    float average = 0;
    int finish = 0;
    int min = 0,min_index = 0;
    Disk result[N];   
    printf("输入%d个磁道号:",N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&num[i].visit);
        num[i].flag = 0;
    }
    printf("输入起始磁道号:");
    scanf("%d",&where);
    while (test_visit(num) != 0)
    {
        for(int i = 0;i < N;i++)
        {
            if(num[i].flag == 0)
            {
                num[i].distance = abs_cal(num[i].visit, where);
                min = num[i].distance;
                min_index = i;
            }
        }
        for(int i = 0;i < N;i++)
        {
            if(num[i].flag == 0)
            {
                if(num[i].distance < min)
                {
                    min = num[i].distance;
                    min_index = i;
                }
            }
        }
        result[finish].visit = num[min_index].visit;
        result[finish].distance = min;
        where =  result[finish].visit;
        finish++;
        num[min_index].flag = 1;
    }
    printf("磁道号  移动距离\n");
    for(int i = 0;i < N;i++)
    {
        //calculate moving distance
        average += result[i].distance;
        printf("%-10d%-10d\n",result[i].visit,result[i].distance);
    }
    
    average = average / (N*1.0);
    printf("平均寻道长度为:%f\n",average);
}

void SCAN()
{   
    Disk num[N];
    int where = 0;
    int distance = 0;
    float average = 0;
    int finish = 0;
    int min = 0,min_index = 0;
    Disk result[N];   
    printf("输入%d个磁道号:",N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&num[i].visit);
        num[i].flag = 0;
    }
    printf("输入起始磁道号:");
    scanf("%d",&where);
    while(test_out(where, num) != -1)
    {
        for(int i=0;i<N;i++)
        {
            if(num[i].flag == 0)
            {
                if(where == num[i].visit)
                {
                    result[finish].visit = where;
                    result[finish].distance = distance;
                    num[i].flag = 1;
                    finish++;
                    distance = 0;
                }
            }
        }
        if(test_out(where, num) == -1)
        {
            break;
        }
        distance++;
        where++;
    }
    distance = 0;
    while (test_in(where, num) != -1)
    {
        for(int i=0;i<N;i++)
        {
            if(num[i].flag == 0)
            {
                if(where == num[i].visit)
                {
                    result[finish].visit = where;
                    result[finish].distance = distance;
                    num[i].flag = 1;
                    finish++;
                    distance = 0;
                }
            }
        }
        where--;
        distance++;
    }
    printf("磁道号  移动距离\n");
    for(int i = 0;i < N;i++)
    {
        //calculate moving distance
        average += result[i].distance;
        printf("%-10d%-10d\n",result[i].visit,result[i].distance);
    }
    average = average / (N*1.0);
    printf("平均寻道长度为:%f\n",average);
}

void CSCAN()
{
    Disk num[N];
    int where = 0;
    int distance = 0;
    float average = 0;
    int finish = 0;
    int min = 0,min_index = 0;
    Disk result[N];   
    printf("输入%d个磁道号:",N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&num[i].visit);
        num[i].flag = 0;
    }
    printf("输入起始磁道号:");
    scanf("%d",&where);
    while(test_out(where, num) != -1)
    {
        for(int i=0;i<N;i++)
        {
            if(num[i].flag == 0)
            {
                if(where == num[i].visit)
                {
                    result[finish].visit = where;
                    result[finish].distance = distance;
                    num[i].flag = 1;
                    finish++;
                    distance = 0;
                }
            }
        }
        if(test_out(where, num) == -1)
        {
            break;
        }
        distance++;
        where++;
    }
    if(test_in(where, num) != -1)
    {
        int pos = find_smallest(where, num);
        result[finish].visit = num[pos].visit;
        result[finish].distance = abs_cal(num[pos].visit, where);
        where = num[pos].visit;
        num[pos].flag = 1;
        finish++;
    }
    while(test_out(where, num) != -1)
    {
        for(int i=0;i<N;i++)
        {
            if(num[i].flag == 0)
            {
                if(where == num[i].visit)
                {
                    result[finish].visit = where;
                    result[finish].distance = distance;
                    num[i].flag = 1;
                    finish++;
                    distance = 0;
                }
            }
        }
        if(test_out(where, num) == -1)
        {
            break;
        }
        distance++;
        where++;
    }
    printf("磁道号  移动距离\n");
    for(int i = 0;i < N;i++)
    {
        //calculate moving distance
        average += result[i].distance;
        printf("%-10d%-10d\n",result[i].visit,result[i].distance);
    }
    average = average / (N*1.0);
    printf("平均寻道长度为:%f\n",average);
}