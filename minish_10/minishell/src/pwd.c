/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:00:56 by mavardan          #+#    #+#             */
/*   Updated: 2023/04/03 20:01:53 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../inc/builtins.h"
#include "../libft/libft.h"

void	pwd(char **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && ENOENT == errno)
	{
		cwd = get_env("PWD", env);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	// printf("%s\n", cwd);
	free(cwd);
}
