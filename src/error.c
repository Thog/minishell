/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:45:44 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/22 11:25:51 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printsignal(pid_t pid, int status)
{
	if (status != SIGINT)
		ft_printf_fd(2, "[%d]%*d\n", pid, 4, status);
}
