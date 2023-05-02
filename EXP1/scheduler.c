#include <stdio.h>
#include <stdlib.h>
#define N 4
struct process
{
    int id; //进程编号
    int arrive_time; //到达时间
    int serve_time; //服务时间
    int start_time; //开始时间
    int end_time; //结束时间
    int turn_over_time;
    double weight_turn_over_time;
} ;
typedef struct PCB {
    int id; //进程编号
    float arrive_time; //到达时间
    float serve_time; //服务时间
    float start_time; //开始时间
    float end_time; //结束时间
    float turn_over_time;
    float weight_turn_over_time;
    double priority; //优先级（响应比）
} PCB;

void FCFS()
{
    struct process p[N];
    int i;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("请输入%d个进程的到达时间和服务时间：\n", N);
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
    printf("进程编号 到达时间 服务时间 开始时间 结束时间 周转时间      带权周转时间\n");
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

void SJF()
{
    struct process p[N];
    int n=N;
    int num_ready=0;
    int ptr=0;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("请输入%d个进程的到达时间和服务时间：\n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d%d", &p[i].arrive_time, &p[i].serve_time);
        p[i].id = i+1;
    }    
    while(n>0)
    {
        p[ptr].start_time = p[ptr].arrive_time;
        p[ptr].end_time = p[ptr].start_time + p[ptr].serve_time;
        p[ptr].turn_over_time = p[ptr].end_time - p[ptr].arrive_time;
        p[ptr].weight_turn_over_time = (p[ptr].end_time - p[ptr].arrive_time) * 1.0 / p[ptr].serve_time;
        n--;
        for(int i=ptr+1;i<N;i++)
        {
            if(p[i].arrive_time < p[ptr].end_time)
            {
                num_ready++;
            }
        }  
        for(int i=ptr+1;i<num_ready+ptr;i++)
        {
            if(p[i].serve_time > p[i+1].serve_time)
            {
                struct process tmp = p[i];
                p[i] = p[i+1];
                p[i+1] = tmp;
            }
        }
        for(int i=ptr+1;i<=num_ready+ptr+1; i++)
        {
            p[i].start_time = p[i-1].end_time;
            p[i].end_time = p[i].start_time + p[i].serve_time;
            p[i].turn_over_time = p[i].end_time - p[i].arrive_time;
            p[i].weight_turn_over_time = (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
        }
        n-=num_ready;
        ptr+=num_ready+1;
        num_ready=0;
    }
    printf("进程编号 到达时间 服务时间 开始时间 结束时间 周转时间      带权周转时间\n");
    for (int i = 0; i < N; i++)
        printf("%-10d%-10d%-10d%-10d%-10d%-10d%-10f\n", p[i].id, p[i].arrive_time, p[i].serve_time, p[i].start_time, p[i].end_time, p[i].turn_over_time, p[i].weight_turn_over_time);
    for (int i = 0; i < N; i++)
    {
        sum_turnover_time += (p[i].end_time - p[i].arrive_time);
        sum_weight_turnover_time += (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("平均周转时间：%.2f\n", sum_turnover_time / N);
    printf("平均带权周转时间：%.2f\n", sum_weight_turnover_time / N);
}

void HRN()
{
    PCB p[N];
    int ptr=0,num_ready=0;
    int n=N,min_index=0;
    float min = 0;
    int no_ready = 1;
    float sum_turnover_time = 0, sum_weight_turnover_time = 0;
    printf("请输入%d个进程的到达时间和服务时间: \n", N);
    for (int i = 0; i < N; i++)
    {
        scanf("%f%f", &p[i].arrive_time, &p[i].serve_time);
        p[i].id = i+1;
    }    
    while(n > 0)
    {
        if(no_ready == 1)
        {
            p[ptr].start_time = p[ptr].arrive_time;
        }
        else if (no_ready == 0)
        {
            p[ptr].start_time = p[ptr - 1].end_time;
        }
        p[ptr].end_time = p[ptr].start_time + p[ptr].serve_time;
        p[ptr].turn_over_time = p[ptr].end_time - p[ptr].arrive_time;
        p[ptr].weight_turn_over_time = (p[ptr].end_time - p[ptr].arrive_time) * 1.0 / p[ptr].serve_time;
        n--;
        for(int i=ptr+1;i<N;i++)
        {
            if(p[i].arrive_time < p[ptr].end_time)
            {
                num_ready++;
            }
        }  
        if(num_ready != 0)
        {
            no_ready = 0;
        }
        else 
        {
            no_ready = 1;
            ptr++;
            continue;
        }
        for(int i = ptr + 1;i < num_ready + ptr + 1;i++)
        {
            p[i].priority = 1 + ((p[ptr].end_time - p[i].arrive_time)* 1.0) / (p[i].serve_time * 1.0);
        }
        min = p[ptr + 1].priority;
        min_index = ptr + 1;
        for(int i = ptr+1;i < num_ready + ptr + 1;i++)
        {
            if(p[i].priority > min)
            {
                min = p[i].priority;
                min_index = i;
            }
        }
        if((ptr + 1) != min_index)
        {
            PCB tmp = p[min_index];
            p[min_index] = p[ptr + 1];
            p[ptr + 1] = tmp;
        }
        ptr++;
        num_ready=0;
        min_index=0;
    }
    printf("进程编号  到达时间  服务时间  开始时间  结束时间  周转时间      带权周转时间\n");
    for (int i = 0; i < N; i++)
        printf("%-10d%-10f%-10f%-10f%-10f%-10f%-10f\n", p[i].id, p[i].arrive_time, p[i].serve_time, p[i].start_time, p[i].end_time, p[i].turn_over_time, p[i].weight_turn_over_time);
    for (int i = 0; i < N; i++)
    {
        sum_turnover_time += (p[i].end_time - p[i].arrive_time);
        sum_weight_turnover_time += (p[i].end_time - p[i].arrive_time) * 1.0 / p[i].serve_time;
    }
    printf("平均周转时间：%.2f\n", sum_turnover_time / N);
    printf("平均带权周转时间：%.2f\n", sum_weight_turnover_time / N);
}
