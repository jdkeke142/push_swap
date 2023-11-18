/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:44:12 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 22:44:51 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "actions.h"

void	rotate_lst_multiple(t_list *lst, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		rotate_lst(lst);
		i++;
	}
}

void	reverse_rotate_lst_multiple(t_list *lst, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		reverse_rotate_lst(lst);
		i++;
	}
}
