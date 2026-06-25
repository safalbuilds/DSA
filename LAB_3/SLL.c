#include <stdio.h>
#include <stdlib.h>

struct SLL
{
    int data;
    struct SLL *next;
};

struct SLL *first = NULL, *last = NULL;

struct SLL *create_node(int element)
{
    struct SLL *NewNode = (struct SLL *)malloc(sizeof(struct SLL));
    NewNode->data = element;
    NewNode->next = NULL;
    return NewNode;
}

void insert_at_beginning(int element)
{
    struct SLL *NewNode = create_node(element);

    if (!first)
    {
        first = last = NewNode;
    }
    else
    {
        NewNode->next = first;
        first = NewNode;
    }
}

void insert_at_end(int element)
{
    struct SLL *NewNode = create_node(element);

    if (!first)
    {
        insert_at_beginning(element);
    }
    else
    {
        last->next = NewNode;
        last = NewNode;
    }
}

void insert_at_pos(int pos, int element)
{
    struct SLL *NewNode = create_node(element);

    if (pos == 1)
    {
        insert_at_beginning(element);
    }
    else
    {
        struct SLL *temp = first;
        for (int i = 1; i < pos - 1 && temp->next != NULL; i++)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            insert_at_end(element);
        }
        NewNode->next = temp->next;
        temp->next = NewNode;
    }
}

void delete_from_beginning()
{
    if (!first)
    {
        printf("SLL is empty");
    }
    else if (!first->next)
    {
        first = last = NULL;
    }
    else
    {
        first = first->next;
    }
}

void delete_from_end()
{
    struct SLL *temp = first;
    if (!first)
    {
        printf("SLL is empty");
    }
    else if (!first->next)
    {
        first = last = NULL;
    }
    else
    {
        while (temp->next != last)
        {
            temp = temp->next;
        }
        temp->next = NULL;
    }
}

void delete_from_pos(int pos)
{

    if (pos == 1)
    {
        delete_from_beginning();
    }
    else
    {
        struct SLL *temp = first;
        for (int i = 1; i < pos - 1 && temp->next != NULL; i++)
        {
            temp = temp->next;
        }
        struct SLL *tempp = temp->next;
        tempp= tempp->next;
        if (temp->next == NULL)
        {
            delete_from_end();
        }
        temp->next = tempp;
    }
}

void search(int element)
{
    int flag = 0;

    struct SLL *temp = first;
    while (temp != NULL)
    {
        if (temp->data == element)
        {
            flag = 1;
            printf("Element %d found\n", element);
            break;
            ;
        }
        temp = temp->next;
    }
    if (flag == 0)
    {
        printf("Element %d not found\n", element);
    }
}

void traversal()
{
    if (first != NULL)
    {
        struct SLL *temp = first;
        while (temp != NULL)
        {
            printf("%d -> ", temp->data);
            temp = temp->next;
        };
        printf("NULL\n");
    }
    else
    {
        printf("Empty SLL\n");
    }
}

int main()
{
    traversal();

    insert_at_end(100);
    traversal();

    insert_at_beginning(200);
    traversal();

    insert_at_end(300);
    traversal();

    insert_at_beginning(400);
    traversal();

    insert_at_pos(2, 500);
    traversal();

    // delete_from_beginning();
    // traversal();

    // delete_from_end();
    // traversal();

    // delete_from_pos(1);
    // traversal();

    delete_from_pos(3);
    traversal();

    search(200);
    search(300);
}