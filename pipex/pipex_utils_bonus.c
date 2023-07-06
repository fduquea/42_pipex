/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:24:47 by fduque-a          #+#    #+#             */
/*   Updated: 2023/07/06 14:46:22 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// check for errors
void	func_check(int result, char *message)
{
	if (result == -1)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		if (message)
			ft_printf("pipex: ");
		perror(message);
		exit(1);
	}
}

// make envp become a char** only containing the PATHS
// find the "PATH=" string in envp
// use ft_split to divide all the paths
// return the new char** containing only the paths
static char	**func_get_real_envp(char **envp)
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
static char	*func_build_path(char *envp, char *command)
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
