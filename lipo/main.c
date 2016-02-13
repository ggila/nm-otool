/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 13:08:20 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/13 13:14:54 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lipo.h"
#include "macho.h"

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
	if (ac != 2)
		usage();
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
