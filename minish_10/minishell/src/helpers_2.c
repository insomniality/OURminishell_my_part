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

//pastoren "" es haskanum ei vorpes arandzin argument

#include "../libft/libft.h"
#include "src.h"


int ft_arrlen(void *arr, int typsz)
{
	int	i;

	i = 0;
	while (arr + (i * typsz) != NULL)
		i++;
	return (i);
}

int ft_strchr_indx(const char *s, int c)
{
	int		i;
	char	*a;

	i = 0;
	a = ft_strchr(s, c);
	if (a == NULL)
		return (-1);
	while (&(s[i]) != a)
		i++;
	return (i);
}

int	ft_chrcnt(char *str, char chr)
{
	int		i;
	int		j;
	char	a;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		a = str[i];
		if (a == '\'' || a == '\"')
		{
			i++;
			while (str[i] && str[i] != a)
				i++;
		}
		else if (a == chr)
			j++;
		i++;
	}
	return (j);
}

char	*pipfin(char *t) // xujuja grats; heto parzecnel; "pwd |    " senc depq; SARQI ERROR!!!!!!
{
	char	*eef;
	char	*txt;
	char	*txt2;
	char	*txt3;
	
	txt = ft_strdup(t); // miamit funkciaic drsin@ vor free chanem	
	eef = ft_strtrim(txt, " "); //!!!!!! karelia tab, enter tenc baner avelacnel; miat heto irakani het khamemeates
	if (eef[ft_strlen(eef) - 1] == '|')
	{
		free(eef);
		free(txt);
		ft_putstr_fd("Err: You must input somthing after pipe\n", 2);
		// exit(1);
		return (NULL);
	}
	else
	{
		free(eef);
		return (txt);
	}
}
