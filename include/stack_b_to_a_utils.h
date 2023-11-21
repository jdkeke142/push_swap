/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:35:50 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:44:23 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_B_TO_A_UTILS_H
# define STACK_B_TO_A_UTILS_H

# include "stack_b_to_a.h"
# include "stack.h"

t_moveset			count_prepare_stack_a(t_list *stack_a_markup,
						t_markup *stack_a_arr, t_markup	*markup,
						t_stack_boundaries	*stack_a_boundaries);
t_moveset			count_prepare_stack_b(t_list *stack_b_markup,
						int stack_b_curr_size);
t_combined_moveset	find_best_moveset(t_list *stack_a_markup,
						t_markup *stack_a_arr, t_list *stack_b_markup,
						t_stack_boundaries	*stack_a_boundaries);
void				apply_combined_moveset(t_combined_moveset combined_moveset,
						t_list *moves, t_list *stack_a_markup,
						t_list *stack_b_markup);

#endif
