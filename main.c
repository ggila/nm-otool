/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:17:27 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/08 10:19:48 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "hash_tables.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define HT_GET_STR(magic) ((t_val*)ht_get(&ht, &magic))->str
#define HT_GET_IND(magic) ((t_val*)ht_get(&ht, &magic))->i

typedef struct	s_val
{
	char	*str;
	int		i;
}				t_val;

static int magic_key[] = {0xfeedface, 0xcefaedfe,
							0xfeedfacf, 0xcffaedfe,
							0xcafebabe, 0xbebafeca};

static t_val magic_val[] = {{"MH_MAGIC", 0},
							{"MH_CIGAM", 1},
							{"MH_MAGIC_64", 2},
							{"MH_CIGAM_64", 3},
							{"FAT_MAGIC", 4},
							{"FAT_CIGAM", 5}};

static const t_kv magic_kv[] = {{&magic_key[0], 4, &magic_val[0], sizeof(magic_val[0])},
							{&magic_key[1], 4, &magic_val[1], sizeof(magic_val[1])},
							{&magic_key[2], 4, &magic_val[2], sizeof(magic_val[2])},
							{&magic_key[3], 4, &magic_val[3], sizeof(magic_val[3])},
							{&magic_key[4], 4, &magic_val[4], sizeof(magic_val[4])},
							{&magic_key[5], 4, &magic_val[5], sizeof(magic_val[5])},
							KV_NULL};

void	print_stat(t_hash_tbl *ht, int mach_stat[], int i)
{
	t_kv	*kv;
	char	*mag_str;
	int		mag_ind;

	printf("stat:\n");
	while ((kv = ht_getnextkv(ht)) != NULL)
	{
		mag_str = ((t_val*)(kv->value))->str;
		mag_ind = ((t_val*)(kv->value))->i;
		printf("\t%s:\t\t%d\t%d%%\n", mag_str, mag_ind, (int)(100 * ((double)mag_ind) / i));
	}
	printf("total: %d\n", i);
}

int		main(int ac, char **av)
{
	int				fd;
	void			*ptr;
	struct stat		buf;
	t_hash_tbl		ht;

	int i = 0;
	int magic;
	int macho_stat[6];

	ht_init(&ht, 7, &int_cmp, &int_hash);
	ht_fill(&ht, magic_kv);
	ft_bzero(macho_stat, 6 * sizeof(int));
	while (++i < ac)
	{
//		printf("%s: ", av[i]);
		fflush(stdout);
		if (((fd = open(av[i], O_RDONLY)) == -1)  ||
				(fstat(fd, &buf) == -1) ||
				((ptr = mmap(0, buf.st_size, PROT_READ,
							 MAP_PRIVATE, fd, 0)) == MAP_FAILED))
			perror("open");
		else
		{
			magic = *(int*)ptr;
			if (ht_isset(&ht, &magic))
			{
//				printf("%x -> %s\n", magic, HT_GET_STR(magic));
				macho_stat[HT_GET_IND(magic)] += 1;
			}
//			else
//				printf("not a mach-o file\n");
		}
		if (fd != -1)
			close(fd);
	}
	print_stat(&ht, macho_stat, --i);
	return (0);
}
