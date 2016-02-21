/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 11:33:46 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/21 18:26:29 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "ft_printf.h"

#define WHITE_SPACE "                              "
#define LEN_WS 30
#define ARGS "[file ...]"

extern const t_opt	g_opt[];

static int	get_opt_len(int len[])
{
	int	i;
	int	max;

	i = 0;
	max = -1;
	while (!IS_OPT_NULL(i))
	{
		len[i] = 0;
		if (g_opt[i].c_opt)
		{
			len[i] += 1;
			if (g_opt[i].str_opt)
				len[i] += 2;
		}
		if (g_opt[i].str_opt)
			len[i] += ft_strlen(g_opt[i].str_opt);
		if (len[i] > max)
			max = len[i];
	}
	return max;
}

static void	print_opt(int len[], int max)
{
	int		i;
	t_opt	o;

	i = 0;
	ft_printf("\n");
	i = 0;
	while (!IS_OPT_NULL(i))
	{
		o = g_opt[i];
		if (o.c_opt)
		{
			ft_printf("-%c", o.c_opt);
			if (o.str_opt)
				ft_printf(", ");
		}
		if (o.str_opt)
			ft_printf("--%s", o.str_opt);
		ft_printf("%s     %s\n",
				WHITE_SPACE + LEN_WS + max - len[i], o.comment);
	}
}

void		usage(const char *prog_name)
{
	int		len[32];
	int		max;

	ft_printf("usage: %s", prog_name);
	if (!IS_OPT_NULL(0))
		ft_printf(" [<options>] [--]");
	ft_printf(" %s\n", ARGS);
	if (!IS_OPT_NULL(0))
	{
		max = get_opt_len(len);
		print_opt(len, max);
	}
}
