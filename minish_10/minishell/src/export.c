/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:03:46 by mavardan          #+#    #+#             */
/*   Updated: 2023/03/03 20:37:06 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/builtins.h"
#include "../libft/libft.h"

static int	equal_sign_pos(char *text)
{
	int	pos;

	if (!text)
		return (-1);
	pos = 0;
	while (text[pos])
	{
		if ('=' == text[pos])
		{
			return (pos);
		}
		++pos;
	}
	if (!text[pos])
	{
		return (-1);
	}
	return (0);
}

static int	is_valid_identifier(char *text)
{
	if (!text)
	{
		ft_putstr_fd("export: NULL pointer\n", 2);
		return (0);
	}
	if (ft_isalpha(text[0]) || '_' == text[0])
	{
		return (1);
	}
	ft_putstr_fd("export: invalid identifier\n", 2);
	return (0);
}

static int	is_valid_export_arg(char *text)
{
	int	pos;
	int	i;

	pos = equal_sign_pos(text);
	if (!is_valid_identifier(text) || 1 > pos)
	{
		return (0);
	}
	i = 0;
	while (i < pos)
	{
		if (!ft_isprint(text[i]))
			return (0);
		++i;
	}
	if (!ft_isprint(text[pos + 1]) || ' ' == text[pos + 1])
	{
		ft_putstr_fd("export: invalid command arg", 2);
		return (0);
	}
	return (1);
}

static char	*get_env_var(char *text)
{
	char	*var_name;
	int		pos;
	int		i;

	if (is_valid_export_arg(text))
	{
		pos = equal_sign_pos(text);
		var_name = malloc (sizeof(char) * (pos + 1));
		if (!var_name)
			return (NULL);
		i = 0;
		while (i < pos)
		{
			var_name[i] = text[i];
			++i;
		}
		var_name[pos] = '\0';
		return (var_name);
	}
	return (NULL);
}


void	export(char *text, t_data *data)
{
	char	**envp;
	char	*var_name;
	char	*var_val;
	int		pos;

	envp = data->envp;
	if (is_valid_export_arg(text))
	{
		pos = equal_sign_pos(text);
		var_name = (char *)malloc(sizeof(char) * (pos + 1));
		var_val = (char *)malloc(sizeof(char) * (ft_strlen(text) - pos));
		if (!var_name && !var_val)
			perror("export malloc error");
		var_name = ft_memcpy(var_name, text, pos);
		var_name[pos] = '\0';
		var_val = ft_memcpy(var_val, text + pos + 1, ft_strlen(text) - pos);
		if (-1 != get_env_var_pos_by_name(var_name, envp))
			update_env(var_name, var_val, envp);
		else
			add_env(var_name, var_val, data);
	}
}

//static void	fill_env(char **envp, t_data *data)
//{
//	int	i;
//	int	cnt;
//
//	cnt = 0;
//	while (envp && envp[cnt])
//		++cnt;
//	data->envp = (char **)malloc(sizeof(char *) * (cnt + 1));
//	if (!data->envp)
//	{
//		perror("data->env");
//		return ;
//	}
//	i = 0;
//	while (i < cnt)
//	{
//		data->envp[i] = ft_strdup(envp[i]);
//		++i;
//	}
//	data->envp[cnt] = NULL;
//}

//int main(int argc, char **argv, char **envp)
//{
//	t_data	*data;
//	data = (t_data *)malloc(sizeof(t_data));
//	fill_env(envp, data);
//	env(data->envp);
//	printf("\n----------------- MAIN export1 ---------------------\n");
//	//printf("----- main export 1, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	export("mmm=nmbmnbnm", data);
//	env(data->envp);
//	//printf("----- main export 1, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	env(data->envp);
//	printf("\n\n----------------- MAIN export2 --------------------\n");
//	//printf("----- main export 2, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	export("mmm=22222222222nmbmnbnm", data);
//	env(data->envp);
//	return (0);
//}
