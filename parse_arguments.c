/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarchys <ymarchys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 17:53:00 by ymarchys          #+#    #+#             */
/*   Updated: 2018/02/18 17:53:00 by ymarchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char			**fill_files(char **argv, int n, t_ls *ls)
{
	char	**files;
	int		i;

	i = 0;
	files = (char**)malloc(sizeof(char*) * (n + 1));
	while (i < n)
		files[i++] = *argv++;
	files[i] = NULL;
	if (!ls->not_sort)
		sort_ascii_bubble(files, n);
	return (files);
}

static void			remove_file(char **files, int i)
{
	while (files[i])
	{
		files[i] = files[i + 1];
		i++;
	}
}

void				parse_arguments(char **argv, int n, t_ls *ls)
{
	t_stat				buf;
	char				**files;
	int					i;

	i = 0;
	files = fill_files(argv, n, ls);
	ls->argc = n;
	while (files[i])
	{
		if (lstat(files[i], &buf) == -1)
		{
			write(2, "ls: ", 4);
			perror(files[i]);
			remove_file(files, i);
			ls->argc--;
			ls->error = 1;
		}
		else
			i++;
	}
	if (!ls->not_sort)
		ls_sort(files, ls->argc, ls, NULL);
	ft_ls(files, ls);
	free(files);
}
