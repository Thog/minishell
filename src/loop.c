/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/09/20 14:38:01 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**minishell_split(char *line)
{
	return (ft_strsplitcmp(line, &ft_isblank));
}

int			minishell_loop(t_env *env)
{
	char	*line;
	char	**args;
	int		status;
	int		sig;

	line = ft_strnew(1);
	status = 1;
	sig = 1;
	ft_putstr("$> ");
	while (status == 1 && get_next_line(0, &line) == 1)
	{
		args = minishell_split(line);
		status = minishell_execute(args, env, &sig);
		while (*args && **args)
			ft_strdel(args++);
		if (!sig)
			ft_putchar('\n');
		if (status == 1)
			ft_putstr("$> ");
	}
	if (status == 1)
		ft_putchar('\n');
	return (env->exit_code);
}
