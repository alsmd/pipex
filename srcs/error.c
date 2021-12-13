/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:04:44 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 03:47:22 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	show_error(char *target_name, int status, int has_to_exit)
{
	char	*str_1;
	char	*str_2;
	char	*tmp;

	str_1 = "bash: ";
	if (status == FILE_DO_NOT_EXIST)
		str_2 = ": No such file or directory\n";
	else if (status == CMD_NOT_FOUND)
		str_2 = ": command not found\n";
	else if (status == PATH_NOT_PRESENT)
		str_2 = ": is not present in enviroment's varibles!\n";
	else if (status == PIPE_ERROR)
		str_2 = ": Something went wrong opening!\n";
	else if (status == FORK_ERROR)
		str_2 = ": Fork could not be used!\n";
	tmp = ft_strjoin(str_1, target_name);
	str_1 = ft_strjoin(tmp, str_2);
	free(tmp);
	write(2, str_1, ft_strlen(str_1));
	free(str_1);
	if (has_to_exit)
		exit(status);
}
