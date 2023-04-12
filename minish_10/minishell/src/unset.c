/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:03:46 by mavardan          #+#    #+#             */
/*   Updated: 2023/04/05 20:53:43 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/builtins.h"
#include "../libft/libft.h"

int	unset(char *env_var, t_data *data)
{
	char	**envp;
	char	**envp_new;
	int		len;
	int		i;
	int		pos;
	int		j;

	envp = data->envp;
	pos = get_env_var_pos_by_name(env_var, envp);
	if (-1 != pos)
	{
		len = envp_len(envp);
		envp_new = (char **)malloc(sizeof(char *) * (len - 1));
		if (!envp_new)
		{
			perror("unset envp_new");
			return (-1);
		}
		i = 0;
		j = 0;
		while (i < len - 1)
		{
			if (i != pos)
				envp_new[j++] = ft_strdup(envp[i]);
			++i;
		}
		envp_new[len - 2] = NULL;
		ft_free(envp, envp_len(envp));
		data->envp = envp_new;
		return (0);
	}
	return (1);
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
//
//
//int main(int argc, char **argv, char **envp)
//{
//	t_data	*data;
//	data = (t_data *)malloc(sizeof(t_data));
//	fill_env(envp, data);
////	env(data->envp);
//	printf("\n-------------- MAIN unset 1 ----------------\n");
//	//printf("----- main export 1, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	export("mmm=nmbmnbnm", data);
//	export("mmm2=5456454", data);
//	env(data->envp);
//	//printf("----- main export 1, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	printf("\n\n------------ MAIN unset 2 -----------------\n");
//	unset("mmm", data);
//	//printf("----- main export 2, envp = %p, data->envp[0] = %s, len = %d\n", data->envp, data->envp[0], envp_len(data->envp));
//	//export("mmm=22222222222nmbmnbnm", data);
//	env(data->envp);
//	return (0);
//}
