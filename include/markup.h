/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:45:56 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:01:02 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARKUP_H
# define MARKUP_H

# include "indexing.h"

typedef struct s_markup
{
	int	markup;
	int	kept_amount;
}				t_markup;

typedef enum e_markup_mode
{
	MARKUP_BY_INDEX,
	MARKUP_GREATER_THAN
}			t_markup_mode;

t_markup	markup_greater_than(t_indexed *lst, int lst_size, int markup);
t_markup	markup_by_index(t_indexed *lst, int lst_size, int markup);
t_markup	get_markup_head(t_markup_mode mode, t_indexed *lst, int lst_size);

#endif
