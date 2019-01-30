/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:04:09 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 14:04:10 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_mode(t_file *tree, char *mode)
{
	mode[11] = 0;
	mode[0] = ft_entry_type(tree, 'e');
	mode[1] = (char)(tree->info->st_mode & S_IRUSR ? 'r' : '-');
	mode[2] = (char)(tree->info->st_mode & S_IWUSR ? 'w' : '-');
	if (tree->info->st_mode & S_ISUID)
		mode[3] = (char)(tree->info->st_mode & S_IXUSR ? 's' : 'S');
	else
		mode[3] = (char)(tree->info->st_mode & S_IXUSR ? 'x' : '-');
	mode[4] = (char)(tree->info->st_mode & S_IRGRP ? 'r' : '-');
	mode[5] = (char)(tree->info->st_mode & S_IWGRP ? 'w' : '-');
	if (tree->info->st_mode & S_ISGID)
		mode[6] = (char)(tree->info->st_mode & S_IXGRP ? 's' : 'S');
	else
		mode[6] = (char)(tree->info->st_mode & S_IXGRP ? 'x' : '-');
	mode[7] = (char)(tree->info->st_mode & S_IROTH ? 'r' : '-');
	mode[8] = (char)(tree->info->st_mode & S_IWOTH ? 'w' : '-');
	if (tree->info->st_mode & S_ISVTX)
		mode[9] = (char)(tree->info->st_mode & S_IXOTH ? 't' : 'T');
	else
		mode[9] = (char)(tree->info->st_mode & S_IXOTH ? 'x' : '-');
	mode[10] = ft_entry_type(tree, 'a');
	ft_printf("%-12s", mode);
}

void	ft_print_date(t_file *tree, char *optns)
{
	char			*date;
	__darwin_time_t	timesec;

	if (ft_strchr(optns, 'u'))
		timesec = tree->info->st_atimespec.tv_sec;
	else if (ft_strchr(optns, 'U'))
		timesec = tree->info->st_birthtimespec.tv_sec;
	else if (ft_strchr(optns, 'c'))
		timesec = tree->info->st_ctimespec.tv_sec;
	else
		timesec = tree->info->st_mtimespec.tv_sec;
	date = ctime(&timesec);
	if (ft_strchr(optns, 'T'))
		ft_printf("%.20s ", date + 4);
	else
		ft_printf("%.6s %.5s ", date + 4,
				time(0) - timesec > 15768000 ? date + 19 : date + 11);
}

void	ft_print_size(t_file *tree, t_length *lengths, const char *mode)
{
	if (mode[0] == 'c' || mode[0] == 'b')
		if (ft_strequ(tree->name, "autofs_nowait"))
			ft_printf("%2d, %#3.8x ",
					major(tree->info->st_rdev), minor(tree->info->st_rdev));
		else
			ft_printf("%2d, %3d ",
					major(tree->info->st_rdev), minor(tree->info->st_rdev));
	else
		ft_printf("%*lld ", lengths->sizelen, tree->info->st_size);
}

void	ft_printdir_l(t_file *tree, t_length lengths, char *optns)
{
	char	buf[255];
	char	mode[12];

	while (tree)
	{
		ft_print_inode(tree, lengths, optns);
		ft_print_mode(tree, mode);
		ft_printf("%*d ", ft_nbrlen_ls(lengths.nlinklen), tree->info->st_nlink);
		ft_printf("%-*s  ", lengths.usrlen,
				getpwuid(tree->info->st_uid)->pw_name);
		ft_printf("%-*s  ", lengths.grplen,
				getgrgid(tree->info->st_gid)->gr_name);
		ft_print_size(tree, &lengths, mode);
		ft_print_date(tree, optns);
		ft_printf("%s%s", tree->name, ft_strchr(optns, 'p') &&
			S_ISDIR(tree->info->st_mode) ? "/" : "");
		ft_printf("%s", S_ISLNK(tree->info->st_mode) ? " -> " : "\n");
		if (S_ISLNK(tree->info->st_mode))
		{
			buf[readlink(tree->fullpath, buf, 255)] = 0;
			ft_printf("%s\n", buf);
		}
		ft_print_xattr(tree, mode[10], optns);
		tree = tree->next;
	}
}

void	ft_printdir(t_file *tree, char *optns, blkcnt_t total)
{
	int			col;
	t_length	lengths;

	col = 1;
	ft_max_lenght(tree, &lengths);
	if (ft_strchr(optns, 'l') && ft_printf(tree ? "total %lld\n" : "", total))
		ft_printdir_l(tree, lengths, optns);
	else
	{
		ft_printf(tree && ft_strchr(optns, 's') ? "total %lld\n" : "", total);
		while (tree)
		{
			ft_print_inode(tree, lengths, optns);
			ft_printf("%-*s", lengths.namelen + 5, tree->name);
			ft_printf(col == COLUMNS || !tree->next ? "\n" : "");
			col = col++ == COLUMNS ? 1 : col;
			tree = tree->next;
		}
	}
}
