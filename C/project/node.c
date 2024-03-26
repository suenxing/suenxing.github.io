#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct node node;

struct node
{
    int value;
    node *next;
};

node *search(node *head, int value)
{
    node *p = head;
    for (int i = 0; p->next != NULL; ++i)
    {
        if (p->value == value)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

node *add(node *p, int value)
{
    node *f = (node *)malloc(sizeof(node));
    f->next = NULL;
    f->value = value;

    if (p->next == NULL)
    {
        p->next = f;
    }
    else
    {
        node *t = (node *)malloc(sizeof(node));
        t = p->next;
        p->next = f;
        f->next = t;
    }
}
node *add(node *p, node *new)
{

    if (p->next == NULL)
    {
        p->next = new;
    }
    else
    {
        new->next = p->next;
        p->next = new;
    }
}

node *del(node *p, int count)
{
    node *f = p, *q;
    for (size_t i = 0; i < count - 1; i++)
    {
        f = f->next;
    }
    q = f->next->next;
    free(f->next);
    f->next = q;
}
node *change(node *p, int count, int nvalue)
{
    node *f = p;
    for (size_t i = 0; i < count; i++)
    {
        f = f->next;
    }
    f->value = nvalue;
}
int main()
{
    node *head = (node *)malloc(sizeof(node));
    node *p = head;
    int lenth = 1, t;
    head->value = -1;
    head->next = NULL;
    for (int i = 0; i < 100; ++i)
    {
        node *s = (node *)malloc(sizeof(node));
        p->next = s;
        s->value = i;
        s->next = NULL;
        p = s;
        ++lenth;
    }

    for (int j = 0; j < 25; ++j)
    {
        p = head;
        srand((unsigned)time(NULL));
        t = rand();
        for (int i = 0; i < t % lenth - 1; ++i)
        {
            p = p->next;
        }
        if (p->next != NULL)
        {
            node *temp = p->next;
            p->next = p->next->next;
            free(temp);
            temp = NULL;
        }
        else
        {
            free(p);
            p = head;
        }
        --lenth;
    }

    for (int j = 0; j < 30; j++)
    {
        p = head;
        srand((unsigned)time(NULL));
        t = rand();
        for (int i = 0; i < t % lenth; ++i)
        {
            p = p->next;
        }
        p->value = -1;
    }

    p = head;
    t = rand() % lenth;
    for (int i = 0; p->next != NULL; ++i)
    {
        if (p->value == t)
        {
            printf("找到了%d，在%d个\n", t, i);
            goto goto_YES;
        }
        p = p->next;
    }
    printf("没找到~\n");
goto_YES:
    p = head;
    while (p->next != NULL)
    {
        printf("%d ", p->value);
        p = p->next;
    }
    system("pause");
    return 0;
}