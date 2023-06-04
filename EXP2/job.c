#include <stdio.h>
#include <stdlib.h>
#define N 5
struct job
{
    int id; //编号
    int arrive_time; //到达时间
    int serve_time; //服务时间
    int start_time; //开始时间
    int end_time; //结束时间
    int turn_over_time;
    double weight_turn_over_time;
} ;

typedef struct _job_pri {
    int id; //编号
    float arrive_time; //到达时间
    float serve_time; //服务时间
    float start_time; //开始时间
    float end_time; //结束时间
    float turn_over_time;
    float weight_turn_over_time;
    int priority; //优先级
} job_pri;

void FCFS()
{
    struct job p[N];
    int i;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("先来先服务（FCFS）算法：\n");
    printf("请输入%d个作业的到达时间和服务时间(按到达时间先后排序):\n", N);
    for (i = 0; i < N; i++)
        scanf("%d%d", &p[i].arrive_time, &p[i].serve_time);
    p[0].start_time = p[0].arrive_time;
    p[0].end_time = p[0].start_time + p[0].serve_time;
    p[0].turn_over_time = p[0].end_time - p[0].arrive_time;
    p[0].weight_turn_over_time = (p[0].end_time - p[0].arrive_time) * 1.0 / p[0].serve_time;
    for (i = 1; i < N; i++)
    {
        if (p[i - 1].end_time > p[i].arrive_time)
            p[i].start_time = p[i - 1].end_time;
        else
            p[i].start_time = p[i].arrive_time;
        p[i].end_time = p[i].start_time + p[i].serve_time;
        p[i].turn_over_time = p[i].end_time - p[i].arrive_time;
        p[i].weight_turn_over_time = (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("作业编号 到达时间 服务时间 开始时间 结束时间 周转时间      带权周转时间\n");
    for (i = 0; i < N; i++)
        printf("%-10d%-10d%-10d%-10d%-10d%-10d%-10f\n", i + 1, p[i].arrive_time, p[i].serve_time, p[i].start_time, p[i].end_time, p[i].turn_over_time, p[i].weight_turn_over_time);
    for (i = 0; i < N; i++)
    {
        sum_turnover_time += (p[i].end_time - p[i].arrive_time);
        sum_weight_turnover_time += (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("平均周转时间：%.2f\n", sum_turnover_time / N);
    printf("平均带权周转时间：%.2f\n", sum_weight_turnover_time / N);
}

void priority_first()
{
    job_pri p[N];
    int n = N, ptr = 0;
    float time = 0;
    int min = 0, min_index = 0;
    int num_ready = 0;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("优先权优先调度算法\n");
    printf("请输入%d个作业的到达时间和服务时间以及优先级(按到达时间先后排序):\n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%f%f%d", &p[i].arrive_time, &p[i].serve_time,&p[i].priority);
        p[i].id = i+1;
    }   
    while(n > 0)
    {
        for(int i=ptr;i<N;i++)
        {
            if(p[i].arrive_time <= time)
            {
                num_ready++;
            }
        }
        min = p[ptr].priority;
        min_index = ptr;
        for(int i=ptr;i<num_ready + ptr;i++)
        {
            if(p[i].priority < min)
            {
                min = p[i].priority;
                min_index = i;
            }
        }
        if(min_index != ptr)
        {
            job_pri tmp = p[min_index];
            p[min_index] = p[ptr];
            p[ptr] = tmp;
        }
        if(ptr != 0 && p[ptr].arrive_time < p[ptr-1].end_time)
        {
            p[ptr].start_time = p[ptr - 1].end_time;
        }
        else
        {
            p[ptr].start_time = p[ptr].arrive_time;
        }
        p[ptr].end_time = p[ptr].start_time + p[ptr].serve_time;
        p[ptr].turn_over_time = p[ptr].end_time - p[ptr].arrive_time;
        p[ptr].weight_turn_over_time = (p[ptr].end_time - p[ptr].arrive_time) * 1.0 / p[ptr].serve_time;
        n--;
        ptr++;
        time += p[ptr].serve_time;
        num_ready = 0;
    }
    printf("进程编号  到达时间  服务时间  优先级  开始时间  结束时间  周转时间      带权周转时间\n");
    for (int i = 0; i < N; i++)
        printf("%-10d%-10f%-10f%-10d%-10f%-10f%-10f%-12f\n", p[i].id, p[i].arrive_time, p[i].serve_time,p[i].priority, p[i].start_time, p[i].end_time, p[i].turn_over_time, p[i].weight_turn_over_time);
    for (int i = 0; i < N; i++)
    {
        sum_turnover_time += (p[i].end_time - p[i].arrive_time);
        sum_weight_turnover_time += (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("平均周转时间：%.2f\n", sum_turnover_time / N);
    printf("平均带权周转时间：%.2f\n", sum_weight_turnover_time / N);
}

void round_scheduler()
{
    struct job p[N];
    int i=0,ptr = 0;
    int num_ready=0;
    int save[N];
    int finish=0;
    int time = 0, piece = 1;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("简单轮转法调度算法\n");
    printf("请输入%d个作业的到达时间和服务时间(按到达时间先后排序):\n", N);
    for (i = 0; i < N; i++)
    {
        scanf("%d%d", &p[i].arrive_time, &p[i].serve_time);
        p[i].end_time = -1;
        p[i].start_time = -1;
        save[i] = 0;
    }
    while (finish != N)
    {   
        if(p[ptr].end_time != -1)
        {
            if(ptr == N)
            {
                ptr = 0;
            }
            else
            {
                ptr ++;
            }
            continue;
        }
        if(p[ptr].arrive_time <= time && p[ptr].end_time == -1)
        {
            save[ptr] += piece;
            if(p[ptr].start_time == -1)
            {
                p[ptr].start_time = time;
            }
            time += piece;
            if(save[ptr] == p[ptr].serve_time)
            {
                p[ptr].end_time = time;
                finish++;
            }
        }
        if(ptr == N)
        {
            ptr = 0;
        }
        else
        {
            ptr++;
        }
    }
    printf("作业编号 到达时间 服务时间 开始时间 结束时间 周转时间      带权周转时间\n");
    for(int i=0;i<N;i++)
    {
        p[i].turn_over_time = p[i].end_time - p[i].arrive_time;
        p[i].weight_turn_over_time = (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
        printf("%-10d%-10d%-10d%-10d%-10d%-10d%-10f\n", i + 1, p[i].arrive_time, p[i].serve_time, p[i].start_time, p[i].end_time, p[i].turn_over_time, p[i].weight_turn_over_time);
        sum_turnover_time += (p[i].end_time - p[i].arrive_time);
        sum_weight_turnover_time += (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("平均周转时间：%.2f\n", sum_turnover_time / N);
    printf("平均带权周转时间：%.2f\n", sum_weight_turnover_time / N);
}