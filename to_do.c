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
   struct category* categories = NULL;
   int choice;

   do
   {
        printf("\nWelcome TO-DO LIST\n");
        printf("\n");
        printf("1. Add category\n");
        printf("2. Add task\n");
        printf("3. Delete task\n");
        printf("4. Display category by task\n");
        printf("5. Count of all tasks\n");
        printf("6. Exit\n");
        printf("Get started now: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                char name_category[100];
                printf("Enter the name of the category: ");
                scanf("%s", name_category);
                struct category* new_category = create_category(name_category);
                new_category->next = categories;
                categories = new_category;
                break;

            case 2:
                char category_name[100];
                char task_about[100];
                printf("Enter the name of the category: ");
                scanf("%s", category_name);
                printf("Enter the task: ");
                scanf("%s", task_about);

                struct category* node1 = find_category(categories, category_name);
                if(node1 != NULL)
                {
                    add_task(node1, task_about);
                }
                else
                {
                    printf("Category is not found. Create a category by entering 1. \n");
                }
                break;

            case 3:
                char category_name[100];
                char task_about[100];
                printf("Enter the name of the category: ");
                scanf("%s", category_name);
                printf("Enter the task you want ot delete: ");
                scanf("%s", task_about);

                struct category* node1 = find_category(categories, category_name);
                if(node1 != NULL)
                {
                    delete_task(node1, task_about);
                }
                else
                {
                    printf("Sorry! The category is not found. \n");
                }
                break;
            
            case 4:
                display_task_by_category(categories);
                break;

            case 5:
                printf("Total number of tasks: %d\n", count_task(categories));
                break;

            case 6:
                break;

            default:
                printf("Invalid choice, please try again\n");
        }
    } while(choice != 6);
    return 0;
}