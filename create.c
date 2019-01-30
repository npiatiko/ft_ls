/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:46:48 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 13:46:50 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ft_new_node(char *pathname, char *name, char *optns)
{
	t_file		*new_node;
	struct stat	buf;

	new_node = (t_file *)malloc(sizeof(t_file));
	new_node->parent = ft_strjoin(pathname, "/");
	ft_memcpy(new_node->name, name, ft_strlen(name) + 1);
	new_node->fullpath = ft_strjoin(new_node->parent, new_node->name);
	if (ft_strchr(optns, 'L'))
		stat(new_node->fullpath, &buf);
	else
		lstat(new_node->fullpath, &buf);
	new_node->info = (struct stat *)malloc(sizeof(struct stat));
	new_node->info = ft_memcpy(new_node->info, &buf, sizeof(struct stat));
	return (new_node);
}

t_file	*ft_reverse_tree(t_file *tree)
{
	t_file	*reverse;
	t_file	*tmp;

	reverse = NULL;
	while (tree)
	{
		tmp = tree->next;
		tree->next = reverse;
		reverse = tree;
		tree = tmp;
	}
	return (reverse);
}

t_file	*ft_new_tree(char *pathname, blkcnt_t *total, char *optns)
{
	struct dirent	*entry;
	t_file			*tree;
	t_file			*tmp;
	char			*strerror;
	DIR				*dir;

	tree = 0;
	if (!(dir = opendir(pathname)))
	{
		strerror = ft_strjoin("ls: ", pathname);
		perror(strerror);
		free(strerror);
	}
	while (dir && (entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.' && !ft_strchr(optns, 'a'))
			continue;
		tmp = ft_new_node(pathname, entry->d_name, optns);
		*total += tmp->info->st_blocks;
		tmp->next = tree;
		tree = tmp;
	}
	if (dir)
		closedir(dir);
	return (tree);
}

void	ft_recursive(t_file *tree, char *optns)
{
	char	*path;

	while (tree)
	{
		if (S_ISDIR(tree->info->st_mode) &&
			ft_strcmp(tree->name, "..") && ft_strcmp(tree->name, "."))
		{
			path = ft_strjoin(tree->parent, tree->name);
			ft_printf("\n%s:\n", path);
			ft_make_tree(path, optns);
			free(path);
		}
		tree = tree->next;
	}
}

void	ft_make_tree(char *pathname, char *optns)
{
	t_file		*tree;
	blkcnt_t	total;

	total = 0;
	tree = ft_new_tree(pathname, &total, optns);
	tree = ft_strchr(optns, 'f') ?
			ft_reverse_tree(tree) : ft_sort_tree(tree, optns);
	ft_printdir(tree, optns, total);
	if (ft_strchr(optns, 'R'))
		ft_recursive(tree, optns);
	ft_del_tree(tree);
}
