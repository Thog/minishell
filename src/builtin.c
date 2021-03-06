/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:57:53 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/21 10:30:34 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						minishell_builtin_exit(char **args, t_env *env)
{
	int		ac;
	int		code;

	ac = char_array_length(args);
	if (ac > 2)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else
	{
		code = ac == 2 ? (unsigned int)ft_atoi(args[1]) : 0;
		env->exit_code = code;
		return (2);
	}
	return (1);
}

int						minishell_builtin_echo(char **args, t_env *env)
{
	(void)env;
	args++;
	while (args && *args)
	{
		ft_putstr(*args);
		args++;
		if (args && *args)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (1);
}
