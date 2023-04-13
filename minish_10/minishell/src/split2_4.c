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

void	quoter(char const *s, char *cq, char **ddy, int *x)
{
	int *_i = &x[0];
	int *_j = &x[1];
	int *_k = &x[2];
	if (!(!(s[x[0]]) && c_check(s, x[0] - 1, cq)))
	{
		x[0] = _sp2(s, x, cq);
		ddy[x[2]++] = ft_substr(s, x[1], x[0] - x[1]);
		// printf("dh[%s]\n", ddy[x[2] - 1]);
		x[1] = x[0] + 1;
	}
	// x[0]++;
}

int	qt_strt(char const *s, int *x, char *c)
{
	int *_i = &x[0];
	int *_j = &x[1];
	int *_k = &x[2];
	
	if((s[x[0]] == '\'' || s[x[0]] == '\"')) // prabel chakerdi naxord@   && x[0] != 0;&& c_check(s, x[0] - 1, c)
	{
		x[1] = ++x[0];
		if (s[x[0] - 1] == '\'')
			while (s[x[0]] != '\0' && s[x[0]] != '\'')
				x[0]++;
		else if (s[x[0] - 1] == '\"')
			while (s[x[0]] != '\0' && s[x[0]] != '\"')
				x[0]++;
		else
			return (--x[0]);
	}
	else if((s[x[0]] == '\'' || s[x[0]] == '\"')) // nsahn chakerdi naxord@   && x[0] != 0;&& !c_check(s, x[0] - 1, c)
		return (x[0]);
	return (x[0]);
}

void	_pieces_p3(char const *s, int **i, char a, char *c)
{
	if (a == '>' || a == '<')
	{
		while (s[(**i)] && c_check(s, ++(**i), " 	><")) // s[++i] != a
			;
		if (s[(**i)])
			(**i)++;
		while (s[(**i)] && !c_check(s, (**i), " 	"))
			(**i)++;
	}
	else if (c_check(s, (**i)++, c))
		while (s[(**i)] && c_check(s, (**i), c))
			(**i)++;
}

void	_pieces_p2(char const *s, int *i, int *j, char *c)
{
	char	a;

	a = s[*i];
	if ( (((*i) == 0 && s[(*i)] && !c_check(s, (*i), " 	><")) 
	|| ((*i) != 0 && s[(*i)] && !c_check(s, (*i), "><") 
	&& c_check(s, (*i) - 1, " 	\"\'"))))
		(*j)++;
	if (a == '\"' || a == '\'')
	{
		while (s[++(*i)] != a)
			;
		(*i)++;
		(*j)++;
	}
	else
		_pieces_p3(s, &i, a, c);
}

int	_pieces(char const *s, char *c) // vrode arden chishta // V
{
	char	a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		_pieces_p2(s, &i, &j, c);
	return (j);
}
