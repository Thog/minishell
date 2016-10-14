/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/13 10:37:40 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array		*array_get(t_array *env, char *name)
{
	int		size;

	size = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->data, name, size))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int			char_array_length(char **array)
{
	int		result;

	result = 0;
	while (*array && **array)
	{
		array++;
		result++;
	}
	return (result);
}

void		destroy_char_array(char **array)
{
	char	**origin;
	char	**index;

	index = array;
	origin = index;
	while (array && *array)
	{
		index = array;
		array++;
		ft_strdel(index);
	}
	free(origin);
}
