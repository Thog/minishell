/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:19:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/09/20 14:46:37 by tguillem         ###   ########.fr       */
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
		ft_printf_fd(2, "%s: %s: %s\n", prg, access_flag ? "permission denied"
			: "command not found", name);
		return (0);
	}
	access_flag = access(*path, X_OK) == -1;
	if (access_flag)
		ft_printf_fd(2, "%s: %s: %s\n", prg, "permission denied", name);
	return (!access_flag);
}
