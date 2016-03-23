/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:09:36 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 15:00:36 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_env(char **env, char *name)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(name);
	while (*env)
	{
		if (!ft_strncmp(*env, name, size))
			return (i);
		env++;
		i++;
	}
	return (-1);
}

void		set_env(t_env *env, char *key, char *value, int free_value)
{
	t_array		*tmp;

	if (!(tmp = array_get(env->env, key)))
	{
		tmp = array_init(env->env, ft_strjoin(key, value));
		if (!env->env)
			env->env = tmp;
	}
	else
		tmp->data = ft_strjoin(key, value);
	if (free_value)
		ft_strdel(&value);
}

void		remove_env(t_array **env, char *key)
{
	t_array	*prev;
	t_array	*tmp;
	int		size;

	tmp = *env;
	prev = NULL;
	size = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, key, size))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->data);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void		print_env(t_env *env)
{
	t_array	*tmp;

	tmp = env->env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
