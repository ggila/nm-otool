/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 16:13:09 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/23 09:07:20 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "ft_printf.h"

static char	get_stat(t_ofile *ofile, int fd)
{
	struct stat		buf;

	if (fstat(fd, buf) == -1)
	{
		ft_printf("can't stat file: %s\n", ofile->file_name);
		return (KO);
	}
	if ((buf->st_mode & S_IFMT) != S_IFREG)
	{
		ft_printf("not a regular file:%s\n", ofile->file_name);
		return (KO);
	}
	ofile->file_size = buf.st_size;
	ofile->file_size = buf.st_size;
	return (OK);
}

void		*map_file(t_ofile *ofile)
{
	int				fd;
	void			*ptr;

	if ((fd = open(ofile->file_name, O_RDONLY)) == -1)
	{
		if (fd != -1)
			close(fd);
		ft_printf("can't open file: %s\n", ofile->file_name);
		return (NULL);
	}
	get_stat(ofile, fd);
	if ((ptr = mmap(0, buf.st_size, PROT_READ,
				MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd);
		ft_printf("can't map file: %s\n", ofile->file_name);
		return (NULL);
	}
	close(fd);
	ofile->file_addr = ptr;
	return (ptr);
}
