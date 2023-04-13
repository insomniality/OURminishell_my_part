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
	return (a);
}
/*
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
			// printf("cmd not found\n");
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
*/
int main(int argc, char **argv, char **envp)
{
	char	*txt;

	t_glob = (t_data *)malloc(sizeof(t_data));
	t_glob->exit_status = 0;
	fill_env(envp, &t_glob);
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
		add_history(txt);
		if (ispipe(txt))
		{
			m_pipe(ft_chrcnt(txt, '|'), txt);
			continue ;
		}
		else
			main2(txt);
		free(txt);
	}
	free_ar((void **)t_glob->envp);
	free(t_glob);
}
