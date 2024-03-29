/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:49:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 16:34:57 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "markup.h"

t_markup	*markup_new(int number, int keep)
{
	t_markup	*markup;

	markup = malloc(sizeof(t_markup));
	if (!markup)
		return (NULL);
	markup->number = number;
	markup->keep = keep;
	return (markup);
}
