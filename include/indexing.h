/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:59:58 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 16:52:26 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXING_H
# define INDEXING_H

typedef struct s_indexed
{
	int	number;
	int	index;
}				t_indexed;

t_indexed	*get_indexed_list(int *lst, int lst_size);

#endif
