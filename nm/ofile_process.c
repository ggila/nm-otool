/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofile_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 16:39:35 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/22 16:46:18 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ofile.h"
#include "nm.h"
#include "ft_printf.h"

void			ofile_process(char *file, t_nm_flag *flag)
{
	ft_printf("%s\n", file);
	(void)flag;
}
