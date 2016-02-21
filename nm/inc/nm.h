/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:57:44 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/21 19:23:24 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdint.h>

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

typedef struct	s_env
{
	t_nm_opt	opt;
}				t_env;
#endif
