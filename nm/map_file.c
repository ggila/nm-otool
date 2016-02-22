/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 16:13:09 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/22 18:15:28 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "ft_printf.h"

static char	get_stat(char *file, int fd, struct stat *buf)
{
	if (fstat(fd, buf) == -1)
	{
		ft_printf("%s, stat() failed\n", file);
		return (KO);
	}
	if ((buf->st_mode & S_IFMT) != S_IFREG)
	{
		ft_printf("%s: not a regular file\n", file);
		return (KO);
	}
	return (OK);
}

void		*map_file(char *file)
{
	struct stat		buf;
	int				fd;
	void			*ptr;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		if (fd != -1)
			close(fd);
		ft_printf("%s: open() failed\n", file);
		return (NULL);
	}
	get_stat(file, fd, &buf);
	if ((ptr = mmap(0, buf.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd);
		ft_printf("mmap() failed\n");
		return (NULL);
	}
	close(fd);
	return (ptr);
}
