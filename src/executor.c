/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:01:01 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/14 18:32:49 by tguillem         ###   ########.fr       */
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
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(name, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	else if (parent < -1)
		ft_putstr_fd("minishell: FORK ERROR!\n", 2);
	else
	{
		child = waitpid(parent, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			child = waitpid(parent, &status, WUNTRACED);
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
	return (name);
}

int			minishell_execute(char *name, char **args, t_env *env)
{
	char	*path;

	path = NULL;
	if (!name || !*name)
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (0);
	if (!ft_strcmp(name, "cd"))
		return (minishell_buildin_cd(args, env->env));
	if (!ft_strcmp(name, "env"))
		return (minishell_buildin_env(env->env));
	path = find_path(name, env->paths);
	return (execute(path, args, env->env));
}
