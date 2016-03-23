/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 17:38:19 by tguillem         ###   ########.fr       */
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

int				minishell_buildin_setenv(char **args, t_env *env)
{
	char	*key;
	int		ac;

	ac = char_array_length(args);
	if (ac == 1)
		print_env(env);
	else if (ac < 4)
	{
		key = ft_strjoin(args[1], "=");
		set_env(env, key, ac == 3 ? args[2] : "", 0);
		ft_strdel(&key);
	}
	else
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	return (1);
}

int				minishell_buildin_unsetenv(char **args, t_env *env)
{
	char	*key;
	int		ac;

	ac = char_array_length(args);
	if (ac == 2)
	{
		key = ft_strjoin(args[1], "=");
		if (array_get(env->env, key))
			remove_env(env, key);
		ft_strdel(&key);
	}
	else
		ft_putstr_fd("unsetenv: Too many arguments.\n", 2);
	return (1);
}

static int		minishell_buildin_env_internal(char **args, t_env *env)
{
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
	print_env(env);
	return (1);
}

int				minishell_buildin_env(char **args, t_env *env)
{
	if (!ft_strcmp(args[0], "env"))
		return (minishell_buildin_env_internal(args, env));
	else if (!ft_strcmp(args[0], "setenv"))
		return (minishell_buildin_setenv(args, env));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (minishell_buildin_unsetenv(args, env));
	return (0);
}
