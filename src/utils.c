/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/14 18:30:29 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array		*array_init(t_array *root, char *str)
{
	t_array		*result;
	t_array		*tmp;

	tmp = root;
	if (!(result = (t_array*)malloc(sizeof(t_array))))
		return (NULL);
	result->data = str;
	result->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
		return (root);
	}
	return (result);
}

t_array		*convert_paths(char *path)
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

int			get_env(char **env, char *name)
{
	int	i;

	i = 0;
	while (*env)
	{
		if (ft_strstr(*env, name) != NULL)
			return (i);
		env++;
		i++;
	}
	return (-1);
}
