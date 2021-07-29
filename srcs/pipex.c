/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 17:10:10 by tmatias           #+#    #+#             */
/*   Updated: 2021/07/29 17:11:02 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipein(int pipefd[2], int in, char *cmd1)
{
	char	**args;

	close(pipefd[0]);
	args = ft_split(cmd1, ' ');
	if (dup2(in, 0) == -1)
		ft_exit("Failed to connect infile with STDIN");
	if (dup2(pipefd[1], 1) == -1)
		ft_exit("Failed to connect STDOUT with pipe's WRITE END");
	if (args[0][0] == '/')
	{
		if (execve(args[0], args, environ) == -1)
			ft_exit("Invalid command address.");
	}
	else
		ft_exec(args[0], args);
	ft_freecharmatrix(args);
	close(in);
	close(pipefd[1]);
	wait(NULL);
}

void	pipeout(int pipefd[2], int out, char *cmd2)
{
	char	**args;

	close(pipefd[1]);
	args = ft_split(cmd2, ' ');
	dup2(pipefd[0], 0);
	dup2(out, 1);
	if (args[0][0] == '/')
	{
		if (execve(args[0], args, environ) == -1)
			ft_exit("Invalid command address.");
	}
	else
		ft_exec(args[0], args);
	ft_freecharmatrix(args);
	close(out);
	close(pipefd[0]);
}

void	ft_exec(char *cmd, char **args)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
		{
			environ[i] += 5;
			paths = ft_split(environ[i], ':');
			break ;
		}
		i++;
	}
	ft_testpaths(cmd, args, paths);
}

void	ft_testpaths(char *cmd, char **args, char **paths)
{
	int		i;
	char	*temp;
	char	*newpath;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		newpath = ft_strjoin(temp, cmd);
		execve(newpath, args, environ);
		free(newpath);
		free(temp);
		i++;
	}
	ft_freecharmatrix(paths);
	ft_exit("No such command found.");
}

void	ft_pipex(int argc, char **argv)
{
	int		in;
	int		out;
	int		pip;
	int		pipefd[2];
	pid_t	pid;

	in = open(argv[1], O_RDONLY);
	if (in == -1)
		ft_exit("Failed to open the input file.");
	out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (out == -1)
		ft_exit("Failed to open the output file.");
	pip = pipe(pipefd);
	if (pip == -1)
		ft_exit("Failed to create a pipe.");
	pid = fork();
	if (pid == -1)
		ft_exit("Failed to fork the process.");
	if (pid == 0)
		pipeout(pipefd, out, argv[3]);
	else
		pipein(pipefd, in, argv[2]);
}
