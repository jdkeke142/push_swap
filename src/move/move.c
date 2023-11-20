/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:04:40 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/20 19:21:43 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

t_move	*move_new(t_stack stack, t_action action)
{
	t_move	*move;

	move = malloc(sizeof(t_move));
	if (!move)
		return (NULL);
	move->stack = stack;
	move->action = action;
	return (move);
}
