/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:27:38 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 10:04:26 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*g_child;

void	signal_handler(int signal)
{
	(void)signal;
	if (!*g_child)
		ft_putstr("\n$> ");
}

int		minishell_init(t_env **env_data, char **env)
{
	if (!(*env_data = (t_env*)malloc(sizeof(t_env))) ||
		!(g_child = (pid_t*)ft_memalloc(sizeof(pid_t))))
		return (-1);
	(*env_data)->env = to_array(env);
	(*env_data)->paths = convert_paths(env[get_env(env, "PATH=")]);
	(*env_data)->exit_code = 0;
	return (signal(SIGINT, signal_handler) == SIG_ERR);
}
