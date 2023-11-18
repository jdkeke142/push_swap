/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:04:31 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 13:36:50 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

int	count_markup_keep(t_list *markup_lst)
{
	t_list_node	*markup_lst_cpy;
	t_markup	*markup;
	int			keep_count;

	keep_count = 0;
	markup_lst_cpy = markup_lst->first;
	while (markup_lst_cpy)
	{
		markup = (t_markup *) markup_lst_cpy->content;
		if (markup->keep)
			keep_count++;
		markup_lst_cpy = markup_lst_cpy->next;
	}
	return (keep_count);
}

typedef struct s_markup_kept
{
	int	kept_count;
	int	number;
	int	index;
}				t_markup_kept;

int	find_markup_head(t_list *indexed_lst, t_markup_mode markup_mode)
{
	t_list_node		*indexed_lst_cpy;
	t_markup_kept	last_kept;
	t_markup_kept	indexed;
	t_indexed		*indexed_node;
	t_list			*markup;

	indexed_lst_cpy = indexed_lst->first;
	last_kept = (t_markup_kept){0, 0, 0};
	while (indexed_lst_cpy)
	{
		indexed_node = (t_indexed *) indexed_lst_cpy->content;
		markup = get_markup(indexed_lst, indexed_node->number, markup_mode);
		indexed = (t_markup_kept){count_markup_keep(markup),
			indexed_node->number, indexed_node->index};
		if (indexed.kept_count > last_kept.kept_count)
			last_kept = indexed;
		if (indexed.kept_count == last_kept.kept_count
			&& indexed.index < last_kept.index)
			last_kept = indexed;
		ft_lstdestroy(markup, &free);
		indexed_lst_cpy = indexed_lst_cpy->next;
	}
	return (last_kept.number);
}
