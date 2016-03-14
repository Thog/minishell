#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft.h"
# include <stdlib.h>

typedef struct			s_array
{
	char				*data;
	struct s_array		*next;
}						t_array;

typedef struct			s_env
{
	char				**env;
	t_array				*paths;
}						t_env;


int						minishell_init(t_env **env_data, char **env);
void					minishell_loop(char **env);
int						minishell_execute(char *name, char **args, char **env);
t_array					*convert_paths(char *path);
t_array					*array_init(t_array *root, char *str);
char					*extract_paths(char **env);
#endif
