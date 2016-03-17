/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prgm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/17 09:41:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			prepare_args(char *str, void *data,
						int (*compute_options)(void*, char))
{
	int		result;

	result = 2;
	{
		while (*str == '-' && *(str + 1) && (result = compute_options(data,
			*++str)))
			;
		return (result == 0);
	}
	return (1);
}

int					ft_parse_args(int ac, char **av, void *data,
						int (*compute_options)(void*, char))
{
	int i;
	int stop;

	stop = 0;
	i = 0;
	ac--;
	av++;
	while (i < ac && !stop)
		stop = prepare_args(av[i++], data, compute_options);
	return (i);
}
