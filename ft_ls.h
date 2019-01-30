/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:28:52 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/29 15:28:52 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define COLUMNS 3

# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

typedef struct	s_file
{
	char			*parent;
	char			*fullpath;
	char			name[1024];
	struct stat		*info;
	struct s_file	*next;
}				t_file;

typedef struct	s_length
{
	int				namelen;
	int				nlinklen;
	int				usrlen;
	int				grplen;
	int				sizelen;
	int				inodelen;
	int				blkcntsize;
}				t_length;

void			ft_printdir(t_file *tree, char *optns, blkcnt_t total);
void			ft_make_tree(char *pathname, char *optns);
void			ft_parse_optns(int ac, char **av, char *options);
t_file			*ft_sort_tree(t_file *tree, char *optns);
t_file			*ft_reverse_tree(t_file *tree);
t_file			*ft_parse_args(int ac, char **av, t_file **errs, char *optns);
t_file			*ft_new_node(char *pathname, char *name, char *optns);
void			ft_del_tree(t_file *tree);
int				ft_nbrlen_ls(long long num);
void			ft_max_lenght(t_file *tree, t_length *lenghts);
void			ft_print_inode(t_file *tree, t_length lengths, char *optns);
char			ft_entry_type(t_file *tree, char type);
//void			ft_print_size(t_file *tree, t_length *lengths, const char *mode);
void			ft_print_xattr(t_file *tree,char mode,char *optns);

#endif
