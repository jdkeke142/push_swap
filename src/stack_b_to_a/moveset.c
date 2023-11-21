/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:32:04 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:47:57 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_b_to_a_utils.h"
#include "move.h"
#include "actions.h"

static t_combined_moveset	combine_moveset(t_moveset stack_a_moveset,
	t_moveset stack_b_moveset)
{
	t_moveset	stack_both_moveset;
	int			total_count;

	stack_both_moveset = (t_moveset){0, stack_a_moveset.direction};
	if (stack_a_moveset.direction == stack_b_moveset.direction)
	{
		if (stack_a_moveset.count > stack_b_moveset.count)
		{
			stack_both_moveset.count = stack_b_moveset.count;
			stack_a_moveset.count = stack_a_moveset.count
				- stack_b_moveset.count;
			stack_b_moveset.count = 0;
		}
		else
		{
			stack_both_moveset.count = stack_a_moveset.count;
			stack_b_moveset.count = stack_b_moveset.count
				- stack_a_moveset.count;
			stack_a_moveset.count = 0;
		}
	}
	total_count = stack_both_moveset.count + stack_a_moveset.count
		+ stack_b_moveset.count;
	return ((t_combined_moveset){stack_a_moveset, stack_b_moveset,
		stack_both_moveset, total_count});
}

t_combined_moveset	find_best_moveset(t_list *stack_a_markup,
	t_markup *stack_a_arr, t_list *stack_b_markup,
	t_stack_boundaries	*stack_a_boundaries)
{
	t_markup			*markup;
	t_combined_moveset	best_moveset;
	t_combined_moveset	moveset;
	int					stack_b_curr_size;
	t_list_node			*stack_b_markup_cpy;

	stack_b_curr_size = 0;
	stack_b_markup_cpy = stack_b_markup->first;
	while (stack_b_markup_cpy)
	{
		markup = (t_markup *) stack_b_markup_cpy->content;
		moveset = combine_moveset(count_prepare_stack_a(stack_a_markup,
					stack_a_arr, markup, stack_a_boundaries),
				count_prepare_stack_b(stack_b_markup, stack_b_curr_size));
		if (stack_b_curr_size == 0
			|| moveset.total_count < best_moveset.total_count)
			best_moveset = moveset;
		stack_b_markup_cpy = stack_b_markup_cpy->next;
		stack_b_curr_size++;
	}
	return (best_moveset);
}

static void	apply_moveset_moves(t_stack stack, t_moveset moveset,
	t_list *moves)
{
	int	count;

	count = moveset.count;
	while (count > 0)
	{
		if (moveset.direction == DIR_REGULAR)
			ft_lstadd_back(moves, move_new(stack, ACT_ROTATE));
		else
			ft_lstadd_back(moves, move_new(stack, ACT_REVERSE_ROTATE));
		count--;
	}
}

static void	apply_moveset_markup(t_stack stack, t_moveset moveset,
	t_list *stack_a_markup, t_list *stack_b_markup)
{
	int	count;

	count = moveset.count;
	while (count > 0)
	{
		if (moveset.direction == DIR_REGULAR)
		{
			if (stack == STACK_BOTH)
				rotate_lsts(stack_a_markup, stack_b_markup);
			else if (stack == STACK_A)
				rotate_lst(stack_a_markup);
			else
				rotate_lst(stack_b_markup);
		}
		else
		{
			if (stack == STACK_BOTH)
				reverse_rotate_lsts(stack_a_markup, stack_b_markup);
			else if (stack == STACK_A)
				reverse_rotate_lst(stack_a_markup);
			else
				reverse_rotate_lst(stack_b_markup);
		}
		count--;
	}
}

void	apply_combined_moveset(t_combined_moveset combined_moveset,
	t_list *moves, t_list *stack_a_markup, t_list *stack_b_markup)
{
	apply_moveset_moves(STACK_A, combined_moveset.stack_a, moves);
	apply_moveset_moves(STACK_B, combined_moveset.stack_b, moves);
	apply_moveset_moves(STACK_BOTH, combined_moveset.stack_both, moves);
	apply_moveset_markup(STACK_A, combined_moveset.stack_a,
		stack_a_markup, stack_b_markup);
	apply_moveset_markup(STACK_B, combined_moveset.stack_b,
		stack_a_markup, stack_b_markup);
	apply_moveset_markup(STACK_BOTH, combined_moveset.stack_both,
		stack_a_markup, stack_b_markup);
}
