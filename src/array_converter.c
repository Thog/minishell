/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_converter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 15:41:08 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/24 09:27:51 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array			*to_array(char **src)
{
	t_array		*root;

	root = NULL;
	while (*src && **src)
	{
		root = array_init(root, ft_strdup(*src));
		src++;
	}
	return (root);
}

char			**to_char_array(t_array *src)
{
	t_array	*tmp;
	char	**result;
	int		i;

	i = 0;
	tmp = src;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!(result = (char **)ft_memalloc(sizeof(char **) * (i + 1))))
		return (NULL);
	i = 0;
	tmp = src;
	while (tmp)
	{
		result[i++] = tmp->data;
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}
