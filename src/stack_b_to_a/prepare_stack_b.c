/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stack_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:38:22 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:49:20 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack_b_to_a.h"
#include "ft_list.h"

t_moveset	count_prepare_stack_b(t_list *stack_b_markup,
	int stack_b_curr_size)
{
	if (stack_b_curr_size <= (stack_b_markup->size - 1) / 2)
		return ((t_moveset){stack_b_curr_size, DIR_REGULAR});
	return ((t_moveset){stack_b_markup->size - stack_b_curr_size, DIR_REVERSE});
}
