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

// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

/* void	redir(char const *s, char *c, int *x, int cmdi)
{
	char	*r;
	char	*fname;
	char	*fn;
	int		fstrt;
	int		fd;
	int		_x[2];

	x[0] = x[1];
	x[0]++;
	if (s[x[0]] == '>' || s[x[0]] == '<')
		x[0]++;
	while (c_check(s, x[0], c)) // s[x[0]] && // petqa?
		x[0]++;
	if (s[x[0]] == '>' || s[x[0]] == '<')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(s[x[0]], 2);
		ft_putstr_fd("\'\n", 2);
		// u exit ~
	}
	
	fstrt = x[0];
	while (s[x[0]] && !c_check(s, x[0], c))
		x[0]++;

	fname = ft_substr(s, fstrt, x[0] - fstrt);
	_x[0] = ft_strlen(fname);
	_x[1] = 0;
	fn = fname;
	fname = annihilator(fn, _x, c);
	free(fn);
	r = ft_substr(s, x[1], x[0] - x[1]); // ">     <      file1  "
	if (s[x[1]] != '\0' && s[x[1]] == '>' && s[x[1] + 1] != '>')
	{
		fd = open(fname, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (t_glob->t_cmnds[cmdi].out != 1)
			close(t_glob->t_cmnds[cmdi].out);
		t_glob->t_cmnds[cmdi].out = fd;
	}
	if (s[x[1]] != '\0' && s[x[1]] == '>' && s[x[1] + 1] == '>')
	{
		fd = open(fname, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (t_glob->t_cmnds[cmdi].out != 1)
			close(t_glob->t_cmnds[cmdi].out);
		t_glob->t_cmnds[cmdi].out = fd;
	}
	if (s[x[1]] != '\0' && s[x[1]] == '<' && s[x[1] + 1] != '<')
	{
		fd = open(fname, O_RDONLY, 0644);
		if (t_glob->t_cmnds[cmdi].inp != 0)
			close(t_glob->t_cmnds[cmdi].inp);
		t_glob->t_cmnds[cmdi].inp = fd;
	}
	if (s[x[1]] != '\0' && s[x[1]] == '<' && s[x[1] + 1] == '<')
	{
		// code 
	}	
	if (t_glob->t_cmnds[cmdi].inp == -1 || t_glob->t_cmnds[cmdi].out == -1) // || t_glob->t_cmnds[0].out < -1
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(fname, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	free(r);
	free(fname);
} */

// void	m_than(char *s, char *filnm, int i)
// {
// 	char a;
// 	int fd;

// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		fd = open(filnm, O_CREAT | O_RDWR);
// 	else if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] != '>')
// 		fd = open(filnm, O_CREAT | O_TRUNC | O_RDWR);
// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		while (read(fd, &a, 1) != 0)
// 			;
// 	write(fd, c, strlen(c));
// 	close(fd);
// }

// int main() //int argc, char **argv, char **envp
// {
// 	char a;
// 	int fd;
// 	char c[] = "mmaakm";

// 	int i = 0;
// 	char s[] = ">>";

// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		fd = open("qarerku.txt", O_CREAT | O_RDWR);
// 	else if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] != '>')
// 		fd = open("qarerku.txt", O_CREAT | O_TRUNC | O_RDWR);
// 	if (s[i] == '>' && strlen(s) - 1 > i && s[i + 1] == '>')
// 		while (read(fd, &a, 1) != 0)
// 			;
// 	write(fd, c, strlen(c));
// 	close(fd);
// }
