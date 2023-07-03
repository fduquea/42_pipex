/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/03 22:25:04 by fduque-a         ###   ########.fr       */
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
	if (path == NULL)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		ft_printf("pipex: %s: command not found\n", args[0]);
		ft_split_free(args);
		free(path);
		exit(127);
	}
	execve(path, args, envp);
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
	return (NULL);
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
		waitpid(pid, NULL, 0);
	}
}

void	func_pipex(char **envp, char **argv, int argc)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(argv[1], O_RDONLY);
	func_check(access(argv[1], R_OK), argv[1]);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	func_check(access(argv[argc - 1], W_OK), argv[argc - 1]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	func_exec_command(argv[2], envp);
	func_run_command(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	**real_envp;

	if (argc == 5)
	{
		real_envp = func_get_real_envp(envp);
		if (real_envp == NULL)
			ft_printf("pipex: PATH not found in envp.\n"); // to do
		func_pipex(real_envp, argv, argc);
	}
	else
		ft_printf("Usage:./pipex file1 cmd1 cmd2 file2\n");
	return (1);
}
