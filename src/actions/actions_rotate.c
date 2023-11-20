/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:27:49 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/20 19:30:01 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	rotate_lst(t_list *lst)
{
	void	*first_content;

	first_content = ft_lstdel_front(lst);
	if (first_content == NULL)
		return ;
	ft_lstadd_back(lst, first_content);
}

void	reverse_rotate_lst(t_list *lst)
{
	void	*last_content;

	last_content = ft_lstdel_back(lst);
	if (last_content == NULL)
		return ;
	ft_lstadd_front(lst, last_content);
}

void	rotate_lsts(t_list *lst, t_list *lst_2)
{
	rotate_lst(lst);
	rotate_lst(lst_2);
}

void	reverse_rotate_lsts(t_list *lst, t_list *lst_2)
{
	reverse_rotate_lst(lst);
	reverse_rotate_lst(lst_2);
}
