/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/16 13:13:42 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Implement it correctly http://pubs.opengroup.org/onlinepubs/009696699/utilities/cd.html
int				minishell_buildin_cd(char **args, t_env *env)
{
	int		ac;
	t_array	*tmp;
	char	*path;

	ac = char_array_length(args);

	if (ac > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		if (ac == 1)
		{
			tmp = array_get(env->env, "HOME");
			if (tmp == NULL)
			{
				ft_printf_fd(2, "cd: HOME not set\n");
				return (1);
			}
			path = tmp->data + 5;
		}
		else
			path = args[1];
		tmp = array_get(env->env, "PWD");
		if (!chdir(path))
		{
			if (!tmp)
			{
				tmp = array_init(env->env, ft_strjoin("PWD=", path));
				if (!env->env)
					env->env = tmp;
			}
			else
				tmp->data = ft_strjoin("PWD=", path);
		}
	}
	return (1);
}
