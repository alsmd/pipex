/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:52:37 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 19:10:22 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char *env[])
{
	int	index;

	index = 0;
	while (env[index] != 0)
	{
		if (env[index][0] == 'P' && env[index][1] == 'A' && \
			env[index][2] == 'T' && env[index][3] == 'H')
			return (&env[index][5]);
		index++;
	}
	return (0);
}

/* void	print_commands(t_pipex *tpipex)
{
	t_command	*begin;
	int			index;

	begin = tpipex->commands;
	index = 0;
	while (begin)
	{
		printf("name: %s\nargv:\n", begin->params[0]);
		while (begin->params[index] != 0)
		{
			printf("%s\n", begin->params[index]);
			index++;
		}
		index = 0;
		begin = begin->next;
	}
} */

void	free_objs(t_pipex *tpipex)
{
	t_command	*begin;
	t_command	*tmp;
	int			index;

	begin = tpipex->commands;
	while (begin)
	{
		index = 0;
		while (begin->params[index] != 0)
		{
			free(begin->params[index]);
			index++;
		}
		free(begin->params);
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	index = 0;
	while (tpipex->paths[index])
	{
		free(tpipex->paths[index]);
		index++;
	}
	free(tpipex->paths);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	tpipex;
	char	*path;
	int		id;
	int		status;

	if (argc < 5)
		return (0);
	ft_bzero(&tpipex, sizeof(t_pipex));
	if (!ft_strncmp(argv[1], "here_doc", 9))
		tpipex.limiter = argv[2];
	if (argc < 6 && tpipex.limiter != 0)
		return (0);
	path = get_path(env);
	if (path == 0)
		show_error("Path", PATH_NOT_PRESENT, 1);
	tpipex.paths = ft_split(path, ':');
	if (verify_commands(&tpipex, &argv[1], argc - 1) == 0)
		return (0);
	id = fork();
	if (id == 0)
		start_pipex(&tpipex, env);
	waitpid(id, &status, 0);
	free_objs(&tpipex);
	return (0);
}
