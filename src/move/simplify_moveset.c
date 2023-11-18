/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_moveset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:33:03 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 14:01:47 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

static void	get_simplified_moveset_apply(t_list	*moveset,
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

static t_list	*get_simplified_moveset_action(t_list	*moveset,
	t_action action)
{
	t_list		*simplified_moveset;
	t_list_node	*moveset_cpy;
	t_move		*move;
	int			ra_count;
	int			rb_count;

	moveset_cpy = moveset->first;
	simplified_moveset = ft_lstnew();
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
			get_simplified_moveset_apply(simplified_moveset, &ra_count,
				&rb_count, action);
			ft_lstadd_back(simplified_moveset,
				move_new(move->stack, move->action));
		}
		moveset_cpy = moveset_cpy->next;
	}
	get_simplified_moveset_apply(simplified_moveset, &ra_count,
		&rb_count, action);
	return (simplified_moveset);
}

t_list	*get_simplified_moveset(t_list	*moveset)
{
	t_list	*rotate_simplified;
	t_list	*reverse_rotate_simplified;

	rotate_simplified = get_simplified_moveset_action(moveset, ACT_ROTATE);
	reverse_rotate_simplified = get_simplified_moveset_action(rotate_simplified,
			ACT_REVERSE_ROTATE);
	ft_lstdestroy(rotate_simplified, &free);
	return (reverse_rotate_simplified);
}
