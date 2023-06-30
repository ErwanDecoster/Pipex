/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:24:37 by edecoste          #+#    #+#             */
/*   Updated: 2023/06/30 11:08:55 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	close_all(t_data *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	close(pipex->infile);
	close(pipex->outfile);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*res;

	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, X_OK) == 0)
			return (res);
		free(res);
		paths++;
	}
	return (NULL);
}

static void	first_child(t_data *pipex, char **av, char **envp)
{
	if (dup2(pipex->pipe[1], 1) == -1 || dup2(pipex->infile, 0) == -1)
		ft_putstr_fd("Error: dup2 1 didn't work\n", 2);
	else
	{
		pipex->args = ft_split(av[2], ' ');
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->args[0]);
		if (!pipex->cmd)
		{
			ft_putstr_fd("Error: command not found : ", 2);
			ft_putendl_fd(av[2], 2);
			child_free(pipex);
			exit(1);
		}
		close_all(pipex);
		if (execve(pipex->cmd, pipex->args, envp) == -1)
		{
			ft_putstr_fd("Error: execve first child\n", 2);
			child_free(pipex);
			exit(1);
		}
	}
	close_all(pipex);
	exit(1);
}

static void	second_child(t_data *pipex, char **av, char **envp)
{
	if (dup2(pipex->pipe[0], 0) == -1 || dup2(pipex->outfile, 1) == -1)
		ft_putstr_fd("Error: dup2 2 didn't work\n", 2);
	else
	{
		pipex->args = ft_split(av[3], ' ');
		pipex->cmd = get_cmd(pipex->cmd_paths, pipex->args[0]);
		if (!pipex->cmd)
		{
			ft_putstr_fd("Error: command not found : ", 2);
			ft_putendl_fd(av[3], 2);
			child_free(pipex);
			exit(1);
		}
		close_all(pipex);
		if (execve(pipex->cmd, pipex->args, envp) == -1)
		{
			ft_putstr_fd("Error: execve second child\n", 2);
			child_free(pipex);
			exit(1);
		}
	}
	close_all(pipex);
	exit(1);
}

void	childs(t_data *pipex, char **av, char **envp)
{
	if (pipex->infile > 0 && !is_justspace(av[2]))
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			ft_putstr_fd("Error: first child\n", 2);
		if (pipex->pid1 == 0)
			first_child(pipex, av, envp);
	}
	if (is_justspace(av[2]))
		ft_putstr_fd("Error: first command empty\n", 2);
	if (pipex->outfile > 0 && !is_justspace(av[3]))
	{
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			ft_putstr_fd("Error: second child\n", 2);
		if (pipex->pid2 == 0)
			second_child(pipex, av, envp);
	}
	if (is_justspace(av[3]))
		ft_putstr_fd("Error: second command empty\n", 2);
}
