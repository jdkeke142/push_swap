/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:43:03 by kjimenez          #+#    #+#             */
/*   Updated: 2023/11/27 17:51:52 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ft_stdio.h"
#include "indexing.h"
#include "ft_string.h"
#include "actions.h"

static int	is_sorted(t_list *stack_a)
{
	t_list_node	*stack_a_cpy;
	t_indexed	*indexed;
	t_indexed	*last_number;

	stack_a_cpy = stack_a->first->next;
	last_number = (t_indexed *) stack_a->first->content;
	while (stack_a_cpy)
	{
		indexed = (t_indexed *) stack_a_cpy->content;
		if (indexed->number < last_number->number)
			return (0);
		last_number = indexed;
		stack_a_cpy = stack_a_cpy->next;
	}
	return (1);
}

static int	checker_action(char *line, t_list *stack_a, t_list *stack_b)
{
	if (ft_strcmp("pa\n", line) == 0)
		push_lst(stack_b, stack_a);
	else if (ft_strcmp("pb\n", line) == 0)
		push_lst(stack_a, stack_b);
	else if (ft_strcmp("sa\n", line) == 0)
		swap_lst(stack_a);
	else if (ft_strcmp("sb\n", line) == 0)
		swap_lst(stack_b);
	else if (ft_strcmp("ss\n", line) == 0)
		swap_lsts(stack_a, stack_b);
	else if (ft_strcmp("ra\n", line) == 0)
		rotate_lst(stack_a);
	else if (ft_strcmp("rb\n", line) == 0)
		rotate_lst(stack_b);
	else if (ft_strcmp("rr\n", line) == 0)
		rotate_lsts(stack_a, stack_b);
	else if (ft_strcmp("rra\n", line) == 0)
		reverse_rotate_lst(stack_a);
	else if (ft_strcmp("rrb\n", line) == 0)
		reverse_rotate_lst(stack_b);
	else if (ft_strcmp("rrr\n", line) == 0)
		reverse_rotate_lsts(stack_a, stack_b);
	else
		return (0);
	return (1);
}

static void	checker_error(char *line, t_list *stack_a, t_list *stack_b)
{
	ft_putstr_fd("Error\n", 2);
	free(line);
	ft_lstdestroy(stack_a, &free);
	ft_lstdestroy(stack_b, &free);
}

static void	checker(int *numbers, int numbers_count)
{
	t_list	*stack_a;
	t_list	*stack_b;
	char	*line;

	line = get_next_line(0);
	stack_a = get_indexed_list(numbers, numbers_count);
	stack_b = ft_lstnew();
	while (line)
	{
		if (!checker_action(line, stack_a, stack_b))
		{
			checker_error(line, stack_a, stack_b);
			return ;
		}
		free(line);
		line = get_next_line(0);
	}
	if (stack_b->first == NULL && is_sorted(stack_a))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_lstdestroy(stack_a, &free);
	ft_lstdestroy(stack_b, &free);
}

int	main(int argc, char *args[])
{
	int			*numbers;
	int			numbers_count;

	if (argc < 2)
		return (0);
	numbers_count = 0;
	numbers = parse(args, &numbers_count);
	if (numbers == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	checker(numbers, numbers_count);
	free(numbers);
}
