/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:37:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 16:36:57 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "move.h"
#include "actions.h"

int	get_markup_index(t_list *stack_markup, t_markup *markup)
{
	t_list_node	*stack_markup_cpy;
	t_markup	*found_markup;
	int			i;

	stack_markup_cpy = stack_markup->first;
	i = 0;
	while (stack_markup_cpy)
	{
		found_markup = (t_markup *) stack_markup_cpy->content;
		if (markup->number == found_markup->number)
			break ;
		stack_markup_cpy = stack_markup_cpy->next;
		i++;
	}
	return (i);
}

static void	prepare_stack_b(t_list *stack_b_markup, t_markup *markup,
	t_list *moveset)
{
	int			move_count;
	int			markup_index;

	markup_index = get_markup_index(stack_b_markup, markup);
	if (markup_index <= (stack_b_markup->size - 1) / 2)
	{
		move_count = markup_index;
		apply_moveset(STACK_B, move_count, ACT_ROTATE, moveset);
		rotate_lst_multiple(stack_b_markup, move_count);
	}
	else
	{
		move_count = stack_b_markup->size - markup_index;
		apply_moveset(STACK_B, move_count, ACT_REVERSE_ROTATE, moveset);
		reverse_rotate_lst_multiple(stack_b_markup, move_count);
	}
}

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

static int	prepare_stack_a_closest_in(t_markup *stack_a_arr,
	int stack_a_arr_size, t_markup	*markup, int highest_value)
{
	t_markup	arr_markup;
	int			closest_number;
	int			closest_index;
	int			i;

	closest_number = highest_value + 1;
	i = 0;
	closest_index = 0;
	while (i < stack_a_arr_size)
	{
		arr_markup = stack_a_arr[i];
		if (arr_markup.number > markup->number
			&& arr_markup.number < closest_number)
		{
			closest_number = arr_markup.number;
			closest_index = i;
		}
		i++;
	}
	return (closest_index);
}

static void	prepare_stack_a(t_list *stack_a_markup, t_markup *stack_a_arr,
	t_markup *markup, t_stack_boundaries *stack_a_boundaries,
	t_list *moveset)
{
	int	closest_index;
	int	move_count;

	if (markup->number > stack_a_boundaries->highest_value
		|| markup->number < stack_a_boundaries->lowest_value)
		closest_index = prepare_stack_a_closest_out(stack_a_arr,
				stack_a_markup->size, stack_a_boundaries->lowest_value);
	else
		closest_index = prepare_stack_a_closest_in(stack_a_arr, stack_a_markup
				->size, markup, stack_a_boundaries->highest_value);
	if (closest_index <= (stack_a_markup->size - 1) / 2)
	{
		move_count = closest_index;
		rotate_lst_multiple(stack_a_markup, move_count);
		apply_moveset(STACK_A, move_count, ACT_ROTATE, moveset);
	}
	else
	{
		move_count = stack_a_markup->size - closest_index;
		reverse_rotate_lst_multiple(stack_a_markup, move_count);
		apply_moveset(STACK_A, move_count, ACT_REVERSE_ROTATE, moveset);
	}
}

static int	count_prepare_stack_a(t_list *stack_a_markup, t_markup *stack_a_arr,
	t_markup	*markup, t_stack_boundaries	*stack_a_boundaries)
{
	int	closest_index;

	if (markup->number > stack_a_boundaries->highest_value
		|| markup->number < stack_a_boundaries->lowest_value)
		closest_index = prepare_stack_a_closest_out(stack_a_arr,
				stack_a_markup->size, stack_a_boundaries->lowest_value);
	else
		closest_index = prepare_stack_a_closest_in(stack_a_arr,
				stack_a_markup->size, markup,
				stack_a_boundaries->highest_value);
	if (closest_index <= (stack_a_markup->size - 1) / 2)
		return (closest_index);
	return (stack_a_markup->size - closest_index);
}

static int	count_prepare_stack_b(t_list *stack_b_markup, int stack_b_curr_size)
{
	if (stack_b_curr_size <= (stack_b_markup->size - 1) / 2)
		return (stack_b_curr_size);
	return (stack_b_markup->size - stack_b_curr_size);
}

static t_markup	*find_best_markup(t_list *stack_a_markup,
	t_markup *stack_a_arr, t_list *stack_b_markup,
	t_stack_boundaries	*stack_a_boundaries)
{
	t_markup		*markup;
	t_markup		*best_markup;
	int				best_count;
	int				count;
	int				stack_b_curr_size;
	t_list_node		*stack_b_markup_cpy;

	best_markup = NULL;
	stack_b_curr_size = 0;
	stack_b_markup_cpy = stack_b_markup->first;
	while (stack_b_markup_cpy)
	{
		markup = (t_markup *) stack_b_markup_cpy->content;
		count = count_prepare_stack_b(stack_b_markup, stack_b_curr_size)
			+ count_prepare_stack_a(stack_a_markup, stack_a_arr, markup,
				stack_a_boundaries);
		if (best_markup == NULL || count < best_count)
		{
			best_markup = markup;
			best_count = count;
		}
		stack_b_markup_cpy = stack_b_markup_cpy->next;
		stack_b_curr_size++;
	}
	return (best_markup);
}

t_markup	*stack_markup_to_array(t_list	*stack_markup)
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

void	stack_b_to_a(t_list	*stack_a_markup,
	t_list *stack_b_markup, t_list *moves)
{
	t_stack_boundaries	*stack_a_boundaries;
	t_markup			*best_markup;
	t_markup			*stack_a_array;

	while (stack_b_markup->size > 0)
	{
		stack_a_boundaries = get_stack_boundaries(stack_a_markup);
		stack_a_array = stack_markup_to_array(stack_a_markup);
		best_markup = find_best_markup(stack_a_markup,
				stack_a_array, stack_b_markup, stack_a_boundaries);
		prepare_stack_a(stack_a_markup, stack_a_array, best_markup,
			stack_a_boundaries, moves);
		prepare_stack_b(stack_b_markup, best_markup, moves);
		push_lst(stack_b_markup, stack_a_markup);
		ft_lstadd_back(moves, move_new(STACK_B, ACT_PUSH));
		free(stack_a_boundaries);
		free(stack_a_array);
	}
}
