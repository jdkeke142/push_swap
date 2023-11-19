/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:16:34 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/19 16:20:26 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

char	**join_args(char **args)
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

void	free_args(char **args)
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

int	is_str_num(char *str)
{
	size_t	i;
	int		sign;

	sign = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		sign = 1;
	while (str[sign + i] && ft_isdigit(str[sign + i]))
		i++;
	if (i < 1)
		return (0);
	return (i + sign == ft_strlen(str));
}

int	is_str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	contains_number(int *numbers, int numbers_count, int number)
{
	int	i;

	i = 0;
	while (i < numbers_count)
	{
		if (numbers[i] == number)
			return (1);
		i++;
	}
	return (0);
}
