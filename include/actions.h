/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:23:26 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:12:10 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "ft_list.h"

void	swap_lst(t_list **lst);
void	push_lst(t_list **lst_src, t_list **lst_dest);
void	rotate_lst(t_list **lst);
void	reverse_rotate_lst(t_list **lst);

#endif

