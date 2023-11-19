/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 14:30:07 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/19 16:20:33 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

char	**join_args(char **args);
void	free_args(char **args);
int		is_str_num(char *str);
int		is_str_empty(char *str);
int		contains_number(int *numbers, int numbers_count, int number);

#endif
