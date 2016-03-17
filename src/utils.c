/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/17 09:36:07 by tguillem         ###   ########.fr       */
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

t_array		*array_get(t_array *env, char *name)
{
	while (env)
	{
		if (ft_strstr(env->data, name) != NULL)
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

void		destroy_array(t_array *array)
{
	t_array	*to_del;
	t_array	*tmp;

	if (array)
	{
		tmp = array;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			free(to_del->data);
			free(to_del);
		}
	}
}
