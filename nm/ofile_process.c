/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofile_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:35 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/23 08:16:29 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ofile.h"
#include "nm.h"
#include "ft_printf.h"

static void	check_member(char *name, t_ofile *ofile)
{
	int		len;
	char	*p;

	len = ft_strlen(name);
	if (len >= 4 && name[len - 1] == ')')
	{
		p = ft_strrchr(name, '(');
		if (p != NULL && p != name)
		{
			ofile->member_name = p + 1;
			*p = '\0';
			name[len - 1] = '\0';
		}
	}
}

void			ofile_process(t_ofile *ofile, t_nm_flag *flag)
{
	void	*ptr;

	ft_printf("%s\n", ofile->file_name);
	check_member(ofile->file_name, ofile);
	if ((ptr = map_file(ofile->file_name)) == NULL)
		return;
	ofile_fill(ofile, ptr, flag);
	(void)flag;
}
