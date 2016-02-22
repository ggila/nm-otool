/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:57:44 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/22 16:39:18 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdint.h>

# include "ofile.h"

# ifndef OK
#  define OK 0
# endif
# ifndef KO
#  define KO -1
# endif

typedef struct	s_nm_opt
{
	uint32_t	flag;
	char		*s;
	char		*b;
}				t_nm_opt;

typedef struct	s_olist
{
	char			*file;
	struct s_olist	*next;
}				t_olist;

typedef struct s_nm_flag
{
	int	n;
}				t_nm_flag;

typedef struct	s_env
{
	t_nm_opt	opt;
	t_nm_flag	flag;
	t_olist		*ofile;
}				t_env;

t_nm_flag		process_flag(t_nm_opt *opt);
void			ofile_process(char *file, t_nm_flag *flag);

#endif
