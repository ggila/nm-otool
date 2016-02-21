/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 18:43:19 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/21 19:27:27 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "options.h"
#include "ft_printf.h"

int	main(int ac, char **av)
{
	t_env	g_env;
	int		i;

	if ((i = check_opt(ac, av, &(g_env.opt))) == KO)
		return (EXIT_FAILURE);
	while (i < ac)
	{
		ft_printf("%s\n", av[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
