/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:09:36 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/22 08:23:49 by tguillem         ###   ########.fr       */
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
