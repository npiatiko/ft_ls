/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:41:01 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 14:41:01 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_collect_flags(char *av, char *optns)
{
	static int	i = 0;

	while (*av)
		if (ft_strchr("ABCFGHLOPRSTUW@abcdefghiklmnopqrstuwx1", *av))
		{
			if (*av == 'f')
				optns[i++] = 'a';
			optns[i++] = *av;
			*av++ = 0;
		}
		else
		{
			ft_printf("illegal option -- %c\nusage: "
			"ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", *av);
			exit(1);
		}
}

void	ft_parse_optns(int ac, char **av, char *options)
{
	int	j;

	j = 1;
	while (ac - 1)
	{
		if (*av[j] == '-' && *(av[j] + 1))
		{
			*av[j]++ = 0;
			ft_collect_flags(av[j], options);
		}
		else
			break ;
		j++;
		ac--;
	}
}

t_file	*ft_sort_args(t_file *list, t_file **errs, char *optns)
{
	char	a[100];

	*errs = ft_sort_tree(*errs, a);
	return (ft_sort_tree(list, optns));
}

t_file	*ft_parse_args(int ac, char **av, t_file **errs, char *optns)
{
	t_file		*list;
	t_file		*tmp;
	struct stat	buf;

	list = 0;
	*errs = 0;
	while (ac-- - 1 && !**av)
		av++;
	while (ac--)
	{
		tmp = ft_new_node(*av[0] == '/' ? "" : ".", *av, optns);
		if (lstat(*av, &buf))
		{
			tmp->next = *errs;
			*errs = tmp;
		}
		else
		{
			tmp->next = list;
			list = tmp;
		}
		av++;
	}
	return (ft_sort_args(list, errs, optns));
}
