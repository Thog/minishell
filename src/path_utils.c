/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 08:46:40 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/23 11:33:40 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*compute_path(char *dir, char *name)
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

t_array			*convert_paths(char *path)
{
	t_array	*result;
	char	**paths;
	int		i;

	if (!path)
		return (NULL);
	result = NULL;
	i = 0;
	paths = ft_strsplit(path + 5, ':');
	while (paths[i] && *paths[i])
	{
		result = array_init(result, ft_strdup(paths[i]));
		free(paths[i++]);
	}
	free(paths);
	return (result);
}

char			*find_path(char *name, t_array *paths, int *info)
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
	return (!ft_strncmp("./", name, 2) ? ft_strdup(name) : NULL);
}

void			rebuild_paths(t_env *env)
{
	t_array		*path;

	path = array_get(env->env, "PATH=");
	if (env->paths)
		destroy_array(&env->paths);
	if (path)
		env->paths = convert_paths(path->data);
	else
		env->paths = NULL;
}

char		*join_paths(char *base, char *suffix)
{
	char		*tmp;
	char		*res;
	int			base_len;

	tmp = NULL;
	if (suffix && *suffix == '/')
		return (ft_strdup(suffix));
	base_len = ft_strlen(base);
	if (*(base + base_len) != '/')
	{
		tmp = base;
		base = ft_strjoin(base, "/");
	}
	res = ft_strjoin(base, suffix);
	if (tmp)
		ft_strdel(&base);
	return (res);
}
