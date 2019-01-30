/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_ls_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:50:07 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 14:17:36 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_del_tree(t_file *tree)
{
	t_file	*tmp;

	while (tree)
	{
		tmp = tree;
		tree = tree->next;
		free(tmp->info);
		free(tmp->parent);
		free(tmp->fullpath);
		free(tmp);
	}
}

int		ft_nbrlen_ls(long long num)
{
	int len;

	len = num == 0 ? 1 : 0;
	while (num)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

void	ft_max_lenght(t_file *tree, t_length *lenghts)
{
	ft_bzero(lenghts, sizeof(t_length));
	while (tree)
	{
		if (ft_strlen(tree->name) > (size_t)lenghts->namelen)
			lenghts->namelen = (int)ft_strlen(tree->name);
		if (ft_nbrlen_ls(tree->info->st_blocks) > lenghts->blkcntsize)
			lenghts->blkcntsize = ft_nbrlen_ls(tree->info->st_blocks);
		if (ft_nbrlen_ls(tree->info->st_ino) > lenghts->inodelen)
			lenghts->inodelen = ft_nbrlen_ls(tree->info->st_ino);
		if (tree->info->st_nlink > lenghts->nlinklen)
			lenghts->nlinklen = tree->info->st_nlink;
		if (S_ISBLK(tree->info->st_mode) || S_ISCHR(tree->info->st_mode))
			lenghts->sizelen = 7;
		else if (ft_nbrlen_ls(tree->info->st_size) > lenghts->sizelen)
			lenghts->sizelen = ft_nbrlen_ls(tree->info->st_size);
		if ((int)ft_strlen(getpwuid(tree->info->st_uid)->pw_name) > lenghts->usrlen)
			lenghts->usrlen =
					(int)ft_strlen(getpwuid(tree->info->st_uid)->pw_name);
		if ((int)ft_strlen(getgrgid(tree->info->st_gid)->gr_name) > lenghts->grplen)
			lenghts->grplen =
					(int)ft_strlen(getgrgid(tree->info->st_gid)->gr_name);
		tree = tree->next;
	}
}

void	ft_print_inode(t_file *tree, t_length lengths, char *optns)
{
	if (ft_strchr(optns, 'i'))
		ft_printf("%*lld ", lengths.inodelen, tree->info->st_ino);
	if (ft_strchr(optns, 's'))
		ft_printf("%*lld ", lengths.blkcntsize, tree->info->st_blocks);
}

char	ft_entry_type(t_file *tree, char type)
{
	acl_t	acl;

	if (type == 'e')
		if (S_ISDIR(tree->info->st_mode))
			return ('d');
		else if (S_ISBLK(tree->info->st_mode))
			return ('b');
		else if (S_ISCHR(tree->info->st_mode))
			return ('c');
		else if (S_ISFIFO(tree->info->st_mode))
			return ('p');
		else
			return (char)(S_ISLNK(tree->info->st_mode) ? 'l' : '-');
	else
	{
		if (listxattr(tree->fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
			return ('@');
		else if ((acl = acl_get_file(tree->fullpath, ACL_TYPE_EXTENDED)))
		{
			free(acl);
			return ('+');
		}
		else
			return (' ');
	}
}
