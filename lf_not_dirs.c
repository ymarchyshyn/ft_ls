/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lf_not_dirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarchys <ymarchys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:51:00 by ymarchys          #+#    #+#             */
/*   Updated: 2018/03/01 17:51:00 by ymarchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char			**fill_files(char **files, int count_not_dirs, char *path)
{
	int			i;
	int			k;
	char		**not_dirs;

	if (!(not_dirs = (char**)malloc(sizeof(char*) * (count_not_dirs + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (files[i])
	{
		if (!(is_dir(files[i], path)))
			not_dirs[k++] = ft_strdup(files[i]);
		i++;
	}
	not_dirs[k] = NULL;
	return (not_dirs);
}

int					count_not_dirs(char **files, char *path)
{
	int			i;
	int			not_dirs;

	i = 0;
	not_dirs = 0;
	while (files[i])
	{
		if (!is_dir(files[i], path))
			not_dirs++;
		i++;
	}
	return (not_dirs);
}

void				lf_not_dirs(char **files, t_ls *ls, char *path)
{
	int			i;
	int			n;
	char		**not_dirs;
	int			w[4];

	i = 0;
	if (!(n = count_not_dirs(files, path)))
		return ;
	not_dirs = fill_files(files, n, path);
	w[0] = max_links(not_dirs, ls, path);
	if ((w[1] = max_len_user(not_dirs, ls, path)) == -1)
		return ;
	if ((w[2] = max_len_group(not_dirs, ls, path)) == -1)
		return ;
	w[2] = max_len_group(not_dirs, ls, path);
	w[3] = max_size(not_dirs, ls, path);
	while (not_dirs[i])
	{
		if (print_dot(not_dirs[i], ls))
			print_lf(not_dirs[i], w, path, ls);
		i++;
	}
	free_words(not_dirs);
	ls->new_line = 1;
}
