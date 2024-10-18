#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct task
{
    char task_about[100];
    struct *task next;
};

struct category
{
    char category_name[100];
    struct task* tasks;
    struct category* next;
};

struct *task create_task(const char* task_about)
{
    struct task* newnode = malloc(sizeof(struct task));
    strcpy(newnode->task_about, task_about);
    newnode->next = NULL;
    return newnode;
}

struct category* create_category(const char* category_name)
{
    struct category* newnode = malloc(sizeof(struct category));
    strcpy(newnode->category_name, category_name);
    newnode->tasks = NULL;
    newnode->next = NULL;
    return newnode;
}

struct category* find_category(struct category* head, const char* category_name)
{
    struct category* node1 = head;
    while(node1 != NULL && strcmp(node1->category_name, category_name) != 0)
    {
        node1 = node1->next;
    }
    return node1;
}

void add_task(struct category* category_name, const char* task_about)
{
    struct task* new_task = create_task(task_about);
    new_task->next = category_name->tasks;
    category_name->tasks = new_task;
}

void delete_task(struct category* category_name, const char* task_about)
{
    struct task* node2 = category_name->tasks;
    struct task* prev = NULL;

    while(node2 !=  NULL && strcmp(node2->task_about, task_about)!=0 )
    {
        prev = node2;
        node2 = node2->next;
    }

    if(node2 != NULL)
    {
        if(prev==NULL)
        {
            category_name->tasks = node2->next;
        }
        else
        {
            prev->next = node2->next;
        }
        free(node2);
    }
}

int count_task(struct category* head)
{
    int count = 0;
    struct category* node1 = head;

    while(node1 != NULL)
    {
        struct task* task_node = node1->tasks;
        while(task_node!=NULL)
        {
            count++;
            task_node = task_node->next;
        }
    }
    return count;
}

void display_task_by_category(struct category* head)
{
    struct category* node1 = head;

    while(node1 != NULL)
    {
        printf("Category: %s\n", node1->category_name);
        struct task* task_node = node1->tasks;
        while(task_node != NULL)
        {
            printf(" -> Task: %s\n", task_node->task_about);
            task_node = task_node->next;
        }
        node1 = node1->next;
    }
}

int main()
{
    
}