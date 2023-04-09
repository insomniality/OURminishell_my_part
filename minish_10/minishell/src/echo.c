/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
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

void	echo(char *text)
{
	int	is_minus_n;

	is_minus_n = 0;
	if (!text || 0 == ft_strlen(text))
	{
		printf("\n");
	}
	else
	{
		if (ft_strlen(text) >= 2)
		{
			if ('-' == text[0] && 'n' == text[1])
				is_minus_n = 1;
		}
		printf("%s", text);
		if (!is_minus_n)
			printf("\n");
	}
}
