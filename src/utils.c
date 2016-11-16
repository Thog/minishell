/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:19:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/23 08:46:35 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_access(char *path)
{
	if (access(path, X_OK))
	{
		if (access(path, F_OK))
			return (2);
		return (1);
	}
	return (0);
}

int				end_with(char *str, char c)
{
	return (str ? (str[ft_min(ft_strlen(str) - 1, 0)] == c) : 0);
}

int				can_execute(char *name, t_array *paths, char **path, char *prg)
{
	int		access_flag;

	*path = find_path(name, paths, &access_flag);
	if (!*path || (!ft_strcmp(*path, name) && access_flag))
	{
		if (name && *name != '/')
		{
			ft_printf_fd(2, "%s: %s: %s\n", prg, access_flag ?
				"permission denied" : "command not found", name);
			return (0);
		}
	}
	if (!*path)
		*path = ft_strdup(name);
	if ((access_flag = access(*path, F_OK)) == -1)
		ft_printf_fd(2, "%s: %s: %s\n", prg, "command not found", name);
	else if ((access_flag = access(*path, X_OK)) == -1)
		ft_printf_fd(2, "%s: %s: %s\n", prg, "permission denied", name);
	return (!access_flag);
}

char		*get_env_special(t_env *env, char *key, char *postfix, int index)
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
