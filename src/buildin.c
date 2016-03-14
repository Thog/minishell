/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/14 18:24:48 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				minishell_buildin_cd(char **args, char **env)
{
	(void)args;
	(void)env;
	return (1);
}

int				minishell_buildin_env(char **env)
{
	char	**tmp;

	tmp = env;
	while (*tmp)
	{
		ft_putstr(*tmp);
		ft_putchar('\n');
		tmp++;
	}
	return (1);
}
