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

void	annihenv(char **sm, char *c)
{
	char	*gl;
	char	*gm;
	char	*gr;
	int		j;
	int		strtj;

	j = 0;
	strtj = j;
	while ((*sm)[j] && ft_strchr(&((*sm)[strtj]), '$') != NULL) // &(*sm)[strtj]
	{
		gm = NULL;
		j = strtj;
		// strtj = j;
		while ((*sm)[j] != '$')
			j++;
		if (j == 0) // == 0
			gl = ft_strdup("");
		else
			gl = ft_substr((*sm), 0, j);

		if (c_check((*sm), j + 1, " 	") || ((*sm)[j] && !(*sm)[j + 1]))
			gm = ft_strdup("$");

		j++;
		strtj = j;
		while ((*sm)[j] && !c_check((*sm), j, c) && (*sm)[j] != '$')//$PATH_ (ibr prabel)
			j++;
		if (gm == NULL)
		{
			if (j == strtj) // == 0
				gm = ft_strdup("");
			else
				gm = ft_substr((*sm), strtj, j - strtj);

			if ((ft_strlen(gm) == 1 && gm[0] == '?' && gm[1] == '\0')
			||  (ft_strlen(gm) > 1 && (gm)[0] == '?' && (gm[1] == ' ' || gm[2] == '\"'))) //ft_strncmp
			{
				free(gm);
				gm = ft_itoa(t_glob->errstat);
			}
			else
			{
				gr = gm;
				gm = ft_strjoin("", getenv(gr));
				free(gr);
			}
		}
		// gm = ft_substr((*sm), strtj, j - 1);
		// j++;
		strtj = j;
		while ((*sm)[j]) //$PATH_ (ibr prabel) 
			j++;
		if (j == strtj) // == 0
			gr = ft_strdup("");
		else
			gr = ft_substr((*sm), strtj, j - strtj);
		// gr = ft_substr((*sm), strtj, j);
		free((*sm));
		if(!gm)
			(*sm) = ft_strjoin(gl, "");
		else
			(*sm) = ft_strjoin(gl, gm);
		strtj = ft_strlen(*sm);
		j = strtj;
		free(gl);
		gl = (*sm);
		// printf("quoted dollar $$$ == %s\n", gl);
		(*sm) = ft_strjoin(gl, gr);
		free(gl);
		free(gr);
		if (gm != NULL)
			free(gm);
	}
}

char *annihilator(char const *s, int *x, char *c)//char **env
{
	char	*big;
	char	a;
	int		i;
	int		strt;
	char	*snt[3];

	// char	*sl;
	// char	*sm;
	// char	*sr;

	// char	*gl;
	// char	*gm;
	// char	*gr;
	// int		j;
	// int		strtj;

	i = 0;
	big = ft_substr(s, x[1], x[0] - x[1]);
	if (ft_strchr(&(big[i]), '\'') != NULL || ft_strchr(&(big[i]), '\"') != NULL)
	{
		while (ft_strchr(&(big[i]), '\'') != NULL || ft_strchr(&(big[i]), '\"') != NULL)
		{
			if (ft_strchr(big, '\'') == NULL && ft_strchr(big, '\"') == NULL)
				return (big);
			i = 0;
			strt = 0;
			while (big[i] != '\'' && big[i] != '\"')
				i++;
			a = big[i];
			if (i != strt)
				snt[0] = ft_substr(big, strt, i - strt);
			else
				snt[0] = ft_strdup("");
			i++;
			strt = i;
			
			while (big[i] && big[i] != a)
				i++;
			if (i != strt)
				snt[1] = ft_substr(big, strt, i - strt);
			else
				snt[1] = ft_strdup("");;
			// envqt2(c, snt[1]);
			if (a == '\"' && ft_strchr(snt[1], '$'))
				annihenv(&(snt[1]), c);
			//
			i++;
			strt = i;
			while (big[i])
				i++;
			if (i != strt)
				snt[2] = ft_substr(big, strt, i - strt);
			else
				snt[2] = ft_strdup("");
			free(big);
			big = ft_strjoin(snt[0], snt[1]);
			free(snt[0]);
			free(snt[1]);
			i = ft_strlen(big);
			snt[0] = big;
			big = ft_strjoin(snt[0], snt[2]);
			free(snt[0]);
			free(snt[2]);
		}
	}
	else if (ft_strchr(big, '$') != NULL)
		annihenv(&big, c);
	// printf("quoted dollar $$$ == %s\n", big);
	// if (ft_strchr(big, '$') != NULL)
	// 	annihenv(&big, c);
	return (big);
}

void	redir(char const *s, char *c, int *x, int cmdi)
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
		printf("%i\n", t_glob->t_cmnds[cmdi].out);
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
		/* code */
	}	
	if (t_glob->t_cmnds[cmdi].inp == -1 || t_glob->t_cmnds[cmdi].out == -1) // || t_glob->t_cmnds[0].out < -1
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(fname, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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

void	_motor(char const *s, char **ddy, int *x, int cmdi)
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
			x[1] = _sp1(s, x, " 	");
			// if (s[x[1]] == '\'' || s[x[1]] == '\"' )
			// 	continue ;
			if (!( !(s[x[0]]) && c_check(s, x[0] - 1, " 	")) )
			{
				if (s[x[1]] == '>' || s[x[1]] == '<')
					redir(s, " 	", x, cmdi);
				x[0] = _sp2(s, x, " 	");
				if (s[x[1]] != '>' && s[x[1]] != '<')
					ddy[x[2]++] = annihilator(s, x, " 	");
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

char	**split2(char const *s, char *c, int cmdi)
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
	_motor(s, ddy, x, cmdi);
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