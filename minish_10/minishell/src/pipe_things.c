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


void	m_pipe_p2(int pipn, char **txt, char **txt2, char ***m_argv)
{
	int	i;
	int	j;

	j = 0;
	while (j <= pipn)
	{
		m_pipe_p2_1(txt, txt2);
		i = 0;
		while (!c_check((*txt2), i, " 	") && (*txt2)[i])
			i++;
		if ((*txt2)[i] == '\0')
			(*m_argv) = split_fk((*txt2), " 	");
		else
			(*m_argv) = split2((*txt2), " 	", j);
		free((*txt2));
		lowerc(&(*m_argv));
		t_glob->t_cmnds[j].cmd = (*m_argv);
		if (j++ != pipn) // baci verjinic
		{
			(*txt2) = (*txt);
			(*txt) = ft_strdup(ft_strchr((*txt), '|') + 1);
			free((*txt2));
		}
		(*m_argv) = NULL;
	}
}

void	m_pipe_p1(int pipn, char **txt, char **txt2, int ***fd)
{
	int	i;

	t_glob->t_cmnds = (t_cmds *)malloc(sizeof(t_cmds) * (pipn + 1)); //commandneri qanakov enq malloc anum
	i = 0;
	while (i <= pipn)
	{
		t_glob->t_cmnds[i].inp = 0;
		t_glob->t_cmnds[i++].out = 1;
	}
	(*txt2) = pipfin((*txt)); //zut sarqi vor error tpi
	free((*txt));
	(*txt) = (*txt2);
	i = 0; //////// Part1; txt is finalized by this point; leaks are managed(not cheacked for sure)
	(*fd) = malloc(sizeof(int *) * (pipn + 1)); // + 3
	(*fd)[pipn] = NULL; // + 2
	while (i < pipn)  // + 2
	{
		(*fd)[i] = (int *)malloc(sizeof(int) * 2); // miat aravot@ dziiiii
		pipe((*fd)[i++]);
	}
}

void	*m_pipe(int pipn, char *txt) // ciklik chi (verjum chka pipe vor het ga main)
{
	int		j;
	char	*txt2;
	int		*pid;
	int		**fd;
	char	**m_argv;

	m_pipe_p1(pipn, &txt, &txt2, &fd);
	pid = malloc(sizeof(int) * (pipn + 1)); // + 2 araj
	m_pipe_p2(pipn, &txt, &txt2, &m_argv);
	j = 0;
	while (j <= pipn) // 1 pipe-i case-@ mtatsi; 0-n petq chi vortev iran 0 chenq talu (for now)
	{
		pid[j] = fork();
		if (pid[j] == 0)
		{
			m_pipe_p3_f1(pipn, &j, &fd);
			m_pipe_p3_f2(pipn, &j);
		}
		free_ar((void **)t_glob->t_cmnds[j++].cmd); // !!!
	}
	m_pipe_p4_c1(pipn, &fd);
	m_pipe_p5_fr1(pipn, &fd, &txt, &pid);
	return (NULL); // inch vor uzenq
}

