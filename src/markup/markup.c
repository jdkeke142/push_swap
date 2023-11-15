/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:55 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/13 15:30:38 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

static int	get_markup_number(t_list *markup, t_markup_mode markup_mode)
{
	t_indexed	*content;

	content = ((t_indexed *)markup->content);
	if (markup_mode == MARKUP_GREATER_THAN)
		return (content->number);
	return (content->index);
}

static int	get_markup_comparison(t_list *markup, t_markup_mode markup_mode,
	int last_kept)
{
	t_indexed	*content;

	content = ((t_indexed *)markup->content);
	if (markup_mode == MARKUP_GREATER_THAN)
		return (content->number >= last_kept);
	else
		return (content->index == last_kept
			||content->index == last_kept + 1);
}

#include <stdio.h>

//Start from markup head to the end of the list
//Once end of the list reached start from the beginning of the list to markup head (skip it)

/*
	List 2:
	60
	50

	List 1:
	30 <-- HEAD
	20
	5
	10
*/

static t_list	*markup_populate(t_list	*lst, t_markup_mode markup_mode,
	int reset_last_kept)
{
	static int	last_kept;
	t_list		*lst_cpy;
	t_markup	*markup;
	t_list		*markup_lst;

	markup_lst = NULL;
	lst_cpy = lst;
	if (reset_last_kept)
		last_kept = get_markup_number(lst_cpy, markup_mode);
	while (lst_cpy)
	{
		markup = malloc(sizeof(t_markup));
		markup->number = ((t_indexed *)lst_cpy->content)->number;
		if (get_markup_comparison(lst_cpy, markup_mode, last_kept))
		{
			markup->keep = 1;
			last_kept = get_markup_number(lst_cpy, markup_mode);
		}
		else
			markup->keep = 0;
		ft_lstadd_back(&markup_lst, ft_lstnew(markup));
		lst_cpy = lst_cpy->next;
	}
	return (markup_lst);
}

t_list	*get_before_markup_head(t_list *indexed_lst, t_list *markup_head)
{
	t_list	*indexed_lst_cpy;
	t_list	*before_markup_head;

	before_markup_head = NULL;
	indexed_lst_cpy = indexed_lst;
	while (indexed_lst_cpy && indexed_lst_cpy != markup_head)
	{
		ft_lstadd_back(&before_markup_head,
			ft_lstnew(indexed_lst_cpy->content));
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	return (before_markup_head);
}

t_list	*get_markup(t_list *indexed_lst, t_list *markup_head,
	t_markup_mode markup_mode)
{
	t_list		*begin_markup_lst;
	t_list		*end_markup_lst;
	t_list		*markup_lst;
	t_list		*before_markup_head;

	markup_lst = NULL;
	before_markup_head = get_before_markup_head(indexed_lst, markup_head);
	end_markup_lst = markup_populate(markup_head, markup_mode, 1);
	begin_markup_lst = markup_populate(before_markup_head, markup_mode, 0);
	while (begin_markup_lst)
	{
		ft_lstadd_back(&markup_lst, ft_lstnew(begin_markup_lst->content));
		begin_markup_lst = begin_markup_lst->next;
	}
	while (end_markup_lst)
	{
		ft_lstadd_back(&markup_lst, ft_lstnew(end_markup_lst->content));
		end_markup_lst = end_markup_lst->next;
	}
	return (markup_lst);
}
