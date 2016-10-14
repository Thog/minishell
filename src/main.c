/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:27:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/13 10:33:01 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_data;
	int		result;

	(void)ac;
	(void)av;
	env_data = NULL;
	if (minishell_init(&env_data, env))
		return (1);
	result = minishell_loop(env_data);
	minishell_cleanup(env_data, 1);
	resource_manager_destroy();
	return (result);
}
