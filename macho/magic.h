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

/*
** magic number of macho-file
*/

/*
** (uint32_t key, t_magic_val val}
*/

typedef struct	s_magic_val
{
	const char	*const str;
	const char	*const architecture;
}				t_magic_val;

/*
** magic node
*/

/*
** data
*/

typedef struct			s_magic_data
{
	uint32_t		key;
	t_magic_val		val;
}						t_magic_data;

/*
** htab
*/

# define DATA_MAGIC_SIZE 6
# define HT_MAGIC_SIZE (2 * DATA_MAGIC_SIZE)

typedef struct	s_magic
{
	t_magic_data	_data[DATA_MAGIC_SIZE];
	t_magic_val		*val[HT_MAGIC_SIZE];
}				t_magic;

static t_magic	g_magic = {{{0xfeedface, {"MH_MAGIC", "32-bit"}},
							{0xcefaedfe, {"MH_CIGAM", "32-bit"}},
							{0xfeedfacf, {"MH_MAGIC_64", "64-bit"}},
							{0xcffaedfe, {"MH_CIGAM_64", "64-bit"}},
							{0xcafebabe, {"FAT_MAGIC", "fat"}},
							{0xbebafeca, {"FAT_CIGAM", "fat"}}},
							{0}};

/*
** htab
*/

t_magic_val	*magic_get(uint32_t key);

#endif
