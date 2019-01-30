/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xattr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:55:59 by npiatiko          #+#    #+#             */
/*   Updated: 2019/01/30 12:56:00 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_xattr(t_file *tree, char mode, char *optns)
{
	char	buf[1024];
	ssize_t	start;
	ssize_t	len;

	start = 0;
	if (mode != '@' || !ft_strchr(optns, '@'))
		return ;
	len = listxattr(tree->fullpath, buf, 1024, XATTR_NOFOLLOW);
	while (start < len)
	{
		ft_printf("\t%s\t%d\n", (buf + start),
				getxattr(tree->fullpath, buf + start, 0, 0, 0, XATTR_NOFOLLOW));
		start += ft_strlen(buf + start) + 1;
	}
}
