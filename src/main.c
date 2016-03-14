#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_data;

	(void)ac;
	(void)av;
	env_data = NULL;
	if (minishell_init(&env_data, env) == -1)
			return (1);
	minishell_loop(env);
	return (0);
}
