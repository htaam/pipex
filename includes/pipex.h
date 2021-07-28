#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

extern char	**environ;

void		ft_pipex(int argc, char **argv);
void		pipein(int pipefd[2], int in, char *cmd1);
void		pipeout(int pipefd[2], int out, char *cmd2);
void		ft_exec(char *cmd, char **args);
void		ft_testpaths(char *cmd, char **args, char **paths);

#endif