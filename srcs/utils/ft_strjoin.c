/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:44:37 by flavio            #+#    #+#             */
/*   Updated: 2021/12/11 04:37:29 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (!src || !dst)
		return (0);
	while (src[index] && index + 1 < size)
	{
		dst[index] = src[index];
		index++;
	}
	if (size > 0)
		dst[index] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	index = 0;
	if (size < dst_len)
		return (size + src_len);
	while (src[index] && (dst_len + 1) < size)
	{
		dst[dst_len + index] = src[index];
		index++;
		size--;
	}
	dst[dst_len + index] = 0;
	return (dst_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	size_t	s1len;
	size_t	s2len;
	size_t	size;

	if (s1 == 0 || s2 == 0)
		return (0);
	else
	{
		s1len = ft_strlen(s1);
		s2len = ft_strlen(s2);
		size = s1len + s2len;
	}
	string = (char *) ft_calloc(size + 1, sizeof(char));
	if (!string)
		return (0);
	ft_strlcpy(string, s1, s1len + 1);
	ft_strlcat(string, s2, s1len + s2len + 1);
	return (string);
}
