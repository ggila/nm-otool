/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 18:43:19 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/22 13:02:11 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "nm.h"
#include "options.h"
#include "ft_printf.h"

static void	add_ofile(char *file, t_env env)
{
	static t_olist	**list = &(env->ofile);
	t_olist			*new;

	if (!(new = malloc(sizeof(t_olist))))
	{
		write(1, "malloc() failed\n", 16);
		return (KO);
	}
	if (!(new->file = ft_strdup(file)))
	{
		write(1, "ft_strdup() failed\n", 19);
		return (KO);
	}
	new->next = NULL;
	list = &(new->next);
}

static int	read_arg(int ac, char **av, t_env *env)
{
	int		i;

	if ((i = get_opt(ac, av, &(env->opt))) == KO)
		return (KO);
	if (i == ac && add_ofile("a.out") == KO)
		return (KO);
	while (i < ac)
		if (add_ofile())
	return (OK);
}

int	main(int ac, char **av)
{
	t_env	env;

	ft_bzero(env, sizeof(t_env));
	if (read_arg(ac, av, &env) == KO)
		return (EXIT_FAILURE);
	while (i < ac)
	{
		ft_printf("%s\n", av[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
