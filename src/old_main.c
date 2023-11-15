int	main(int argc, char *args[])
{
	(void) argc;
	//(void) sa_needed;
	t_list	*stack_a;
	t_list	*stack_a_indexed;
	t_list	*stack_a_markup;
	t_list	*stack_a_markup_head;
	t_list	*stack_b_indexed;
	t_list	*stack_b_markup;
	int count = 0;

	stack_a = NULL;

	int i = 1;
	int *args_nbr = malloc(argc * sizeof(int));
	while (args[i]) {
		args_nbr[i] = ft_atoi(args[i]);
		printf("Nbr is %d\n", args_nbr[i]);

		ft_lstadd_back(&stack_a, ft_lstnew(&args_nbr[i]));
		i++;
	}

	stack_b_indexed = NULL;
	stack_b_markup = NULL;

	stack_a_indexed = get_indexed_list(stack_a, ft_lstsize(stack_a));
	stack_a_markup_head = find_markup_head(stack_a_indexed, MARKUP_BY_INDEX);
	stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX);

	printf("Using as markup head %d\n", ((t_indexed *) stack_a_markup_head->content)->number);

	while (count_markup_keep(stack_a_markup) != ft_lstsize(stack_a_markup))
	{
		if (sa_needed(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX))
		{
			swap_lst(&stack_a_markup);
			swap_lst(&stack_a_indexed);
			printf("sa\n");
			count++;
			stack_a_markup = get_markup(stack_a_indexed, stack_a_markup_head, MARKUP_BY_INDEX);
		}
		else if (((t_markup *)stack_a_markup->content)->keep == 0)
		{
			push_lst(&stack_a_markup, &stack_b_markup);
			push_lst(&stack_a_indexed, &stack_b_indexed);
			printf("pb\n");
			count++;
		}
		else
		{
			rotate_lst(&stack_a_markup);
			rotate_lst(&stack_a_indexed);
			printf("ra\n");
			count++;
		}
		//printf("\n");
		}


	/*printf("Stack A BEFORE :\n");
	ft_lstiter(stack_a_markup, print_content2);
	printf("\n");
	printf("Stack B BEFORE :\n");
	ft_lstiter(stack_b_markup, print_content2);*/


	//Find the best moveset
	//Apply it (Preparing Stack A and Stack B)
	//Push value from stack b to stack a
	//Repeat until stack B is empty
	//No move should be printed yet but every move should have been saved,
	//At the end, the moveset from the two markup modes should be compared and the best one (the one with the lowest count of moves) should print all its move
	while (ft_lstsize(stack_b_markup) > 0)
	{
		t_list	*stack_b_markup_cpy;
		t_list	*best_moveset = NULL;
		int		stack_b_total_size;
		int		stack_b_curr_size;

		stack_b_total_size = ft_lstsize(stack_b_markup);
		stack_b_curr_size = 0;
		stack_b_markup_cpy = stack_b_markup;

		t_list	*stack_a_markup_cpy = stack_a_markup;
		t_markup *stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;
		int stack_a_smallest_value = stack_a_markup_cpy_casted->number;
		int stack_a_biggest_value = stack_a_markup_cpy_casted->number;
		while (stack_a_markup_cpy)
		{
			stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;

			if (stack_a_markup_cpy_casted->number < stack_a_smallest_value)
				stack_a_smallest_value = stack_a_markup_cpy_casted->number;

			if (stack_a_markup_cpy_casted->number > stack_a_biggest_value)
				stack_a_biggest_value = stack_a_markup_cpy_casted->number;

			stack_a_markup_cpy = stack_a_markup_cpy->next;
		}

		while (stack_b_markup_cpy)
		{
			t_list		*moveset = NULL;
			t_markup	*markup2 = (t_markup *) stack_b_markup_cpy->content;

			//printf("Number we are checking is : %d\n", markup2->number);

			int	move_count;
			if (stack_b_curr_size + 1 <= stack_b_total_size / 2)
			{
				move_count = stack_b_curr_size;
				while (move_count > 0)
				{
					ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_B, DIR_REGULAR)));
					move_count--;
				}
			}
			else if (stack_b_curr_size > 0)
			{
				//printf("Stack b curr size : %d Total size : %d\n", stack_b_curr_size, stack_b_total_size);
				move_count = stack_b_total_size - stack_b_curr_size;
				while (move_count > 0)
				{
					ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_B, DIR_REVERSE)));
					move_count--;
				}
			}
			//printf("Size for moveset 0 : %d\n", ft_lstsize(moveset));

			//Find the smallest value in stack A
			//Find the biggest value in stack A

			//Is the markup2 value bigger than the biggest value in stack A or smaller than the smallest value in stack B ?
			//If yes rotate stack A until the first value is the smallest of the stack
			//If not rotate stack A until the markup2 is smaller than the first value of stack A and bigger than the last value of stack A

			if (markup2->number > stack_a_biggest_value
				|| markup2->number < stack_a_smallest_value)
			{
				//printf("Bigger or smaller than everything\n");
				stack_a_markup_cpy = lstcpy(stack_a_markup);
				int count = 0;
				while (1)
				{
					stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;
					if (stack_a_markup_cpy_casted->number == stack_a_smallest_value)
						break ;

					rotate_lst(&stack_a_markup_cpy);
					count++;
				}
				free(stack_a_markup_cpy);
				stack_a_markup_cpy = lstcpy(stack_a_markup);
				int reverse_count = 0;
				while (1)
				{
					stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;
					if (stack_a_markup_cpy_casted->number == stack_a_smallest_value)
						break ;

					reverse_rotate_lst(&stack_a_markup_cpy);
					reverse_count++;
				}
				free(stack_a_markup_cpy);
				if (count <= reverse_count)
				{
					while (count > 0)
					{
						ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_A, DIR_REGULAR)));
						//printf("Rotate\n");
						count--;
					}
				}
				else
				{
					while (reverse_count > 0)
					{
						ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_A, DIR_REVERSE)));
						//printf("Reverse rotate\n");
						reverse_count--;
					}
				}
				//printf("It was %d moves for rotate and %d moves for reverse rotate\n", count, reverse_count);
			}
			else
			{
				stack_a_markup_cpy = lstcpy(stack_a_markup);

				int count = 0;
				while (1)
				{
					stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;
					t_markup	*stack_a_markup_cpy_last_casted = (t_markup *) ft_lstlast(stack_a_markup_cpy)->content;
					if (markup2->number < stack_a_markup_cpy_casted->number && markup2->number > stack_a_markup_cpy_last_casted->number)
						break ;

					rotate_lst(&stack_a_markup_cpy);
					count++;
				}
				free(stack_a_markup_cpy);
				stack_a_markup_cpy = lstcpy(stack_a_markup);
				int reverse_count = 0;
				while (1)
				{
					stack_a_markup_cpy_casted = (t_markup *) stack_a_markup_cpy->content;
					t_markup	*stack_a_markup_cpy_last_casted = (t_markup *) ft_lstlast(stack_a_markup_cpy)->content;
					if (markup2->number < stack_a_markup_cpy_casted->number && markup2->number > stack_a_markup_cpy_last_casted->number)
						break ;

					reverse_rotate_lst(&stack_a_markup_cpy);
					reverse_count++;
				}
				if (count <= reverse_count)
				{
					while (count > 0)
					{
						ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_A, DIR_REGULAR)));
						count--;
					}
				}
				else
				{
					while (reverse_count > 0)
					{
						ft_lstadd_back(&moveset, ft_lstnew(move_new(STACK_A, DIR_REVERSE)));
						reverse_count--;
					}
				}

				//il trie tout il fait juste pas le rotate final et groupe pas ra suivi de rb par rr et inversement
				//et tout est dans le main
			}

			//printf("Size for moveset %d: %d\n", markup2->number, ft_lstsize(moveset));
			//printf("Size for best moveset : %d\n", ft_lstsize(best_moveset));
			///t_list	*moveset_cpy = moveset;
			//while (moveset_cpy)
			//{
				//t_move	*move = (t_move *) moveset_cpy->content;

				//t_direction direction = move->direction;
				//t_stack stack = move->stack;

				//printf("Direction is : %d and stack is %d\n", direction, stack);
			////	moveset_cpy = moveset_cpy->next;
			///}

			if (best_moveset == NULL || ft_lstsize(moveset) < ft_lstsize(best_moveset))
			{
				//if (moveset == NULL)
				//	printf("Moveset is null\n");
				free(best_moveset);
				best_moveset = moveset;
			}

			//printf("In stack A smallest value is : %d and biggest value is : %d\n", stack_a_smallest_value, stack_a_biggest_value);

			stack_b_markup_cpy = stack_b_markup_cpy->next;
			stack_b_curr_size++;
		}

		t_list	*best_moveset_cpy = best_moveset;
		//if (best_moveset == NULL)
		//	printf("It's null...\n");
		while (best_moveset_cpy)
		{
			t_move	*move = (t_move *) best_moveset_cpy->content;

			t_direction direction = move->direction;
			t_stack stack = move->stack;

			if (direction == DIR_REGULAR) {
				if (stack == STACK_A)
				{
					printf("ra\n");
					rotate_lst(&stack_a_markup);
					count++;
				}
				else
				{
					printf("rb\n");
					rotate_lst(&stack_b_markup);
					count++;
				}
			} else {
				if (stack == STACK_A)
				{
					printf("rra\n");
					reverse_rotate_lst(&stack_a_markup);
					count++;
				}
				else
				{
					printf("rrb\n");
					reverse_rotate_lst(&stack_b_markup);
					count++;
				}
			}

			best_moveset_cpy = best_moveset_cpy->next;
		}
		push_lst(&stack_b_markup, &stack_a_markup);
		printf("pa\n");
		count++;
	}



	printf("Stack A AFTER :\n");
	ft_lstiter(stack_a_markup, print_content2);
	printf("\n");
	printf("Stack B AFTER :\n");
	ft_lstiter(stack_b_markup, print_content2);
	printf("Number of actions: %d", count);
}
