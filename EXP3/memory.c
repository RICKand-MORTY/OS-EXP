#include <stdio.h>
#include <stdlib.h>

#define FREE                0
#define OCCUPIED            1
#define MEMORY_LENGTH       512
typedef struct  _Area
{
    int id;
    int size;
    int address;
    int flag;       //flag=1 means the ares is occupied,otherwise is free

}Area;

typedef struct _Linklist
{
    Area data;
    struct _Linklist* prior;
    struct _Linklist* next;

}*PLinklist,Linkist;


PLinklist head;
PLinklist tail;
PLinklist this;
//initial data structure    

void initial()
{
    head = (PLinklist)malloc(sizeof(Linkist));
    tail = (PLinklist)malloc(sizeof(Linkist));
    head->data.size = 0;
    head->data.flag = OCCUPIED;
    head->prior = NULL;
    head->next = tail;
    tail->prior = head;
    tail->next = NULL;
    tail->data.size = MEMORY_LENGTH;
    this = head->next;
}
int test_small(PLinklist node)
{
    PLinklist p=head->next;
    while (p!=NULL)
    {
        if(p->data.flag == FREE && p->data.size > node->data.size)
        {
            return 1;
        }
        p=p->next;
    }
    return 0;
}
int test_big(PLinklist node)
{
    PLinklist p=tail;
    while (p!=NULL)
    {
        if(p->data.flag==FREE && p->data.size > node->data.size)
        {
            return 1;
        }
        p=p->prior;
    }
    return 0;
}
void change_node_small(PLinklist node)
{
    PLinklist p=head->next;
    while (p!=NULL)
    {
        if(p->data.flag==FREE && p->data.size > node->data.size)
        {
            node->next = p;
            node->prior = p->prior;
            p->prior->next = node;
            p->prior = node;
            break;
        }
        p=p->next;
    }
}

void change_node_big(PLinklist node)
{
    PLinklist p=tail;
    while (p!=NULL)
    {
        if(p->data.flag==FREE && p->data.size > node->data.size)
        {
            node->prior = p;
            node->next = p->next;
            if(p->next != NULL)
            {
                p->next->prior = node;
            }
            p->next = node;
            if(p == tail)
            {
                tail = p->next;
            }
            break;
        }
        p=p->prior;
    }
}

int first_fit(int id,int size)
{
    PLinklist node = (PLinklist)malloc(sizeof(Linkist));
    PLinklist ptr = head->next;
    node->data.id = id;
    node->data.size = size;
    node->data.flag = OCCUPIED;
    while(ptr!=NULL)
    {
        if(ptr->next == NULL && ptr->data.size < size)
        {
            printf("空闲空间不足!\n");
            return 1;
        }
        if(ptr->data.id == id)
        {
            printf("id已存在,无法分配!\n");
            return 1;
        }
        else if(ptr->data.flag == FREE )
        {
            if(ptr->data.size == size)
            {
                ptr->data.flag == OCCUPIED;
                ptr->data.id == id;
                return 0;
            }
            else if(ptr->data.size > size)
            {
                node->next=ptr;
                node->prior=ptr->prior;
                node->data.address=ptr->data.address;
                ptr->prior->next=node;
                ptr->prior=node;
                ptr->data.address=node->data.address+node->data.size;
                ptr->data.size-=size;
                return 0;
            }
        }
        ptr = ptr->next;
    }
}

int cyclic_first_fit(int id,int size)
{
    PLinklist node = (PLinklist)malloc(sizeof(Linkist));
    PLinklist ptr = this;
    node->data.id = id;
    node->data.size = size;
    node->data.flag = OCCUPIED;
    while(ptr!=NULL)
    {
        if(ptr->next == this && ptr->data.size < size)
        {
            printf("空闲空间不足!\n");
            return 1;
        }
        if(ptr->data.id == id)
        {
            printf("id已存在,无法分配!\n");
            return 1;
        }
        else if(ptr->data.flag == FREE )
        {
            if(ptr->data.size == size)
            {
                ptr->data.flag == OCCUPIED;
                ptr->data.id == id;
                this = ptr;
                return 0;
            }
            else if(ptr->data.size > size)
            {
                node->next=ptr;
                node->prior=ptr->prior;
                node->data.address=ptr->data.address;
                ptr->prior->next=node;
                ptr->prior=node;
                ptr->data.address=node->data.address+node->data.size;
                ptr->data.size-=size;
                this = ptr;
                return 0;
            }
        }
        ptr = ptr->next;
        
    }
}

int best_fit()
{

} 

int worst_fit()
{

}

//alloc memeory
void alloc_memory(int (*alloc_func)(int,int))
{
    int id=0,size=0;
    printf("请输入作业号和所需内存大小： ");
    scanf("%d%d",&id,&size);

    if (id<=0 || size<=0)
        printf("错误！请输入正确的作业号和请求的内存大小");

    if(alloc_func(id,size) == 0)
        printf("分配成功！\n");
    else
        printf("分配失败！\n");
}

//free memory
int free_memory(int mode)
{
    int id=0;
    PLinklist ptr = head->next;
    PLinklist tmp = NULL;
    printf("输入需要释放内存的作业号：");
    scanf("%d",&id);
    while(ptr != NULL )
    {
        if(ptr->data.id == id)
        {
            ptr->data.id = 0;
            ptr->data.flag = FREE;
            if (ptr->prior->data.flag == FREE && ptr->next->data.flag == OCCUPIED)
            {
                //the prior area is free and the next area is occupied
                tmp = ptr->prior;
                ptr->prior->data.size += ptr->data.size;
                ptr->prior->next = ptr->next;
                ptr->next->prior = ptr->prior;
                free(ptr);
                if(mode == 3)
                {
                    if(test_small(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_small(tmp);
                    }
                }
                else if(mode == 4)
                {
                    if(test_big(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_big(tmp);
                    }
                } 
                printf("释放内存成功！\n");
                return 0;
            }
            if (ptr->next->data.flag == FREE && ptr->prior->data.flag == OCCUPIED) 
            {
                //prior area is occupied but the next area is free
                tmp = ptr;
                ptr->data.size += ptr->next->data.size;
                if(ptr->next->next!=NULL)
                {
                    ptr->next->next->prior = ptr;
                    ptr->next = ptr->next->next;
                }
                else
                {
                    ptr->next = ptr->next->next;
                }
                free(ptr->next);
                if(mode == 3)
                {
                    if(test_small(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_small(tmp);
                    }
                }
                else if(mode == 4)
                {
                    if(test_big(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_big(tmp);
                    }
                } 
                printf("释放内存成功！\n");
                return 0;
            }
            if(ptr->prior->data.flag == FREE && ptr->next->data.flag == FREE)
            {
                //both side of area is free
                tmp = ptr->prior;
                ptr->prior->data.size += ptr->data.size + ptr->next->data.size;
                if(ptr->next->next==NULL)
                {
                    ptr->next->next->prior = ptr->prior;
                    ptr->prior->next = ptr->next->next;
                }
                else
                {
                    ptr->prior->next = ptr->next->next;
                }
                free(ptr->next);
                free(ptr);
                if(mode == 3)
                {
                    if(test_small(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_small(tmp);
                    }
                }
                else if(mode == 4)
                {
                    if(test_big(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_big(tmp);
                    }
                } 
                printf("释放内存成功！\n");
                return 0;
            }
            tmp = ptr;
            if(mode == 3)
                {
                    if(test_small(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_small(tmp);
                    }
                }
                else if(mode == 4)
                {
                    if(test_big(tmp)==1)
                    {
                        tmp->prior->next = tmp->next;
                        if(tmp->next!=NULL)
                        {
                        tmp->next->prior = tmp->prior;
                        }
                        change_node_big(tmp);
                    }
                } 
            printf("释放内存成功！\n");
            return 0;
        }
        ptr = ptr->next;
    }
    if(ptr == NULL)
    {
        printf("内存中没有该作业！\n");
        return 1;
    }
}

void show_memory()
{
    printf("------------------");
    printf("内存分配情况");
    printf("------------------\n");
    PLinklist p = head->next;
    while(p)
    {
        printf("分区号：");
        if (p->data.id==FREE)
            printf("FREE\n");
        else
            printf("%d \n", p->data.id);
        printf("起始地址：%d\n", p->data.address);
        printf("内存大小：%d\n", p->data.size);
        printf("分区状态：");
        if (p->data.flag==FREE)
            printf("空闲\n");
        else
            printf("已分配\n");
        printf("------------------\n");
        p=p->next;
    }
}
