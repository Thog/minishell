#include "minishell.h"

t_array	*array_init(t_array *root, char *str)
{
	t_array		*result;
	t_array		*tmp;

	tmp = root;
	if (!(result = (t_array*)malloc(sizeof(t_array))))
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

t_array		*convert_paths(char *path)
{
	t_array	*result;
	char	**paths;
	int		i;

	if (!path)
		return (NULL);
	result = NULL;
	i = 0;
	paths = ft_strsplit(path + 5, ':');
	while (paths[i] && *paths[i])
	{
		result = array_init(result, ft_strdup(paths[i]));
		free(paths[i++]);
	}
	free(paths);
	return (result);
}

char		*extract_paths(char **env)
{
	while (*env)
	{
		if (ft_strstr(*env, "PATH") != NULL)
			return (*env);
		env++;
	}
	return (NULL);
}
