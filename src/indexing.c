/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:01:53 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/18 14:29:13 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "indexing.h"
#include "ft_string.h"

static void	swap(int *i, int *j)
{
	int	tmp;

	tmp = *i;
	*i = *j;
	*j = tmp;
}

static void	sort(int *numbers, int numbers_count)
{
	int	i;
	int	j;
	int	min_idx;

	i = 0;
	while (i < numbers_count - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < numbers_count)
		{
			if (numbers[j] < numbers[min_idx])
				min_idx = j;
			j++;
		}
		swap(&numbers[min_idx], &numbers[i]);
		i++;
	}
}

static int	*get_sorted_numbers(int *numbers, int numbers_count)
{
	int				*sorted_numbers;
	unsigned long	size;

	size = numbers_count * sizeof(int);
	sorted_numbers = malloc(size);
	ft_memcpy(sorted_numbers, numbers, size);
	sort(sorted_numbers, numbers_count);
	return (sorted_numbers);
}

static int	get_number_index(int number, int *sorted_numbers, int numbers_count)
{
	int		i;

	i = 0;
	while (i < numbers_count)
	{
		if (sorted_numbers[i] == number)
			return (i);
		i++;
	}
	return (-1);
}

t_list	*get_indexed_list(int *numbers, int numbers_count)
{
	int			i;
	t_list		*indexed_lst;
	int			*sorted_numbers;
	t_indexed	*indexed_num;

	indexed_lst = ft_lstnew();
	sorted_numbers = get_sorted_numbers(numbers, numbers_count);
	i = 0;
	while (i < numbers_count)
	{
		indexed_num = malloc(sizeof(t_indexed));
		indexed_num->number = numbers[i];
		indexed_num->index = get_number_index(numbers[i],
				sorted_numbers, numbers_count);
		ft_lstadd_back(indexed_lst, indexed_num);
		i++;
	}
	free(sorted_numbers);
	return (indexed_lst);
}
