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

// what if delimiterneri setum ' kam " em talis??

int	_sp1(char const *s, int *x, char *c) // araja gnum minchev prabel mabel chlini
{
	int *_i = &x[0];
	int *_j = &x[1];
	int *_k = &x[2];
	// while (s[x[0]] && x[0] - x[1] == 0 && s[x[0]] == c)
	while (s[x[0]] && (x[0] - x[1] == 0) && c_check(s, x[0], c)) // && s[x[0]] != '\'' && s[x[0]] != '\"'
	{
		x[0]++;
		x[1]++;
	}
	return (x[1]);
}

int	_sp2(char const *s, int *x, char *c)
{
	int *_i = &x[0];
	int *_j = &x[1];
	int *_k = &x[2];

	// while (!(c_check(s, x[0], c)) && s[x[0]]) // && (s[x[0]] != '\'') && (s[x[0]] != '\"')
	// 	x[0]++;
	while (s[x[0]] && !(c_check(s, x[0], c)))
	{
		while (s[x[0]] && !(c_check(s, x[0], c)) && s[x[0]] != '\'' && s[x[0]] != '\"') // && (s[x[0]] != '\'') && (s[x[0]] != '\"')
			x[0]++;
		if (s[x[0]] == '\'')
		{
			x[0]++;
			while (s[x[0]] && s[x[0]] != '\'') // && (s[x[0]] != '\'') && (s[x[0]] != '\"')
				x[0]++;
			x[0]++;
		}
		else if (s[x[0]] == '\"')
		{
			x[0]++;
			while (s[x[0]] && s[x[0]] != '\"') // && (s[x[0]] != '\'') && (s[x[0]] != '\"')
				x[0]++;
			x[0]++;
		}
	}
	return (x[0]);
}


void	_motor_p2(char const **s, char **c, char ***ddy, int **x)
{
	int *_i = &(*x)[0];
	int *_j = &(*x)[1];
	int *_k = &(*x)[2];

	if ((*s)[(*x)[0]] == '\'' || (*s)[(*x)[0]] == '\"')
	{
		(*x)[1] = _sp1(*s, *x, *c);
		if (!( !((*s)[(*x)[0]]) && c_check(*s, (*x)[0] - 1, *c)) )
		{
			(*x)[0] = qt_strt(*s, *x, *c);
			(*ddy)[(*x)[2]++] = ft_substr(*s, (*x)[1], (*x)[0] - (*x)[1]);
			if ((*s)[(*x)[0]] == '\"' && 
			ft_strchr((*ddy)[(*x)[2] - 1], '$') != NULL && 
			!c_check(ft_strchr((*ddy)[(*x)[2] - 1], '$'), 1, *c) && 
			ft_strlen((*ddy)[(*x)[2] - 1]) > 1) // qpq free u nor@ // "$" depq@ ba? #parse
				envqt(*c, *ddy, (*x)[2] - 1);
			(*x)[1] = (*x)[0] + 1;
		}
	}
}

char *annihilator(char const *s, int *x, char *c)//char **env
{
	char	*big;
	char	a;
	int		i;
	int		lup;
	int		strt;

	char	*sl;
	char	*sm;
	char	*sr;

	char	*gl;
	char	*gm;
	char	*gr;
	int		j;
	int		strtj;

	lup = 0;
	big = ft_substr(s, x[1], x[0] - x[1]);
	while (ft_strchr(&(big[lup]), '\'') != NULL || ft_strchr(&(big[lup]), '\"') != NULL)
	{
		if (ft_strchr(big, '\'') == NULL && ft_strchr(big, '\"') == NULL)
			return (big);
		i = 0;
		strt = 0;
		while (big[i] != '\'' && big[i] != '\"')
			i++;
		a = big[i];
		if (i != strt)
			sl = ft_substr(big, strt, i - strt);
		else
			sl = ft_strdup("");
		i++;
		strt = i;
		
		while (big[i] && big[i] != a)
			i++;
		if (i != strt)
			sm = ft_substr(big, strt, i - strt);
		else
			sm = ft_strdup("");;
		// envqt2(c, sm);
		if (a == '\"' && ft_strchr(sm, '$'))
		{
			j = 0;
			strtj = j;
			while (sm[j] && ft_strchr(sm, '$') != NULL)
			{
				j = 0;
				strtj = j;
				while (sm[j] != '$')
					j++;
				if (j == strtj) // == 0
					gl = ft_strdup("");
				else
					gl = ft_substr(sm, strtj, j);
				j++;
				strtj = j;
				while (sm[j] && !c_check(sm, j, c) && sm[j] != '$')//$PATH_ (ibr prabel)
					j++;
				if (j == strtj)// == 0
					gm = ft_strdup("");
				else
					gm = ft_substr(sm, strtj, j - 1);
				// gm = ft_substr(sm, strtj, j - 1);
				gr = gm;
				gm = getenv(gr);
				free(gr);
				// j++;
				strtj = j;
				while (sm[j]) //$PATH_ (ibr prabel) 
					j++;
				if (j == strtj) // == 0
					gr = ft_strdup("");
				else
					gr = ft_substr(sm, strtj, j);
				// gr = ft_substr(sm, strtj, j);
				free(sm);
				if(!gm)
					sm = ft_strjoin(gl, "");
				else
					sm = ft_strjoin(gl, gm);
				free(gl);
				gl = sm;
				// printf("quoted dollar $$$ == %s\n", gl);
				sm = ft_strjoin(gl, gr);
				free(gl);
				free(gr);
			}
		}
		//
		i++;
		strt = i;
		while (big[i])
			i++;
		if (i != strt)
			sr = ft_substr(big, strt, i - strt);
		else
			sr = ft_strdup("");
		free(big);
		big = ft_strjoin(sl, sm);
		free(sl);
		free(sm);
		lup = ft_strlen(big);
		sl = big;
		big = ft_strjoin(sl, sr);
		free(sl);
		free(sr);
	}
	// printf("quoted dollar $$$ == %s\n", big);
	return (big);
}

void	redir(char const *s, char *c, int *x)
{
	char	*r;
	char	*fname;
	int		fstrt;
	int		fd;

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
	r = ft_substr(s, x[1], x[0] - x[1]); // ">     <      file1  "

	if (s[x[1]] != '\0' && s[x[1]] == '>' && s[x[1] + 1] != '>')
	{
		fd = open(fname, O_CREAT | O_TRUNC | O_WRONLY);
		// write(fd, txt, strlen(txt));
		close(fd);
	}
	if (s[x[1]] != '\0' && s[x[1]] == '>' && s[x[1] + 1] == '>')
	{
		fd = open(fname, O_CREAT | O_APPEND | O_WRONLY);
		// while (read(fd, &a, 1) != 0)
		// 	;
		// write(fd, txt, strlen(txt)));
		close(fd);
	}
	if (s[x[1]] != '\0' && s[x[1]] == '<' && s[x[1] + 1] != '<')
	{
		fd = open(fname, O_TRUNC | O_RDONLY);
		close(fd);
	}
	if (s[x[1]] != '\0' && s[x[1]] == '<' && s[x[1] + 1] == '<')
	{
		/* code */
	}	

	// if ((x[0] != x[1] + 1) && (s[x[0]] == '>' || s[x[0]] == '<')) // qci error
	// {
	// 	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	// 	ft_putchar_fd(s[x[0]], 2);
	// 	ft_putstr_fd("\'\n", 2);
	// }
	free(r);
	free(fname);
	// t_glob->t_cmnds->out = fd;
}

void	_motor(char const *s, char *c, char **ddy, int *x)
{
	int *_i = &x[0];
	int *_j = &x[1];
	int *_k = &x[2];

	while (s[x[0]] && (x[0] <= ft_strlen((char *)s)) && (ft_strlen(s) != 0 || (!s[x[0]] && x[0] != x[1])))
	{
		// if (s[x[0]] && (c_check(s, x[0], c) || !(s[x[0]]) || ((s[x[0]] == '\'' || s[x[0]] == '\"') && x[0] - x[1] != 0))
		// || (!s[x[1]] && x[0] != x[1]) && s[x[1]] != '\0') // && s[x[1]] != '\0' // && s[x[0]] != '\'' && s[x[0]] != '\"'
		// if(s[x[0]] && !(s[x[0]] == '\'' || s[x[0]] == '\"')) // VTANGAVORA !!!!!!!!!!!!!!!!!!!!
		// {
			x[1] = _sp1(s, x, c);
			// if (s[x[1]] == '\'' || s[x[1]] == '\"' )
			// 	continue ;
			if (!( !(s[x[0]]) && c_check(s, x[0] - 1, c)) )
			{
				if (s[x[1]] == '>' || s[x[1]] == '<')
					redir(s, c, x);
				x[0] = _sp2(s, x, c);
				if (s[x[1]] != '>' && s[x[1]] != '<')
					ddy[x[2]++] = annihilator(s, x, c);
				// if ((s[x[0]] == '\'' && s[x[1]] != '\'') || (s[x[0]] == '\"' 
				// && s[x[1]] != '\"'))
				// {
				// 	x[1] = x[0];
				// 	continue ;
				// }
				// else
				x[1] = x[0] + 1;
			}
		// }
		// else
		// 	_motor_p2(&s, &c, &ddy, &x);

		// if (c_check(s, x[0], c))
		// 	x[1]++;
		x[0]++;
	}
}

char	**split2(char const *s, char *c)
{
	char			**ddy;
	int				x[3];

	if (!s || !qt_check(s) || ft_strlen(s) == 0)
	{
		ddy = (char **)malloc(sizeof(char *) * 1);
		ddy[0] = NULL;
		return (ddy);
	}
	x[0] = 0;
	x[1] = 0;
	x[2] = 0;
	ddy = (char **)malloc(sizeof(char *) * ((_pieces(s, c) + 1))); // POXEL PIECES@ vor redir@ hashvi charni
	_motor(s, c, ddy, x);
	ddy[x[2]] = NULL;
	x[0] = 0;
	// while (ddy[x[0]] != NULL) // !!!!!!! ES SAGH PETQA SPLIT ANELU @NTACQUM LINI  !!!!!!!!!!!!!!!
	// {
	// 	if (ddy[x[0]] && ft_strlen(ddy[x[0]]) > 1 && ddy[x[0]][0] == '$')
	// 		envqt(c, ddy, x[0]);
	// 	x[0]++;
	// }
	return (ddy);
}

// int main(int argc, char **argv, char **envp) // testing
// {
// 	int i = 0;
// 	// while(envp[i])
// 	// 	printf("%s|\n", envp[i++]);
// 	// char x[] = "\'Z a	V\'  x	b 	\"	M \" l	 	  ";
// 	char x[] = "\'\'v      az            v \' \" Z a	V  \" \'x \" M   ;$USER ; fff\" l	d	 	\"\"  \"\"";
// 	char **y = split2(x, " 	");
// 	i = 0;
// 	printf("\n");
// 	while(y[i])
// 		printf("%s|\n", y[i++]);
// }
// gcc ../libft/libft.a split_fin2.c; ./a.out