/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/15 19:29:02 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "actions.h"
#include "markup.h"
#include "indexing.h"
#include <stdio.h>

/*
Plan : markup is a struct number and boolean keep
we can get a list of markup using any markup head and a list with INDEXED numbers
*/
static void	print_content(void *content)
{
	t_markup	markup;

	markup = *((t_markup *)content);
	printf("Number is : %d Keep ? : %d\n", markup.number, markup.keep);
}

int	main(void)
{
	/*int			test_array[7];
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

	list_size = 7;*/

	t_list	*stack_a;
	t_list	*stack_b;
	t_list	*markup_lst;

	int num1 = -2147483648;
	int num2 = 2100;
	int num3 = 220010;
	int num4 = -1;
	int	num5 = 7;
	int	num6 = 210815;
	int	num7 = 121;

	stack_a = NULL;
	ft_lstadd_back(&stack_a, ft_lstnew(&num1));
	ft_lstadd_back(&stack_a, ft_lstnew(&num2));
	ft_lstadd_back(&stack_a, ft_lstnew(&num3));
	ft_lstadd_back(&stack_a, ft_lstnew(&num4));
	ft_lstadd_back(&stack_a, ft_lstnew(&num5));
	ft_lstadd_back(&stack_a, ft_lstnew(&num6));
	ft_lstadd_back(&stack_a, ft_lstnew(&num7));

	stack_b = get_indexed_list(stack_a, ft_lstsize(stack_a));

	markup_lst = markup_greater_than(stack_b, stack_b->next->next->next);
	ft_lstiter(markup_lst, print_content);
	//ft_lstiter(stack_a, print_content2);
	//(void) stack_b;
	//ft_lstiter(stack_b, print_content);

	/*stack_b = ft_lstcpy(stack_a);
	ft_lstsort(&stack_b, ft_lstsize(stack_b));

	printf("Lst a content :\n");
	ft_lstiter(stack_a, print_content);

	printf("Lst b content :\n");
	ft_lstiter(stack_b, print_content);*/

	/*markup_index_head = get_markup_head(MARKUP_BY_INDEX, indexed_lst, list_size);
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

	swap_lst(&lst);*/
}
