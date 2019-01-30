/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:36:26 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 15:36:27 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_treelen(t_file *list, t_file *errs)
{
	int	len;

	len = 0;
	while (errs || list)
		if (errs)
		{
			len++;
			errs = errs->next;
		}
		else
		{
			len++;
			list = list->next;
		}
	return (len);
}

void	ft_print_args(t_file *errs, t_file *list, int ac, char *optns)
{
	t_file	*tree;

	while (errs || list)
	{
		if (errs)
		{
			ft_make_tree(errs->name, optns);
			errs = errs->next;
		}
		else if (S_ISDIR(list->info->st_mode))
		{
			ft_printf(ac > 1 ? "\n%s:\n" : "", list->name);
			ft_make_tree(list->name, optns);
			list = list->next;
		}
		else
		{
			tree = ft_new_node(list->name[0] == '/' ?
					"" : ".", list->name, optns);
			tree->next = 0;
			ft_printdir(tree, optns, tree->info->st_blocks);
			ft_del_tree(tree);
			list = list->next;
		}
	}
}

int		main(int ac, char **av)
{
	char	options[100];
	t_file	*list;
	t_file	*errs;

	ft_bzero(options, 100);
	errs = 0;
	ft_parse_optns(ac, av, options);
	list = ft_parse_args(ac, ++av, &errs, options);
	ac = ft_treelen(list, errs);
	if (errs || list)
		ft_print_args(errs, list, ac, options);
	else
		ft_make_tree(".", options);
	ft_del_tree(errs);
	ft_del_tree(list);
//	system("leaks a.out");
	return (0);
}
