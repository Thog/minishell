/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:19:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/14 09:06:26 by tguillem         ###   ########.fr       */
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
