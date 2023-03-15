/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:53:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/15 16:19:22 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

/*t_markup	get_markup_head(t_markup_mode mode, t_indexed *lst, int lst_size)
{
	int			i;
	t_markup	markup_head;
	t_markup	markup;

	i = 0;
	while (i < lst_size)
	{
		if (mode == MARKUP_GREATER_THAN)
			markup = markup_greater_than(lst, lst_size, i);
		else
			markup = markup_by_index(lst, lst_size, i);
		if (markup.kept_amount > markup_head.kept_amount)
			markup_head = markup;
		i++;
	}
	return (markup_head);
}*/
