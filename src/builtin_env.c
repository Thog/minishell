/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 07:51:13 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/14 13:44:54 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		compute_options(void *data, char *c)
{
	int		*info;

	info = (int *)data;
	if (*info != 0 && *info < 256)
		return (0);
	if (*c == 'i')
		*info = 257;
	else if (*c == 'v' || (*c == '\0' && (*(c - 1) == '-')))
	{
		info[1]++;
		if (info[1] != 1)
			ft_printf_fd(2, "#env verbosity now at %d\n", info[1]);
	}
	else if (*c)
	{
		*info = *c;
		return (0);
	}
	return (1);
}

static void		print_verbose_message(char **args)
{
	int		i;

	i = 0;
	ft_printf_fd(2, "#env executing: %s\n", args[0]);
	while (args[i])
	{
		ft_printf_fd(2, "#env    args[%d]= \'%s\'\n", i, args[i]);
		i++;
	}
}

static void		execute_array(char **args, t_env *env, int *data)
{
	char		*path;
	int			i;
	t_array		*tmp_array;

	tmp_array = compute_env(*data == 257 ? NULL : env->env, args, &i, data[1]);
	if (args[i] && (i != 0 || *args[i] != '-'))
	{
		if (data[1])
			print_verbose_message(args);
		if (can_execute(args[i], env->paths, &path, "env"))
			execute(path, args + i, tmp_array);
		ft_strdel(&path);
	}
	else
	{
		print_env(tmp_array);
		destroy_array(&tmp_array);
	}
}

int				minishell_builtin_env(char **args, t_env *env)
{
	int		ac;
	int		data[2];
	int		i;
	char	*usage;

	data[0] = 0;
	data[1] = 0;
	usage = "[-iv] [name=value]... [utility [argument...]]";
	ac = char_array_length(args);
	if (ac > 1)
	{
		i = ft_parse_args(ac, args, &data, &compute_options) - 1;
		i = !i ? 1 : i;
		if (data[0] != 0 && data[0] < 256)
			return (ft_usage(args[0], usage, (char)*data));
		data[1] = data[1] != 0 ? 2 : 0;
		if (args[i])
			execute_array(args + i, env, data);
		else
			print_env(env->env);
	}
	else
		print_env(env->env);
	return (1);
}
