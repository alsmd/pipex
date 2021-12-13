/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:52:37 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/11 17:11:18 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>


int	main(int argc, char *argv[], char *env[])
{
	char	*cat = "/usr/bin/cat";
	char	*wc = "/usr/bin/wc";
	char	*filein = "filein";
	char	*fileout = "fileout";
	int		id;
	int		fd[2];
	char	**argv_cmd;
	int		status;

	pipe(fd);
	id = fork();
	if (id == 0)
	{
		dup2(open(filein, O_RDWR), STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		argv_cmd = ft_split(cat, ' ');
		close(fd[0]);
		execve(cat, argv_cmd, env);
		exit(0);
	}
	wait(&status);
	dup2(fd[0], STDIN_FILENO);
	argv_cmd = ft_split(wc, ' ');
	close(fd[1]);
	execve(wc, argv_cmd, env);
	/* 
	dup2(open(fileout, O_RDWR), STDOUT_FILENO);
	argv_cmd = ft_split(wc, ' ');
	id = fork();
	if (id == 0)
		execve(wc, argv_cmd, env);
	wait(&status);
	write(2, "here", 4);
	exit(0);
	argv_cmd = ft_split(wc, ' ');
	execve(wc, argv_cmd, env); */
	return (0);
}
