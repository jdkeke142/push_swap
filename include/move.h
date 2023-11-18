/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:05:22 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 20:15:47 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "ft_list.h"

typedef enum e_action
{
	ACT_SWAP,
	ACT_ROTATE,
	ACT_REVERSE_ROTATE,
	ACT_PUSH
}			t_action;

typedef enum e_stack
{
	STACK_A,
	STACK_B,
	STACK_BOTH
}			t_stack;

typedef struct s_move
{
	t_stack		stack;
	t_action	action;
}				t_move;

t_move	*move_new(t_stack stack, t_action action);
void	print_moveset(t_list	*moveset);
t_list	*get_simplified_moveset(t_list	*moveset);
void	apply_moveset(t_stack stack, int count, t_action action,
			t_list *moveset);

#endif
