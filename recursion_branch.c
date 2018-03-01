/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_branch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarchys <ymarchys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:52:00 by ymarchys          #+#    #+#             */
/*   Updated: 2018/03/01 14:52:00 by ymarchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_dir_continue(t_ls *ls, char **files, char *path, int n)
{
	int i;

	i = 0;
	sort_ascii_bubble(files, n);
	if (ls->recursively)
		parse_files(files, n, ls, path);
	else
	{
		ls_sort(files, n, ls, path);
		i = 0;
		while (i < n)
			ft_printf("%s\n", files[i++]);
	}
}

static void		ls_dir_recursion(char *dirname, t_ls *ls, char *path)
{
	char			**files;
	char			*tmp1;
	char			*tmp2;
	int				n;

	files = NULL;
	tmp1 = ft_strjoin(path, dirname);
	tmp2 = ft_strjoin(tmp1, "/");
	ft_strdel(&tmp1);
	if ((n = ls_count_files(dirname, tmp2)))
	{
		files = (char **)malloc(sizeof(char *) * (n + 1));
		files = ls_read_files(files, tmp2);
		ls_dir_continue(ls, files, tmp2, n);
		free_words(files);
	}
	ft_strdel(&tmp2);
}

//static int		recursion_end(char **files, char *path, t_ls *ls)
//{
//	int i;
//	int dirs;
//
//	i = 0;
//	dirs = 0;
//	if (ls->include_dot)
//	{
//		while (files[i])
//			if (is_dir(files[i++], path) && (dirs += 1) > 2)
//				return (0);
//	}
//	else
//	{
//		while (files[i])
//		{
//			if (skip_dots(files[i]) && is_dir(files[i], path))
//				return (0);
//			i++;
//		}
//	}
//	return (1);
//}

void			recursion_branch(char **files, t_ls *ls, char *path)
{
	int		i;
	char 	*tmp;

	i = 0;
	tmp = NULL;
	if (ls->long_format)
		lf(files, ls, path);
	else
		print_files(files, ls, path);
//	while (files[i])
//		ft_printf("FILE >> %s\n", files[i++]);
//	ft_printf("%s\n", path);
//	i = 0;
//	if (recursion_end(files, path, ls))
//	{
////		free_words(files);
//		ft_strdel(&path);
//		return ;
//	}
	while (files[i])
	{
		tmp = ft_strjoin(path, files[i]);
		if (is_dir(tmp, NULL))
		{
			if (print_dot(files[i], ls) && skip_dots(files[i]))
			{
				ft_printf("\n%s%s:\n", path, files[i]);
				ls_dir_recursion(files[i], ls, path);
			}
		}
		if (tmp != NULL)
			ft_strdel(&tmp);
		i++;
	}
}