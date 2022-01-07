/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:03:35 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/07 17:17:36 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_command	*create_new_command(t_pipex *tpipex, char *command)
{
	t_command	*begin;
	t_command	*new_cmd;

	new_cmd = (t_command *) ft_calloc(1, sizeof(t_command));
	tokenzine(command, '\'', ' ', 1);
	tokenzine(command, '\"', ' ', 1);
	new_cmd->params = ft_split(command, ' ');
	destokenzine_commands(new_cmd->params);
	new_cmd->full_instruction = command;
	begin = tpipex->commands;
	if (begin == 0)
		tpipex->commands = new_cmd;
	else
	{
		while (begin->next)
			begin = begin->next;
		new_cmd->before = begin;
		begin->next = new_cmd;
	}
	return (new_cmd);
}

void	check_command_exist(t_pipex *tpipex, t_command *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		index;
	int		exist;

	index = 0;
	exist = 0;
	while (tpipex->paths[index] != 0)
	{
		tmp = ft_strjoin(tpipex->paths[index], "/");
		cmd_path = ft_strjoin(tmp, cmd->params[0]);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd->params[0]);
			cmd->params[0] = cmd_path;
			exist = 1;
			break ;
		}
		else
			free(cmd_path);
		index++;
	}
	if (exist == 0)
		cmd->not_exist = 1;
}

int	verify_commands(t_pipex *tpipex, char *commands[], int number_commands)
{
	int			index;
	t_command	*cmd;

	index = 1;
	if (tpipex->limiter != 0)
		index = 2;
	number_commands -= 1;
	while (index < number_commands)
	{
		cmd = create_new_command(tpipex, commands[index]);
		check_command_exist(tpipex, cmd);
		index++;
	}
	tpipex->filein = commands[0];
	tpipex->fileout = commands[number_commands];
	return (1);
}
