/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/30 11:02:09 by tguillem         ###   ########.fr       */
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

static char		*get_special(t_env *env, char *key, char *postfix, int index)
{
	t_array	*tmp;

	if ((tmp = array_get(env->env, key)))
	{
		if (postfix)
			return (ft_strjoin(tmp->data + index, postfix + 1));
		else
			return (ft_strdup(tmp->data + index));
	}
	return (NULL);
}

static char		*getpwd(char *str, char *params, t_env *env)
{
	char	*path;

	if (!str || *str == '~')
	{
		if (!(path = get_special(env, "HOME=", str, 5)))
			return (ft_error_return("cd: HOME not set\n", NULL));
	}
	else
	{
		if (*params == 1 || *str == '-')
		{
			if (!(path = get_special(env, "OLDPWD=", str, 7)))
				return (ft_error_return("cd: OLDPWD not set\n", NULL));
		}
		else
			path = str;
	}
	return (path);
}

int				minishell_builtin_cd(char **args, t_env *env)
{
	int		tmp;
	char	*tmp2;
	char	*path;
	char	*params;

	if ((tmp = char_array_length(args)) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		params = ft_strnew(3);
		ft_parse_args(tmp, args, params, &compute_options);
		tmp2 = get_oldpwd(env);
		path = getpwd(tmp == 1 ? NULL : args[1], params, env);
		tmp = check_access(path);
		if (path && !tmp && !chdir(path))
		{
			set_env(env, "PWD=", getcwd(NULL, 0), 0);
			set_env(env, "OLDPWD=", tmp2, 1);
		}
		else if (path && tmp && (tmp2 = tmp == 2 ? "no such file or directory" :
					"permission denied"))
			ft_printf_fd(2, "cd: %s: %s\n", tmp2, path);
		ft_strdel(&params);
	}
	return (1);
}
