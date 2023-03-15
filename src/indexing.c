/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:01:53 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/15 18:06:20 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indexing.h"

static t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*temp_lst;
	t_list	*lst_cpy;

	if (!lst)
		return (NULL);
	temp_lst = lst;
	lst_cpy = NULL;
	while (temp_lst)
	{
		ft_lstadd_back(&lst_cpy, ft_lstnew(temp_lst->content));
		temp_lst = temp_lst->next;
	}
	return (lst_cpy);
}

static void	ft_lstsort_swap(t_list *elem_1, t_list *elem_2)
{
	void	*temp;

	temp = elem_1->content;
	elem_1->content = elem_2->content;
	elem_2->content = temp;
}

static void	ft_lstsort(t_list **lst, int lst_size)
{
	int		i;
	int		j;
	t_list	*elem;
	t_list	*next_elem;
	t_list	*temp_lst;

	temp_lst = *lst;
	i = 0;
	while (i <= lst_size)
	{
		temp_lst = *lst;
		j = 0;
		while (j < lst_size - 1)
		{
			elem = temp_lst;
			next_elem = elem->next;
			if (*((int *)elem->content) > *((int *)next_elem->content))
				ft_lstsort_swap(elem, next_elem);
			temp_lst = next_elem;
			j++;
		}
		i++;
	}
}

static int	ft_lstfind_num(t_list *lst, int number)
{
	t_list	*lst_cpy;
	int		number_found;
	int		i;

	lst_cpy = lst;
	i = 0;
	while (lst_cpy)
	{
		number_found = *((int *) lst_cpy->content);
		if (number_found == number)
			return (i);
		lst_cpy = lst_cpy->next;
		i++;
	}
	return (-1);
}

t_list	*get_indexed_list(t_list *lst, int lst_size)
{
	t_list		*lst_cpy;
	t_list		*indexed_lst;
	t_list		*sorted_lst;
	t_indexed	*indexed_num;
	int			number;

	indexed_lst = NULL;
	lst_cpy = lst;
	sorted_lst = ft_lstcpy(lst);
	ft_lstsort(&sorted_lst, lst_size);
	while (lst_cpy)
	{
		number = *((int *) lst_cpy->content);
		indexed_num = malloc(sizeof(t_indexed));
		indexed_num->number = number;
		indexed_num->index = ft_lstfind_num(sorted_lst, number);
		ft_lstadd_back(&indexed_lst, ft_lstnew(indexed_num));
		lst_cpy = lst_cpy->next;
	}
	ft_lstclear(&sorted_lst, NULL);
	return (indexed_lst);
}
