/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:19:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/24 09:43:20 by tguillem         ###   ########.fr       */
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

t_array			*array_dup(t_array *src)
{
	t_array			*tmp;
	t_array			*result;

	tmp = src;
	result = NULL;
	while (tmp)
	{
		if (result)
			array_init(result, ft_strdup(tmp->data));
		else
			result = array_init(result, ft_strdup(tmp->data));
		tmp = tmp->next;
	}
	return (result);
}
