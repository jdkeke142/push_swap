/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   markup.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:45:56 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/17 22:24:02 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARKUP_H
# define MARKUP_H

# include "indexing.h"

typedef struct s_markup
{
	int	number;
	int	keep;
}				t_markup;

typedef enum e_markup_mode
{
	MARKUP_BY_INDEX,
	MARKUP_GREATER_THAN
}			t_markup_mode;

t_list		*get_markup(t_list *indexed_lst, int markup_head,
				t_markup_mode markup_mode);
int			count_markup_keep(t_list *markup_lst);
int			find_markup_head(t_list *indexed_lst, t_markup_mode markup_mode);
t_markup	*markup_new(int number, int keep);

#endif
