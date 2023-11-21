/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_b_to_a.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:33:46 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 12:34:23 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_B_TO_A_H
# define STACK_B_TO_A_H

typedef enum e_direction
{
	DIR_REGULAR,
	DIR_REVERSE
}			t_direction;

typedef struct s_moveset
{
	int			count;
	t_direction	direction;
}				t_moveset;

typedef struct s_combined_moveset
{
	t_moveset	stack_a;
	t_moveset	stack_b;
	t_moveset	stack_both;
	int			total_count;
}				t_combined_moveset;

#endif
