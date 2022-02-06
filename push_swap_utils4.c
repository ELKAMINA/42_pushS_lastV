#include "push_swap.h"

int calc_median(t_list **head)
{
    int max;
    int min;
    int median;
    t_list *start;
    t_list *start2;

    start = *head;
    start2 = *head;
    min = lower(&start);
    max = higher(&start2);
    median = (max - min)/2;
    return(median);
}

int update_pos(t_list **head, t_list *oneNode)
{
    int     size;
    int     i;
    int     pos;
    t_list *temp;

    temp = *head;
    i = 1;
    pos = 1;
    size = ft_lstsize(*head);
    while (temp->data != oneNode->data & i <= size)
    {
        pos++;
        temp = temp->next;
        i++;
    }
    return(pos);
}

int middle (t_list **head)
{
    int size;
    int mid;

    size = ft_lstsize(*head);
    if (size % 2 != 0)
    {
        mid = (size + 1) / 2;
    }
    else 
        mid = size / 2;
    return (mid);
}

void circularing_LL(t_list **A)
{
    t_list  *copy;
    t_list  *head;

    copy = *A;
    head = *A;
    while (copy->next != NULL)
        copy = copy->next;
    copy->next = head;
    head->previous = copy;
}

void 	sorting_above_six(t_list **head_A, t_list **head_B)
{
    t_list *copy;
    // t_list *test;
    t_list *moving;
    t_list *current;
    t_list  *bais;
    int size;
    int i;

    bais = *head_B;
    i = 0;
    // test = (*head_A);
    size = ft_lstsize(*head_A);
    circularing_LL(head_A);
    copy = *head_A;
    while(i < size)
    {
        moving = copy;
        current = copy->next;
        while (current != copy)
        {
            if (current->data > moving->data)
            {
                moving = current;
                copy->sort += 1;
            }
            current = current->next;
        }
        copy = copy->next;
        i++;
    }
    node_to_sendtoB(head_A, size);
    // i = 0;
    // while(i < size)
    // {
    //     printf("[%d] --- {%d}\n", test->data, test->sort);
    //     test = test->next;
    //     i++;
    // }
}

int max_sort(t_list   **head, int size)
{
    int min_int;
    int max;
    int i;
    
    i = 0;
    min_int = -32767;
    max = min_int;
    while (i < size)
    {
        if  (max < (*head)->sort)
            max = (*head)->sort;
        *head = (*head)->next;
        i++;
    }
    return (max);
}

void node_to_sendtoB(t_list **A, int size)
{
    t_list *copy;
    int sort_max;
    t_list *moving;
    t_list *current;
    t_list  *test;
    int     i;

    copy = *A;
    test = (*A);
    sort_max = max_sort(A, size);
    while (copy->sort != sort_max)
        copy = copy->next;
    copy->boolean = 'T';
    moving = copy;
    current = copy->next;
    while (current != copy)
    {
        if (current->data > moving->data)
        {
            moving = current;
            moving->boolean = 'T';
        }
        current = current->next;
    }
    i = 0;
    while(i < size)
    {
        printf("[%d] --- {%c}\n", test->data, test->boolean);
        test = test->next;
        i++;
    }

}
// void sorting_under_hundred(t_list **head_A, t_list **head_B)
// {
//     int median;
//     t_list  *copy;
//     int length;
//     int pos;
//     int i;
//     int j;
//     int k;

//     i = 1;
//     j = 1;
//     k = 0;
//     median = calc_median(head_A);
//     copy = *head_A;
//     pos = 1;

//     while (copy != NULL)
//     {

//         // if (copy->data < median)
//         // {
//         //     pos = update_pos(head_A, copy);
//         //     if (pos == 1)
//         //         push_b(head_B, head_A);
//         //     else if (pos == 2)
//         //     {
//         //         swap_a(head_A);
//         //         push_b(head_B, head_A);
//         //     }
//         //     else if (pos <= middle(head_A))
//         //     {
//         //         while (i < pos)
//         //         {
//         //             rotate_a(head_A);
//         //             i++;v
//         //         }
//         //         push_b(head_B, head_A);
//         //     }
//         //     else
//         //     {
//         //         i = pos;
//         //         while (i <= ft_lstsize(*head_A))
//         //         {
//         //             rev_rotate_a(head_A);
//         //             i++;
//         //         }
//         //         push_b(head_B, head_A);
//         //     }
//         //     copy = *head_A;
//         //     i = 1;
//         // }
//         // else 
//         //     copy = copy->next;
//     }
//     sortList_ascending(head_A);
//     sortList_descending(head_B);
//     length = ft_lstsize(*head_B);
//     while (k < length)
//     {
//         push_a(head_A, head_B);
//         k++;
//     }
// }



