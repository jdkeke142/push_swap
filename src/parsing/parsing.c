/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:21:08 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/19 16:26:14 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "ft_stdlib.h"
#include <limits.h>

static int	parse_conditions_num(int *numbers, int numbers_count, char *arg)
{
	long long int	number;

	if (!is_str_num(arg))
		return (0);
	number = ft_atoll(arg);
	if (number < INT_MIN || number > INT_MAX)
		return (0);
	if (contains_number(numbers, numbers_count, number))
		return (0);
	return (1);
}

static int	parse_conditions_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_str_empty(args[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	*parse_cancel(char **joined_args, int *numbers)
{
	free(numbers);
	free_args(joined_args);
	return (NULL);
}

int	*parse(char **args, int *numbers_count)
{
	int			i;
	char		**joined_args;
	int			*numbers;

	if (!parse_conditions_args(args))
		return (NULL);
	joined_args = join_args(args);
	*numbers_count = 0;
	while (joined_args[*numbers_count])
		(*numbers_count)++;
	numbers = malloc(*numbers_count * sizeof(int));
	if (!numbers)
		return (NULL);
	i = 0;
	while (joined_args[i])
	{
		if (!parse_conditions_num(numbers, i, joined_args[i]))
			return (parse_cancel(joined_args, numbers));
		numbers[i] = ft_atoi(joined_args[i]);
		i++;
	}
	free_args(joined_args);
	return (numbers);
}
