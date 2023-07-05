/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/05 15:50:54 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// check for errors
void	func_check(int result, char *message)
{
	if (result == -1)
	{
		ft_printf("pipex: ");
		perror(message);
		exit(1);
	}
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

// build the path to the command binary
char	*func_build_path(char *envp, char *command)
{
	char	*path_slash;
	char	*path;

	path_slash = ft_strjoin(envp, "/");
	path = ft_strjoin(path_slash, command);
	free(path_slash);
	return (path);
}

// get the command binary from envp
char	*func_get_path(char *comm, char **envp)
{
	int		i;
	char	*path;
	char	**real_envp;

	real_envp = func_get_real_envp(envp);
	if (real_envp == NULL)
		return (NULL);
	i = 0;
	while (real_envp[i])
	{
		path = func_build_path(real_envp[i], comm);
		if (access(path, F_OK) == 0)
		{
			ft_split_free(real_envp);
			return (path);
		}
		free(path);
		i++;
	}
	ft_split_free(real_envp);
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
	if (path == NULL || envp == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("pipex: %s: command not found\n", args[0]);
		if (path)
			free(path);
		if (args)
			ft_split_free(args);
		exit(127);
	}
	execve(path, args, envp);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf("pipex: %s: command not found\n", args[0]);
	ft_split_free(args);
	free(path);
	exit(127);
}


void	func_exec_command(char *command, char **envp)
{
	int	pid;
	int	pipefd[2];

	func_check(pipe(pipefd), "pipe");
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		func_run_command(command, envp);
	}
	else if (pid == -1)
		func_check(pid, "fork");
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}

void	func_pipex(char **envp, char **argv, int argc, int i)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	func_check(access(argv[1], R_OK), argv[1]);
	func_check(access(argv[argc - 1], W_OK), argv[argc - 1]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	func_exec_command(argv[2 + i], envp);
	while (argc - 5 - i > 0)
	{
		func_exec_command(argv[3 + i], envp);
		i++;
	}
	func_run_command(argv[argc - 2], envp);
}

void	func_here_doc(char *eof)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	ft_printf("heredoc> ");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, eof, ft_strlen(eof)) || ft_strclen(line, '\n') != ft_strlen(eof)))
	{
		ft_putstr_fd(line, fd_heredoc);
		free(line);
		ft_printf("heredoc> ");
		line = get_next_line(0);
	}
	free(line);
	close(fd_heredoc);
}

int	main(int argc, char **argv, char **envp)
{
	int		heredoc;
	int		i;

	heredoc = 0;
	if (argc >= 5)
	{
		if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
			heredoc = 1;
		else if (!ft_strncmp(argv[1], "here_doc", 8))
		{
			ft_printf("Usage:./pipex 'infile'/'here_doc LIMITER' cmd1/x cmd2/x ... outfile\n");
			return (1);
		}
		if (heredoc == 1)
			func_here_doc(argv[2]);
		i = 0 + heredoc;
		func_pipex(envp, argv, argc, i);
	}
	else
		ft_printf("Usage:./pipex 'infile'/'here_doc LIMITER' cmd1/x cmd2/x ... outfile\n");
	return (1);
}
