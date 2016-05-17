/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/05/17 15:51:13 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	**wrap_str(char *str)
{
	char		**result;

	if (!(result = (char **)ft_memalloc(sizeof(char**) * 2)))
		return (NULL);
	*result = str;
	*(result + 1) = NULL;
	return (result);
}

static char	**merge_array(char **dest, char **src)
{
	char		**result;
	char		**tmp;
	char		**tmp2;
	char		**tmp3;

	if (!(result = (char **)ft_memalloc(sizeof(char**) * (
						char_array_length(src) + char_array_length(dest) + 1))))
		return (NULL);
	tmp = result;
	tmp2 = dest;
	tmp3 = src;
	while (dest && *dest)
		*tmp++ = *dest++;
	free(tmp2);
	while (src && *src)
		*tmp++ = *src++;
	free(tmp3);
	*tmp = NULL;
	return (result);
}*/

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
				tmp = NULL;
			else
			{
				tmp = index;
				*tmp = ft_strdup(ft_strchr(*index, '"') + 1);
			}
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
