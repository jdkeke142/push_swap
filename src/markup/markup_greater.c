/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:46:55 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:07:23 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

static int	markup_greater_than_next(t_indexed *lst, int last_kept, int markup)
{
	int	start;
	int	kept_amount;

	kept_amount = 0;
	start = markup - 1;
	while (start >= 0)
	{
		if (lst[start].number > last_kept)
		{
			last_kept = lst[start].number;
			kept_amount++;
		}
		start--;
	}
	return (kept_amount);
}

static int	markup_greater_than_prev(t_indexed *lst, int lst_size,
	int last_kept, int markup)
{
	int	start;
	int	kept_amount;

	kept_amount = 0;
	start = markup + 1;
	while (start <= lst_size - 1)
	{
		if (lst[start].number > last_kept)
		{
			last_kept = lst[start].number;
			kept_amount++;
		}
		start++;
	}
	return (kept_amount);
}

t_markup	markup_greater_than(t_indexed *lst, int lst_size, int markup)
{
	int			kept_amount;
	int			last_kept;

	kept_amount = 1;
	last_kept = lst[markup].number;
	kept_amount += markup_greater_than_prev(lst, lst_size, last_kept,
			markup);
	kept_amount += markup_greater_than_next(lst, last_kept, markup);
	return ((t_markup){lst[markup].number, kept_amount});
}
