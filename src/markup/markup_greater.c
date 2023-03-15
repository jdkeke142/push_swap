/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:55 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/15 19:29:12 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

static void	markup_greater_than_populate(t_list **markup_lst,
	t_list *markup_head, void (*lstadd)(t_list **, t_list *))
{
	t_list		*markup_head_cpy;
	int			last_kept;
	t_markup	*markup;

	markup_head_cpy = markup_head;
	last_kept = ((t_indexed *)markup_head_cpy->content)->number;
	markup_head_cpy = markup_head_cpy->next;
	while (markup_head_cpy)
	{
		markup = malloc(sizeof(t_markup));
		markup->number = ((t_indexed *)markup_head_cpy->content)->number;
		if (markup->number > last_kept)
		{
			markup->keep = 1;
			last_kept = markup->number;
		}
		else
			markup->keep = 0;
		lstadd(markup_lst, ft_lstnew(markup));
		markup_head_cpy = markup_head_cpy->next;
	}
}

t_list	*markup_greater_than(t_list *indexed_lst, t_list *markup_head)
{
	t_list	*reversed_lst;
	t_list	*reversed_markup_head;
	t_list	*indexed_lst_cpy;
	t_list	*markup_lst;

	reversed_lst = NULL;
	indexed_lst_cpy = indexed_lst;
	markup_lst = NULL;
	while (indexed_lst_cpy)
	{
		ft_lstadd_front(&reversed_lst, ft_lstnew(indexed_lst_cpy->content));
		if (indexed_lst_cpy == markup_head)
			reversed_markup_head = reversed_lst;
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	ft_lstadd_front(&markup_lst, ft_lstnew(markup_head->content));
	markup_greater_than_populate(&markup_lst, markup_head, ft_lstadd_back);
	markup_greater_than_populate(&markup_lst, reversed_markup_head,
		ft_lstadd_front);
	return (markup_lst);
}
