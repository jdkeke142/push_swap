/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/03/16 21:20:58 by kjimenez         ###   ########.fr       */
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

static void	print_content2(void *content)
{
	t_indexed	markup;

	markup = *((t_indexed *)content);
	printf("Number is : %d Index : %d\n", markup.number, markup.index);
}

static int	sa_needed(t_list *stack_a, t_list *stack_a_indexed, t_list *markup_head, t_markup_mode mode)
{
	t_list	*stack_a_markup;
	int		keep_swap;
	int		keep_without_swap;

	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);

	keep_without_swap = count_markup_keep(stack_a_markup);
	swap_lst(&stack_a);
	stack_a_markup = get_markup(stack_a_indexed, markup_head, mode);
	keep_swap = count_markup_keep(stack_a_markup);
	swap_lst(&stack_a);
	free(stack_a_markup);
	return (keep_swap > keep_without_swap);
}

int	main(void)
{
	(void) sa_needed;
	t_list	*stack_a;
	t_list	*stack_a_indexed;
	t_list	*stack_a_markup;
	t_list	*stack_b;
	t_list	*markup_lst;
	t_list	*stack_a_markup_head;

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
	stack_b = NULL;

	stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
	stack_a_markup_head = find_markup_head(stack_a_indexed, MARKUP_GREATER_THAN);
	stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);

	(void) print_content;
	while (count_markup_keep(stack_a_markup) != ft_lstsize(stack_a))
	{
		ft_lstiter(stack_a_indexed, print_content);
		if (((t_markup *)stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a, &stack_b);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			printf("\n\n");
			ft_lstiter(stack_a_indexed, print_content2);
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else
		{
			rotate_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
	}

	(void) stack_b;
	(void) markup_lst;
	/*while (count_markup_keep(stack_a_markup) < ft_lstsize(stack_a_markup))
	{
		printf("\n\n");
		ft_lstiter(stack_a, print_content);
		if (sa_needed(stack_a, stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN))
		{
			swap_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else if (((t_markup*) stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a, &stack_b);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
		else
		{
			rotate_lst(&stack_a);
			stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_GREATER_THAN);
		}
	}*/

	//stack_b = get_indexed_list(stack_a, ft_lstsize(stack_a));

	//markup_head = find_markup_head(stack_b, MARKUP_GREATER_THAN);
	//printf("Best markup head is %d\n", ((t_indexed *) markup_head->content)->number);
	//markup_lst = get_markup(stack_b, stack_b,
	//		MARKUP_BY_INDEX);
	//ft_lstiter(markup_lst, print_content);
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
