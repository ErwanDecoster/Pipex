/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edecoste <edecoste@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:31:19 by edecoste          #+#    #+#             */
/*   Updated: 2023/06/30 16:24:15 by edecoste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*find_path(char **envp)
{
	while (envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	open_files(char **av, t_data *pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0 && errno == 2)
	{
		ft_putstr_fd("Error: no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
	}
	if (pipex->infile < 0 && errno == 13)
	{
		ft_putstr_fd("Error: permission denied: ", 2);
		ft_putendl_fd(av[1], 2);
	}
	pipex->outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
	{
		ft_putstr_fd("Error: permission denied : ", 2);
		ft_putendl_fd(av[4], 2);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	pipex;

	ft_bzero(&pipex, sizeof(t_data));
	if (ac != 5)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2));
	if (!envp || !envp[0] || !ft_strncmp("PATH=", *envp, 5))
		return (ft_putstr_fd("Error: env not found\n", 2), 1);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(find_path(envp), ':');
	pipex.is_pipe_open = pipe(pipex.pipe);
	if (pipex.is_pipe_open < 0)
		msg_error("Error: Pipe\n", &pipex);
	open_files(av, &pipex);
	childs(&pipex, av, envp);
	return (parent_free(&pipex), 0);
}
