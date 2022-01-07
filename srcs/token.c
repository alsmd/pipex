/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:59:03 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/07 17:18:27 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*token(char *command, char limiter, char c, char s)
{
	while (*command)
	{
		if (*command == c)
			*command = s;
		if (*command == limiter)
			break ;
		command++;
	}
	if (*command == limiter)
		command++;
	return (command);
}

void	tokenzine(char *command, char limiter, char c, char s)
{
	char	*tmp;
	int		index;

	index = 0;
	while (command[index])
	{
		if (command[index] == limiter)
		{
			tmp = &command[index];
			tmp++;
			while (*tmp)
			{
				if (*tmp == limiter)
					command = token(command + index + 1, limiter, c, s);
				tmp++;
			}
		}
		index++;
	}
}

void	remove(char *string, char c, char s)
{
	int	index;
	int	size;

	index = 0;
	size = ft_strlen(string);
	while (string[index])
	{
		if (string[index] == c)
		{
			string[index] = s;
			break ;
		}
		index++;
	}
	while (size)
	{
		size--;
		if (string[size] == c)
		{
			string[size] = s;
			break ;
		}
	}
}

void	destokenzine_commands(char **commands)
{
	int	index;

	index = 0;
	while (commands[index])
	{
		tokenzine(commands[index], '\'', 1, ' ');
		tokenzine(commands[index], '\"', 1, ' ');
		remove(commands[index], '\'', 1);
		remove(commands[index], '\"', 1);
		index++;
	}
}
