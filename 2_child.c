/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_child.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:57:30 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/10 20:01:17 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*make_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	child_error(t_pipe *p, char *cause)
{
	int	i;

	i = -1;
	while (p->cmdpath[++i] != NULL)
		free(p->cmdpath[i]);
	free(p->cmdpath);
	close_pipe(p);
	close_file(p, cause);
}

static int	dpdp2(int fd1, int fd2)
{
	if (dup2(fd1, STDIN_FILENO) < 0)
		return (-1);
	if (dup2(fd2, STDOUT_FILENO) < 0)
		return (-1);
	return (0);
}

void	child(t_pipe *p)
{
	p->pid = fork();
	if (p->pid == 0)
	{
		if (p->i == 0)
		{
			if (dpdp2(p->infile, p->pipe[1]) == -1)
				child_error(p, "ERROR when dup2(first child)");
		}
		else if (p->i == p->cmdnum - 1)
		{
			if (dpdp2(p->pipe[(p->i) * 2 - 2], p->outfile) == -1)
				child_error(p, "ERROR when dup2(last child)");
		}
		else
		{
			if (dpdp2(p->pipe[(p->i) * 2 - 2], p->pipe[(p->i) * 2 + 1]) == -1)
				child_error(p, "ERROR when dup2(mid children)");
		}
		close_pipe(p);
		ft_execute(p);
	}
	if (p->i != 0)
		close(p->pipe[p->i * 2 - 1]);
}
