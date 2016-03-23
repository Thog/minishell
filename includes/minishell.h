/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:33:56 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/23 15:02:22 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft.h"
# include <stdlib.h>
# include <dirent.h>

# ifdef linux
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

typedef struct			s_array
{
	char				*data;
	struct s_array		*next;
}						t_array;

typedef struct			s_env
{
	t_array				*env;
	t_array				*paths;
	unsigned int		exit_code;
}						t_env;

extern pid_t			*g_child;
int						minishell_init(t_env **env_data, char **env);
int						minishell_loop(t_env *env);
int						minishell_execute(char *name, char **args, t_env *env,
								int *sig);
t_array					*convert_paths(char *path);
t_array					*array_init(t_array *root, char *str);
t_array					*array_get(t_array *env, char *name);
int						minishell_buildin_cd(char **args, t_env *env);
int						minishell_buildin_env(char **args, t_env *env);
int						minishell_buildin_setenv(char **args, t_env *env);
int						minishell_buildin_exit(char **args, t_env *env);
int						get_env(char **env, char *name);
void					set_env(t_env *env, char *key, char *value,
								int free_value);
void					remove_env(t_array **env, char *key);
void					printsignal(pid_t pid, int status);
void					print_env(t_env *env);
t_array					*to_array(char **src);
char					**to_char_array(t_array *src);
int						char_array_length(char **array);
void					destroy_array(t_array *array);
void					destroy_char_array(char **array);
int						check_access(char *path);
#endif
