/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/19 14:53:10 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_env(t_env *env, char *key, char *value)
{
	t_array		*tmp;

	tmp = array_get(env->env, key);
	if (!tmp)
	{
		tmp = array_init(env->env, ft_strjoin(key, value));
		if (!env->env)
			env->env = tmp;
	}
	else
		tmp->data = ft_strjoin(key, value);
}

static char		*get_oldpwd(t_env *env)
{
	t_array	*tmp;
	char	*old_path;

	if ((tmp = array_get(env->env, "PWD=")))
		old_path = ft_strdup(tmp->data + 4);
	else
		old_path = getcwd(NULL, 0);
	return (old_path);
}

static char		*getpwd(int ac, char **av, t_env *env)
{
	char	*path;
	t_array	*tmp;

	if (ac == 1)
	{
		if (!(tmp = array_get(env->env, "HOME=")))
		{
			ft_printf_fd(2, "cd: HOME not set\n");
			return (NULL);
		}
		path = tmp->data + 5;
	}
	else
		path = av[1];
	return (path);
}

//TODO: Implement it correctly http://pubs.opengroup.org/onlinepubs/009696699/utilities/cd.html
int				minishell_buildin_cd(char **args, t_env *env)
{
	int		ac;
	char	*old_path;
	char	*path;

	if ((ac = char_array_length(args)) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		old_path = get_oldpwd(env);
		path = getpwd(ac, args, env);
		if (path && !chdir(path))
		{
			set_env(env, "PWD=", path);
			if (old_path)
			{
				set_env(env, "OLDPWD=", old_path);
				ft_strdel(&old_path);
			}
		}
	}
	return (1);
}
