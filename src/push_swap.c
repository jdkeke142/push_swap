/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/20 20:04:56 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "stack.h"
#include "parsing.h"
#include "ft_stdio.h"

static t_list	*solve(int *numbers, int numbers_count,
	t_markup_mode markup_mode)
{
	t_list		*moves;
	t_stack_a	*stack_a;
	t_list		*stack_b_markup;

	stack_b_markup = ft_lstnew();
	moves = ft_lstnew();
	stack_a = stack_a_new();
	stack_a->indexed = get_indexed_list(numbers, numbers_count);
	stack_a->markup_head = find_markup_head(stack_a->indexed, markup_mode);
	stack_a->markup = get_markup(stack_a->indexed, stack_a->markup_head,
			markup_mode);
	stack_a_to_b(stack_a, stack_b_markup, moves, markup_mode);
	stack_b_to_a(stack_a->markup, stack_b_markup, moves);
	align_stack_a(stack_a->markup, moves);
	ft_lstdestroy(stack_a->markup, &free);
	ft_lstdestroy(stack_a->indexed, &free);
	ft_lstdestroy(stack_b_markup, &free);
	free(stack_a);
	return (moves);
}

int	main(int argc, char *args[])
{
	t_list		*moves_by_index;
	t_list		*moves_greater_than;
	int			*numbers;
	int			numbers_count;

	(void) argc;
	numbers_count = 0;
	numbers = parse(args, &numbers_count);
	if (numbers == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	moves_by_index = solve(numbers, numbers_count, MARKUP_BY_INDEX);
	moves_greater_than = solve(numbers, numbers_count, MARKUP_GREATER_THAN);
	if (moves_by_index->size < moves_greater_than->size)
		print_moveset(moves_by_index);
	else
		print_moveset(moves_greater_than);
	ft_lstdestroy(moves_by_index, &free);
	ft_lstdestroy(moves_greater_than, &free);
	free(numbers);
}
