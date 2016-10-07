/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/07 20:46:34 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**minishell_split(char *line)
{
	return (ft_strsplitcmp(line, &ft_isblank));
}

static void	clean_args(char **args)
{
	char	**origin;

	origin = args;
	while (*args && **args)
		ft_strdel(args++);
	if (origin)
	{
		free(origin);
		origin = NULL;
	}
}

int			minishell_loop(t_env *env)
{
	char	*line;
	char	**args;
	int		status;
	int		sig;

	line = NULL;
	status = 1;
	sig = 1;
	ft_putstr("$> ");
	while (status == 1 && get_next_line(0, &line) > 0)
	{
		args = minishell_split(line);
		status = minishell_execute(args, env, &sig);
		if (!sig)
			ft_putchar('\n');
		if (status == 1)
			ft_putstr("$> ");
		ft_strdel(&line);
		clean_args(args);
	}
	ft_strdel(&line);
	if (status == 1)
		ft_putchar('\n');
	return (env->exit_code);
}
