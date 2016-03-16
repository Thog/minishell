/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 15:41:08 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/16 13:15:02 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array			*to_array(char **src)
{
	t_array		*root;

	root = NULL;
	while (*src && **src)
	{
		root = array_init(root, ft_strdup(*src));
		src++;
	}
	return (root);
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

char			**to_char_array(t_array *src)
{
	t_array	*tmp;
	char	**result;
	int		i;

	i = 0;
	tmp = src;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(result = (char **)ft_memalloc(sizeof(char **) * (i + 1))))
		return (NULL);
	i = 0;
	tmp = src;
	while (tmp)
	{
		result[i++] = tmp->data;
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}
