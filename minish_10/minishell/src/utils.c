/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:17:18 by mavardan          #+#    #+#             */
/*   Updated: 2023/02/25 18:17:20 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include "../inc/builtins.h"

void	ft_free(char **p, int count)
{
	while (count)
	{
		free((char *)p[count - 1]);
		p[count - 1] = NULL;
		count--;
	}
	free((char **)p);
	p = NULL;
}

int envp_len(char **envp)
{
	int	len;

	len = 0;
	if (!envp)
		return (0);
	while (envp[len])
		++len;
	return (len + 1);
}

// ptrn is env var name, s is a full row
int	is_var_in_env(const char *s, const char *ptrn)
{
	int	i;

	if (!s || !ptrn)
		return (0);
	i = 0;
	while (ptrn[i] && s[i])
	{
		if (s[i] != ptrn[i])
			return 0;
		++i;
	}
	if ('=' == s[i] && '\0' == ptrn[i])
		return (1);
	return (0);
}

int	get_env_var_pos_by_name(const char *env_var, char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while(envp[i])
		{
			if(is_var_in_env(envp[i], env_var))
			{
				return (i);
			}
			++i;
		}
	}
	return (-1);
}

// alter for built-in setenv
int	update_env(char *env_var, char *val, char **envp)
{
	int			pos;
	char		*new_env;
	char		*tmp;

	if (!envp || !env_var || !val)
		return (-1);
	new_env = ft_strjoin(env_var, "=");
	new_env = ft_strjoin(new_env, val);
	if (!new_env)
		return (-1);
	pos = get_env_var_pos_by_name(env_var, envp);
	tmp = envp[pos];
	envp[pos] = new_env;
	free(tmp);
	return (0);
}

static char	**extend_envp(char **envp_old)
{
	char	**envp_new;
	int	i;
	int	cnt;

	cnt = 0;
	cnt = envp_len(envp_old);
	envp_new = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!envp_new)
	{
		perror("envp_new");
		return (NULL);
	}
	i = 0;
	while (i < cnt - 1)
	{
		envp_new[i] = ft_strdup(envp_old[i]);
		++i;
	}
	envp_new[cnt - 1] = NULL;
	envp_new[cnt] = NULL;
	ft_free(envp_old, envp_len(envp_old));
	return (envp_new);
}


int	add_env(char *env_var, char *val, t_data *data)
{
	char	**envp_new;
	char	**envp;
	int		env_pos;
	int		len;
	char	*new_env;

	envp = data->envp;
	if (!envp || !env_var)
		return (-1);
	new_env = ft_strjoin(env_var, "=");
	if (val)
		new_env = ft_strjoin(new_env, val);
	if (!new_env)
		return (-1);
	envp_new = extend_envp(envp);
	if (!envp_new)
		return (-1);
	len = envp_len(envp_new) + 1;
	if (len >= 2)
		envp_new[len - 2] = new_env;
	data->envp = envp_new;
	return (0);
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
			perror("get_env");
			return (NULL);
		}
		val = ft_strdup(envp[env_pos] + ft_strlen(env_var) + 1);
		return (val);
	}
	write(2, "There is no such env var\n", 25);
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
