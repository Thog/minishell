/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:28:46 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 16:26:12 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**wrap_str(char *str)
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
}

static char	**minishell_split(char *line)
{
	char		**result;
	char		*tmp2;
	char		*tmp3;

	result = ft_strsplitcmp(line, &ft_isblank);
	if ((tmp2 = ft_strchr(line, '"')) && tmp2 != line && *(tmp2 - 1) != '\\')
	{
		destroy_char_array(result);
		tmp3 = ft_strsub(line, 0, tmp2 - line);
		result = ft_strsplit(tmp3, ' ');
		ft_strdel(&tmp3);
	}
	tmp2 = line;
	while ((tmp2 = ft_strchr(tmp2, '"')))
	{
		if ((tmp2++ + 1) && *(tmp2 - 1) == '\\')
			continue ;
		if (((tmp3 = ft_strchr(tmp2, '"')) && *(tmp3 - 1) == '\\'))
			continue ;
		else if (!(tmp3 = ft_strchr(tmp2, '"')))
			break ;
		result = merge_array(result, wrap_str(ft_strsub(tmp2, 0, tmp3 - tmp2)));
	}
	return (result);
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
		status = minishell_execute(args[0], args, env, &sig);
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
