/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:45:30 by flavio            #+#    #+#             */
/*   Updated: 2021/12/13 23:48:44 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while ((s1[index] && s2[index]) && index < n)
	{
		if (s1[index] != s2[index] || index == n - 1)
			break ;
		index++;
	}
	if (s1[index] == '\n' && s2[index] == '\0')
		return (0);
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
