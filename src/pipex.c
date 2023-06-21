/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/21 09:56:08 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int argc, char **argv)
// {
// 	if (argv == 5)
// 	{
// 		int fd = open(argv[1], O_RDONLY);
// 	}
// 	else
// 	//printerror
// }

/*
Exercise 1:
Write a program that creates a child process using fork(). The child process should print "Hello" and the parent process should print "Goodbye".

Exercise 2:
Write a program that creates three child processes using fork(). Each child process should print its own process ID (getpid()) and its parent's ID (getppid()).

Exercise 3:
Write a program that creates a child process using fork(). The child process should print "I am the child" and the parent process should print "I am the parent". Use the wait() function in the parent process to wait for the child process to finish before the parent process exits.

Exercise 4:
Write a program that creates a child process using fork(). The child process should count from 1 to 10, printing each number with a small delay between them (use sleep()). The parent process should wait for the child process to finish and then print "Child process completed".

Exercise 5:
Write a program that creates a child process using fork(). The child process should read a number from the user and print whether it is odd or even. The parent process should wait for the child process to finish and then print "Child process completed".

Exercise 6:
Write a program that creates a child process using fork(). The child process should execute another program (e.g., ls, pwd) using the exec() family of functions (e.g., execl(), execvp()). The parent process should wait for the child process to finish and then print "Child process completed".

These exercises should help you practice using the fork() function in various scenarios. Feel free to modify or extend them to further explore process creation and management in C.
*/

// int	main(void)
// {
// 	int	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		printf("Hello\n");
// 		exit(0);
// 	}
// 	else
// 	{
// 		wait(0);
// 		printf("Goodbye\n");
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	int	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		printf("Child 1 process ID: %i\n", getpid());
// 		printf("Child's 1 parent process ID: %i\n\n", getppid());
// 		exit(0);
// 	}
// 	int	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		wait(0);
// 		printf("Child 2 process ID: %i\n", getpid());
// 		printf("Child's 2 parent process ID: %i\n\n", getppid());
// 		exit(0);
// 	}
// 	int pid3 = fork();
// 	if (pid3 == 0)
// 	{
// 		wait(0);
// 		printf("Child 3 process ID: %i\n", getpid());
// 		printf("Child's 3 parent process ID: %i\n\n", getppid());
// 		exit(0);
// 	}
// 	wait(0);
// 	printf("Parent process ID: %i\n", getpid());
// 	return 0;
// }

// int	main(void)
// {
// 	int	pid = fork();
// 	if (pid == 0)
// 	{
// 		printf("I am the child.\n");
// 		exit(0);
// 	}
// 	wait(0);
// 	printf("I am the parent.\n");
// 	return 0;
// }

// int	main(void)
// {
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		int	i = 1;
// 		while (i <= 10)
// 		{
// 			printf("%i\n", i);
// 			sleep(1);
// 			i++;
// 		}
// 		exit(0);
// 	}
// 	wait(0);
// 	printf("Child process completed.\n");
// }

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		printf("Give me a number!!\n");
// 		return 1;
// 	}
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		int	i = atoi(argv[1]);
// 		if (i % 2 == 0)
// 			printf("Your number is even! Nice!\n");
// 		else
// 			printf("Your number is odd, you are weird.\n");
// 		sleep(1);
// 		exit(0);
// 	}
// 	wait(0);
// 	printf("Child process completed.\n");
// 	return 0;
// }

// int	main(void)
// {
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		char *argv[] = {"ls", "-la", NULL};
// 		char *envp[] = {NULL};
// 		execve("/bin/ls", argv, envp);
// 		exit(0);
// 	}
// 	wait(0);
// 	printf("Child process completed.\n");
// }

// Exercise 1:
// Write a program that creates a pipe using the pipe() function. Then, use fork() to create a child process. The parent process should write the string "Hello, child process!" to the pipe, and the child process should read from the pipe and print the received message.

// Exercise 2:
// Write a program that creates a pipe using the pipe() function. Then, use fork() to create a child process. The child process should generate a random number and write it to the pipe. The parent process should read from the pipe and print the received number.

// Exercise 3:
// Write a program that creates a pipe using the pipe() function. Then, use fork() to create a child process. The parent process should write a series of numbers (1 to 10) to the pipe. The child process should read from the pipe, calculate the sum of the numbers, and print the result.

// Exercise 4:
// Write a program that creates a pipe using the pipe() function. Then, use fork() to create a child process. The parent process should write a string to the pipe. The child process should read from the pipe, convert the string to uppercase, and print the result.

// Exercise 5:
// Write a program that creates a pipe using the pipe() function. Then, use fork() to create a child process. The parent process should read a series of numbers from the user and write them to the pipe. The child process should read from the pipe, calculate the average of the numbers, and print the result.

// Exercise 6:
// Write a program that creates two pipes using the pipe() function. Then, use fork() to create a child process. The parent process should write a string to the first pipe, and the child process should read from the first pipe, convert the string to uppercase, and write the result to the second pipe. The parent process should read from the second pipe and print the final result.

// These exercises should help you practice using the pipe() function in various scenarios. Feel free to modify or extend them to further explore interprocess communication with pipes in C.

// int	main(void)
// {
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 		CustomError("Pipe creation failed.");
	
// 	int	pid = fork();
// 	if (pid == -1)
// 		CustomError("Fork creation failed.");
// 	if (pid == 0)
// 	{
// 		char str[100] = {'\0'};
// 		close(fd[1]);
// 		read(fd[0], &str, 100);
// 		printf("%s\n", str);
// 		close(fd[0]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		char *str = "Hello, child process!";
// 		close(fd[0]);
// 		write(fd[1], str, strlen(str));
// 		close(fd[1]);
// 	}
// }

// int	main(void)
// {
// 	int fd[2];
// 	if (pipe(fd) == -1)
// 		CustomError("Pipe creation failed.");
	
// 	int pid = fork();
// 	if (pid == -1)
// 		CustomError("Fork creation failed.");
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		int	n = 100;
// 		char *num = ft_itoa(n);
// 		write(fd[1], num, strlen(num));
// 		close(fd[1]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		wait(0);
// 		close(fd[1]);
// 		char num[15];
// 		read(fd[0], &num, 15);
// 		int n = atoi(num);
// 		printf("%d", n);
// 		close(fd[0]);
// 	}
// }

// int	main(void)
// {
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 		CustomError("Pipe creation failed.");

// 	int pid = fork();
// 	if (pid != 0)
// 	{
// 		close(fd[0]);
// 		char c = 49;
// 		while (c <= '9')
// 		{
// 			write(fd[1], &c, 1);
// 			c++;
// 		}
// 		close(fd[1]);
// 		exit(0);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		sleep(1);
// 		char *str[10];
// 		int i = 0;
// 		while (i < 9)
// 			read(fd[0], str[i++], 1);
// 		i = 1;
// 		close(fd[0]);
// 		int n;
// 		while (i <= 9)
// 		{
// 			n += atoi(str[i]);
// 			i++;
			
// 		}
// 		printf("The sum is: %i", n);
// 	}
//}

// int	main(void)
// {
// 	int fd[2];
// 	if (pipe(fd) == -1)
// 		CustomError("Pipe creation failed");
	
// 	int pid = fork();
// 	if (pid == -1)
// 		CustomError("Fork creation failed.");
	
// 	if (pid == 0)
// 	{
// 		close(fd[1]);
// 		char str[12];
// 		read(fd[0], str, 12);
// 		for (int i = 0; str[i]; i++)
// 		{
// 			if (str[i] >= 'a' && str[i] <= 'z')
// 				str[i] = str[i] - 32;
// 		}
// 		printf("%s\n", str);
// 		close(fd[0]);
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		char *str = "hello world\0";
// 		write(fd[1], str, 12);
// 		close(fd[1]);
// 	}
// }

// Certainly! Here are some exercises to practice using the execve() function in C. In addition to execve(), you can use other basic C functions like printf(), wait(), fork(), exit(), and strcpy(). Remember to include the necessary header files (stdio.h, unistd.h, sys/types.h, sys/wait.h, stdlib.h, string.h, etc.) for each exercise.

// Exercise 1:
// Write a program that uses execve() to execute the ls command. The program should provide the path to the ls command and pass appropriate arguments to list the contents of the current directory.

// Exercise 2:
// Write a program that creates a child process using fork(). The child process should use execve() to execute a different program, such as echo, with a custom message. The parent process should wait for the child process to finish and then print "Child process completed".

// Exercise 3:
// Write a program that creates a child process using fork(). The child process should execute a program that you compile separately (e.g., a simple C program). The parent process should wait for the child process to finish and then print "Child process completed".

// Exercise 4:
// Write a program that reads a command from the user and uses execve() to execute that command. The program should parse the user input to separate the command and its arguments, and then pass them to execve().

// Exercise 5:
// Write a program that reads a command from the user and uses execve() to execute that command with additional environment variables. The program should allow the user to input the environment variables and pass them to execve().

// Exercise 6:
// Write a program that uses execve() to execute a shell script (e.g., a file with a .sh extension). The program should provide the path to the shell script and pass appropriate arguments if required.

// These exercises should help you practice using the execve() function to execute external programs and scripts in various scenarios. Feel free to modify or extend them to further explore the versatility of execve() in C

// int	main(int argc, char **argv)
// {
// 	if (argc == 1)
// 		return 1;
// 	char str[] = "/usr/lib/";
// 	strcat(str, argv[1]);
// 	execve(str, argv + 1, NULL);
// }



/*

Idea:

# ./pipex infile cmd1 cmd2 outfile 
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)


Step to step:
- take 4 arguments.
- 1st and 4th are files
- 2nd and 3rd are shell commands
- env is the environment, it relies on PATH, that are the paths to the commands binaries
- 

- read from infile
- execute cmd1 with infile as input
- send that output to cmd2
- execute cmd2 with that output
- write that to outfile

*/

void	func_exit_error(void)
{
	perror("Error");
	exit(1);
}

void	func_print_error(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(1);
}

int	func_check_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) && envp[i][6])
			return (1);
		i++;
	}
	return (0);
}

char	**func_get_paths(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (!(ft_strnstr(envp[i], "PATH=", 5)))
		i++;
	res = ft_split(envp[i] + 5, ':');
	i = 0;
	while (res[i])
	{
		res[i] = ft_strjoin(res[i], "/");
		i++;
	}
	return(res);

}

char	*func_get_path(char *cmd, char **envp)
{
	char *possible_path;
	int	i;

	i = 0;
	while (envp[i])
	{
		possible_path = ft_strjoin(envp[i], cmd);
		if (access(possible_path, F_OK))
			return (possible_path);
		i++;
	}
	return (NULL);
}

void	func_execute_comm(char *cmd, char **envp)
{
	char **cmd_full;
	char *path;
	
	cmd_full = ft_split(cmd, ' ');
	path = getPath(cmd, envp);
	if (!path)
	{
		ft_split_free(cmd_full);
		free(path);
		printError("Command not found...");
	}
	if (execve(path, cmd_full, envp) == -1)
	{
		ft_split_free(cmd_full);
		free (path);
		printError("Problem executing the command.");
	}
}

void	func_child_process(int infile, char *cmd1, int *fd, char **envp)
{
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	executeIt(cmd1, envp);
	return ;
}

void    func_pipex_main(int infile, int outfile, char *cmd1, char *cmd2, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exitError();
	pid = fork();
	if (pid == -1)
		exitError();
	if (pid == 0)
		childProcess(infile, cmd1, fd, envp);
	wait(0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	executeIt(cmd2, envp);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	int		envp_check;
	char	**real_envp;

	real_envp = NULL;
	envp_check = checkEnvp(envp);
	if (envp_check)
		real_envp = getRealEnvp(envp);
	if (argc == 5 && envp_check)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (infile < 0 || outfile < 0)
			exitError();
		pipexMain(infile, outfile, argv[2], argv[3], real_envp);
	}
	else if (!envp_check)
		printError("No PATHS found for the command binaries...");
	else if (argc != 5)
		printError("Wrong number of arguments, correct usage of the program: './pipex infile cmd1 cmd2 outfile'");
	else
		printError("This error is not supposed to happen.");
	if (real_envp)
		ft_split_free(real_envp);
}
