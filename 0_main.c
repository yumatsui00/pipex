/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:24:56 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/08 15:54:32 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_file(t_pipe *p, char *cause)
{
	if (p->heredoc == 1)
	{
		close(p->infile);
		unlink(".tmp_doc");
	}
	else
		close(p->infile);
	close(p->outfile);
	err_msg(cause);
}

void	close_pipe(t_pipe *p)
{
	int	i;

	i = -1;
	while (++i < p->pipenum)
		close(p->pipe[i]);
}

static void	make_pipe(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->cmdnum - 1)
	{
		if (pipe(p->pipe + (i * 2)) < 0)
		{
			close_pipe(p);
			close_file(p, "ERROR when creating pipe");
		}
		i++;
	}
}

static int	parent(t_pipe *p)
{
	int	i;

	i = -1;
	while (p->cmdpath[++i] != NULL)
		free(p->cmdpath[i]);
	free(p->cmdpath);
	close_pipe(p);
	if (p->heredoc == 1)
	{
		close(p->infile);
		unlink(".tmp_doc");
	}
	else
		close(p->infile);
	close(p->outfile);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	p.argc = argc;
	p.argv = argv;
	p.envp = envp;
	arg_file_check(&p);
	p.cmdnum = p.argc - 3 - p.heredoc;
	p.pipenum = (p.cmdnum - 1) * 2;
	p.pipe = (int *)malloc(sizeof(int) * p.pipenum);
	if (!p.pipe)
		close_file(&p, "ERROR when allocate pipe");
	make_pipe(&p);
	p.envpath = make_path(p.envp);
	p.cmdpath = ft_split(p.envpath, ':');
	if (!p.cmdpath)
	{
		close_pipe(&p);
		close_file(&p, "ERROR when MALLOC in ft_split");
	}
	p.i = -1;
	while (++(p.i) < p.cmdnum)
		child(&p);
	while (--(p.i) > 0)
		waitpid(p.pid, NULL, 0);
	return (parent(&p));
}

//!基本はいけてるけど、sleepの挙動について
//!本家では全てのコマンドがほぼ同時に実行されるため、sleep が二つ以上ある時は、最長のもののみが実行されているように見える→多分治った
//!しかし、このコードでは一つのコマンドが終わるまでwaitしているため、二つ以上あると、合計の長さだけ待ってしまう
//!絶対パスを受け取った時の処理はできていないです
//!メモリリークとかはまだ危うい
//!