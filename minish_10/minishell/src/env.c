/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:17:18 by mavardan          #+#    #+#             */
/*   Updated: 2023/03/06 20:49:48 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/builtins.h"
#include "../libft/libft.h"

void	env(const char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while(envp[i])
		{
			printf("%s\n", envp[i]);
			++i;
		}
	}
}

// void	fill_env(const char **envp, t_data *data)
// {
// 	int	i;
// 	int	cnt;

// 	cnt = 0;
// 	if (!data || !envp)
// 		return ;
// 	while (envp[cnt])
// 		++cnt;
// 	data->envp = (char **)malloc(sizeof(char *) * (cnt + 1));
// 	i = 0;
// 	while (i < cnt)
// 	{
// 		data->envp[i] = ft_strdup(envp[i]);
// 		++i;
// 	}
// 	data->envp[cnt] = NULL;
// }
