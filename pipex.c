/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/29 12:44:41 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Pipex

-I need to execute x number of commands with input from a file and I want to write the output to another file.
-I need to use dup and dup2 to change standard input and output fd from the terminal to the files.
-I need to create a pipe (maybe x amount of pipes?) and then fork (also x amound of times?)
-To exec the commands with execve I need to use the envp and access??

Done -- I need to get the PATH variable from envp and remove the other ones. (split)

Done -- Open infile to ready input and outfile to write output.

Execve reads from STDIN and outputs to STDOUT 
Make standard input the infile and make standard output to outfile (with dup/dup2)

I already have a way to know the true path to use.

I need to make the child process do the first command and the parent process do the second command.
The child process reads from the infile and writes to the pipe.
The parent process reads from the pipe and does the second command.
The parent process writes to the outfile.
I need to use waitpid to wait for the child process to finish before starting the parent process.

*/

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
}

// In the first child process:
// Close the unused end of the pipe.
// Use dup2 to duplicate the read end of the pipe onto the standard input file descriptor (STDIN_FILENO).
// Close the read end of the pipe.
// Use open to open the output file and obtain the file descriptor for writing.
// Use dup2 to duplicate the write end of the pipe onto the standard output file descriptor (STDOUT_FILENO).
// Close the write end of the pipe.
// Execute the second shell command using execve, passing the command and the necessary arguments.
void func_child_process(int *pipefd, int infile, char **envp, char *argv, int i)
{
	if (i == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		func_run_command(argv, envp);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		func_run_command(argv, envp);
	}
	ft_printf("This should not print.Child.\n");
}

// In the second process:
//         Close the write end of the pipe.
//         Use dup2 to duplicate the read end of the pipe onto the standard input file descriptor (STDIN_FILENO).
//         Close the read end of the pipe.
//         Execute the first shell command using execve, passing the command and the necessary arguments.
void func_parent_process(int *pipefd, int outfile, char **envp, char *argv)
{
	dup2(outfile, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	func_run_command(argv, envp);
	ft_printf("This should not print.Parent.\n");
}

// Create a pipe using the pipe function to establish communication between the parent process and the child process.
// Use fork to create a child process.
int	func_pipex(int infile, int outfile, char **envp, char **argv)
{
	int	pid;
	int	pipefd[2];
	int	i;

	i = 0;
	if (pipe(pipefd) == -1)
		return (1); 
	while (argv[i + 3] != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			func_child_process(pipefd, infile, envp, argv[i + 1], i);
		waitpid(pid, NULL, 0);
		i++;
	}
	if (i == 0)
	{
		dup2(outfile, STDOUT_FILENO);
		dup2(infile, STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		func_run_command(argv[1], envp);
	}
	else
		func_parent_process(pipefd, outfile, envp, argv[i + 1]);
	return (0);
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
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	char	**real_envp;

	if (argc == 1)
		return (1);
	real_envp = func_get_real_envp(envp);
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	func_pipex(infile, outfile, real_envp, argv + 1);
	free(real_envp);
	return (0);
}
