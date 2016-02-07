/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:17:27 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/07 18:27:37 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include "hash_tables.h"
#include <stdio.h>

#define HT_GET(magic) (char*)ht_get(&ht, &magic)

static const int magic_key[] = {0xfeedface, 0xcefaedfe,
							0xfeedfacf, 0xcffaedfe,
							0xcafebabe, 0xbebafeca};

static const t_kv magic_kv[] = {{&magic_key[0], 4, "MH_MAGIC", 9},
							{&magic_key[1], 4, "MH_CIGAM", 9},
							{&magic_key[2], 4, "MH_MAGIC_64", 12},
							{&magic_key[3], 4, "MH_CIGAM_64", 12},
							{&magic_key[4], 4, "FAT_MAGIC", 12},
							{&magic_key[5], 4, "FAT_CIGAM", 12},
							KV_NULL};

void key_print(int *a) {printf("%i", *a);}
void value_print(char *a) {printf("%s", a);}

int main(int ac, char **av)
{
	int				fd;
	void			*ptr;
	struct stat		buf;
	t_hash_tbl		ht;

	int i = 0;
	int magic;

	ht_init(&ht, 7, &int_cmp, &int_hash);
	ht_fill(&ht, magic_kv);
	while (++i < ac)
	{
		fd = open(av[i], O_RDONLY);
		fstat(fd, &buf);
		ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0); // != MAP_FAILED
		magic = *(int*)ptr;
		if (ht_isset(&ht, &magic))
			printf("%s: %x -> %s\n", av[i], magic, HT_GET(magic));
	}
}
