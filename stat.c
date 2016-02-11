/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 15:17:27 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/11 20:14:54 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

#include "nm_otool.h"
#include "hash_tables.h"
#include "ft_printf.h"

#define HT_GET_STR(ht, magic) ((t_val*)ht_get(ht, &magic))->str
#define HT_GET_IND(ht, magic) ((t_val*)ht_get(ht, &magic))->i
#define HT_GET_STAT(ht, magic) ((t_val*)ht_get(ht, &magic))->stat
#define HT_INC_STAT(ht, magic) (*(int*)(&(((t_val*)ht_get(ht, &magic))->stat))) += 1

typedef struct	s_val
{
	char	*str;
	int		i;
	int		stat;
}				t_val;

static unsigned int magic_key[] = {0xfeedface, 0xcefaedfe,
									0xfeedfacf, 0xcffaedfe,
									0xcafebabe, 0xbebafeca};

static t_val magic_val[] = {{"MH_MAGIC", 0, 0},
							{"MH_CIGAM", 1, 0},
							{"MH_MAGIC_64", 2, 0},
							{"MH_CIGAM_64", 3, 0},
							{"FAT_MAGIC", 4, 0},
							{"FAT_CIGAM", 5, 0}};

static int g_fd = 1;

static const t_kv magic_kv[] = {{&magic_key[0], sizeof(unsigned int),
										&magic_val[0], sizeof(magic_val[0])},
								{&magic_key[1], sizeof(unsigned int),
										&magic_val[1], sizeof(magic_val[1])},
								{&magic_key[2], sizeof(unsigned int),
										&magic_val[2], sizeof(magic_val[2])},
								{&magic_key[3], sizeof(unsigned int),
										&magic_val[3], sizeof(magic_val[3])},
								{&magic_key[4], sizeof(unsigned int),
										&magic_val[4], sizeof(magic_val[4])},
								{&magic_key[5], sizeof(unsigned int),
										&magic_val[5], sizeof(magic_val[5])},
								KV_NULL};

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

void	*map_file(char *file, int *fd, int *count)
{
	struct stat		buf;
	void			*ptr;

	if (stat(file, &buf) == -1)
	{
		ft_printf_fd(g_fd, "%s: ", file);
		perror("stat");
		return (MAP_FAILED);
	}
	else if ((buf.st_mode & S_IFMT) != S_IFREG)
		return (MAP_FAILED);
	ft_printf_fd(g_fd, "%s: ", strrchr(file, '/') + 1);
	if ((*fd = open(file, O_RDONLY)) == -1)
	{
		perror(file);
		return (MAP_FAILED);
	}
	else if ((ptr = mmap(0, buf.st_size, PROT_READ,
			MAP_PRIVATE, *fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (MAP_FAILED);
	}
	*count += 1;
	return (ptr);
}

void	macho_file_stat(char *file, t_hash_tbl *ht, int *count)
{
	unsigned int		magic;
	int					fd;
	void				*ptr;

	if ((ptr = map_file(file, &fd, count)) != MAP_FAILED)
	{
		magic = *(unsigned int*)ptr;
		if (ht_isset(ht, &magic))
		{
			ft_printf_fd(g_fd, "%x -> %s\n", magic, HT_GET_STR(ht, magic));
			HT_INC_STAT(ht, magic);
		}
		else
			ft_printf_fd(g_fd, "not a mach-o file\n");
	}
	if (fd != -1)
		close(fd);
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

int		main(int ac, char **av)
{
	void			*ptr;
	t_hash_tbl		ht;
	int				i;
	int				count;

	ht_init(&ht, 9, &int_cmp, &int_hash);
	ht_fill(&ht, magic_kv);
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
