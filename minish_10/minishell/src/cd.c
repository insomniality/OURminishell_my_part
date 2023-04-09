/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:03:46 by mavardan          #+#    #+#             */
/*   Updated: 2023/04/03 20:06:54 by mavardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/builtins.h"

int	cd(const char *new_path, char **envp)
{
	char	*buf;
	char	*old_path;
	int		len;

	buf = NULL;
	old_path = get_env("PWD", envp);
	if (!old_path)
		return (-1);
	if (0 == chdir(new_path))
	{
		update_env("PWD", getcwd(buf, 1), envp);
		update_env("OLDPWD", old_path, envp);
	}
	else
	{
		perror("cd");
		return (-1);
	}
	free(buf);
	free(old_path);
	return (0);
}
