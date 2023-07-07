/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/07 18:10:40 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Execute the command with execve, 
// passing the command and the necessary arguments.
static void	func_run_command(char *command, char **envp)
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

static void	func_exec_command(char *file, char *command, char **envp)
{
	int	pid;
	int	pipefd[2];
	int	i;

	func_check(pipe(pipefd), "pipe");
	pid = fork();
	if (pid == 0)
	{
		func_check(access(file, R_OK), file);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		func_run_command(command, envp);
	}
	else if (pid == -1)
		func_check(pid, "fork");
	else
	{
		i = 0;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		while (i++ < 500)
			waitpid(pid, NULL, WNOHANG);
	}
}

static void	func_pipex(char **envp, char **argv, int argc, int i)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	func_check(access(argv[argc - 1], W_OK), argv[argc - 1]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	func_exec_command(argv[1], argv[2 + i], envp);
	while (argc - 5 - i > 0)
	{
		func_exec_command(argv[1], argv[3 + i], envp);
		i++;
	}
	func_run_command(argv[argc - 2], envp);
}

static void	func_here_doc(char *eof)
{
	char	*line;
	int		fd_heredoc;

	fd_heredoc = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0777);
	ft_printf("heredoc> ");
	line = get_next_line(0);
	while (line && (ft_strncmp(line, eof, ft_strlen(eof))
			|| ft_strclen(line, '\n') != ft_strlen(eof)))
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
		else if (!ft_strncmp(argv[1], "here_doc\0", 9))
		{
			ft_printf("Usage:./pipex 'infile'/'here_doc "\
				"LIMITER' cmd1/x cmd2/x ... outfile\n");
			return (1);
		}
		if (heredoc == 1)
			func_here_doc(argv[2]);
		i = 0 + heredoc;
		func_pipex(envp, argv, argc, i);
	}
	else
		ft_printf("Usage:./pipex 'infile'/'here_doc "\
			"LIMITER' cmd1/x cmd2/x ... outfile\n");
	return (0);
}
