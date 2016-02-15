/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:17:27 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/13 19:42:17 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHO_HEADER_H
# define MACHO_HEADER_H

//# include <ft_printf.h>
# include <stdint.h>

# ifndef OK
#  define OK 0
# endif
# ifndef KO
#  define KO 1
# endif

typedef const uint32_t	t_magic_key;

typedef struct			s_magic_val
{
	const char	*const str;
	const int	i;
}						t_magic_val;

typedef struct			s_magic_node
{
	t_magic_key	*magic;
	t_magic_val	*val;
}						t_magic_node;

typedef struct			s_magic_data
{
	t_magic_key		key;
	t_magic_val		val;
}						t_magic_data;

# define DATA_MAGIC_SIZE 6

static t_magic_data		g_magic[] = {{0xfeedface, {"MH_MAGIC", 0}},
									{0xcefaedfe, {"MH_CIGAM", 1}},
									{0xfeedfacf, {"MH_MAGIC_64", 2}},
									{0xcffaedfe, {"MH_CIGAM_64", 3}},
									{0xcafebabe, {"FAT_MAGIC", 4}},
									{0xbebafeca, {"FAT_CIGAM", 5}}};

#endif
