/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prgm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/21 18:45:24 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			prepare_args(char *str, void *data,
						int (*compute_options)(void*, char*))
{
	int		result;

	result = 2;
	{
		while (*str == '-' && (result = compute_options(data,
			++str)))
			;
		return (result == 0);
	}
	return (1);
}

int					ft_parse_args(int ac, char **av, void *data,
						int (*compute_options)(void*, char*))
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

int					ft_usage(char *prg_name, char *usage, char illegal_char)
{
	if (illegal_char)
		ft_printf_fd(2, "%s: illegal option -- %c\n", prg_name, illegal_char);
	ft_printf_fd(2, "usage: %s %s\n", prg_name, usage);
	return (1);
}

char				*ft_error_return(char *str, char *code)
{
	ft_putstr_fd(str, 2);
	return (code);
}
