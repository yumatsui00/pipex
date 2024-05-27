/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ft_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:22 by yumatsui          #+#    #+#             */
/*   Updated: 2024/05/16 15:40:57 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(t_pipe *p)
{
	char	*command;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (p->cmdpath[++i])
	{
		command = ft_strjoin_pipe(p->cmdpath[i], p->args[0]);
		if (command == NULL)
		{
			while (p->args[++j])
				free(p->args[j]);
			free(p->args[j]);
			child_error(p, "ERROR when malloc in strjoin in get_cmd");
		}
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	while (p->args[j])
		free(p->args[j]);
	free(p->args);
	child_error(p, "command not found");
	return (NULL);
}

void	ft_execute(t_pipe *p)
{
	p->args = ft_split(p->argv[2 + p->heredoc + p->i], ' ');
	if (!p->args)
		child_error(p, "ERROR when malloc in split in ft_execute");
	p->cmd = get_cmd(p);
	execve(p->cmd, p->args, p->envp);
	while (*(p->args))
		free(*(p->args));
	free(p->args);
	child_error(p, "ERROR when execve");
}