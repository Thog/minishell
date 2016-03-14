#include "minishell.h"

int		minishell_init(t_env **env_data, char **env)
{
	if (!(*env_data = (t_env*)malloc(sizeof(env_data))))
		return (-1);
	(*env_data)->env = env;
	(*env_data)->paths = convert_paths(extract_paths(env));
	return (0);
}
