/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_moveset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:33:03 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 16:38:52 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

static void	simplify_moveset_apply(t_list	*moveset,
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

static int	simplify_moveset_increment(t_action action, t_move *move,
	int *ra_count, int *rb_count)
{
	if (move->action != action)
		return (0);
	if (move->stack == STACK_A)
		(*ra_count)++;
	if (move->stack == STACK_B)
		(*rb_count)++;
	return (1);
}

static void	simplify_moveset_action(t_list **moveset,
	t_action action)
{
	t_list_node	*moveset_cpy;
	t_list		*simplified_moveset;
	t_move		*move;
	int			ra_count;
	int			rb_count;

	moveset_cpy = (*moveset)->first;
	simplified_moveset = ft_lstnew();
	ra_count = 0;
	rb_count = 0;
	while (moveset_cpy)
	{
		move = (t_move *) moveset_cpy->content;
		if (!simplify_moveset_increment(action, move, &ra_count, &rb_count))
		{
			simplify_moveset_apply(simplified_moveset, &ra_count,
				&rb_count, action);
			ft_lstadd_back(simplified_moveset,
				move_new(move->stack, move->action));
		}
		moveset_cpy = moveset_cpy->next;
	}
	simplify_moveset_apply(simplified_moveset, &ra_count, &rb_count, action);
	ft_lstdestroy(*moveset, &free);
	*moveset = simplified_moveset;
}

void	simplify_moveset(t_list	**moveset)
{
	simplify_moveset_action(moveset, ACT_ROTATE);
	simplify_moveset_action(moveset, ACT_REVERSE_ROTATE);
}
