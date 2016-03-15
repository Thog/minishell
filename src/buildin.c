/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/15 18:46:28 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: Implement it correctly http://pubs.opengroup.org/onlinepubs/009696699/utilities/cd.html
int				minishell_buildin_cd(char **args, t_env *env)
{
	int		ac;
	t_array	*pwd;

	ac = char_array_length(args);
	if (ac != 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
	{
		pwd = array_get(env->env, "PWD");
		if (chdir(args[1]) == 0)
		{
			if (pwd == NULL)
				array_init(pwd, ft_strjoin("PWD=", args[1]));
			else
				pwd->data = ft_strjoin("PWD=", args[1]);
		}
	}
	return (1);
}

//TODO: Implement it correctly http://pubs.opengroup.org/onlinepubs/9699919799/utilities/env.html
int				minishell_buildin_env(t_env *env)
{
	t_array	*tmp;

	tmp = env->env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
	return (1);
}
