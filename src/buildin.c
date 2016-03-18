/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/16 13:13:42 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						minishell_buildin_exit(char **args, t_env *env)
{
	int		ac;

	ac = char_array_length(args);
	if (ac > 2)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		env->exit_code = ac == 2 ? (unsigned int)ft_atoi(args[1]) : 0;
		return (0);
	}
	return (1);
}

int						minishell_buildin_pwd(void)
{
	return (1);
}
