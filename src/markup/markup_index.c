/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:58:05 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:07:19 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

static int	markup_by_index_next(t_indexed *lst, int last_kept, int markup)
{
	int	start;
	int	kept_amount;

	kept_amount = 0;
	start = markup - 1;
	while (start >= 0)
	{
		if (lst[start].index == last_kept + 1)
		{
			last_kept = lst[start].index;
			kept_amount++;
		}
		start--;
	}
	return (kept_amount);
}

static int	markup_by_index_prev(t_indexed *lst, int lst_size, int last_kept,
	int markup)
{
	int	start;
	int	kept_amount;

	kept_amount = 0;
	start = markup + 1;
	while (start <= lst_size - 1)
	{
		if (lst[start].index == last_kept + 1)
		{
			last_kept = lst[start].index;
			kept_amount++;
		}
		start++;
	}
	return (kept_amount);
}

t_markup	markup_by_index(t_indexed *lst, int lst_size, int markup)
{
	int			kept_amount;
	int			last_kept;

	kept_amount = 1;
	last_kept = lst[markup].index;
	kept_amount += markup_by_index_prev(lst, lst_size, last_kept,
			markup);
	kept_amount += markup_by_index_next(lst, last_kept, markup);
	return ((t_markup){lst[markup].number, kept_amount});
}
