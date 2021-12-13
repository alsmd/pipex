/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:57:47 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 19:59:36 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	execute_cmd(t_command *cmd, char *env[], t_pipex *tpipex)
{
	if (cmd->not_exist == 1)
	{
		show_error(cmd->params[0], CMD_NOT_FOUND, 0);
		free_objs(tpipex);
		exit(CMD_NOT_FOUND);
	}
	execve(cmd->params[0], cmd->params, env);
}

void	get_content(t_pipex *tpipex)
{
	int		fd[2];
	char	*line;

	line = get_next_line(STDIN_FILENO);
	pipe(fd);
	while (ft_strncmp(line, tpipex->limiter, ft_strlen(line) - 1))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	last_child(t_pipex *tpipex, t_command *cmd, char *env[])
{
	int			fd_in;

	if (tpipex->limiter != 0)
		get_content(tpipex);
	else
	{
		fd_in = open(tpipex->filein, O_RDONLY);
		if (fd_in == -1)
			show_error(tpipex->filein, FILE_DO_NOT_EXIST, 1);
		dup2(fd_in, STDIN_FILENO);
	}
	execute_cmd(cmd, env, tpipex);
	exit(0);
}

void	parent(t_pipex *tpipex, t_command *cmd, char *env[], int fd[2])
{
	int	fd_file;

	if (cmd->next == 0)
	{
		fd_file = open(tpipex->fileout, O_RDWR | O_CREAT);
		if (tpipex->limiter != 0)
			handler_final_file(fd_file);
		dup2(fd_file, STDOUT_FILENO);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute_cmd(cmd, env, tpipex);
	exit(0);
}

int	start_pipex(t_pipex *tpipex, char *env[])
{
	t_command	*last_cmd;
	int			id;
	int			fd[2];
	int			status;

	last_cmd = tpipex->commands;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (last_cmd->before)
	{
		if (pipe(fd) == -1)
			show_error("Pipe", PIPE_ERROR, 1);
		id = fork();
		if (id == -1)
			show_error("Fork", FORK_ERROR, 1);
		if (id != 0)
		{
			waitpid(id, &status, 0);
			parent(tpipex, last_cmd, env, fd);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		last_cmd = last_cmd->before;
	}
	last_child(tpipex, last_cmd, env);
}
