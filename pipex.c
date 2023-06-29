/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/29 15:53:59 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// build the path to the command binary
char *func_build_path(char *envp, char *command)
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

// Execute the command with execve, passing the command and the necessary arguments.
void	func_run_command(char *command, char **envp)
{
	char	*path;
	char	**args;

	args = ft_split(command, ' ');
	path = func_get_path(args[0], envp);
	execve(path, args, envp);
	ft_printf("Add error message here.func_run_command.\n");
}

// Create a pipe using the pipe function to establish communication between the parent process and the child process.
// Use fork to create a child process.
void	func_pipex(int infile, char **envp, char *comm)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (infile == STDIN_FILENO)
			ft_printf("Add error message here.func_pipex.\n");
		else
			func_run_command(comm, envp);
	}
}

// make envp become a char** only containing the PATHS
// find the "PATH=" string in envp
// use ft_split to divide all the paths
// return the new char** containing only the paths
char **func_get_real_envp(char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	char	**real_envp;
	int		i;

	if (argc > 4)
	{
		i = 0;
		real_envp = func_get_real_envp(envp);
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		func_run_command(argv[2], real_envp);
		while (i + 3 < argc - 2)
		{
			func_pipex(infile, real_envp, argv[i + 3]);
			i++;
		}
		func_run_command(argv[i + 3], real_envp);
	}
	else
		ft_printf("Add error message here.main.\n");
	return (1);
}
