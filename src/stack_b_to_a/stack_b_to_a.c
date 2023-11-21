/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:37:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:49:59 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "actions.h"
#include "stack_b_to_a_utils.h"

t_markup	*stack_markup_to_array(t_list *stack_markup)
{
	int			i;
	t_list_node	*stack_markup_cpy;
	t_markup	*stack_arr;

	i = 0;
	stack_markup_cpy = stack_markup->first;
	stack_arr = malloc(stack_markup->size * sizeof(t_markup));
	while (stack_markup_cpy)
	{
		stack_arr[i] = *((t_markup *) stack_markup_cpy->content);
		stack_markup_cpy = stack_markup_cpy->next;
		i++;
	}
	return (stack_arr);
}

void	stack_b_to_a(t_list *stack_a_markup,
	t_list *stack_b_markup, t_list *moves)
{
	t_stack_boundaries	*stack_a_boundaries;
	t_combined_moveset	best_moveset;
	t_markup			*stack_a_array;

	while (stack_b_markup->size > 0)
	{
		stack_a_boundaries = get_stack_boundaries(stack_a_markup);
		stack_a_array = stack_markup_to_array(stack_a_markup);
		best_moveset = find_best_moveset(stack_a_markup,
				stack_a_array, stack_b_markup, stack_a_boundaries);
		apply_combined_moveset(best_moveset, moves,
			stack_a_markup, stack_b_markup);
		push_lst(stack_b_markup, stack_a_markup);
		ft_lstadd_back(moves, move_new(STACK_B, ACT_PUSH));
		free(stack_a_boundaries);
		free(stack_a_array);
	}
}
