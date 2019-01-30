/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:28:17 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 15:28:18 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_byname(t_file *tmp, t_file *next, char *optns)
{
	optns[100] = 0;
	if (ft_strcmp(tmp->name, next->name) > 0)
		return (1);
	return (0);
}

int		ft_bysize(t_file *tmp, t_file *next, char *optns)
{
	if (tmp->info->st_size < next->info->st_size)
		return (1);
	else if (tmp->info->st_size == next->info->st_size)
		return (ft_byname(tmp, next, optns));
	return (0);
}

int		ft_bytime(t_file *tmp, t_file *next, char *optns)
{
	__darwin_time_t tmpt;
	__darwin_time_t nextt;

	if ((tmpt = tmp->info->st_atimespec.tv_sec) >= 0 && ft_strchr(optns, 'u'))
		nextt = next->info->st_atimespec.tv_sec;
	else if (ft_strchr(optns, 'U'))
	{
		tmpt = tmp->info->st_birthtimespec.tv_sec;
		nextt = next->info->st_birthtimespec.tv_sec;
	}
	else if (ft_strchr(optns, 'c'))
	{
		tmpt = tmp->info->st_ctimespec.tv_sec;
		nextt = next->info->st_ctimespec.tv_sec;
	}
	else
	{
		tmpt = tmp->info->st_mtimespec.tv_sec;
		nextt = next->info->st_mtimespec.tv_sec;
	}
	if (tmpt < nextt)
		return (1);
	return (tmpt == nextt ? ft_byname(tmp, next, optns) : 0);
}

t_file	*ft_sorter(t_file *tree,
		int (*f)(t_file *, t_file *, char *), char *optns)
{
	t_file	*tmp;
	t_file	*next;
	t_file	out;
	int		i;

	i = 1;
	out.next = tree;
	while (i && tree)
	{
		i = 0;
		tree = &out;
		while (tree->next->next)
		{
			tmp = tree->next;
			if ((next = tmp->next) && f(tmp, next, optns))
			{
				tree->next = next;
				tmp->next = next->next;
				next->next = tmp;
				i = 1;
			}
			tree = tree->next;
		}
	}
	return (out.next);
}

t_file	*ft_sort_tree(t_file *tree, char *optns)
{
	int (*f)(t_file *, t_file *, char *);

	if (ft_strchr(optns, 'S'))
		f = ft_bysize;
	else if (ft_strchr(optns, 't'))
		f = ft_bytime;
	else
		f = ft_byname;
	return (ft_strchr(optns, 'r') ?
	ft_reverse_tree(ft_sorter(tree, f, optns)) : ft_sorter(tree, f, optns));
}
