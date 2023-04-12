/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikarzum <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:01:05 by mikarzum          #+#    #+#             */
/*   Updated: 2023/02/10 19:01:10 by mikarzum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// LEAKS!!!
// PARCING!!!
// Change printf to ft_printf
// -1 errorneri depq@ chem grel

//parse ara vor chi kara pipe-ov sksi

// debugging
// gcc -g minishell.c libft/libft.a -lreadline -o minidb; lldb ./minidb

// grel en depq@ erb |-ic heto ban chka grats
// grel en depq@ erb |-ic heto |-a; miat tes irakan@ incha anum

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../inc/builtins.h"
#include <termios.h>
#include "../libft/libft.h"
#include "../inc/builtins.h"
#include "src.h"
# include <stdio.h>
// #include "split_fin2.c"

// t_data	*t_global;


int	ft_chrcnt(char *str, char chr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == chr)
			j++;
		i++;
	}
	// printf("Yep=%i\n",j);
	// j++;
	return (j);
}

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

void	free_ar(void **spl)
{
	int	i;

	i = 0;
	// printf("Mama_mia_%i;_%s\n",i, ((char **)spl)[0]);
	while (spl[i] != NULL)
	{
		free(spl[i++]);
	}
	free(spl);
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

void	lowerc(char ***m_argv)
{
	int	j;

	j = 0;
	while ((*m_argv)[0][j])
	{
		(*m_argv)[0][j] = ft_tolower((*m_argv)[0][j]);
		j++;
	}
}

char **split_fk(char *txt, char *c)
{
	char **a;
	int	x[2];

	if (!txt || !qt_check(txt) || ft_strlen(txt) == 0)
	{
		a = (char **)malloc(sizeof(char *) * 1);
		a[0] = NULL;
		return (a);
	}
	x[1] = 0;
	x[0] = ft_strlen(txt);
	a = (char **)malloc(sizeof(char *) * 2);
	a[0] = annihilator(txt, x, c);  // ft_strdup(txt);
	a[1] = NULL;

	// printf("HELlo;%s;\n", a[0]);
	return (a);
}

void	my_waitpid(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		t_glob->exit_status = WEXITSTATUS(status);
	else if(WIFSIGNALED(status))
	{
		t_glob->exit_status = 128 + WTERMSIG(status);
		if (t_glob->exit_status == 130)
			ft_putstr_fd( "\n", 2);
		else if (t_glob->exit_status == 131)
			ft_putstr_fd( "Quit: 3\n", 2); 
	}
	else
		t_glob->exit_status = status;
	// ft_putnbr_fd(status, 2);
	// ft_putstr_fd("\t", 2);
	// ft_putnbr_fd(t_glob->errstat, 2);
	// ft_putstr_fd("\n", 2);
}

void	builtin_exec(char *s, char **arg, t_data *data) // mi kanchi, zut stugi // arg
{
	char 	**dup;
	int		i;

	dup = get_argv(arg);
	if(ft_memcmp(s, "echo", ft_strlen("echo")) == 0 && ft_strlen(s) == ft_strlen("echo"))
		echo(dup, data); // echo TEXT
	else if(ft_memcmp(s, "cd", ft_strlen("cd")) == 0 && ft_strlen(s) == ft_strlen("cd"))
		cd(dup, data); //cd TEXT //
	else if(ft_memcmp(s, "pwd", ft_strlen("pwd")) == 0 && ft_strlen(s) == ft_strlen("pwd"))
	{
		printf("Mer Pwd\n");
		pwd(data);
	}
	else if(ft_memcmp(s, "export", ft_strlen("export")) == 0 && ft_strlen(s) == ft_strlen("export"))
		;// export(arg, data); // export TEXT
	else if(ft_memcmp(s, "unset", ft_strlen("unset")) == 0 && ft_strlen(s) == ft_strlen("unset"))
		; // unset();
	else if(ft_memcmp(s, "env", ft_strlen("env")) == 0 && ft_strlen(s) == ft_strlen("env"))
		env(data);
	else if(ft_memcmp(s, "exit", ft_strlen("exit")) == 0 && ft_strlen(s) == ft_strlen("exit"))
	{
		i = exit_for_prj(dup, data);
		free_ar((void **)dup);
		exit(i);
	}
	free_ar((void **)dup);
}

int	is_builtin(char *s, char *arg, t_data *data) // mi kanchi, zut stugi
{
	int	i;

	i = 0;
	if(ft_memcmp(s, "echo", ft_strlen("echo")) == 0 && ft_strlen(s) == ft_strlen("echo"))
		i = 1;
	else if(ft_memcmp(s, "cd", ft_strlen("cd")) == 0 && ft_strlen(s) == ft_strlen("cd"))
		i = 1;
	else if(ft_memcmp(s, "pwd", ft_strlen("pwd")) == 0 && ft_strlen(s) == ft_strlen("pwd"))
		i = 1;
	else if(ft_memcmp(s, "export", ft_strlen("export")) == 0 && ft_strlen(s) == ft_strlen("export"))
		i = 1;
	else if(ft_memcmp(s, "unset", ft_strlen("unset")) == 0 && ft_strlen(s) == ft_strlen("unset"))
		i = 1;
	else if(ft_memcmp(s, "env", ft_strlen("env")) == 0 && ft_strlen(s) == ft_strlen("env"))
		i = 1;
	else if(ft_memcmp(s, "exit", ft_strlen("exit")) == 0 && ft_strlen(s) == ft_strlen("exit"))
		i = 1;
	return (i);
}


void	*m_pipe(int pipn, char *txt) // ciklik chi (verjum chka pipe vor het ga main)
{
	int		i;
	int		j;
	char	*txt2;
	int		*pid;
	int		**fd;
	char	**m_argv;
	// t_red	**reds;

	t_glob->t_cmnds = (t_cmds *)malloc(sizeof(t_cmds) * (pipn + 1)); //commandneri qanakov enq malloc anum
	i = 0;
	while (i <= pipn)
	{
		t_glob->t_cmnds[i].inp = 0;
		t_glob->t_cmnds[i++].out = 1;
	}
	// t_glob->t_cmnds->cmd = (char **)malloc(sizeof(char *) * pipn + 1);
	// t_glob->t_cmnds->cmd[pipn] = NULL;
	
	txt2 = pipfin(txt); //zut sarqi vor error tpi
	free(txt);
	txt = txt2;
	i = 0; //////// Part1; txt is finalized by this point; leaks are managed(not cheacked for sure)
	fd = malloc(sizeof(int *) * (pipn + 1)); // + 3
	fd[pipn] = NULL; // + 2
	while (i < pipn)  // + 2
	{
		fd[i] = (int *)malloc(sizeof(int) * 2); // miat aravot@ dziiiii
		pipe(fd[i++]);
	}
	pid = malloc(sizeof(int) * (pipn + 1)); // + 2 araj
	// pid[pipn + 1] = -7; // NULL-i depqum inq@ tiva haskanum. Dra hamar bacasakan tvov em verj@ cuc talis, qanzi pid@ bacasakan chi kara lini.
	
	j = 0; ///////// Part2;
	while (j <= pipn)
	{
		txt2 = txt;
		i = 0;
		if (ft_strchr(txt, '|') != NULL)
		{
			while (txt2 != NULL && &txt2[i] != ft_strchr(txt2, '|'))
				i++;
			txt2 = ft_substr(txt2, 0, i);  // "asdf    " "asdf"
		}
		else
		{
			while (txt2 != NULL && c_check(txt2, i, " 	")) 
				i++;
			txt2 = ft_substr(txt2, i, i + ft_strlen(txt2)); // "dd" "    dd" // "dd      "
		}
		i = 0;
		while (!c_check(txt2, i, " 	") && txt2[i])
			i++;
		if (txt2[i] == '\0')
			m_argv = split_fk(txt2, " 	");
		else
			m_argv = split2(txt2, " 	", j);
		free(txt2);
		
		lowerc(&m_argv);

		t_glob->t_cmnds[j].cmd = m_argv;
		if (j != pipn) // baci verjinic
		{
			txt2 = txt;
			txt = ft_strdup(ft_strchr(txt, '|') + 1);
			free(txt2);
		}
		// free_ar((void **)m_argv); // !!!
		m_argv = NULL;
		j++;
	}
	
	j = 0;

	int	fdin = dup(0);
	int	fdout = dup(1);

	// int	fdout2 = dup(1);

	//skizb

	// if (j == 0)
	// {
	// 	if (t_glob->t_cmnds[j].inp != 0)
	// 		dup2(fdin, STDIN_FILENO);
	// }
	// else if (j == pipn)
	// {
	// 	if (t_glob->t_cmnds[j].out != 1)
	// 		dup2(fdout, STDOUT_FILENO);	
	// }
	

	while (j <= pipn) // 1 pipe-i case-@ mtatsi; 0-n petq chi vortev iran 0 chenq talu (for now)
	{
		pid[j] = fork();
		if (pid[j] == 0)
		{
			if (t_glob->t_cmnds[j].inp == -1 || t_glob->t_cmnds[j].out == -1) // || t_glob->t_cmnds[0].out < -1
				exit (1);
				
				// if (j == 0)
				// {
				// 	if (t_glob->t_cmnds[j].inp != 0)
				// 		dup2(fdin, STDIN_FILENO);
				// }
				// else if (j == pipn)
				// {
				// 	if (t_glob->t_cmnds[j].out != 1)
				// 		dup2(fdout, 1);	
				// }
			if (j == pipn && t_glob->t_cmnds[j].out == 1)
				dup2(fdout, 1);	
			else if (t_glob->t_cmnds[j].out != 1)
				dup2(t_glob->t_cmnds[j].out, STDOUT_FILENO);
			else if (j != pipn) // baci verjinic
				dup2(fd[j][1], STDOUT_FILENO); // write
			if (j == 0 && t_glob->t_cmnds[j].inp == 0)
				dup2(fdin, STDIN_FILENO);
			else if (t_glob->t_cmnds[j].inp != 0)
				dup2(t_glob->t_cmnds[j].inp, 0);
			else if (j != 0) // baci arajinic
				dup2(fd[j - 1][0], STDIN_FILENO); // read

			i = 0;
			while (i < pipn) // pipn * 2
			{
					close(fd[i][1]);
					close(fd[i][0]);
				i++;
			}
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (!(is_builtin(t_glob->t_cmnds[j].cmd[0], t_glob->t_cmnds[j].cmd[0], t_glob))) // ??/, ka pipe, te che, ete chka nor ashxati? (aysinqn built-in@ verjinna)?????
			{
				search(&(t_glob->t_cmnds[j].cmd[0]), getenv("PATH"));
				execve(t_glob->t_cmnds[j].cmd[0], t_glob->t_cmnds[j].cmd, 0);
			}
			else
				builtin_exec(t_glob->t_cmnds[j].cmd[0], t_glob->t_cmnds[j].cmd, t_glob);
			exit(1); // stex execve ka; hetevabar petq chi child-um free anel m_argv-n
		}
		free_ar((void **)t_glob->t_cmnds[j].cmd); // !!!
		j++;
	}

	i = 0;
	while (i < pipn)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		// if (t_glob->t_cmnds[i].inp != 0)
		// 	close(t_glob->t_cmnds[i].inp);
		// if (t_glob->t_cmnds[i].out != 1)
		// 	close(t_glob->t_cmnds[i].out);	
		
		// close(fd[i / 2][i % 2]);
		// close(fd[i / 2][(i + 1) % 2]);
		// if (i % 2 != 1 && t_glob->t_cmnds[i / 2].inp != 0)
			// close (t_glob->t_cmnds[i].inp);
		// if (i % 2 != 1 && t_glob->t_cmnds[i / 2].out != 1)
			// close (t_glob->t_cmnds[i].out);
		i++;
	}

	i = 0;
	// printf("aaaaaaaaa\n");

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	i = 0;
	while (i < pipn + 1)
		my_waitpid(pid[i++]);
	define_signals();
	free(txt);
	free(pid);
	free_ar((void **)fd);

	free(t_glob->t_cmnds); // VORTEV METS MALLOCA 1 hat vori mej sagh kan

	return (NULL); // inch vor uzenq
}

int		validornot(char *txt)
{
	int		i;
	char	*a;

	if (*txt == '\0')
		return (0);
	i = 0;
	while (txt[i] == ' ' || txt[i] == '	') // tab-@ vayte chesel kara input anes; indz tvuma signala dra hamar
		i++;
	if (txt[i] == '\0')
		return (0);
	a = pipfin(txt);
	if (a == NULL)
		return (0);
	else
		free(a);
	if(qt_check(txt) == 0)
		return (0);
	return (1);
}

void ignore_symbols(void)
{
	struct termios new_settings;

	if (tcgetattr(0, &new_settings))
		perror("minishell: tcsetattr");
	new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_settings))
		perror("minishell: tcsetattr");
}

void reprompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	ignore_symbols();
	rl_replace_line("", 0); //
	rl_redisplay();
	t_glob->exit_status = 1;
}

void	define_signals()
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	main2(int *i, char **txt, char ***m_argv, pid_t *pid)
{
	char	*txt2;
	int		fblt;

	int		out;

	out = dup(1);
	
	*pid = 0;
	t_glob->t_cmnds = (t_cmds *)malloc(sizeof(t_cmds)); //commandneri qanakov enq malloc anum
	t_glob->t_cmnds->inp = 0;
	t_glob->t_cmnds->out = 1;
	// t_glob->t_cmnds->cmd = (char **)malloc(sizeof(char *) * 2);
	// t_glob->t_cmnds->cmd[1] = NULL;

	*(i) = 0;
	while (*txt != NULL && c_check(*txt, *i, " 	")) 
		*(i) += 1;
	txt2 = ft_substr(*txt, *i, *(i) + ft_strlen(*txt)); // "dd" "    dd" // "dd      "
	*(i) = 0;
	while (!c_check(txt2, *i, " 	") && (txt2)[*i])
		*(i) += 1;
	if ((txt2)[*i] == '\0')
		*m_argv = split_fk(txt2, " 	");
	else
		*m_argv = split2(txt2, " 	", 0);

	lowerc(&(*m_argv));

	t_glob->t_cmnds->cmd = *m_argv;

	*m_argv = NULL;
	free(txt2);
	fblt = is_builtin(t_glob->t_cmnds->cmd[0], t_glob->t_cmnds->cmd[1], t_glob);
	if (fblt == 0)
		*pid = fork();
	if (*pid == 0)
	{
		if (t_glob->t_cmnds[0].inp == -1 || t_glob->t_cmnds[0].out == -1) // || t_glob->t_cmnds[0].out < -1
			exit (1);
		if (t_glob->t_cmnds[0].inp != 0)
			dup2(t_glob->t_cmnds[0].inp, 0);
		if (t_glob->t_cmnds[0].out != 1)
			dup2(t_glob->t_cmnds[0].out, 1);;
		if (fblt == 1)
		{
			builtin_exec(t_glob->t_cmnds->cmd[0], t_glob->t_cmnds->cmd, t_glob);
			dup2(out, 1);
		}
		search(&(t_glob->t_cmnds->cmd[0]), getenv("PATH"));
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (fblt == 0)
		{
			execve(t_glob->t_cmnds->cmd[0], t_glob->t_cmnds->cmd, NULL); // stex execve ka; hetevabar petq chi child-um free anel m_argv-n
			printf("cmd not found\n");
			exit(1);
		}
	}
	if (t_glob->t_cmnds[0].inp != 0)
		close (t_glob->t_cmnds[0].inp);
	if (t_glob->t_cmnds[0].out != 1)
		close (t_glob->t_cmnds[0].out);
	close(out);

	free_ar((void **)t_glob->t_cmnds->cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	my_waitpid(*pid);
	define_signals();
	free(t_glob->t_cmnds);
}

int	ispipe(char *s)
{
	int		i;
	char	a;

	i = 0;

	while (s[i] && s[i] != '|')
	{
		a = s[i];
		if (a == '\'' || a == '\"')
		{
			i++;
			while (s[i] != a)
				i++;
		}
		i++;
	}
	if(s[i] && s[i] == '|')
		return (1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	// t_data	*data;
	// data = (t_data *)malloc(sizeof(t_data));

	pid_t	pid;
	char	*txt;
	char	**m_argv;
	int		i;

	t_glob = (t_data *)malloc(sizeof(t_data));
	t_glob->exit_status = 0;
	fill_env(envp, &t_glob);
	// printf("%s_%s\n", envp[0] , (t_glob->envp)[0]); // , (t_glob->envp)[0]

	// t_glob->t_cmnds = (t_cmds *)malloc(sizeof(t_cmds));
	// t_glob->t_cmnds->inp = 0;
	// t_glob->t_cmnds->out = 1;

	define_signals();
	while (1)
	{
		i = 0; // havai
		i++; // havai
		txt = readline("minishell ");
		if (!txt)
		{
			// printf("minishell fdgcgvhbjnm%s\n", txt);
			break ;
		}
		if (validornot(txt) == 0)
		{
			free(txt);
			continue ;
		}
		add_history(txt); // validiz verev? vor "				" depqn el history-i mej grvi
		if (ispipe(txt)) // lav parsh arats chi; orinak ete '|'-n chakertneri meja etc.
		{
			m_pipe(ft_chrcnt(txt, '|'), txt);
			continue ;
		}
		else
			main2(&i, &txt, &m_argv, &pid);
		free(txt);
	}

	// + HIMA AMEN TEGH VORTEGH HNARAVORA EXIT LINI PITI FREE ANEM SAGH????????
	free_ar((void **)t_glob->envp);
	free(t_glob);

	// while (1)
	// {
	// 	/* code */
	// }
	
	//ft_putendl_fd("exit", 2);
	return (0);
}

// /sbin/ping -c 5 google.com | /usr/bin/wc -l; use "which commandName" in terminal to know where commands store

// for (int u = 0; m_argv[u] != NULL; u++)
// {
// 	ft_putnbr_fd(u, 2);
// 	write(2, "{", 1);
// 	write(2, m_argv[u], ft_strlen(m_argv[u]));
// 	write(2, "}", 1);
// 	write(2, "\n", 1);
// }
