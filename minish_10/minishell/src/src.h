/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <mikarzum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:05:40 by mikarzum          #+#    #+#             */
/*   Updated: 2022/08/09 18:43:44 by mikarzum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H

// #define QUOT1 '\''
// #define QUOT2 '\"'

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <fcntl.h>
#include <string.h>
# include "../inc/builtins.h"

int		ft_strchr_indx(const char *s, int c);
char	**split2(char const *s, char *c, int cmdi);
void	define_signals();
int		c_check(char const *s, int idx, char *c);
void	free_ar(void **spl);
void	search(char **name, char *pth);
char	**split_fk(char *txt, char *c);
int		qt_check(char const *s);
int		c_check(char const *s, int idx, char *c);
void	envqt(char *c, char **ddy, int x);
void	envqt2(char *c, char *ddy);
char	*annihilator(char const *s, int *x, char *c);
void	annihenv(char **sm, char *c);
int		qt_strt(char const *s, int *x, char *c);
void	quoter(char const *s, char *cq, char **ddy, int *x);
int		_sp2(char const *s, int *x, char *c);
int		_pieces(char const *s, char *c);
void	redir(char const *s, char *c, int *x, int cmdi);


#endif
