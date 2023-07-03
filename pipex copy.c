/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/03 19:47:24 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// build the path to the command binary
char	*func_build_path(char *envp, char *command)
{
	char	*path;

	path = ft_strjoin(envp, "/");
	path = ft_strjoin(path, command);
	return (path);
}

// get the command binary from envp
char	*func_get_path(char *comm, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		path = func_build_path(envp[i], comm);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_printf("Add error message here.func_get_path.\n");
	return (NULL);
}

// Execute the command with execve, 
// passing the command and the necessary arguments.
void	func_run_command(char *command, char **envp)
{
	char	*path;
	char	**args;

	args = ft_split(command, ' ');
	path = func_get_path(args[0], envp);
	execve(path, args, envp);
	ft_printf("Add error message here.func_run_command.\n");
}

// make envp become a char** only containing the PATHS
// find the "PATH=" string in envp
// use ft_split to divide all the paths
// return the new char** containing only the paths
char	**func_get_real_envp(char **envp)
{
	char	**real_envp;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			real_envp = ft_split(path, ':');
			free(path);
			return (real_envp);
		}
		i++;
	}
	ft_printf("Add error message here.func_get_real_envp\n");
	return (NULL);
}

void	func_exec_command(char *command, char **envp)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		ft_printf("Add error message here.func_exec_command.\n");
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		func_run_command(command, envp);
	}
	else if (pid < 0)
		ft_printf("Add error message here.func_exec_command.\n");
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	func_pipex(char **envp, char **argv, int argc, int i)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(argv[1], O_RDONLY);
	if (access(argv[1], R_OK) == -1)
		ft_printf("Add error message here.func_pipex infile access.\n");
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (access(argv[argc - 1], W_OK) == -1)
		ft_printf("Add error message here.func_pipex outfile access.\n");
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (argc == 4)
		func_run_command(argv[2], envp);
	else
	{
		func_exec_command(argv[2], envp);
		while (argc - 5 - i++ > 0)
			func_exec_command(argv[3 + i], envp);
		func_run_command(argv[argc - 2], envp);
	}
}

void	func_here_doc(char *eof)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	ft_printf("> ");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, eof, ft_strlen(eof))
			|| ft_strclen(line, '\n') != ft_strlen(eof)))
	{
		ft_putstr_fd(line, fd_heredoc);
		free(line);
		ft_printf("> ");
		line = get_next_line(0);
	}
	free(line);
	close(fd_heredoc);
}

int	main(int argc, char **argv, char **envp)
{
	char	**real_envp;
	int		heredoc;
	int		i;

	if (argc > 3)
	{
		real_envp = func_get_real_envp(envp);
		heredoc = (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8));
		if (heredoc)
			func_here_doc(argv[2]);
		i = 0 + heredoc;
		func_pipex(real_envp, argv, argc, i);
	}
	else
		ft_printf("Add error message here.main.\n");
}
