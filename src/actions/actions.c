/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:43:58 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/21 17:06:00 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	swap_lst(t_list *lst)
{
	void	*first_content;
	void	*second_content;

	first_content = ft_lstdel_front(lst);
	second_content = ft_lstdel_front(lst);
	if (first_content == NULL || second_content == NULL)
		return ;
	ft_lstadd_front(lst, first_content);
	ft_lstadd_front(lst, second_content);
}

void	push_lst(t_list *lst_src, t_list *lst_dest)
{
	void	*first_content;

	first_content = ft_lstdel_front(lst_src);
	if (first_content == NULL)
		return ;
	ft_lstadd_front(lst_dest, first_content);
}

void	swap_lsts(t_list *lst, t_list *lst_2)
{
	swap_lst(lst);
	swap_lst(lst_2);
}
