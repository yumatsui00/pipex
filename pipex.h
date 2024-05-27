/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:24:40 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/03 15:32:04 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

# define READ 0
# define WRITE 1

typedef struct s_pipe
{
	int		argc;
	char	**argv;
	char	**envp;
	int		infile;
	int		outfile;
	int		heredoc;
	char	*envpath;
	char	**cmdpath;
	char	**args;
	char	*cmd;
	int		cmdnum;
	int		cmd_i;
	int		*pipe;
	int		pipenum;
	int		i;
	pid_t	pid;
}	t_pipe;

//0_main
void	close_file(t_pipe *p, char *cause);
void	close_pipe(t_pipe *p);

//1_arg_file_check
void	arg_file_check(t_pipe *p);

//2_child
char	*make_path(char **envp);
void	child(t_pipe *p);
void	child_error(t_pipe *p, char *cause);

//3_ft_execute
void	ft_execute(t_pipe *p);

//9
void	err_msg(char *cause);
int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int size);
char	*ft_strjoin_pipe(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char *s, char c);

#endif