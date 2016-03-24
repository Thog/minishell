/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/24 15:41:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			post_execute(char ***environ, t_array *env)
{
	free(*environ);
	destroy_array(env);
	ft_memset(g_child, 0, sizeof(g_child));
}

int					execute(char *name, char **args, t_array *env)
{
	pid_t		parent;
	int			status;
	char		**environ;

	environ = to_char_array(env);
	parent = fork();
	if (parent == 0)
	{
		execve(name, args, environ);
		ft_printf_fd(2, "minishell: command not found: %s\n", name);
		exit(1);
	}
	else if (parent < -1)
		ft_putstr_fd("minishell: FORK ERROR!\n", 2);
	else
	{
		*g_child = parent;
		*g_child = waitpid(parent, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			*g_child = waitpid(parent, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			printsignal(*g_child, status);
	}
	post_execute(&environ, env);
	return (!WIFSIGNALED(status));
}

t_array				*compute_env(t_array *env, char **args, int *info)
{
	t_array		*result;
	int			i;
	int			length;
	char		*tmp;

	i = 0;
	length = char_array_length(args);
	result = array_dup(env);
	while (i < length)
	{
		if (!ft_strchr(args[i], '='))
			break ;
		tmp = ft_strsub(args[i], 0, ft_strchr(args[i], '=') - args[i] + 1);
		set_env_array(&result, tmp, ft_strchr(args[i], '=') + 1, 0);
		i++;
	}
	*info = i;
	return (result);
}

static int			builtins_execute(char **args, t_env *env)
{
	if (!ft_strcmp(*args, "exit"))
		return (minishell_builtin_exit(args, env));
	if (!ft_strcmp(*args, "cd"))
		return (minishell_builtin_cd(args, env));
	if (minishell_builtin_env_dispatcher(args, env))
		return (1);
	return (0);
}

int					minishell_execute(char **args, t_env *env, int *sig)
{
	char	*path;
	t_array	*tmp_array;
	int		info;
	int		i;

	path = NULL;
	if (!*args || !ft_isprint(**args))
		return (1);
	tmp_array = compute_env(env->env, args, &i);
	if (i != 0 || !builtins_execute(args, env))
	{
		if (!ft_strcmp((path = find_path(args[i], env->paths, &info)), args[i])
				&& info)
			ft_printf_fd(2, "minishell: %s: %s\n", info ? "permission denied" :
				"command not found", args[i]);
		else
			*sig = execute(path, args + i, tmp_array);
	}
	ft_strdel(&path);
	return (1);
}
