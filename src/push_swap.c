/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/15 23:27:09 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_stdio.h"
#include "actions.h"
#include "markup.h"
#include "indexing.h"
#include <stdio.h>

//Parts: Solve function that returns a list of actions without modifying the passed list
//- Indexing
//- From stack A to stack B
//- From stack B to stack A
//- Align stack A
//- Simply stack A

static int	sa_needed(t_list *stack_a_indexed, t_list *markup_head, t_markup_mode mode)
{
	int		keep_swap;
	int		keep_without_swap;
	t_list	*stack_a_markup;

	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);
	keep_without_swap = count_markup_keep(stack_a_markup);
	swap_lst(&stack_a_indexed);
	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);
	keep_swap = count_markup_keep(stack_a_markup);
	//printf("Keep without swap: %d, Keep with swapp : %d\n", keep_without_swap, keep_swap);
	swap_lst(&stack_a_indexed);
	free(stack_a_markup);
	return (keep_swap > keep_without_swap);
}

typedef struct s_stack_a
{
	t_list	*indexed;
	t_list	*markup;
	t_list	*markup_head;
}				t_stack_a;

t_stack_a	*stack_a_new(void)
{
	t_stack_a	*stack_a;

	stack_a = malloc(sizeof(t_stack_a));
	if (!stack_a)
		return (NULL);
	return (stack_a);
}

typedef enum e_action
{
	ACT_SWAP,
	ACT_ROTATE,
	ACT_REVERSE_ROTATE,
	ACT_PUSH
}			t_action;

typedef enum e_stack
{
	STACK_A,
	STACK_B,
	STACK_BOTH
}			t_stack;

typedef struct s_move
{
	t_stack		stack;
	t_action	action;
}				t_move;

static void	print_content2(void *content)
{
	t_move	*move;

	move = (t_move *) content;
	printf("Move stack : %d action : %d\n", move->stack, move->action);
}

static void	print_content3(void *content)
{
	t_markup	markup;

	markup = *((t_markup *) content);
	printf("Number is : %d Keep : %d\n", markup.number, markup.keep);
}


t_list	*lstcpy(t_list	*lst)
{
	t_list	*new_lst;

	if (lst == NULL)
		return (NULL);
	new_lst = malloc(sizeof(t_list));
	new_lst->content = lst->content;
	new_lst->next = lstcpy(lst->next);
	return (new_lst);
}


t_move	*move_new(t_stack stack, t_action action)
{
	t_move	*move;

	move = malloc(sizeof(t_move));
	if (!move)
		return (NULL);
	move->stack = stack;
	move->action = action;
	return (move);
}

static void	stack_a_to_stack_b(t_stack_a *stack_a, t_list **stack_b_markup,
	t_list **moves, t_markup_mode markup_mode)
{
	t_markup	*stack_a_first_elem;

	while (count_markup_keep(stack_a->markup) != ft_lstsize(stack_a->markup))
	{
		stack_a_first_elem = stack_a->markup->content;
		if (sa_needed(stack_a->indexed, stack_a->markup_head, markup_mode))
		{
			swap_lst(&stack_a->markup);
			swap_lst(&stack_a->indexed);
			ft_lstadd_back(moves, ft_lstnew(move_new(STACK_A, ACT_SWAP)));
			stack_a->markup_head = get_markup(stack_a->indexed,
					stack_a->markup_head, markup_mode);
		}
		else if (stack_a_first_elem->keep == 0)
		{
			push_lst(&stack_a->markup, stack_b_markup);
			ft_lstadd_back(moves, ft_lstnew(move_new(STACK_A, ACT_PUSH)));
		}
		else
		{
			rotate_lst(&stack_a->markup);
			rotate_lst(&stack_a->indexed);
			ft_lstadd_back(moves, ft_lstnew(move_new(STACK_A, ACT_ROTATE)));
		}
	}
}

typedef struct s_stack_a_boundaries
{
	int	lowest_value;
	int	highest_value;
}				t_stack_a_boundaries;

t_stack_a_boundaries	*stack_a_boundaries_new(int lowest_value,
	int highest_value)
{
	t_stack_a_boundaries	*boundaries;

	boundaries = malloc(sizeof(t_stack_a_boundaries));
	if (!boundaries)
		return (NULL);
	boundaries->lowest_value = lowest_value;
	boundaries->highest_value = highest_value;
	return (boundaries);
}

static t_stack_a_boundaries	*get_stack_a_boundaries(t_list *stack_a_markup)
{
	t_stack_a_boundaries	*boundaries;
	t_list					*stack_a_markup_cpy;
	t_markup				*stack_a_markup_casted;

	stack_a_markup_cpy = stack_a_markup;
	stack_a_markup_casted = (t_markup *) stack_a_markup_cpy->content;
	boundaries = stack_a_boundaries_new(stack_a_markup_casted->number,
			stack_a_markup_casted->number);
	while (stack_a_markup_cpy)
	{
		stack_a_markup_casted = (t_markup *) stack_a_markup_cpy->content;
		if (stack_a_markup_casted->number < boundaries->lowest_value)
			boundaries->lowest_value = stack_a_markup_casted->number;
		if (stack_a_markup_casted->number > boundaries->highest_value)
			boundaries->highest_value = stack_a_markup_casted->number;
		stack_a_markup_cpy = stack_a_markup_cpy->next;
	}
	return (boundaries);
}

static void	apply_moveset(t_stack stack, int count, t_action action,
	t_list **moveset)
{
	while (count > 0)
	{
		ft_lstadd_back(moveset, ft_lstnew(move_new(stack, action)));
		count--;
	}
}

static void	prepare_stack_b(t_list *stack_b_markup, int stack_b_curr_size,
	t_list **moveset)
{
	int			move_count;
	int			stack_b_total_size;

	move_count = 0;
	stack_b_total_size = ft_lstsize(stack_b_markup);
	if (stack_b_curr_size + 1 <= stack_b_total_size / 2)
	{
		move_count = stack_b_curr_size;
		apply_moveset(STACK_B, move_count, ACT_ROTATE, moveset);
	}
	else if (stack_b_curr_size > 0)
	{
		move_count = stack_b_total_size - stack_b_curr_size;
		apply_moveset(STACK_B, move_count, ACT_REVERSE_ROTATE, moveset);
	}
}

static void	prepare_stack_a_out(t_list	*stack_a_markup,
	t_stack_a_boundaries	*stack_a_boundaries, t_list **moveset)
{
	int			count;
	t_markup	*stack_a_markup_casted;
	t_list		*stack_a_markup_cpy;
	t_list		*stack_a_markup_cpy_rev;

	count = 0;
	stack_a_markup_cpy = lstcpy(stack_a_markup);
	stack_a_markup_cpy_rev = lstcpy(stack_a_markup);
	while (1)
	{
		stack_a_markup_casted = (t_markup *) stack_a_markup_cpy->content;
		if (stack_a_markup_casted->number == stack_a_boundaries->lowest_value)
		{
			apply_moveset(STACK_A, count, ACT_ROTATE, moveset);
			break ;
		}
		stack_a_markup_casted = (t_markup *) stack_a_markup_cpy_rev->content;
		if (stack_a_markup_casted->number == stack_a_boundaries->lowest_value)
		{
			apply_moveset(STACK_A, count, ACT_REVERSE_ROTATE, moveset);
			break ;
		}
		rotate_lst(&stack_a_markup_cpy);
		reverse_rotate_lst(&stack_a_markup_cpy_rev);
		count++;
	}
	free(stack_a_markup_cpy);
	free(stack_a_markup_cpy_rev);
}

static int	is_between_stack_a(t_list	*stack_a_markup, t_markup	*markup)
{
	t_markup	*stack_a_markup_casted;
	t_markup	*stack_a_markup_last_casted;

	stack_a_markup_casted = (t_markup *) stack_a_markup->content;
	stack_a_markup_last_casted = (t_markup *)
		ft_lstlast(stack_a_markup)->content;
	if (markup->number < stack_a_markup_casted->number
		&& markup->number > stack_a_markup_last_casted->number)
		return (1);
	return (0);
}

static void	prepare_stack_a_in(t_list	*stack_a_markup, t_markup	*markup,
	t_list **moveset)
{
	int			count;
	t_list		*stack_a_markup_cpy;
	t_list		*stack_a_markup_cpy_rev;

	count = 0;
	stack_a_markup_cpy = lstcpy(stack_a_markup);
	stack_a_markup_cpy_rev = lstcpy(stack_a_markup);
	while (1)
	{
		if (is_between_stack_a(stack_a_markup_cpy, markup))
		{
			apply_moveset(STACK_A, count, ACT_ROTATE, moveset);
			break ;
		}
		if (is_between_stack_a(stack_a_markup_cpy_rev, markup))
		{
			apply_moveset(STACK_A, count, ACT_REVERSE_ROTATE, moveset);
			break ;
		}
		rotate_lst(&stack_a_markup_cpy);
		reverse_rotate_lst(&stack_a_markup_cpy_rev);
		count++;
	}
	free(stack_a_markup_cpy);
	free(stack_a_markup_cpy_rev);
}

//Convert the list to an array
//Where in stack A is the smaller element that is the closest to the value from B ?
//If found:
  //Is this element closer to the start or the end of stack A ?
  //The distance from the start or the end is the number of rotate or reverse rotate to do
//Else
  //Is the smallest element of stack A closer to the start or thend ?
  //The distance from the start or the end is the number of rotate or reverse rotate to do

static void	prepare_stack_a_fast(t_list *stack_a_markup, t_markup	*markup,
	t_stack_a_boundaries	*stack_a_boundaries, t_list **moveset)
{
	int			i;
	t_list		*stack_a_markup_cpy;
	t_markup	*stack_a_arr;
	int			stack_a_size;

	i = 0;
	stack_a_markup_cpy = stack_a_markup;
	stack_a_size = ft_lstsize(stack_a_markup);
	stack_a_arr = malloc(stack_a_size * sizeof(t_markup));
	while (stack_a_markup_cpy)
	{
		stack_a_arr[i] = *((t_markup *) stack_a_markup_cpy->content);
		stack_a_markup_cpy = stack_a_markup_cpy->next;
		i++;
	}

	if (markup->number > stack_a_boundaries->highest_value
		|| markup->number < stack_a_boundaries->lowest_value)
	{
		prepare_stack_a_out(stack_a_markup, stack_a_boundaries, moveset);
	}
	else
	{
		i = 0;
		int closest_number = stack_a_boundaries->highest_value + 1;
		int closest_index = 0;
		while (i < stack_a_size)
		{
			t_markup markup2 = stack_a_arr[i];
			if (markup2.number > markup->number && markup2.number < closest_number)
			{
				closest_number = markup2.number;
				closest_index = i;
			}
			i++;
		}
		int move_count = 0;
		if (closest_index + 1 <= stack_a_size / 2)
		{
			move_count = closest_index;
			apply_moveset(STACK_A, move_count, ACT_ROTATE, moveset);
		}
		else if (closest_index > 0)
		{
			move_count = stack_a_size - closest_index;
			apply_moveset(STACK_A, move_count, ACT_REVERSE_ROTATE, moveset);
		}
	}
}

static void	prepare_stack_a(t_list *stack_a_markup, t_markup	*markup,
	t_stack_a_boundaries	*stack_a_boundaries, t_list **moveset)
{
	if (markup->number > stack_a_boundaries->highest_value
		|| markup->number < stack_a_boundaries->lowest_value)
		prepare_stack_a_out(stack_a_markup, stack_a_boundaries, moveset);
	else
		prepare_stack_a_in(stack_a_markup, markup, moveset);
}

static t_list	*find_best_moveset(t_list	*stack_a_markup,
	t_list *stack_b_markup, t_stack_a_boundaries	*stack_a_boundaries)
{
	t_list		*stack_b_markup_cpy;
	t_markup	*markup;
	t_list		*moveset;
	t_list		*best_moveset;
	int			stack_b_curr_size;

	stack_b_markup_cpy = stack_b_markup;
	stack_b_curr_size = 0;
	best_moveset = NULL;
	while (stack_b_markup_cpy)
	{
		moveset = NULL;
		markup = (t_markup *) stack_b_markup_cpy->content;
		prepare_stack_b(stack_b_markup, stack_b_curr_size, &moveset);
		(void) prepare_stack_a;
		//prepare_stack_a(stack_a_markup, markup, stack_a_boundaries, &moveset);
		(void) prepare_stack_a_fast;
		prepare_stack_a_fast(stack_a_markup, markup, stack_a_boundaries, &moveset);
		if (best_moveset == NULL
			|| ft_lstsize(moveset) < ft_lstsize(best_moveset))
		{
			free(best_moveset);
			best_moveset = moveset;
		}
		stack_b_markup_cpy = stack_b_markup_cpy->next;
		stack_b_curr_size++;
	}
	return (best_moveset);
}

static void	prepare_both_stack(t_list	**stack_a_markup,
	t_list **stack_b_markup, t_list	*moveset, t_list **moves)
{
	t_list		*moveset_cpy;
	t_move		*move;
	t_stack		stack;
	t_action	action;

	moveset_cpy = moveset;
	while (moveset_cpy)
	{
		move = (t_move *) moveset_cpy->content;
		action = move->action;
		stack = move->stack;
		if (stack == STACK_A && action == ACT_ROTATE)
			rotate_lst(stack_a_markup);
		if (stack == STACK_A && action == ACT_REVERSE_ROTATE)
			reverse_rotate_lst(stack_a_markup);
		if (stack == STACK_B && action == ACT_ROTATE)
			rotate_lst(stack_b_markup);
		if (stack == STACK_B && action == ACT_REVERSE_ROTATE)
			reverse_rotate_lst(stack_b_markup);
		ft_lstadd_back(moves, ft_lstnew(move_new(stack, action)));
		moveset_cpy = moveset_cpy->next;
	}
}

static void	stack_b_to_stack_a(t_list	**stack_a_markup,
	t_list **stack_b_markup, t_list **moves)
{
	t_list					*best_moveset;
	t_stack_a_boundaries	*stack_a_boundaries;

	while (ft_lstsize(*stack_b_markup) > 0)
	{
		stack_a_boundaries = get_stack_a_boundaries(*stack_a_markup);
		best_moveset = find_best_moveset(*stack_a_markup, *stack_b_markup,
				stack_a_boundaries);
		prepare_both_stack(stack_a_markup, stack_b_markup, best_moveset, moves);
		push_lst(stack_b_markup, stack_a_markup);
		ft_lstadd_back(moves, ft_lstnew(move_new(STACK_B,
					ACT_PUSH)));
	}

}

static void	align_stack_a_moveset(t_list	**stack_a_markup, int total_size,
	int smallest_index, t_list **moves)
{
	int			move_count;
	t_action	action;

	move_count = 0;
	if (smallest_index + 1 <= total_size / 2)
	{
		move_count = smallest_index;
		action = ACT_ROTATE;
	}
	else if (smallest_index > 0)
	{
		move_count = total_size - smallest_index;
		action = ACT_REVERSE_ROTATE;
	}
	while (move_count > 0)
	{
		if (action == ACT_ROTATE)
			rotate_lst(stack_a_markup);
		else if (action == ACT_REVERSE_ROTATE)
			reverse_rotate_lst(stack_a_markup);
		ft_lstadd_back(moves, ft_lstnew(move_new(STACK_A, action)));
		move_count--;
	}
}

static void	align_stack_a(t_list	**stack_a_markup, t_list **moves)
{
	t_list		*stack_a_markup_cpy;
	int			smallest_index;
	int			smallest_number;
	int			i;
	t_markup	*markup;

	stack_a_markup_cpy = *stack_a_markup;
	smallest_index = 0;
	i = 0;
	smallest_number = ((t_markup *) stack_a_markup_cpy->content)->number;
	while (stack_a_markup_cpy)
	{
		markup = (t_markup *) stack_a_markup_cpy->content;
		if (markup->number < smallest_number)
		{
			smallest_index = i;
			smallest_number = markup->number;
		}
		stack_a_markup_cpy = stack_a_markup_cpy->next;
		i++;
	}
	align_stack_a_moveset(stack_a_markup, ft_lstsize(*stack_a_markup),
		smallest_index, moves);
}

static void	simplify_moveset_apply(t_list	**moveset,
	int *ra_count_ptr, int *rb_count_ptr, t_action action)
{
	int	ra_count;
	int	rb_count;
	int	rr_count;

	ra_count = *ra_count_ptr;
	rb_count = *rb_count_ptr;
	if (ra_count > rb_count)
	{
		rr_count = rb_count;
		ra_count = ra_count - rb_count;
		rb_count = 0;
	}
	else
	{
		rr_count = ra_count;
		rb_count = rb_count - ra_count;
		ra_count = 0;
	}
	apply_moveset(STACK_B, rb_count, action, moveset);
	apply_moveset(STACK_A, ra_count, action, moveset);
	apply_moveset(STACK_BOTH, rr_count, action, moveset);
	*ra_count_ptr = 0;
	*rb_count_ptr = 0;
}

static void	simplify_moveset_action(t_list	**moveset, t_action action)
{
	t_list	*simplified_moveset;
	t_list	*moveset_cpy;
	t_move	*move;
	int		ra_count;
	int		rb_count;

	moveset_cpy = *moveset;
	simplified_moveset = NULL;
	ra_count = 0;
	rb_count = 0;
	while (moveset_cpy)
	{
		move = (t_move *) moveset_cpy->content;
		if (move->action == action && move->stack == STACK_A)
			ra_count++;
		else if (move->action == action && move->stack == STACK_B)
			rb_count++;
		else
		{
			simplify_moveset_apply(&simplified_moveset, &ra_count,
				&rb_count, action);
			ft_lstadd_back(&simplified_moveset,
				ft_lstnew(move_new(move->stack, move->action)));
		}
		moveset_cpy = moveset_cpy->next;
	}
	simplify_moveset_apply(&simplified_moveset, &ra_count,
		&rb_count, action);
	free(*moveset);
	*moveset = simplified_moveset;
}

static void	simplify_moveset(t_list	**moveset)
{
	simplify_moveset_action(moveset, ACT_ROTATE);
	simplify_moveset_action(moveset, ACT_REVERSE_ROTATE);
}

static t_list	*solve(t_list *stack_a_standalone, t_markup_mode markup_mode)
{
	t_list		*moves;
	t_stack_a	*stack_a;
	t_list		*stack_b_markup;

	stack_b_markup = NULL;
	stack_a = stack_a_new();
	stack_a->indexed = get_indexed_list(stack_a_standalone,
			ft_lstsize(stack_a_standalone));
	stack_a->markup_head = find_markup_head(stack_a->indexed, markup_mode);
	stack_a->markup = get_markup(stack_a->indexed, stack_a->markup_head,
			markup_mode);
	stack_a_to_stack_b(stack_a, &stack_b_markup, &moves, markup_mode);
	stack_b_to_stack_a(&stack_a->markup, &stack_b_markup, &moves);

	align_stack_a(&stack_a->markup, &moves);


	(void) print_content3;
	/*printf("Stack A AFTER :\n");
	ft_lstiter(stack_a->markup, print_content3);
	printf("\n");
	printf("Stack B AFTER :\n");
	ft_lstiter(stack_b_markup, print_content3);*/

	simplify_moveset(&moves);
	return (moves);
}

static void print_move_stack_both(t_move	*move)
{
	if (move->stack != STACK_BOTH)
		return ;
	if (move->action == ACT_ROTATE)
		ft_printf("rr\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rrr\n");
}

static void print_move_stack_a(t_move	*move)
{
	if (move->stack != STACK_A)
		return ;
	if (move->action == ACT_PUSH)
		ft_printf("pb\n");
	if (move->action == ACT_ROTATE)
		ft_printf("ra\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rra\n");
	if (move->action == ACT_SWAP)
		ft_printf("sa\n");
}

static void print_move_stack_b(t_move	*move)
{
	if (move->stack != STACK_B)
		return ;
	if (move->action == ACT_PUSH)
		ft_printf("pa\n");
	if (move->action == ACT_ROTATE)
		ft_printf("rb\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rrb\n");
}

static void print_moveset(t_list	*moveset)
{
	t_list	*moveset_cpy;
	t_move	*move;

	moveset_cpy = moveset;
	while (moveset_cpy)
	{
		move = (t_move *) moveset_cpy->content;
		print_move_stack_a(move);
		print_move_stack_b(move);
		print_move_stack_both(move);
		moveset_cpy = moveset_cpy->next;
	}
}

#include "ft_stdlib.h"

int	main(int argc, char *args[])
{
	t_list	*stack_a;
	t_list	*moves;
	int		*args_nbr;
	int		i;

	(void) argc;
	stack_a = NULL;
	i = 1;
	args_nbr = malloc(argc * sizeof(int));
	while (args[i])
	{
		args_nbr[i] = ft_atoi(args[i]);
		ft_lstadd_back(&stack_a, ft_lstnew(&args_nbr[i]));
		i++;
	}
	moves = solve(stack_a, MARKUP_BY_INDEX);
	(void) print_content2;
	(void) moves;
	(void) print_moveset;
	print_moveset(moves);
	///printf("Number of actions: %d\n", ft_lstsize(moves));
}
