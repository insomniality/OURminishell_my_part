/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:17:18 by mavardan          #+#    #+#             */
/*   Updated: 2023/04/05 21:13:19 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include "../inc/builtins.h"

int	get_export_var_pos_by_name(const char *var, char **exportp)
{
	int	i;

	i = 0;
	if (exportp)
	{
		while (exportp[i])
		{
			if (is_var_in_env(exportp[i], var) || \
					ft_strncmp(var, exportp[i], ft_strlen(var)))
			{
				return (i);
			}
			++i;
		}
	}
	return (-1);
}

int	update_export(char *var, char *val, t_data *data)
{
	int			pos;
	char		*new_var;
	char		*tmp;

	if (!data || !data->exportp || !var)
		return (set_get_exit_status(data, 2));
	if (!val)
		new_var = ft_strdup(var);
	else
	{
		new_var = ft_strjoin(var, "=\"");
		new_var = ft_strjoin(new_var, val);
		new_var = ft_strjoin(new_var, "\"");
	}
	if (!new_var)
		return (set_get_exit_status(data, 2));
	pos = get_env_var_pos_by_name(var, data->exportp);
	//TODO
	if (-1 == pos)
	{
		free(new_var);
		return (set_get_exit_status(data, 0));
	}
	tmp = data->exportp[pos];
	data->exportp[pos] = new_var;
	free(tmp);
	return (set_get_exit_status(data, 0));
}

int	get_env_var_pos_by_name(const char *env_var, char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (is_var_in_env(envp[i], env_var))
			{
				return (i);
			}
			++i;
		}
	}
	return (-1);
}

// alter for built-in setenv
int	update_env(char *env_var, char *val, t_data *data)
{
	char		**envp;
	int			pos;
	char		*new_env;
	char		*tmp;

	if (!data || !data->envp || !env_var || !val)
		return (set_get_exit_status(data, 2));
	envp = data->envp;
	new_env = ft_strjoin(env_var, "=");
	new_env = ft_strjoin(new_env, val);
	if (!new_env)
		return (set_get_exit_status(data, 2));
	pos = get_env_var_pos_by_name(env_var, envp);
	tmp = envp[pos];
	envp[pos] = new_env;
	free(tmp);
	return (set_get_exit_status(data, 0));
}

int	add_env(char *env_var, char *val, t_data *data)
{
	char	**envp_new;
	char	**envp;
	int		env_pos;
	int		len;
	char	*new_env;

	if (!data || !data->envp || !env_var || !val)
		return (set_get_exit_status(data, 2));
	envp = data->envp;
	new_env = ft_strjoin(env_var, "=");
	if ('\0' != val[0])
		new_env = ft_strjoin(new_env, val);
	if (!new_env)
		return (set_get_exit_status(data, 2));
	envp_new = extend_ch_pp(envp);
	if (!envp_new)
		return (set_get_exit_status(data, 2));
	len = envp_len(envp_new) + 1;
	if (len >= 2)
		envp_new[len - 2] = new_env;
	data->envp = envp_new;
	return (set_get_exit_status(data, 0));
}

int	add_var_to_export(char *var, char *val, t_data *data)
{
	char	**exportp_new;
	int		pos;
	int		len;
	char	*new_var;

	if (!data || !data->exportp || !var)
		return (set_get_exit_status(data, 2));
	//TODO may be if ('\0' == val)
	if (!val)
		new_var = ft_strdup(var);
	else
	{
		new_var = ft_strjoin(var, "=\"");
		new_var = ft_strjoin(new_var, val);
		new_var = ft_strjoin(new_var, "\"");
		exportp_new = extend_ch_pp(data->exportp);
		if (!new_var || !exportp_new)
			return (set_get_exit_status(data, 2));
		len = envp_len(exportp_new) + 1;
		if (len >= 2)
			exportp_new[len - 2] = new_var;
		data->exportp = exportp_new;
	}
	return (set_get_exit_status(data, 0));
}

char	**extend_ch_pp(char **ch_pp)
{
	char	**envp_new;
	int		i;
	int		cnt;

	cnt = 0;
	cnt = envp_len(ch_pp);
	envp_new = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!envp_new)
	{
		perror("envp_new");
		return (NULL);
	}
	i = 0;
	while (i < cnt - 1)
	{
		envp_new[i] = ft_strdup(ch_pp[i]);
		++i;
	}
	envp_new[cnt - 1] = NULL;
	envp_new[cnt] = NULL;
	ft_free(ch_pp, envp_len(ch_pp));
	return (envp_new);
}

// alter for built-in getenv
char	*get_env(char *env_var, char **envp)
{
	int		env_pos;
	int		len;
	char	*tmp;
	char	*val;

	if (!envp || !env_var)
		return (NULL);
	env_pos = get_env_var_pos_by_name(env_var, envp);
	if (-1 != env_pos)
	{
		len = ft_strlen(envp[env_pos]) - (ft_strlen(env_var) + 1);
		val = (char *)malloc(sizeof(char) * (len + 1));
		if (!val)
		{
			perror("get var");
			return (NULL);
		}
		val = ft_strdup(envp[env_pos] + ft_strlen(env_var) + 1);
		return (val);
	}
	ft_putstr_fd("There is no such var\n", 2);
	return (NULL);
}

/*
int main (int argc, char **argv, char **envp)
{
	//update_env("PWD", "jhrfkjrhejhtrjg", envp);
	env();
	get_env("PWDDD", envp);

	return 0;
}*/
