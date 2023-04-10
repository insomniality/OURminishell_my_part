/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:01:05 by mikarzum          #+#    #+#             */
/*   Updated: 2023/02/10 19:01:10 by mikarzum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "src.h"

void	search(char **name, char *pth) // pwd; /pwd; ./pwd; errori depqum ughaki ban chi poxum(anum); pth = getenv();
{
	char	**pts;
	int		i;
	char	*buf1;
	char	*buf2;

	// write(2, "=>", 1);
	// write(2, *name, ft_strlen(*name));
	// write(2, ";\n", 1);

	if ((*name)[0] && (*name)[0] == '.' && (*name)[1] && (*name)[1] == '/')
		pts = split_fk(*name, " 	");
	else
		pts = ft_split(pth, ':');
	
	i = 0;
	while (pts[i] != NULL)
	{
		if ((*name)[0] && (*name)[0] != '/')
		{
			buf1 = ft_strjoin(pts[i], "/");
			buf2 = ft_strjoin(buf1, *name);
			free(buf1);
		}
		else
			buf2 = ft_strdup(*name);
		
		if (access(buf2, X_OK) == 0)
		{
			free(buf2);
			break ;
		}
		free(buf2);
		i++;
	}
	if(pts[i] != NULL)
	{
		if ((*name)[0] && (*name)[0] != '/')
		{
			buf1 = ft_strjoin(pts[i], "/");
			buf2 = ft_strjoin(buf1, *name);
			free(buf1);
		}
		else
			buf2 = ft_strdup(*name);
		free(*name);
		*name = ft_strdup(buf2);
		free(buf2);
	}
	else if (pts[i] == NULL)
	{
		ft_putstr_fd("-bash: ", 2);
		ft_putstr_fd(*name, 2);
		ft_putstr_fd(": command not found\n", 2);
		//printf("exiteedddd\n");
		// t_glob->errstat = 127;
		exit(127);
	}
	free_ar((void **)pts);
	// errori depqum ughaki ban chi poxum(anum)
}