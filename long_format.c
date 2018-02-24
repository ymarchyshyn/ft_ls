/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarchys <ymarchys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:30:00 by ymarchys          #+#    #+#             */
/*   Updated: 2018/02/20 13:30:00 by ymarchys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				long_format(char **files, t_ls *ls, char *path)
{
	int			i;
	int 		w[4];

	i = 0;
	w[0] = max_links(files);
	if ((w[1] = max_len_user(files)) == -1)
		return ;
	if ((w[2] = max_len_group(files)) == -1)
		return ;
	w[2] = max_len_group(files);
	w[3] = max_size(files);
	ft_printf("total %lld\n", ls_total(files, ls, path));
	while (files[i])
	{
		if (print_dot(files[i], ls))
			print_long_format(files[i], w, path);
		i++;
	}
}