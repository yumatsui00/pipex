/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_arg_file_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:29:48 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/15 13:20:34 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

static void	chore_in_heredoc(int fd, t_pipe *p)
{
	char	*buff;

	buff = NULL;
	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &buff) == 0)
		{
			free(buff);
			close(fd);
			unlink(".tmp_doc");
			err_msg("ERROR in GNL");
		}
		if (!ft_strncmp(p->argv[2], buff, ft_strlen(p->argv[2])) && \
									buff[ft_strlen(p->argv[2])] == '\n')
			break ;
		write(fd, buff, ft_strlen(buff));
		free(buff);
	}
}

static void	here_document(t_pipe *p)
{
	int	fd;

	fd = open(".tmp_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		err_msg("ERROR when opening here_doc\n");
	chore_in_heredoc(fd, p);
	close(fd);
	p->infile = open(".tmp_doc", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".tmp_doc");
		err_msg("ERROR when opening heredoc");
	}
}

static void	check_infile(t_pipe *p)
{
	if (p->heredoc == 1)
		here_document(p);
	else
	{
		p->infile = open(p->argv[1], O_RDONLY);
		if (p->infile < 0)
		{
			perror("ERROR when opening infile");
			exit(1);
		}
	}
	return ;
}

static void	check_outfile(t_pipe *p)
{
	if (p->heredoc == 1)
		p->outfile = open(p->argv[p->argc - 1], O_CREAT | O_WRONLY | \
						O_APPEND, 0000644);
	else
		p->outfile = open(p->argv[p->argc - 1], O_CREAT | O_RDWR | \
						O_TRUNC, 0000644);
	if (p->outfile < 0)
	{
		close(p->infile);
		perror("ERROR when opening outfile");
		exit(1);
	}
}

void	arg_file_check(t_pipe *p)
{
	if (p->argc <= 4)
		err_msg("TOO_FEW_ARGS");
	if (p->argv[1] && (ft_strncmp("here_doc", p->argv[1], 8) == 0))
		p->heredoc = 1;
	else
		p->heredoc = 0;
	check_infile(p);
	check_outfile(p);
}
