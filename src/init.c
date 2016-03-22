/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:27:38 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/22 09:41:16 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_init(t_env **env_data, char **env)
{
	if (!(*env_data = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	(*env_data)->env = to_array(env);
	(*env_data)->paths = convert_paths(env[get_env(env, "PATH=")]);
	(*env_data)->exit_code = 0;
	return (0);
}
