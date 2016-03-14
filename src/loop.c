#include "minishell.h"

static char	**minishell_split(char *line)
{
	return (ft_strsplit(line, ' '));
}

int			minishell_execute(char *name, char **args, char **env)
{
	pid_t		parent;
	pid_t		child;
	int			status;

	parent = fork();
	if (parent == 0)
	{
		ft_putnbr(execve(name,  args, env));
	}
	else if (parent < -1)
		;
	else
	{
		child = waitpid(parent, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			child = waitpid(parent, &status, WUNTRACED);
	}
	return (1);
}

void		minishell_loop(char **env)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	line = ft_strnew(1);
	status = 1;
	i = 0;
	while (status)
	{
		ft_putstr("$> ");
		get_next_line(0, &line);
		args = minishell_split(line);
		status = minishell_execute(args[0], args, env);
		i = 0;
		while (args[i] && *args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}
