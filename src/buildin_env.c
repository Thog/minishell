/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/19 14:34:04 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		compute_options(void *data, char *c)
{
	int		*info;

	info = (int *)data;
	if (*info != 0 && *info < 256)
		return (1);
	if (*c == 'i')
		*info = 257;
	else if (*c == 'v')
		*info = 258;
	else if (*c == '\0')
		*info = 260;
	else
	{
		*info = *c;
		return (0);
	}
	return (1);
}

int				minishell_buildin_env(char **args, t_env *env)
{
	t_array	*tmp;
	int		ac;
	int		data;

	data = 0;
	ac = char_array_length(args);
	if (ac > 1)
	{
		ft_parse_args(ac, args, &data, &compute_options);
		if (data != 0 && data < 256)
			return (ft_usage(args[0],
				"[-iv] [name=value]... [utility [argument...]]", (char)data));
	}
	tmp = env->env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (1);
}
