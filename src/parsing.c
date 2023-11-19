/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:21:08 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/19 12:57:58 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include <limits.h>

static char	**join_args(char **args)
{
	char	*str;
	char	*str_tmp;
	char	**joined_args;
	int		i;

	i = 1;
	str = ft_strdup("");
	while (args[i])
	{
		str_tmp = str;
		str = ft_strjoin(str, args[i]);
		free(str_tmp);
		str_tmp = str;
		str = ft_strjoin(str, " ");
		free(str_tmp);
		i++;
	}
	joined_args = ft_split(str, ' ');
	free(str);
	return (joined_args);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static int	is_str_num(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i == ft_strlen(str));
}

int	*parse_cancel(char **joined_args, int *numbers)
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
	long long	number;

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
		if (!is_str_num(joined_args[i]))
			return (parse_cancel(joined_args, numbers));
		number = ft_atoll(joined_args[i]);
		if (number < INT_MIN || number > INT_MAX)
			return (parse_cancel(joined_args, numbers));
		numbers[i] = (int) number;
		i++;
	}
	free_args(joined_args);
	return (numbers);
}
