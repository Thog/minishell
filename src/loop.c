/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/16 11:23:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**minishell_split(char *line)
{
	return (ft_strsplit(line, ' '));
}

int		minishell_loop(t_env *env)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	line = ft_strnew(1);
	status = 1;
	i = 0;
	ft_putstr("$> ");
	while (status == 1 && get_next_line(0, &line) == 1)
	{
		args = minishell_split(line);
		status = minishell_execute(args[0], args, env);
		i = 0;
		while (args[i] && *args[i])
			free(args[i++]);
		free(args);
		if (status == 1)
			ft_putstr("$> ");
	}
	if (status == 1)
		ft_putchar('\n');
	return (env->exit_code);
}
