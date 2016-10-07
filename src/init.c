/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:27:38 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/07 20:38:37 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*g_child;

void	signal_handler(int signal)
{
	(void)signal;
	if (!*g_child && signal != SIGQUIT && signal != SIGTSTP)
	{
		if (signal != SIGINFO)
			ft_putchar('\n');
		ft_putstr("$> ");
	}
}

int		minishell_init(t_env **env_data, char **env)
{
	int		path;

	if (!(*env_data = (t_env*)ft_memalloc(sizeof(t_env))) ||
		!(g_child = (pid_t*)ft_memalloc(sizeof(pid_t))))
		return (-1);
	path = get_env(env, "PATH=");
	(*env_data)->env = to_array(env);
	(*env_data)->paths = convert_paths(path == -1 ? NULL : env[path]);
	(*env_data)->exit_code = 0;
	return (signal(SIGINT, signal_handler) == SIG_ERR ||
			signal(SIGINFO, signal_handler) == SIG_ERR ||
			signal(SIGQUIT, signal_handler) == SIG_ERR ||
			signal(SIGTSTP, signal_handler) == SIG_ERR);
}

int		minishell_cleanup(t_env *env, int shutdown)
{
	destroy_array(env->env);
	destroy_array(env->paths);
	env->paths = NULL;
	if (shutdown)
	{
		free(g_child);
		free(env);
	}
	return (1);
}
