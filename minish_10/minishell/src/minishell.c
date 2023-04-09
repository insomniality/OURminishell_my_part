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
// #include <readline.h>
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
	while (spl[i] != NULL)
		free(spl[i++]);
	free(spl);
}

char	*pipfin(char *t) // xujuja grats; heto parzecnel; "pwd |    " senc depq; SARQI ERROR!!!!!!
{
	char	*eef;
	char	*txt;
	char	*txt2;
	char	*txt3;
	
	// petq chi
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
	// while (1)
	// {
	// 	// historium kextotna mnum, bayc ste maqrum em strtrim-ov returni vaxt; het dzem? (xosqi "pwd |    "-n sargum em "pwd |")
	// 	// vorosheci kextot toghnem (aka txt-in join aneluc eef-@ chem ta)
	// 	eef = ft_strtrim(txt, " "); //!!!!!! karelia tab, enter tenc baner avelacnel; miat heto irakani het khamemeates
	// 	if (eef[ft_strlen(eef) - 1] == '|')
	// 	{
	// 		free(eef);
	// 		free(txt);
	// 		ft_putstr_fd("Err: You must input somthing after pipe\n", 2);
	// 		// exit(1);
	// 		return (NULL);

	// 		/*
	// 		return (ft_strdup(t));

	// 		txt3 = readline("> ");
	// 		while (*txt3 == '\0')
	// 		{
	// 			free(txt3);
	// 			txt3 = readline("> ");
	// 		}
	// 		txt2 = ft_strtrim(txt3, " "); // txt2-@ stegh txt3-i maqur tarberakna
	// 		// free(txt3);
	// 		if (txt2[ft_strlen(txt2) - 1] == '|')
	// 		{
	// 			// karelia rekursiv
	// 			free(txt2);
				
	// 			txt2 = ft_strjoin(txt, txt3);
	// 			free(txt);
	// 			txt = txt2;
	// 			txt2 = NULL;

	// 			free(eef);
	// 			free(txt3);
	// 			continue ;
	// 		}
	// 		else
	// 		{
	// 			// printf("CONT_ =>'%s'\n", txt);
	// 			free(txt2);
	// 			// free(txt3);
	// 		}
	// 		break ;
	// 		*/
	// 	}
	// 	else
	// 	{
	// 		free(eef);
	// 		return (txt);
	// 	}
	// }
	// txt2 = ft_strjoin(eef, txt3);
	// free(txt);
	// txt = txt2;
	// // txt2 = NULL;
	// free(txt3);
	
	// free(eef);

	// // printf("\n%s\n", txt);
	// return (txt);
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
		t_glob->errstat = WEXITSTATUS(status);
	else if(WIFSIGNALED(status))
	{
		t_glob->errstat = 128 + WTERMSIG(status);
		if (t_glob->errstat == 130)
			ft_putstr_fd( "\n", 2);
		else if (t_glob->errstat == 131)
			ft_putstr_fd( "Quit: 3\n", 2); 
	}
	else
		t_glob->errstat = status;
	// ft_putnbr_fd(status, 2);
	// ft_putstr_fd("\t", 2);
	// ft_putnbr_fd(t_glob->errstat, 2);
	// ft_putstr_fd("\n", 2);
}

int	is_builtin(char *s, char *arg, t_data *data)
{
	int	i;

	i = 0;
	if(ft_memcmp(s, "echo", ft_strlen("echo")) == 0 && ft_strlen(s) == ft_strlen("echo"))
	{
		echo(arg); // echo TEXT
		i = 1;
	}
	else if(ft_memcmp(s, "cd", ft_strlen("cd")) == 0 && ft_strlen(s) == ft_strlen("cd"))
	{
		cd(arg, data->envp); //cd TEXT //
		i = 1;
	}
	else if(ft_memcmp(s, "pwd", ft_strlen("pwd")) == 0 && ft_strlen(s) == ft_strlen("pwd"))
	{
		printf("Bareeeev\n");
		pwd(data->envp);
		printf("Veeeeebar\n");
		i = 1;
	}
	else if(ft_memcmp(s, "export", ft_strlen("export")) == 0 && ft_strlen(s) == ft_strlen("export"))
	{
		export(arg, data); // export TEXT
		i = 1;
	}
	else if(ft_memcmp(s, "unset", ft_strlen("unset")) == 0 && ft_strlen(s) == ft_strlen("unset"))
	{
		// unset();
		i = 1;
	}
	else if(ft_memcmp(s, "env", ft_strlen("env")) == 0 && ft_strlen(s) == ft_strlen("env"))
	{
		env((const char **)data->envp);
		i = 1;
	}
	else if(ft_memcmp(s, "exit", ft_strlen("exit")) == 0 && ft_strlen(s) == ft_strlen("exit"))
	{
		//exit();
		i = 1;
	}
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
	fd = malloc(sizeof(int *) * (pipn + 1));
	fd[pipn] = NULL;
	while (i < pipn)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2); // miat aravot@ dziiiii
		pipe(fd[i++]);
	}
	pid = malloc(sizeof(int) * (pipn + 2));
	pid[pipn + 1] = -7; // NULL-i depqum inq@ tiva haskanum. Dra hamar bacasakan tvov em verj@ cuc talis, qanzi pid@ bacasakan chi kara lini.
	
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
			m_argv = split2(txt2, " 	");
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
	while (j <= pipn) // 1 pipe-i case-@ mtatsi; 0-n petq chi vortev iran 0 chenq talu (for now)
	{
		/*
		// t_red[j] = (t_red *)malloc(sizeof(t_red));
		// (t_red[j])->hdoc = ft_strjoin();

		// txt2 = txt;
		// i = 0;
		// if (ft_strchr(txt, '|') != NULL)
		// {
		// 	while (txt2 != NULL && &txt2[i] != ft_strchr(txt2, '|'))
		// 		i++;
		// 	txt2 = ft_substr(txt2, 0, i);  // "asdf    " "asdf"
		// }
		// else
		// {
		// 	while (txt2 != NULL && c_check(txt2, i, " 	")) 
		// 		i++;
		// 	txt2 = ft_substr(txt2, i, i + ft_strlen(txt2)); // "dd" "    dd" // "dd      "
		// }
		// i = 0;
		// while (!c_check(txt2, i, " 	") && txt2[i])
		// 	i++;
		// if (txt2[i] == '\0')
		// 	m_argv = split_fk(txt2, " 	");
		// else
		// 	m_argv = split2(txt2, " 	");
		// free(txt2);

		// lowerc(&m_argv);

		// t_glob->t_cmnds->cmd[j] = ft_strdup(m_argv[0]);

		// printf("nya=%s\n", t_glob->t_cmnds->cmd[j]);
		*/
		pid[j] = fork();
		if (pid[j] == 0)
		{
			if (j != pipn) // baci verjinic
				dup2(fd[(j + 1) % pipn][1], STDOUT_FILENO); // write
			if (j != 0) // baci arajinic
				dup2(fd[j % pipn][0], STDIN_FILENO); // read
			i = 0;
			while (i < pipn * 2)
			{
				close(fd[i / 2][i % 2]);
				close(fd[i / 2][(i + 1) % 2]);
				i++;
			}
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			
			// ft_putstr_fd(t_glob->t_cmnds[j].cmd[0], 2);
			// write(2, "+\n", 2);
			if (!(is_builtin(t_glob->t_cmnds[j].cmd[0], t_glob->t_cmnds[j].cmd[0], t_glob))) // ??/, ka pipe, te che, ete chka nor ashxati? (aysinqn built-in@ verjinna)?????
			{
				search(&(t_glob->t_cmnds[j].cmd[0]), getenv("PATH"));
				execve(t_glob->t_cmnds[j].cmd[0], t_glob->t_cmnds[j].cmd, NULL);
			}
			// #ESTEGHFREE?
			exit(1); // stex execve ka; hetevabar petq chi child-um free anel m_argv-n
		}
		// if (j != pipn) // baci verjinic
		// {
		// 	txt2 = txt;
		// 	txt = ft_strdup(ft_strchr(txt, '|') + 1);
		// 	free(txt2);
		// }
		free_ar((void **)t_glob->t_cmnds[j].cmd); // !!!
		j++;
	}
	i = 0;
	while (i < pipn * 2)
	{
		close(fd[i / 2][i % 2]);
		close(fd[i / 2][(i + 1) % 2]);
		i++;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	i = 0;
	while (pid[i] != -7)
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
	// rl_replace_line("", 0); //
	rl_redisplay();
	t_glob->errstat = 1;
}

void define_signals()
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	main2(int *i, char **txt, char ***m_argv, pid_t *pid)
{
	char *txt2;

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
		*m_argv = split2(txt2, " 	");

	lowerc(&(*m_argv));

	t_glob->t_cmnds->cmd = *m_argv;

	*m_argv = NULL;
	free(txt2);
	if (!(is_builtin(t_glob->t_cmnds->cmd[0], t_glob->t_cmnds->cmd[1], t_glob)))
		*pid = fork();
	if (*pid == 0)
	{
		search(&(t_glob->t_cmnds->cmd[0]), getenv("PATH"));
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		// if(builin chi)
			execve(t_glob->t_cmnds->cmd[0], t_glob->t_cmnds->cmd, NULL); // stex execve ka; hetevabar petq chi child-um free anel m_argv-n
		// else
			// builtin
		exit(1);
	}
	free_ar((void **)t_glob->t_cmnds->cmd);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	my_waitpid(*pid);
	define_signals();
	free(t_glob->t_cmnds);
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
	t_glob->errstat = 0;
	fill_env(envp, t_glob);

	// t_glob->t_cmnds = (t_cmds *)malloc(sizeof(t_cmds));
	// t_glob->t_cmnds->inp = 0;
	// t_glob->t_cmnds->out = 1;

	define_signals();
	while (1)
	{
		txt = readline("minishell ");
		if (!txt)
			break ;
		if (validornot(txt) == 0)
		{
			free(txt);
			continue ;
		}
		add_history(txt); // validiz verev? vor "				" depqn el history-i mej grvi
		if (ft_strchr(txt, '|') != NULL) // lav parsh arats chi; orinak ete '|'-n chakertneri meja etc.
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

	ft_putendl_fd("exit", 2);
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
