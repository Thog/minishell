/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 15:15:24 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(char *name, char **args, char **env)
{
	pid_t		parent;
	int			status;

	parent = fork();
	if (parent == 0)
	{
		execve(name, args, env);
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
	ft_memset(g_child, 0, sizeof(g_child));
	return (!WIFSIGNALED(status));
}

static char	*compute_path(char *dir, char *name)
{
	char			*tmp2;
	char			*result;

	tmp2 = ft_strcmp(dir, "/") ? ft_strjoin(dir, "/") : ft_strdup("/");
	result = ft_strjoin(tmp2, name);
	if (access(result, X_OK) == -1)
		ft_strdel(&result);
	ft_strdel(&tmp2);
	return (result);
}

static char	*find_path(char *name, t_array *paths, int *info)
{
	DIR				*dir;
	struct dirent	*tmp;
	char			*result;

	*info = 0;
	while (paths)
	{
		if ((dir = opendir(paths->data)))
		{
			while ((tmp = readdir(dir)))
			{
				if (!ft_strcmp(tmp->d_name, name))
				{
					if ((result = compute_path(paths->data, name)))
						return (result);
					*info = 1;
				}
			}
			closedir(dir);
		}
		paths = paths->next;
	}
	return (ft_strdup(name));
}

int			minishell_execute(char *name, char **args, t_env *env, int *sig)
{
	char	*path;
	char	**tmp_env;
	int		info;

	path = NULL;
	tmp_env = NULL;
	if (!name || !*name)
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (minishell_buildin_exit(args, env));
	if (!ft_strcmp(name, "cd"))
		return (minishell_buildin_cd(args, env));
	if (minishell_buildin_env(args, env))
		return (1);
	if (!ft_strcmp((path = find_path(name, env->paths, &info)), name) && info)
		ft_printf_fd(2, "minishell: %s: %s\n", info ? "permission denied" :
			"command not found", name);
	else
	{
		tmp_env = to_char_array(env->env);
		*sig = execute(path, args, tmp_env);
		free(tmp_env);
	}
	ft_strdel(&path);
	return (1);
}
