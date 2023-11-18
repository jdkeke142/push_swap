/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a_align.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:23:59 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 15:29:20 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "actions.h"
#include "markup.h"

static void	align_stack_a_moveset(t_list	*stack_a_markup, int total_size,
	int smallest_index, t_list *moves)
{
	int			move_count;
	t_action	action;

	if (smallest_index <= (total_size - 1) / 2)
	{
		move_count = smallest_index;
		action = ACT_ROTATE;
	}
	else
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
		ft_lstadd_back(moves, move_new(STACK_A, action));
		move_count--;
	}
}

void	align_stack_a(t_list	*stack_a_markup, t_list *moves)
{
	t_list_node	*stack_a_markup_cpy;
	int			smallest_index;
	int			smallest_number;
	int			i;
	t_markup	*markup;

	stack_a_markup_cpy = stack_a_markup->first;
	smallest_index = 0;
	i = 0;
	smallest_number = ((t_markup *) ft_lstfirst(stack_a_markup))->number;
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
	align_stack_a_moveset(stack_a_markup, stack_a_markup->size,
		smallest_index, moves);
}
