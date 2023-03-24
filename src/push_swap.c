/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/24 05:02:36 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "actions.h"
#include "markup.h"
#include "indexing.h"
#include <stdio.h>

/*
Plan : markup is a struct number and boolean keep
we can get a list of markup using any markup head and a list with INDEXED numbers
*/
/*static void	print_content(void *content)
{
	t_indexed	indexed;

	indexed = *((t_indexed *) content);
	printf("Number is : %d Index : %d\n", indexed.number, indexed.index);
}*/

static void	print_content2(void *content)
{
	t_markup	markup;

	markup = *((t_markup *) content);
	printf("Number is : %d Keep : %d\n", markup.number, markup.keep);
}

/*static void	print_content2(void *content)
{
	t_indexed	markup;

	markup = *((t_indexed *)content);
	printf("Number is : %d Index : %d\n", markup.number, markup.index);
}*/

static int	sa_needed(t_list *stack_a_indexed, t_list *markup_head, t_markup_mode mode)
{
	int		keep_swap;
	int		keep_without_swap;
	t_list	*stack_a_markup;

	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);
	keep_without_swap = count_markup_keep(stack_a_markup);
	swap_lst(&stack_a_markup);
	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);
	keep_swap = count_markup_keep(stack_a_markup);
	swap_lst(&stack_a_markup);
	free(stack_a_markup);
	return (keep_swap > keep_without_swap);
}


typedef enum e_direction
{
	DIR_REGULAR,
	DIR_REVERSE
}			t_direction;

typedef struct s_move
{
	int			count;
	t_direction	direction;
}				t_move;


t_move	count_sb(t_list *number, t_list *indexed_lst)
{
	int		lst_size;
	int		half_size;
	int		i;
	t_list	*temp_lst;

	lst_size = ft_lstsize(indexed_lst);
	half_size = lst_size / 2;
	temp_lst = indexed_lst;
	i = 0;
	while (temp_lst)
	{
		if (number == temp_lst)
		{
			if (i > half_size)
				return ((t_move){i-half_size, DIR_REVERSE});
			else
				return ((t_move){i, DIR_REGULAR});
		}
		temp_lst = temp_lst->next;
		i++;
	}
	return ((t_move){0, DIR_REGULAR});
}

t_move count_sa(t_list *number, t_list *indexed_lst)
{
	int		num_index;
	int		curr_index;
	int		curr_index2;
	t_list	*temp_lst;
	t_list	*lower_bigger_num;

	curr_index2 = 999999;
	temp_lst = indexed_lst;
	num_index = ((t_indexed *) number->content)->index;
	while (temp_lst)
	{
		curr_index = ((t_indexed *) temp_lst->content)->index;
		if (curr_index > num_index && curr_index < curr_index2)
		{
			lower_bigger_num = temp_lst;
			curr_index2 = curr_index;
		}
		temp_lst = temp_lst->next;
	}

	return (count_sb(lower_bigger_num, indexed_lst));
}

void prepare_a(t_list **indexed_lst, t_move move)
{
	int	i;

	i = 0;
	while (i < move.count)
	{
		if (move.direction == DIR_REGULAR)
		{
			rotate_lst(indexed_lst);
			printf("ra\n");
		}
		else
		{
			reverse_rotate_lst(indexed_lst);
			printf("rra\n");
		}
		i++;
	}
}

void prepare_b(t_list **indexed_lst, t_move move)
{
	int	i;

	i = 0;
	while (i < move.count)
	{
		if (move.direction == DIR_REGULAR)
		{
			rotate_lst(indexed_lst);
			printf("rb\n");
		}
		else
		{
			reverse_rotate_lst(indexed_lst);
			printf("rrb\n");
		}
		i++;
	}
}

//Divide
//We need to find : - Which bigger value is closest to the top in move ?
//					- Which smaller value is closest to the bottom in move ?
//FIRST = NEED TO BE BIGGER
//LAST = NEED TO BE SMALLER
/*e
If first value of Stack A = smallest value of Stack A, rotate Stack A until first value of the stack
is bigger than the value we are going to move from Stack B OR until last value of Stack A is smaller than the value we are going to move from Stack B

ELSE

Rotate Stack A until value we are going to move from Stack B is bigger than first value of stack A and
smaller than last value of stack A
*/

t_list	*find_smallest(t_list *index_lst)
{
	t_list	*tmp_lst;
	t_list	*smallest_value;
	int		curr_number;
	int		smallest_number;

	tmp_lst = index_lst;
	smallest_value = NULL;
	while (tmp_lst)
	{
		curr_number = ((t_indexed *)(tmp_lst->content))->number;
		if (smallest_value != NULL)
			smallest_number = ((t_indexed *)(smallest_value->content))->number;
		if (smallest_value == NULL || curr_number < smallest_number)
			smallest_value = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (smallest_value);
}

t_move count_for_top(t_list *number, t_list *indexed_lst)
{
	int		lst_size;
	int		half_size;
	int		i;
	t_list	*temp_lst;

	lst_size = ft_lstsize(indexed_lst);
	half_size = lst_size / 2;
	temp_lst = indexed_lst;
	i = 0;
	while (temp_lst)
	{
		if (number == temp_lst)
		{
			if (i > half_size)
				return ((t_move){i - half_size, DIR_REVERSE});
			else
				return ((t_move){i, DIR_REGULAR});
		}
		temp_lst = temp_lst->next;
		i++;
	}
	return ((t_move){0, DIR_REGULAR});
}

t_move count_for_bottom(t_list *number, t_list *indexed_lst)
{
	int		lst_size;
	int		half_size;
	int		i;
	t_list	*temp_lst;

	lst_size = ft_lstsize(indexed_lst);
	half_size = lst_size / 2;
	temp_lst = indexed_lst;
	i = 0;
	while (temp_lst)
	{
		if (number == temp_lst)
		{
			if (i > half_size)
				return ((t_move){(ft_lstsize(indexed_lst) - 1) - i,
					DIR_REVERSE});
			else
				return ((t_move){i + 1, DIR_REGULAR});
		}
		temp_lst = temp_lst->next;
		i++;
	}
	return ((t_move){0, DIR_REGULAR});
}

void	best_move(t_list *indexed_lst)
{
		int 	count;
		t_list *temp_lst;
		t_move	move_sb;
		t_move	move_sa;

		temp_lst = indexed_lst;
		while (temp_lst)
		{
			if (count_for_top(temp_lst, indexed_lst).count > count_for_bottom(temp_lst, indexed_lst).count)
				count = count_sb(temp_lst, indexed_lst).count + count_for_bottom(temp_lst, indexed_lst).count;
			else
				count = count_sb(temp_lst, indexed_lst).count + count_for_top(temp_lst, indexed_lst).count;
			if (count < move_sa.count + move_sb.count)
			{
				move_sb = count_sb(temp_lst, indexed_lst);
				move_sa =  count_sa(temp_lst, indexed_lst);
			}
			temp_lst = temp_lst->next;
		}

		prepare_b(&indexed_lst, move_sb);
		prepare_a(&indexed_lst, move_sa);
}

int	main(void)
{
	//(void) sa_needed;
	t_list	*stack_a;
	t_list	*stack_a_indexed;
	t_list	*stack_a_markup;
	t_list	*stack_b;
	t_list	*markup_lst;
	t_list	*stack_a_markup_head;
	t_list	*stack_b_indexed;
	t_list	*stack_b_markup;

	int num1 = -2147483648;
	int num2 = 2100;
	int num3 = 220010;
	int num4 = -1;
	int	num5 = 7;
	int	num6 = 210815;
	int	num7 = 121;

	stack_a = NULL;
	ft_lstadd_back(&stack_a, ft_lstnew(&num1));
	ft_lstadd_back(&stack_a, ft_lstnew(&num2));
	ft_lstadd_back(&stack_a, ft_lstnew(&num3));
	ft_lstadd_back(&stack_a, ft_lstnew(&num4));
	ft_lstadd_back(&stack_a, ft_lstnew(&num5));
	ft_lstadd_back(&stack_a, ft_lstnew(&num6));
	ft_lstadd_back(&stack_a, ft_lstnew(&num7));
	stack_b = NULL;
	stack_b_indexed = NULL;
	stack_b_markup = NULL;

	stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
	stack_a_markup_head = find_markup_head(stack_a_indexed, MARKUP_BY_INDEX);
	stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX);

	printf("Using as markup head %d\n", ((t_indexed *) stack_a_markup_head->content)->number);

while (count_markup_keep(stack_a_markup) != ft_lstsize(stack_a_markup))
	{
		if (sa_needed(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX))
		{
			swap_lst(&stack_a_markup);
			swap_lst(&stack_a_indexed);
			printf("sa\n");
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX);
		}
		if (((t_markup *)stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a_markup, &stack_b_markup);
			push_lst(&stack_a_indexed, &stack_b_indexed);
			printf("pb\n");
		}
		else
		{
			rotate_lst(&stack_a_markup);
			rotate_lst(&stack_a_indexed);
			printf("ra\n");
		}
		//printf("\n");
		}


	printf("Stack A BEFORE :\n");
	ft_lstiter(stack_a_markup, print_content2);
	printf("\n");
	printf("Stack B BEFORE :\n");
	ft_lstiter(stack_b_markup, print_content2);

	printf("Count for bottom : %d\n", count_for_bottom(stack_a->next->next->next->next, stack_a).count);
	//t_list *smallest = find_smallest(stack_a_indexed);

	//printf("Smallest value of stack A is : %d\n", ((t_indexed *) smallest->content)->number);

	/*while (count_markup_keep(stack_a_markup) != ft_lstsize(stack_a_markup))
	{
		if (sa_needed(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX))
		{
			swap_lst(&stack_a_markup);
			swap_lst(&stack_a_indexed);
			printf("sa\n");
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX);
		}
		if (((t_markup *)stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a_markup, &stack_b_markup);
			push_lst(&stack_a_indexed, &stack_b_indexed);
			printf("pb\n");
		}
		else
		{
			rotate_lst(&stack_a_markup);
			rotate_lst(&stack_a_indexed);
			printf("ra\n");
		}
		//printf("\n");
		}

										printf("\nStack A INDEXED:\n");
		ft_lstiter(stack_a_indexed, print_content);
		printf("\nStack B INDEXED :\n");
		ft_lstiter(stack_b_indexed, print_content);

		int z = 0;
		while (z < 3)
		{
					t_list *temp_lst;
		t_list	*best;
		int		last_move;
		t_move	move_sb;
		t_move	move_sa;

		temp_lst = stack_b_indexed;
		last_move = 9999;
		while (temp_lst)
		{
			int count = count_sb(temp_lst, stack_b_indexed).count + count_sa(temp_lst, stack_a_indexed).count;
			if (count < last_move)
			{
				best = temp_lst;
				move_sb = count_sb(temp_lst, stack_b_indexed);
				move_sa =  count_sa(temp_lst, stack_a_indexed);
				last_move = count;
			}
			temp_lst = temp_lst->next;
		}

		(void) best;

		//printf("Best one to move is : %d\n", ((t_indexed *) best->content)->number);

		prepare_b(&stack_b_indexed, move_sb);
		prepare_a(&stack_a_indexed, move_sa);

		push_lst(&stack_b_indexed, &stack_a_indexed);

								printf("\nStack A INDEXED:\n");
		ft_lstiter(stack_a_indexed, print_content);
		printf("\nStack B INDEXED :\n");
		ft_lstiter(stack_b_indexed, print_content);
		z++;
		}*/
	/*while (count_markup_keep(stack_a_markup) != ft_lstsize(stack_a))
	{
		ft_lstiter(st ack_a_indexed, print_content);
		if (((t_markup *)stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a, &stack_b);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			printf("\n\n");
			ft_lstiter(stack_a_indexed, print_content2);
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else
		{
			rotate_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
	}*/

	(void) stack_b;
	(void) markup_lst;
	/*while (count_markup_keep(stack_a_markup) < ft_lstsize(stack_a_markup))
	{
		printf("\n\n");
		ft_lstiter(stack_a, print_content);
		if (sa_needed(stack_a, stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN))
		{
			swap_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else if (((t_markup*) stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a, &stack_b);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else
		{
			rotate_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
	}*/

	//stack_b = get_indexed_list(stack_a, ft_lstsize(stack_a));

	//markup_head = find_markup_head(stack_b, MARKUP_GREATER_THAN);
	//printf("Best markup head is %d\n", ((t_indexed *) markup_head->content)->number);
	//markup_lst = get_markup(stack_b, stack_b,
	//		MARKUP_BY_INDEX);
	//ft_lstiter(markup_lst, print_content);
	//ft_lstiter(stack_a, print_content2);
	//(void) stack_b;
	//ft_lstiter(stack_b, print_content);

	/*stack_b = ft_lstcpy(stack_a);
	ft_lstsort(&stack_b, ft_lstsize(stack_b));

	printf("Lst a content :\n");
	ft_lstiter(stack_a, print_content);

	printf("Lst b content :\n");
	ft_lstiter(stack_b, print_content);*/

	/*markup_index_head = get_markup_head(MARKUP_BY_INDEX, indexed_lst, list_size);
	printf("Markup head by index is %d and kept %d\n", markup_index_head.markup, markup_index_head.kept_amount);

	markup_greater_head = get_markup_head(MARKUP_GREATER_THAN, indexed_lst, list_size);
	printf("Markup head greater than is %d and kept %d\n", markup_greater_head.markup, markup_greater_head.kept_amount);
	t_list	*stack_a;
	t_list	*stack_b;
	int num_1;

	num_1 = 5;
	stack_b = NULL;
	stack_a = ft_lstnew(&num_1);
	printf("Lst 1 content :\n");
	ft_lstiter(stack_a, print_content);
	printf("Lst 2 content :\n");
	ft_lstiter(stack_b, print_content);

	push_lst(&stack_a, &stack_b);
	printf("Lst 1 content :\n");
	ft_lstiter(stack_a, print_content);
	printf("Lst 2 content :\n");
	ft_lstiter(stack_b, print_content);

	swap_lst(&lst);*/
}
