/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a_to_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:02:17 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 16:47:19 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "ft_list.h"
#include "move.h"
#include "stack.h"

static int	sa_needed(t_stack_a *stack_a, t_markup_mode mode)
{
	int		keep_swap;
	int		keep_without_swap;
	t_list	*stack_a_markup;

	keep_without_swap = count_markup_keep(stack_a->markup);
	swap_lst(stack_a->indexed);
	stack_a_markup = get_markup(stack_a->indexed, stack_a->markup_head, mode);
	keep_swap = count_markup_keep(stack_a_markup);
	swap_lst(stack_a->indexed);
	ft_lstdestroy(stack_a_markup, &free);
	return (keep_swap > keep_without_swap);
}

static void	stack_a_to_b_rotate(t_stack_a *stack_a, t_list *moves)
{
	rotate_lst(stack_a->markup);
	rotate_lst(stack_a->indexed);
	ft_lstadd_back(moves, move_new(STACK_A, ACT_ROTATE));
}

static void	stack_a_to_b_push(t_stack_a *stack_a, t_list *stack_b_markup,
	t_list *moves)
{
	push_lst(stack_a->markup, stack_b_markup);
	free(ft_lstdel_front(stack_a->indexed));
	ft_lstadd_back(moves, move_new(STACK_A, ACT_PUSH));
}

static void	stack_a_to_b_swap(t_stack_a *stack_a, t_markup_mode markup_mode,
	t_list *moves)
{
	swap_lst(stack_a->markup);
	swap_lst(stack_a->indexed);
	ft_lstadd_back(moves, move_new(STACK_A, ACT_SWAP));
	ft_lstdestroy(stack_a->markup, &free);
	stack_a->markup = get_markup(stack_a->indexed,
			stack_a->markup_head, markup_mode);
}

void	stack_a_to_b(t_stack_a *stack_a, t_list *stack_b_markup,
	t_list *moves, t_markup_mode markup_mode)
{
	t_markup	*stack_a_first_elem;

	while (count_markup_keep(stack_a->markup) != stack_a->markup->size)
	{
		stack_a_first_elem = (t_markup *) ft_lstfirst(stack_a->markup);
		if (sa_needed(stack_a, markup_mode))
			stack_a_to_b_swap(stack_a, markup_mode, moves);
		else if (stack_a_first_elem->keep == 0)
			stack_a_to_b_push(stack_a, stack_b_markup, moves);
		else
			stack_a_to_b_rotate(stack_a, moves);
	}
}
