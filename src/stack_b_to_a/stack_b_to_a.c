/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:37:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/20 20:27:25 by kjimenez         ###   ########.fr       */
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

typedef enum e_direction
{
	DIR_REGULAR,
	DIR_REVERSE
}			t_direction;

typedef struct s_moveset
{
	int			count;
	t_direction	direction;
}				t_moveset;

typedef struct s_combined_moveset
{
	t_moveset	stack_a;
	t_moveset	stack_b;
	t_moveset	stack_both;
	int			total_count;
}				t_combined_moveset;

static t_moveset	count_prepare_stack_b(t_list *stack_b_markup,
	int stack_b_curr_size)
{
	if (stack_b_curr_size <= (stack_b_markup->size - 1) / 2)
		return ((t_moveset){stack_b_curr_size, DIR_REGULAR});
	return ((t_moveset){stack_b_markup->size - stack_b_curr_size, DIR_REVERSE});
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

static t_moveset	count_prepare_stack_a(t_list *stack_a_markup, t_markup *stack_a_arr,
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

static t_combined_moveset	find_best_moveset(t_list *stack_a_markup,
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

static void	apply_combined_moveset(t_combined_moveset combined_moveset,
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
