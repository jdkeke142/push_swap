/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:08:26 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:42:45 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "ft_list.h"
# include "markup.h"

typedef struct s_stack_boundaries
{
	int	lowest_value;
	int	highest_value;
}				t_stack_boundaries;

typedef struct s_stack_a
{
	t_list	*indexed;
	t_list	*markup;
	int		markup_head;
}				t_stack_a;

void				stack_a_to_b(t_stack_a *stack_a, t_list *stack_b_markup,
						t_list *moves, t_markup_mode markup_mode);
void				stack_b_to_a(t_list	*stack_a_markup,
						t_list *stack_b_markup, t_list *moves);
void				align_stack_a(t_list	*stack_a_markup, t_list *moves);
t_stack_boundaries	*get_stack_boundaries(t_list *stack_markup);
t_stack_a			*stack_a_new(void);

#endif
