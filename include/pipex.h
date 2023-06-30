/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:52 by edecoste          #+#    #+#             */
/*   Updated: 2023/06/30 11:08:55 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <unistd.h>
//# include <sys/types.h>
# include <sys/uio.h>
/* malloc, free, exit */
# include <stdlib.h>
/* open, unlink */
# include <fcntl.h>
/* waitpid, wait */
# include <sys/wait.h>
/* strerror */
# include <string.h>
/*to perror*/
# include <stdint.h>
# include <errno.h>

typedef struct s_data
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipe[2];
	int		is_pipe_open;
	char	*paths;
	char	**cmd_paths;
	char	**args;
	char	*cmd;
}	t_data;

/* childs.c */
void	childs(t_data *pipex, char **av, char **envp);

/* free.c */
void	msg_error(char *error, t_data *pipex);
void	close_pipes(t_data *pipex);
void	parent_free(t_data *pipex);
void	child_free(t_data *pipex);
int		is_justspace(char *str);

/* utils */
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);

#endif