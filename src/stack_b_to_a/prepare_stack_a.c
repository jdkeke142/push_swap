/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stack_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:29:10 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:40:48 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_b_to_a.h"
#include "stack.h"

static int	prepare_stack_a_closest_out(t_markup *stack_a_arr,
	int stack_a_arr_size, int lowest_value)
{
	int			i;

	i = 0;
	while (i < stack_a_arr_size
		&& stack_a_arr[i].number != lowest_value)
		i++;
	return (i);
}

static void	prepare_stack_a_closest_in_set(int i, int stack_a_arr_size,
	int *last_move_count, int *closest_index)
{
	int	move_count;

	if (i <= (stack_a_arr_size - 1) / 2)
		move_count = i;
	else
		move_count = stack_a_arr_size - i;
	if (move_count < *last_move_count)
	{
		*closest_index = i;
		*last_move_count = move_count;
	}
}

static int	prepare_stack_a_closest_in(t_markup *stack_a_arr,
	int stack_a_arr_size, t_markup	*markup)
{
	t_markup	arr_markup;
	int			closest_index;
	int			last_move_count;
	int			i;

	i = 0;
	closest_index = 0;
	last_move_count = stack_a_arr_size;
	while (i < stack_a_arr_size)
	{
		arr_markup = stack_a_arr[i];
		if ((i == 0
				&& arr_markup.number > markup->number
				&& stack_a_arr[stack_a_arr_size - 1].number < markup->number)
			|| (i > 0
				&& arr_markup.number > markup->number
				&& stack_a_arr[i - 1].number < markup->number))
			prepare_stack_a_closest_in_set(i, stack_a_arr_size,
				&last_move_count, &closest_index);
		i++;
	}
	return (closest_index);
}

t_moveset	count_prepare_stack_a(t_list *stack_a_markup, t_markup *stack_a_arr,
	t_markup	*markup, t_stack_boundaries	*stack_a_boundaries)
{
	int	closest_index;

	if (markup->number > stack_a_boundaries->highest_value
		|| markup->number < stack_a_boundaries->lowest_value)
		closest_index = prepare_stack_a_closest_out(stack_a_arr,
				stack_a_markup->size, stack_a_boundaries->lowest_value);
	else
		closest_index = prepare_stack_a_closest_in(stack_a_arr,
				stack_a_markup->size, markup);
	if (closest_index <= (stack_a_markup->size - 1) / 2)
		return ((t_moveset){closest_index, DIR_REGULAR});
	return ((t_moveset){stack_a_markup->size - closest_index, DIR_REVERSE});
}
