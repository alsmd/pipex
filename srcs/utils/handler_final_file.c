/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_final_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:20:46 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 19:24:13 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	handler_final_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
}
