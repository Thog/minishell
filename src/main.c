/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:27:34 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/14 18:30:09 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_data;

	(void)ac;
	(void)av;
	env_data = NULL;
	if (minishell_init(&env_data, env) == -1)
		return (1);
	minishell_loop(env_data);
	return (0);
}
