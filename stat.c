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

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>

#include "hash_tables.h"
#include "ft_printf.h"
#include "macho.h"

#define HT_GET_STR(ht, magic) ((t_val*)ht_get(ht, &magic))->str
#define HT_GET_IND(ht, magic) ((t_val*)ht_get(ht, &magic))->i
#define HT_GET_STAT(ht, magic) ((t_val*)ht_get(ht, &magic))->stat
#define HT_INC_STAT(ht, magic) (*(int*)(&(((t_val*)ht_get(ht, &magic))->stat))) += 1

typedef struct	s_magic_val
{
	char	*str;
	int		i;
	int		stat;
}				t_magic_val;

typedef struct	s_magic
{
	uint32_t	magic;
	t_magic_val	val;
}				t_magic;

static t_magic magic_data[] = {{0xfeedface, {"MH_MAGIC", 0, 0}},
								{0xcefaedfe, {"MH_CIGAM", 1, 0}},
								{0xfeedfacf, {"MH_MAGIC_64", 2, 0}},
								{0xcffaedfe, {"MH_CIGAM_64", 3, 0}},
								{0xcafebabe, {"FAT_MAGIC", 4, 0}},
								{0xbebafeca, {"FAT_CIGAM", 5, 0}}};

static int g_fd = 1;

void	print_stat(t_hash_tbl *ht, int i)
{
	t_kv	*kv;
	char	*mag_str;
	int		quant;
	int		sum = 0;

	ft_printf("stat:\n");
	while ((kv = ht_getnextkv(ht)) != NULL)
	{
		mag_str = ((t_val*)(kv->value))->str;
		quant = ((t_val*)(kv->value))->stat;
		sum += quant;
		ft_printf("\t%s:\t%d\t%.1f%%\n", mag_str, quant, (100 * ((double)quant) / i));
	}
	ft_printf("\tother:\t\t%d\t%.1f%%\n", i - sum, (100 * ((double)(i - sum)) / i));
	ft_printf("total: %d\n", i);
}

void b(t_val *d) {ft_printf_fd(g_fd, "str: %s | index: %d", d->str, d->i);}

void	macho_file_stat(char *file, t_hash_tbl *ht, int *count)
{
	unsigned int		magic;
	void				*ptr;

	if ((ptr = map_file(file)))
	{
		*count += 1;
		magic = *(unsigned int*)ptr;
		if (ht_isset(ht, &magic))
		{
			ft_printf_fd(g_fd, "%x -> %s\n", magic, HT_GET_STR(ht, magic));
			HT_INC_STAT(ht, magic);
		}
		else
			ft_printf_fd(g_fd, "not a mach-o file\n");
	}
}

void	macho_dir_stat(char *dir, t_hash_tbl *ht, int *count)
{
	DIR				*dp;
	struct dirent	*ep;
	char			file[1024];
	int				len;

	dp = opendir (dir);
	if (dp != NULL)
	{
		file[0] = 0;
		strcat(file, dir);
		strcat(file, "/");
		len = ft_strlen(file);
		while ((ep = readdir(dp)) != NULL)
		{
			file[len] = 0;
			strcat(file, ep->d_name);
			if (ep->d_name[0] != '.')
				macho_file_stat(file, ht, count);
		}
		closedir(dp);
	}
	else
		perror("opendir");
}

int		check_opt(int ac, char **av)
{
	int	fd;

	if (ac == 1)
		return (0);
	if (ft_strcmp(av[1], "--verbose") == 0)
		return (1);
	if ((g_fd = open("/dev/null", O_WRONLY)) == -1)
	{
		perror("open \"/dev/null\"");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	ht_fill(t_hash_tbl *const ht, t_magic const data[], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ht->nodes[i].key = (void*)&data[i];
		ht->nodes[i].key_size = size;
		ht->nodes[i].value = (void*)&data[i].val;
		ht->nodes[i].value_size = sizeof(data[i].val);
		i++;
	}
}

int		main(int ac, char **av)
{
	void			*ptr;
	t_hash_tbl		ht;
	int				i;
	int				count;

	ht_init(&ht, 9, &int_cmp, &int_hash);
	my_fill(&ht, magic_data, 6);
	i = check_opt(ac, av);
	count = 0;
	if (ac == i + 1)
		macho_dir_stat(".", &ht, &count);
	else
	{
		count = 0;
		while (++i < ac)
		{
			macho_dir_stat(av[i], &ht, &count);
			write(1, "\n", 1);
			count++;
		}
	}
	print_stat(&ht, count);
	return (0);
}
