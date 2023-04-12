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


void	envqt_p2(char **e, char **f, char **w, char **c)
{
	int	i;

	i = 1;
	if ((*e)[i] != '$')
		while ((*e)[i] && !c_check(*e, i, *c)) //  && (*e)[i] != '/"'
			i++;
	*e = ft_substr(*e, 1, i - 1);

	if ((ft_strlen(*e) == 1 && (*e)[0] == '?' && (*e)[1] == '\0')
	||  (ft_strlen(*e) > 1 && (*e)[0] == '?' && ((*e)[1] == ' ' || (*e)[2] == '\"'))) //ft_strncmp
		*w = ft_itoa(t_glob->exit_status);
	else if(getenv(*e) != NULL)
		*w = ft_strdup(getenv(*e)); //getenv-@ ches kara free anes !!!!!!!!!!
	else if(getenv(*e) == NULL)
		*w = NULL;
	free(*e);
	if(*w != NULL)
		*e = ft_strdup(*w); // free chanes w-n shash (im het em)
	else
		*e = NULL;
}

void	envqt2_p2(char **e, char **f, char **w, char **c)
{
	int	i;

	i = 1;
	if ((*e)[i] != '$')
		while ((*e)[i] && !c_check(*e, i, *c) && (*e)[i] != '\"')
			i++;
	*e = ft_substr(*e, 1, i - 1);

	if ((ft_strlen(*e) == 1 && (*e)[0] == '?' && (*e)[1] == '\0')
	||  (ft_strlen(*e) > 1 && (*e)[0] == '?' && ((*e)[1] == ' ' || (*e)[2] == '\"'))) //ft_strncmp
		*w = ft_itoa(t_glob->exit_status);
	else if(getenv(*e) != NULL)
		*w = ft_strdup(getenv(*e)); //getenv-@ ches kara free anes !!!!!!!!!!
	else if(getenv(*e) == NULL)
		*w = NULL;
	free(*e);
	if(*w != NULL)
		*e = ft_strdup(*w); // free chanes w-n shash (im het em)
	else
		*e = NULL;
}

void	envqt_p3(char **e, char **f, char **w)
{
	*f = *w;
	if (*e != NULL)
	{
		*w = ft_strjoin(*f, *e);
		free(*f);
		free(*e);
	}
}

void	envqt(char *c, char **ddy, int x)
{
	char	*e;
	char	*f;
	char	*w;
	int		i;

	e = ft_strchr(ddy[x], '$');
	envqt_p2(&e, &f, &w, &c);
	i = 0;
	while (ddy[x][i] != '$')
		i++;
	if (w != NULL)
		free(w);
	w = ft_substr(ddy[x], 0, i); // skizb@
	envqt_p3(&e, &f, &w);
	if (ddy[x][++i] != '$')
		while (!c_check(ddy[x], i, c) && ddy[x][i])
			i++;
	e = ft_substr(ddy[x], i, ft_strlen(&ddy[x][i])); // e-n free chenq anum vortev cuca tali getenv()-i vra
	f = w;
	w = ft_strjoin(f, e);
	free(f);
	free(e);
	free(ddy[x]);
	ddy[x] = ft_strdup(w);
	free(w);
}

void	envqt2(char *c, char *ddy)
{
	char	*e;
	char	*f;
	char	*w;
	int		i;

	e = ft_strchr(ddy, '$');
	envqt2_p2(&e, &f, &w, &c);
	i = 0;
	while (ddy[i] != '$')
		i++;
	if (w != NULL)
		free(w);
	w = ft_substr(ddy, 0, i); // skizb@
	envqt_p3(&e, &f, &w);
	if (ddy[++i] != '$')
		while (!c_check(ddy, i, c) && ddy[i])
			i++;
	e = ft_substr(ddy, i, ft_strlen(&ddy[i])); // e-n free chenq anum vortev cuca tali getenv()-i vra
	f = w;
	w = ft_strjoin(f, e);
	free(f);
	free(e);
	free(ddy);
	ddy = ft_strdup(w);
	free(w);
}