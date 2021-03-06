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

void get_index(t_list **head)
{
    t_list *copy;
    int    i;

    copy = *head;
    i = 1;
    while(copy)
    {
        copy->index = i;
        copy = copy->next;
        i++;
    }
}

int update_pos(t_list **head, t_list *oneNode, int size)
{
    int     i;
    int     pos;
    t_list *temp;

    temp = *head;
    i = 1;
    pos = 1;
    while ((temp->data != oneNode->data) & (i <= size))
    {
        pos++;
        temp = temp->next;
        i++;
    }
    return(pos);
}

int middle (int size)
{
    int mid;

    if (size % 2 != 0)
    {
        mid = (size + 1) / 2;
    }
    else 
        mid = size / 2;
    return (mid);
}

void decircularing(t_list **A, int size)
{
  t_list *copy;
  int i;

  i = 0;
  copy = *A;
  copy->previous = NULL;
  while (i < size - 1)
  {
      copy = copy->next;
      i++;
  }
  copy->next = NULL;
}

// Ok envoie bien les bons dans B et laisse les T dans A
void  cost_calculation_pushtoB(t_list **head_A, t_list **head_B, int size)
{
    decircularing(head_A, size);
    t_list  *copy;
    int i;

    i = 1;
    copy = *head_A;
    get_index(head_A);
    while (copy)
    {
        if (copy->boolean == 'F')
        {
            if (copy->index == 1)
                push_b(head_B, head_A);
            else if (copy->index == 2)
            {
                swap_a(head_A);
                push_b(head_B, head_A);
            }
            else if (copy->index <= middle(ft_lstsize(*head_A)))
            {
                while (i < copy->index)
                {
                    rotate_a(head_A);
                    i++;
                }
                push_b(head_B, head_A);
            }
            else
            {
                i = copy->index;
                while (i <= ft_lstsize(*head_A))
                {
                    rev_rotate_a(head_A);
                    i++;
                }
                push_b(head_B, head_A);
            }
            copy = *head_A;
            get_index(head_A);
            i = 1;
        }
        else
            copy = copy->next;
        i = 1;
    }
}

void cost_calculation_toheadList(t_list **head)
{
    t_list *copy;
    int size;
    int i;

    copy = *head;
    i = 0;
    size = ft_lstsize(*head);
    get_index(head);
    while (copy)
    {
        if (copy->index == 1)
            copy->moves = 0;
        else if (copy->index == 2)
            copy->moves = 1;
        else if (copy->index <= middle(size))
        {
            while (i < copy->index - 1)
            {
                copy->moves += 1;
                i++;
            }
        }
        else
        {
            i = copy->index;
            while (i <= size)
            {
                copy->moves += 1;
                i++;
            }
        }
        //printf("copy data : (%d) ==> copy moves : (%d) ==> copy index : (%d)\n", copy->data, copy->moves, copy->index);
        copy = copy->next;
        i = 0;
    }
}

void pushing_toheadListB(t_list **headB, int index)
{
    t_list *copy;
    int size;
    int i;

    i = 0;
    copy = *headB;
    size = ft_lstsize(*headB);
    get_index(headB);
    while (copy->index != index)
        copy = copy->next;
    if (copy->index == 1)
        return ;
    else if (copy->index == 2)
        swap_b(headB);
    else if (copy->index <= middle(size))
    {
        while (i < copy->index - 1)
        {
            rotate_b(headB);
            i++;
        }
    }
    else
    {
        i = copy->index;
        while (i <= size)
        {
            rev_rotate_b(headB);
            i++;
        }
    }
}

void pushing_toheadListA(t_list **headA, int index, int size)
{
    t_list *copy;
    int i;

    i = 0;
    copy = *headA;
    get_index(headA);
    while (copy->index != index)
        copy = copy->next;
    if (copy->index == 1)
        return ;
    else if (copy->index == 2)
        rotate_a(headA);
    else if (copy->index <= middle(size))
    {
        while (i < copy->index - 1)
        {
            rotate_a(headA);
            i++;
        }
    }
    else
    {
        i = copy->index;
        while (i <= size)
        {
            rev_rotate_a(headA);
            i++;
        }
    }
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


int max_sort(t_list   **head, int size)
{
    int min_int;
    int max;
    int i;
    
    i = 0;
    min_int = -2147483648;
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

int min_moves(t_list   **head)
{
    int min;
    t_list *copy;
    int max_int;

    copy = *head;
    max_int = 2147483647;
    min = max_int;
    while (copy)
    {
        if  (min > copy->total_moves)
            min = copy->total_moves;
        copy = copy->next;
    }
    return (min);
}

void node_to_sendtoB(t_list **A, t_list **B, int size)
{
    t_list *copy;
    int     sort_max;
    t_list *moving;
    t_list *current;

    copy = *A;
    sort_max = max_sort(A, size);
    while (copy->sort != sort_max)
        copy = copy->next;
    copy->boolean = 'T';
    //printf("FIRST ELEMENT: DATA------> %d, SORT : %d ---> Boolean : %c\n", copy->data, copy->sort, copy->boolean);
    moving = copy;
    current = copy->next;
    while (current != copy)
    {
        if (current->data > moving->data)
        {
            moving = current;
            moving->boolean = 'T';
        }
        //printf("to stack B or not : DATA------> %d, SORT : %d ---> Boolean : %c\n", current->data, current->sort, current->boolean);
        current = current->next;
    }
    cost_calculation_pushtoB(A, B, size);
}

int check_pos_in_A(t_list **A, t_list *oneNode)
{
    t_list *copy;
    t_list *copyformin;
    int lowest;
    int i;

    copy = *A;
    copyformin = *A;
    lowest = lower(&copyformin);
    i = 1;
    get_index(A);
    while (copy && copy->next)
    {
        if (copy->data < oneNode->data && copy->next->data > oneNode->data)
            return (i);
        else if (copy->data == lowest && oneNode->data < copy->data)
            return (copy->index - 1);
        copy = copy->next;
        i++;
    }
    if (copy->data == lowest && oneNode->data < copy->data)
            return (copy->index - 1);
    return (0);
}

void get_cost_to_positionNodeB_inA(t_list **headA, t_list **headB)
{
    t_list  *copyA;
    t_list  *copyB;

    get_index(headA);
    get_index(headB);
    cost_calculation_toheadList(headB);
    cost_calculation_toheadList(headA);
    copyA = *headA;
    copyB = *headB;
    // write(1, "A\n", 2);
    // while (copyA)
    // {
    //     printf("COPY A = %d ------- copyA->moves ==>%d\n", copyA->data, copyA->moves);
    //     copyA = copyA->next;
    // }
    // write(1, "B\n", 2);
    // while (copyB)
    // {
    //     printf("COPY B = %d ------- copyB->moves ==>%d\n", copyB->data, copyB->moves);
    //     copyB = copyB->next;
    // }
    // copyA = *headA;
    // copyB = *headB;
    while(copyB)
    {
        copyB->posinA = check_pos_in_A(headA, copyB) + 1;
        while (copyB->posinA != copyA->index)
            copyA = copyA->next;
        copyB->total_moves = copyA->moves + copyB->moves + 1;
        copyB = copyB->next;
        copyA = *headA;
    }
    // copyB = *headB;
    // write(1, "TOTAL MOVES B\n", 15);
    // while (copyB)
    // {
    //     printf("DATA = %d ====== copyB->total moves ==>%d\n", copyB->data, copyB->total_moves);
    //     copyB = copyB->next;
    // }
}

void ft_optimise(t_list **head_A, t_list **head_B, t_list *copyA, t_list *copyB)
{
 int discard;
 int i;
 t_list *same1;
 t_list *same2;

same1 = *head_A;
same2 = *head_B;
while (same1->data != copyA->data)
    same1 = same1->next;
while (same2->data != copyB->data)
    same2 = same2->next;
// printf("same1 data = %d,  copyA->index ==>%d, copyA->moves ==>%d\n", same1->data, same1->index, same1->moves);
// printf("same2 = %d, copyB->index ==>%d, copyB->moves ==>%d ---> copyB->total moves ==>%d \n", same2->data, same2->index, same2->moves, same2->total_moves);
 discard = same1->moves - same2->moves;
 //printf("discard ==>%d\n", discard);
 i = 1;
 if (same1->moves == 0 && same2->moves > 0)
    pushing_toheadListB(head_B, same2->index);
 else if (same2->moves == 0 && same1->moves > 0)
    pushing_toheadListA(head_A, same1->index, ft_lstsize(*head_A));
// else if (same1->index == 2 && same2->index == 2)
//     ss(head_A, head_B);
else if (same1->index <= middle(ft_lstsize(*head_A)) && same2->index <= middle(ft_lstsize(*head_B)))
 {
     if (discard == 0)
     {
        while (i <= copyB->moves)
        {
            rr(head_A, head_B);
            i++;
        }
     }
     else if (discard < 0)
     {
         while (i <= copyA->moves)
         {
            rr(head_A, head_B);
            i++;
         }
         //discard *= -1;
         while (discard != 0)
         {
            rotate_b(head_B);
            discard++;
         }
     }
    else
     {
         while (i <= copyB->moves)
         {
            rr(head_A, head_B);
            i++;
         }
         while (discard != 0)
         {
            rotate_a(head_A);
            discard--;
         }
     }  
 }
 else if (same1->index > middle(ft_lstsize(*head_A)) && same2->index > middle(ft_lstsize(*head_B)))
 {
    if (discard == 0)
    {
        while (i <= copyB->moves)
        {
            rrr(head_A, head_B);
            i++;
        }
    }
    else if (discard < 0)
    {
        while (i <= copyA->moves)
        {
            rrr(head_A, head_B);
            i++;
        }
        discard *= -1;
        while (discard != 0)
        {
            rev_rotate_b(head_B);
            discard--;
        }
    }
    else
    {
        while (i <= copyB->moves)
        {
            rrr(head_A, head_B);
            i++;
        }
        while (discard != 0)
        {
            rev_rotate_a(head_A);
            discard--;
        }
    }  
 }
 else
 {
    pushing_toheadListB(head_B, copyB->index);
    pushing_toheadListA(head_A, copyA->index, ft_lstsize(*head_A));
 }
}

void get_moves_to_zero(t_list **headA, t_list **headB)
{
    t_list *copyA;
    t_list *copyB;

    copyA = *headA;
    copyB = *headB;
    while (copyA)
    {
        copyA->moves = 0;
        copyA->total_moves = 0;
        copyA = copyA->next;
    }
     while (copyB)
    {
        copyB->moves = 0;
        copyB->total_moves = 0;
        copyB = copyB->next;
    }
}

void pushing_to_A(t_list **head_A, t_list **head_B)
{
    t_list *copyA;
    t_list *copyB;
    t_list *sec_copyB;

    copyA = *head_A;
    copyB = *head_B;    
    sec_copyB = *head_B;
    get_moves_to_zero(head_A, head_B);
    get_cost_to_positionNodeB_inA(head_A, head_B);
    while(copyB->total_moves != min_moves(&sec_copyB))
        copyB = copyB->next;
    //printf("test\n");
    copyB->posinA = check_pos_in_A(head_A, copyB) + 1;
    get_index(head_A);
    while (copyA->index != copyB->posinA)
        copyA = copyA->next;
    //printf("A to be sent ------> %d, B to be sent : %d\n", copyA->data, copyB->data);
    ft_optimise(head_A, head_B, copyA, copyB);
    // pushing_toheadListB(head_B, copyB->index);
    // pushing_toheadListA(head_A, copyA->index, ft_lstsize(*head_A));
    push_a(head_A, head_B);
    
}

void last_sort (t_list **headA)
{
    t_list *copy;
    t_list *copy2;
    int min;

    get_index(headA);
    copy = *headA;
    copy2 = *headA;
    min = lower(&copy2);
    while (copy->data != min)
        copy = copy->next;
    pushing_toheadListA(headA, copy->index, ft_lstsize(*headA));
}

void 	sorting_above_six(t_list **head_A, t_list **head_B)
{
    t_list *copy;
    t_list *moving;
    t_list *current;
    int sizeA;
    int i;

    i = 0;
    copy = *head_A;
    sizeA = ft_lstsize(*head_A);
    circularing_LL(head_A);
    while(i < sizeA)
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
       // printf("MAX SORTED DATA------> %d, MAX SORTED : %d\n", current->data, current->sort);
        copy = copy->next;
        i++;
    }
    node_to_sendtoB(head_A, head_B, sizeA);
    while (*head_B)
        pushing_to_A(head_A, head_B);
    last_sort(head_A);
}