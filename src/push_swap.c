/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/06 18:20:48 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "actions.h"
#include "markup.h"
#include "indexing.h"
#include <stdio.h>

void	print_content(void *content)
{
	int	number;

	number = *((int *)content);
	printf("Number is : %d\n", number);
}

int	main(void)
{
	int			test_array[7];
	int			list_size;
	t_markup	markup_index_head;
	t_markup	markup_greater_head;
	t_indexed	*indexed_lst;

	test_array[0] = -2147483648;
	test_array[1] = 2100;
	test_array[2] = 220010;
	test_array[3] = -1;
	test_array[4] = 7;
	test_array[5] = 210815;
	test_array[6] = 121;

	list_size = 7;

	indexed_lst = get_indexed_list(test_array, list_size);

	markup_index_head = get_markup_head(MARKUP_BY_INDEX, indexed_lst, list_size);
	printf("Markup head by index is %d and kept %d\n", markup_index_head.markup, markup_index_head.kept_amount);

	markup_greater_head = get_markup_head(MARKUP_GREATER_THAN, indexed_lst, list_size);
	printf("Markup head greater than is %d and kept %d\n", markup_greater_head.markup, markup_greater_head.kept_amount);
	t_list	*stack_a;
	t_list	*stack_b;
	int num_1;

	num_1 = 5;
	stack_b = NULL;
	stack_a = ft_lstnew(&num_1);
	printf("Lst 1 content :\n");
	ft_lstiter(stack_a, print_content);
	printf("Lst 2 content :\n");
	ft_lstiter(stack_b, print_content);

	push_lst(&stack_a, &stack_b);
	printf("Lst 1 content :\n");
	ft_lstiter(stack_a, print_content);
	printf("Lst 2 content :\n");
	ft_lstiter(stack_b, print_content);

	//swap_lst(&lst);
}
