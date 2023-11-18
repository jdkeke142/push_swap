/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:55 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 16:36:45 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

static void	get_markup_add(t_indexed *indexed, t_indexed **last_kept,
	t_list *markup_lst, t_markup_mode markup_mode)
{
	if (*last_kept == NULL
		|| (markup_mode == MARKUP_GREATER_THAN
			&& indexed->number > (*last_kept)->number)
		|| (markup_mode == MARKUP_BY_INDEX
			&& (indexed->index == (*last_kept)->index + 1)))
	{
		ft_lstadd_back(markup_lst, markup_new(indexed->number, 1));
		*last_kept = indexed;
	}
	else
		ft_lstadd_back(markup_lst, markup_new(indexed->number, 0));
}

static t_list	*get_markup_from_head(t_list *indexed_lst, int markup_head,
	t_indexed	**last_kept, t_markup_mode markup_mode)
{
	t_list		*markup_lst;
	t_list_node	*indexed_lst_cpy;
	t_indexed	*indexed;
	int			markup_reached;

	markup_reached = 0;
	indexed_lst_cpy = indexed_lst->first;
	markup_lst = ft_lstnew();
	while (indexed_lst_cpy)
	{
		indexed = (t_indexed *) indexed_lst_cpy->content;
		if (indexed->number == markup_head)
			markup_reached = 1;
		if (markup_reached)
			get_markup_add(indexed, last_kept, markup_lst, markup_mode);
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	return (markup_lst);
}

static t_list	*get_markup_before_head(t_list *indexed_lst, int markup_head,
	t_indexed	**last_kept, t_markup_mode markup_mode)
{
	t_list		*markup_lst;
	t_list_node	*indexed_lst_cpy;
	t_indexed	*indexed;

	indexed_lst_cpy = indexed_lst->first;
	markup_lst = ft_lstnew();
	while (indexed_lst_cpy)
	{
		indexed = (t_indexed *) indexed_lst_cpy->content;
		if (indexed->number == markup_head)
			break ;
		get_markup_add(indexed, last_kept, markup_lst, markup_mode);
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	return (markup_lst);
}

void	get_markup_merge(t_list *markup_lst, t_list *markup_before_head,
	t_list *markup_from_head)
{
	t_list_node	*markup_cpy;

	markup_cpy = markup_before_head->first;
	while (markup_cpy)
	{
		ft_lstadd_back(markup_lst, markup_cpy->content);
		markup_cpy = markup_cpy->next;
	}
	markup_cpy = markup_from_head->first;
	while (markup_cpy)
	{
		ft_lstadd_back(markup_lst, markup_cpy->content);
		markup_cpy = markup_cpy->next;
	}
	ft_lstdestroy(markup_before_head, NULL);
	ft_lstdestroy(markup_from_head, NULL);
}

t_list	*get_markup(t_list *indexed_lst, int markup_head,
	t_markup_mode markup_mode)
{
	t_list		*markup_before_head;
	t_list		*markup_from_head;
	t_list		*markup_lst;
	t_indexed	*last_kept;

	markup_lst = ft_lstnew();
	last_kept = NULL;
	markup_from_head = get_markup_from_head(indexed_lst, markup_head,
			&last_kept, markup_mode);
	markup_before_head = get_markup_before_head(indexed_lst, markup_head,
			&last_kept, markup_mode);
	get_markup_merge(markup_lst, markup_before_head, markup_from_head);
	return (markup_lst);
}
