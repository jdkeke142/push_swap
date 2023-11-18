/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:09:02 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 20:03:42 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack_a	*stack_a_new(void)
{
	t_stack_a	*stack_a;

	stack_a = malloc(sizeof(t_stack_a));
	if (!stack_a)
		return (NULL);
	return (stack_a);
}
