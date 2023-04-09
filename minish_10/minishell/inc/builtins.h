/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:17:05 by mavardan          #+#    #+#             */
/*   Updated: 2023/03/08 21:23:43 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define NOT_IN_ENV -2


// typedef struct s_cmd
// {
// 	char	*cmd_name;
// 	char	*args;
// }				t_cmd;


/////////


typedef struct s_cmds
{
	int		inp;
	int		out;
	char	**cmd;
}				t_cmds;

typedef struct	s_data
{
	int		errstat;
	char	**envp;
	t_cmds	*t_cmnds;
}				t_data;

t_data *t_glob;

void	fill_env(char **envp, t_data *data);
int		is_var_in_env(const char *s, const char *ptrn);
int		update_env(char *env_var, char *val, char **envp);
int		add_env(char *env_var, char *val, t_data *data);
char	*get_env(char *env_var, char **envp);
void	pwd(char **envp);
int		cd(const char *new_path, char **envp);
int		get_env_var_pos_by_name(const char *env_var, char **envp);
//void	fill_env(const char **envp, t_data *data);
void	env(const char **envp);
void	echo(char *text);
void	export(char *text, t_data *data);
int		unset(char *env_var, t_data *data);
int		envp_len(char **envp);
void	ft_free(char **p, int count);
//char	**extend_envp(char **envp_old);


#endif
