/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:05:29 by fduque-a          #+#    #+#             */
/*   Updated: 2023/06/15 01:06:24 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	CustomError(char *str)
{
	printf("%s\n", str);
	exit(0);
}

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

int	main(void)
{
	int	fd[2];
	if (pipe(fd) == -1)
		CustomError("Pipe creation failed.");
	
	int	pid = fork();
	if (pid == -1)
		CustomError("Fork creation failed.");
	if (pid == 0)
	{
		char str[100] = {'\0'};
		close(fd[1]);
		read(fd[0], &str, 100);
		printf("%s\n", str);
		close(fd[0]);
		exit(0);
	}
	else
	{
		char *str = "Hello, child process!";
		close(fd[0]);
		write(fd[1], str, strlen(str));
		close(fd[1]);
	}
}