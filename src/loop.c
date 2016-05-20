/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/05/20 17:25:16 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**minishell_split(char *line)
{
	char	**index;
	char	**origin;
	char	**tmp;
	char	*tmp1;

	tmp = NULL;
	origin = ft_strsplitcmp(line, &ft_isblank);
	index = origin;
	while (index && *index)
	{
		if (tmp)
		{
			tmp1 = *tmp;
			*tmp = ft_strjoin(*tmp, " ");
			ft_strdel(&tmp1);
			tmp1 = *tmp;
			*tmp = ft_strjoin(*tmp, *index);
			ft_strdel(&tmp1);
		}
		if (ft_strchr(*index, '"'))
		{
			if (tmp)
				*tmp = ft_trim(*tmp, '"');
			else
				*index = ft_strdup(ft_strchr(*index, '"') + 1);
			tmp = tmp ? NULL : index;
		}
		else if (tmp)
			*index = NULL;
		index++;
	}
	return (origin);
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
