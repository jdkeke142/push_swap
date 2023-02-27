/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:16:42 by kjimenez          #+#    #+#             */
/*   Updated: 2023/02/27 17:40:23 by kjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>

void	print_content(void *content)
{
	int	number;

	number = *((int *)content);
	printf("Number is : %d\n", number);
}

void	swap_lst(t_list **lst)
{
	int		i;
	t_list	*temp_lst;
	void	*first_content;

	if (!(*lst) || ft_lstsize(*lst) < 2)
		return ;
	temp_lst = *lst;
	i = 0;
	while (i < 1)
	{
		temp_lst = temp_lst->next;
		i++;
	}
	first_content = temp_lst->content;
	temp_lst->content = (*lst)->content;
	(*lst)-> content = first_content;
}

void	push_lst(t_list *lst_src, t_list **lst_dest)
{
	ft_lstadd_front(lst_dest, ft_lstnew(lst_src->content));
}

void	rotate_lst(t_list **lst)
{
	t_list	*first_elem;

	first_elem = *lst;
	*lst = (*lst)->next;
	ft_lstlast(*lst)->next = first_elem;
	first_elem->next = NULL;
}

void	reverse_rotate_lst(t_list **lst)
{
	int		i;
	int		lst_size;
	t_list	*temp_lst;
	t_list	*last_elem;

	temp_lst = *lst;
	lst_size = ft_lstsize(*lst);
	i = 0;
	while (i < (lst_size - 1))
	{
		temp_lst = temp_lst->next;
		i++;
	}
	temp_lst->next = NULL;
	last_elem = ft_lstlast(*lst);
	last_elem->next = *lst;
	*lst = last_elem;
}

int	main(void)
{
	t_list	*lst_a;
	int		num_1_a;
	int		num_2_a;
	int		num_3_a;
	int		num_4_a;
	int		num_5_a;
	t_list	*lst_b;
	int		num_1_b;
	int		num_2_b;

	num_1_a = 5;
	num_2_a = 10;
	num_3_a = 15;
	num_4_a = 20;
	num_5_a = 25;
	lst_a = ft_lstnew(&num_1_a);
	ft_lstadd_back(&lst_a, ft_lstnew(&num_2_a));
	ft_lstadd_back(&lst_a, ft_lstnew(&num_3_a));
	ft_lstadd_back(&lst_a, ft_lstnew(&num_4_a));
	ft_lstadd_back(&lst_a, ft_lstnew(&num_5_a));
	printf("Lst 1 content :\n");
	ft_lstiter(lst_a, print_content);
	num_1_b = 15;
	num_2_b = 20;
	lst_b = ft_lstnew(&num_1_b);
	ft_lstadd_back(&lst_b, ft_lstnew(&num_2_b));
	printf("Lst 2 content :\n");
	ft_lstiter(lst_b, print_content);


	reverse_rotate_lst(&lst_a);
	printf("Lst 1 content :\n");
	ft_lstiter(lst_a, print_content);
	printf("Lst 2 content :\n");
	ft_lstiter(lst_b, print_content);
	//swap_lst(&lst);
}
