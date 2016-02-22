/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 21:40:57 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/22 15:42:30 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "libft.h"
#include "options.h"
#include "ft_printf.h"
#include "nm.h"
#include "options.h"

static char	check_char_opt(const char *prog, const char *arg, t_nm_opt *opt)
{
	int i;
	int j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (!IS_OPT_NULL(j) && (g_opt[j].c_opt != arg[i]))
			j++;
		if (IS_OPT_NULL(j))
		{
			ft_printf("%s: illegal option: %c\n\n", prog, arg[i]);
			return (KO);
		}
		opt->flag &= MASK << j;
		i++;
	}
	return (OK);
}

static char	check_str_opt(const char *prog, const char *arg, t_nm_opt *opt)
{
	int	i;

	i = 0;
	while (!IS_OPT_NULL(i) && g_opt[i].str_opt &&
			ft_strcmp(g_opt[i].str_opt, arg))
		i++;
	if (IS_OPT_NULL(i))
	{
		ft_printf("%s: illegal option: %s\n\n", prog, arg);
		return (KO);
	}
	opt->flag &= MASK << i;
	return (OK);
}

static char	is_option(const char *arg)
{
	if ((arg[0] != '-') || (ft_strcmp(arg, "-") == 0))
		return (KO);
	return (OK);
}

int			get_opt(int ac, char **av, t_nm_opt *opt)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "--") == 0)
			return (i + 1);
		if (is_option(av[i]) == KO)
			break ;
		if ((av[i][1] == '-' ? check_str_opt(av[0], av[i] + 2, opt) :
								check_char_opt(av[0], av[i] + 1, opt)) == KO)
		{
			usage(av[0]);
			return (KO);
		}
		i++;
	}
	return (i);
}
