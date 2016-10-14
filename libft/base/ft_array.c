/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 09:01:19 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/14 13:57:39 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array			*array_init(t_array *root, char *str)
{
	t_array		*result;
	t_array		*tmp;

	tmp = root;
	if (!(result = (t_array*)ft_memalloc(sizeof(t_array))))
		return (NULL);
	result->data = str;
	result->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
		return (root);
	}
	return (result);
}

t_array			*array_dup(t_array *src)
{
	t_array			*tmp;
	t_array			*result;

	tmp = src;
	result = NULL;
	while (tmp)
	{
		if (result)
			array_init(result, ft_strdup(tmp->data));
		else
			result = array_init(result, ft_strdup(tmp->data));
		tmp = tmp->next;
	}
	return (result);
}

void			destroy_array(t_array **array)
{
	t_array	*to_del;
	t_array	*tmp;

	if (array && *array)
	{
		tmp = *array;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			ft_memdel((void **)&to_del->data);
			ft_memdel((void **)&to_del);
		}
	}
}

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
		result[i++] = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	result[i] = NULL;
	return (result);
}
