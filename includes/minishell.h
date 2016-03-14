/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:33:56 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/14 18:34:09 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include "libft.h"
# include <stdlib.h>
# include <dirent.h>

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
void					minishell_loop(t_env *env);
int						minishell_execute(char *name, char **args, t_env *env);
t_array					*convert_paths(char *path);
t_array					*array_init(t_array *root, char *str);

int						minishell_buildin_cd(char **args, char **env);
int						minishell_buildin_env(char **env);
int						get_env(char **env, char *name);
#endif
