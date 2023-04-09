/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 20:43:50 by mavardan          #+#    #+#             */
/*   Updated: 2023/03/08 21:26:06 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/builtins.h"

void	fill_env(char **envp, t_data *data)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (envp && envp[cnt])
		++cnt;
	data->envp = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!data->envp)
	{
		perror("data->env");
		return ;
	}
	i = 0;
	while (i < cnt)
	{
		data->envp[i] = ft_strdup(envp[i]);
		++i;
	}
	data->envp[cnt] = NULL;
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_data	*data;
// 	data = (t_data *)malloc(sizeof(t_data));
// 	fill_env(envp, data);
// 	int k = 0;
// 	while (k != 5)
// 	{
// 		pwd(data->envp);
// 		scanf("%d", &k);
// 	}
// 	return (0);
// }
