/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/17 09:41:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(char *name, char **args, char **env)
{
	pid_t		parent;
	pid_t		child;
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
		child = waitpid(parent, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			child = waitpid(parent, &status, WUNTRACED);
		if (WIFSIGNALED(status))
			printsignal(child, status);
	}
	return (1);
}

static char	*find_path(char *name, t_array *paths)
{
	DIR				*dir;
	struct dirent	*tmp;
	char			*tmp2;
	char			*result;

	while (paths)
	{
		if ((dir = opendir(paths->data)))
		{
			while ((tmp = readdir(dir)))
			{
				if (!ft_strcmp(tmp->d_name, name))
				{
					tmp2 = ft_strjoin(paths->data, "/");
					result = ft_strjoin(tmp2, name);
					ft_strdel(&tmp2);
					return (result);
				}
			}
		}
		paths = paths->next;
	}
	return (ft_strdup(name));
}

int			minishell_execute(char *name, char **args, t_env *env)
{
	char	*path;
	char	**tmp_env;
	int		result;

	path = NULL;
	tmp_env = NULL;
	if (!name || !*name)
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (minishell_buildin_exit(args, env));
	if (!ft_strcmp(name, "cd"))
		return (minishell_buildin_cd(args, env));
	if (!ft_strcmp(name, "env"))
		return (minishell_buildin_env(env));
	path = find_path(name, env->paths);
	tmp_env = to_char_array(env->env);
	result = execute(path, args, tmp_env);
	ft_strdel(&path);
	free(tmp_env);
	return (result);
}
