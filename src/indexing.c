/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:01:53 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 16:47:45 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indexing.h"
#include <stdlib.h>

static int	*copy_list(int *lst, int lst_size)
{
	int	*lst_cpy;
	int	i;

	lst_cpy = malloc(lst_size * sizeof(int));
	i = 0;
	while (i < lst_size)
	{
		lst_cpy[i] = lst[i];
		i++;
	}
	return (lst_cpy);
}

static int	*sort_list(int *lst, int lst_size)
{
	int	*sorted_lst;
	int	i;
	int	j;
	int	temp;

	sorted_lst = copy_list(lst, lst_size);
	i = 0;
	temp = 0;
	while (i < lst_size)
	{
		j = i + 1;
		while (j < lst_size)
		{
			if (sorted_lst[i] > sorted_lst[j])
			{
				temp = sorted_lst[i];
				sorted_lst[i] = sorted_lst[j];
				sorted_lst[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (sorted_lst);
}

t_indexed	*get_indexed_list(int *lst, int lst_size)
{
	t_indexed	*indexed_lst;
	int			*sorted_lst;
	int			i;
	int			j;

	sorted_lst = sort_list(lst, lst_size);
	indexed_lst = malloc(lst_size * sizeof(t_indexed));
	i = 0;
	while (i < lst_size)
	{
		j = 0;
		while (sorted_lst[j] != lst[i])
			j++;
		indexed_lst[i] = (t_indexed){lst[i], j};
		i++;
	}
	free(sorted_lst);
	return (indexed_lst);
}
