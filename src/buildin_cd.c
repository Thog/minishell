/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/21 15:10:06 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		compute_options(void *data, char *c)
{
	char	*params;

	params = (char*)data;
	if (*c == '\0')
		*params = 1;
	else
		return (0);
	return (1);
}
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

static char		*getpwd(char *str, char *params, t_env *env)
{
	char	*path;
	t_array	*tmp;

	if (!str)
	{
		if (!(tmp = array_get(env->env, "HOME=")))
		{
			ft_printf_fd(2, "cd: HOME not set\n");
			return (NULL);
		}
		path = tmp->data + 5;
	}
	else
	{
		if (*params == 1)
		{
			if (!(tmp = array_get(env->env, "OLDPWD=")))
			{
				ft_printf_fd(2, "cd: OLDPWD not set\n");
				return (NULL);
			}
			path = tmp->data + 7;
		}
		else
			path = str;
	}
	return (path);
}

//TODO: Implement it correctly http://pubs.opengroup.org/onlinepubs/009696699/utilities/cd.html
int				minishell_buildin_cd(char **args, t_env *env)
{
	int		ac;
	char	*old_path;
	char	*path;
	char	*params;

	if ((ac = char_array_length(args)) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		params = ft_strnew(3);
		ft_parse_args(ac, args, params, &compute_options);
		old_path = get_oldpwd(env);
		path = getpwd(ac == 1 ? NULL : args[1], params, env);
		if (path && !chdir(path))
		{
			set_env(env, "PWD=", path);
			if (old_path)
			{
				set_env(env, "OLDPWD=", old_path);
				ft_strdel(&old_path);
			}
		}
		ft_strdel(&params);
	}
	return (1);
}
