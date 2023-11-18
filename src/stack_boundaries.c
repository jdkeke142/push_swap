/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:14:27 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 20:12:07 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

static t_stack_boundaries	*stack_boundaries_new(int lowest_value,
	int highest_value)
{
	t_stack_boundaries	*boundaries;

	boundaries = malloc(sizeof(t_stack_boundaries));
	if (!boundaries)
		return (NULL);
	boundaries->lowest_value = lowest_value;
	boundaries->highest_value = highest_value;
	return (boundaries);
}

t_stack_boundaries	*get_stack_boundaries(t_list *stack_markup)
{
	t_stack_boundaries	*boundaries;
	t_list_node			*stack_markup_cpy;
	t_markup			*stack_markup_casted;

	stack_markup_cpy = stack_markup->first;
	stack_markup_casted = (t_markup *) stack_markup_cpy->content;
	boundaries = stack_boundaries_new(stack_markup_casted->number,
			stack_markup_casted->number);
	while (stack_markup_cpy)
	{
		stack_markup_casted = (t_markup *) stack_markup_cpy->content;
		if (stack_markup_casted->number < boundaries->lowest_value)
			boundaries->lowest_value = stack_markup_casted->number;
		if (stack_markup_casted->number > boundaries->highest_value)
			boundaries->highest_value = stack_markup_casted->number;
		stack_markup_cpy = stack_markup_cpy->next;
	}
	return (boundaries);
}
