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

void	pwd(char **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && ENOENT == errno)
	{
		cwd = get_env("PWD", env);
	}
	printf("%s\n", cwd);
	free(cwd);
}
