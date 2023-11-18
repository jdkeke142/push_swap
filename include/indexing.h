/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:59:58 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/16 14:56:17 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXING_H
# define INDEXING_H

# include "ft_list.h"

typedef struct s_indexed
{
	int	number;
	int	index;
}				t_indexed;

t_list	*get_indexed_list(int *numbers, int numbers_count);

#endif
