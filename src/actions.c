/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:08:06 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:15:24 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	swap_lst(t_list **lst)
{
	int		i;
	t_list	*temp_lst;
	void	*first_content;

	if (!(*lst) || ft_lstsize(*lst) < 2)
		return ;
	temp_lst = *lst;
	i = 0;
	while (i < 1)
	{
		temp_lst = temp_lst->next;
		i++;
	}
	first_content = temp_lst->content;
	temp_lst->content = (*lst)->content;
	(*lst)-> content = first_content;
}

void	push_lst(t_list **lst_src, t_list **lst_dest)
{
	t_list	*lst_temp;

	if (!(*lst_src) || ft_lstsize(*lst_src) < 1)
		return ;
	ft_lstadd_front(lst_dest, ft_lstnew((*lst_src)->content));
	lst_temp = (*lst_src)->next;
	ft_lstdelone(*lst_src, NULL);
	*lst_src = lst_temp;
}

void	rotate_lst(t_list **lst)
{
	t_list	*first_elem;

	first_elem = *lst;
	*lst = (*lst)->next;
	ft_lstlast(*lst)->next = first_elem;
	first_elem->next = NULL;
}

void	reverse_rotate_lst(t_list **lst)
{
	int		i;
	int		lst_size;
	t_list	*temp_lst;
	t_list	*last_elem;

	temp_lst = *lst;
	lst_size = ft_lstsize(temp_lst);
	i = 0;
	while (i < (lst_size - 2))
	{
		temp_lst = temp_lst->next;
		i++;
	}
	last_elem = ft_lstlast(temp_lst);
	last_elem->next = *lst;
	temp_lst->next = NULL;
	*lst = last_elem;
}
