/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:04:31 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/12 17:55:30 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

int	count_markup_keep(t_list *markup_lst)
{
	t_list		*markup_lst_cpy;
	t_markup	*markup;
	int			keep_count;

	keep_count = 0;
	markup_lst_cpy = markup_lst;
	while (markup_lst_cpy)
	{
		markup = (t_markup *) markup_lst_cpy->content;
		if (markup->keep)
			keep_count++;
		markup_lst_cpy = markup_lst_cpy->next;
	}
	return (keep_count);
}

#include <stdio.h>

t_list	*find_markup_head(t_list *indexed_lst, t_markup_mode markup_mode)
{
	t_list	*indexed_lst_cpy;
	t_list	*markup_lst;
	t_list	*markup_head;
	int		last_keep_count;
	int		keep_count;

	indexed_lst_cpy = indexed_lst;
	last_keep_count = 0;
	while (indexed_lst_cpy)
	{
		markup_lst = get_markup(indexed_lst, indexed_lst_cpy, markup_mode);
		keep_count = count_markup_keep(markup_lst);
		if (markup_head != NULL && keep_count == last_keep_count)
		{
			t_indexed *markup_head_content = (t_indexed *) markup_head->content;
			t_indexed *indexed_lst_content = (t_indexed *) indexed_lst_cpy->content;

			if (indexed_lst_content->index < markup_head_content->index)
				markup_head = indexed_lst_cpy;
		}
		else if (keep_count > last_keep_count)
		{
			markup_head = indexed_lst_cpy;
			last_keep_count = keep_count;
		}
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	return (markup_head);
}
