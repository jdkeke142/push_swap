/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moveset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:30:06 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 20:16:37 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "ft_stdio.h"

static void	print_move_stack_both(t_move *move)
{
	if (move->stack != STACK_BOTH)
		return ;
	if (move->action == ACT_ROTATE)
		ft_printf("rr\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rrr\n");
}

static void	print_move_stack_a(t_move *move)
{
	if (move->stack != STACK_A)
		return ;
	if (move->action == ACT_PUSH)
		ft_printf("pb\n");
	if (move->action == ACT_ROTATE)
		ft_printf("ra\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rra\n");
	if (move->action == ACT_SWAP)
		ft_printf("sa\n");
}

static void	print_move_stack_b(t_move *move)
{
	if (move->stack != STACK_B)
		return ;
	if (move->action == ACT_PUSH)
		ft_printf("pa\n");
	if (move->action == ACT_ROTATE)
		ft_printf("rb\n");
	if (move->action == ACT_REVERSE_ROTATE)
		ft_printf("rrb\n");
}

void	print_moveset(t_list *moveset)
{
	t_list_node	*moveset_cpy;
	t_move		*move;

	moveset_cpy = moveset->first;
	while (moveset_cpy)
	{
		move = (t_move *) moveset_cpy->content;
		print_move_stack_a(move);
		print_move_stack_b(move);
		print_move_stack_both(move);
		moveset_cpy = moveset_cpy->next;
	}
}
