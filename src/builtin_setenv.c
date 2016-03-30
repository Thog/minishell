/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/30 10:39:09 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				minishell_builtin_setenv(char **args, t_env *env)
{
	char	*key;
	int		ac;

	ac = char_array_length(args);
	if (ac == 1)
		print_env(env->env);
	else if (ac < 4)
	{
		if (ft_isstralnum(args[1]))
		{
			key = ft_strjoin(args[1], "=");
			set_env(env, key, ac == 3 ? args[2] : "", 0);
			ft_strdel(&key);
			return (1);
		}
		key = "setenv: Variable name must contain alphanumeric characters.\n";
		ft_putstr_fd(key, 2);
	}
	else
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	return (1);
}

int				minishell_builtin_unsetenv(char **args, t_env *env)
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

int				minishell_builtin_env_dispatcher(char **args, t_env *env)
{
	if (!ft_strcmp(args[0], "env"))
		return (minishell_builtin_env(args, env));
	else if (!ft_strcmp(args[0], "setenv"))
		return (minishell_builtin_setenv(args, env));
	else if (!ft_strcmp(args[0], "unsetenv"))
		return (minishell_builtin_unsetenv(args, env));
	return (0);
}
