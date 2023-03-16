/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:55 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/16 20:59:17 by kjimenez         ###   ########.fr       */
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
		return (content->number > last_kept);
	else
		return (content->index == last_kept + 1);
}

static void	markup_populate(t_list **markup_lst,
	t_list *markup_head, void (*lstadd)(t_list **, t_list *),
	t_markup_mode markup_mode)
{
	t_list		*markup_head_cpy;
	int			last_kept;
	t_markup	*markup;

	markup_head_cpy = markup_head;
	last_kept = get_markup_number(markup_head_cpy, markup_mode);
	markup_head_cpy = markup_head_cpy->next;
	while (markup_head_cpy)
	{
		markup = malloc(sizeof(t_markup));
		markup->number = ((t_indexed *)markup_head_cpy->content)->number;
		if (get_markup_comparison(markup_head_cpy, markup_mode, last_kept))
		{
			markup->keep = 1;
			last_kept = get_markup_number(markup_head_cpy, markup_mode);
		}
		else
			markup->keep = 0;
		lstadd(markup_lst, ft_lstnew(markup));
		markup_head_cpy = markup_head_cpy->next;
	}
}

t_list	*get_markup(t_list *indexed_lst, t_list *markup_head,
	t_markup_mode markup_mode)
{
	t_list		*reversed_lst;
	t_list		*reversed_markup_head;
	t_list		*indexed_lst_cpy;
	t_list		*markup_lst;
	t_markup	*markup;

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
	markup = malloc(sizeof(t_markup));
	markup->number = ((t_indexed *)markup_head->content)->number;
	markup->keep = 1;
	ft_lstadd_front(&markup_lst, ft_lstnew(markup));
	markup_populate(&markup_lst, markup_head, ft_lstadd_back,
		markup_mode);
	markup_populate(&markup_lst, reversed_markup_head,
		ft_lstadd_front, markup_mode);
	return (markup_lst);
}
