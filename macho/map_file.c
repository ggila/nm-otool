/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 16:13:09 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/13 17:15:54 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macho.h"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

static char	get_stat(char *file, struct stat *buf)
{
	if (stat(file, buf) == -1)
	{
		ft_printf("stat() failed\n");
		return (KO);
	}
	if ((buf->st_mode & S_IFMT) != S_IFREG)
	{
		ft_printf("%s: not a regular file\n");
		return (KO);
	}
	return (OK);
}

void	*map_file(char *file, int *count)
{
	struct stat		buf;
	int				fd;
	void			*ptr;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		if (fd != -1)
			close(fd);
		ft_printf("open() failed\n");
		return (NULL);
	}
	get_stat(file, &buf);
	if ((ptr = mmap(0, buf.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		ft_printf("mmap() failed\n");
		return (NULL);
	}
	return (ptr);
}
