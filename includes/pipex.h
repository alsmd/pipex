/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:48:17 by flda-sil          #+#    #+#             */
/*   Updated: 2021/12/13 01:18:14 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
typedef struct s_command
{
	char				**params;
	char				*full_instruction;
	int					not_exist;
	struct s_command	*next;
	struct s_command	*before;
}	t_command;

typedef struct s_pipex
{
	t_command	*commands;
	char		**paths;
	char		*filein;
	char		*fileout;
}	t_pipex;


enum E_ERROR
{
	FILE_DO_NOT_EXIST = 1,
	CMD_NOT_FOUND,
	PATH_NOT_PRESENT,
	PIPE_ERROR,
	FORK_ERROR
};
//Function
void	show_error(char *target_name, int status);
int			verify_commands(t_pipex *tpipex, char *commands[], int number_commands);
int		start_pipex(t_pipex *tpipex, char *env[]);

//UTILS
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);

#endif