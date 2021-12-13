/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:57:47 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 01:18:43 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		execute_cmd(t_command *cmd, char *env[])
{
	execve(cmd->params[0], cmd->params, env);
}

int		start_pipex(t_pipex *tpipex, char *env[])
{
	t_command	*last_cmd;
	int			id;
	int			fd[2];
	int			fd_in;
	int			status;

	last_cmd = tpipex->commands;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (last_cmd->before)
	{
		if (pipe(fd) == -1)
			show_error("Pipe", PIPE_ERROR);
		id = fork();
		if (id == -1)
			show_error("Fork", FORK_ERROR);
		if (id != 0)
		{
			if (last_cmd->next == 0)
				dup2(open(tpipex->fileout, O_RDWR | O_CREAT), STDOUT_FILENO);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			waitpid(id, &status, 0);
			execute_cmd(last_cmd, env);
			exit(0);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		last_cmd = last_cmd->before;
	}
	fd_in = open(tpipex->filein, O_RDONLY);
	if (fd_in == -1)
		show_error(tpipex->filein, FILE_DO_NOT_EXIST);
	dup2(fd_in, STDIN_FILENO);
	execute_cmd(last_cmd, env);
	exit(0);
}