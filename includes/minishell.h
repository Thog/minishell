/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:33:56 by tguillem          #+#    #+#             */
/*   Updated: 2016/10/21 10:10:15 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft.h"
# include <stdlib.h>
# include <dirent.h>

# ifndef __APPLE__
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

typedef struct			s_env
{
	t_array				*env;
	t_array				*paths;
	unsigned int		exit_code;
}						t_env;

extern pid_t			*g_child;
int						minishell_init(t_env **env_data, char **env);
int						minishell_cleanup(t_env *env, int shutdown);
int						minishell_loop(t_env *env);
int						minishell_execute(char **args, t_env *env,
								int *sig);
t_array					*convert_paths(char *path);
char					*find_path(char *name, t_array *paths, int *info);
t_array					*array_get(t_array *env, char *name);
int						minishell_builtin_cd(char **args, t_env *env);
int						minishell_builtin_env(char **args, t_env *env);
int						minishell_builtin_env_dispatcher(char **args,
							t_env *env);
int						minishell_builtin_setenv(char **args, t_env *env);
int						minishell_builtin_exit(char **args, t_env *env);
int						minishell_builtin_echo(char **args, t_env *env);
int						get_env(char **env, char *name);
void					set_env(t_env *env, char *key, char *value,
								int free_value);
void					set_env_array(t_array **env, char *key, char *value,
								int flag);
void					remove_env(t_env *env, char *key);
void					printsignal(pid_t pid, int status);
void					print_env(t_array *env);
int						char_array_length(char **array);
void					destroy_char_array(char **array);
int						check_access(char *path);
void					rebuild_paths(t_env *env);
t_array					*compute_env(t_array *env, char **args, int *info,
								int verbosity);
int						execute(char *name, char **args, t_array *env);
int						end_with(char *str, char c);
int						can_execute(char *name, t_array *paths, char **path,
								char *prg);
#endif
