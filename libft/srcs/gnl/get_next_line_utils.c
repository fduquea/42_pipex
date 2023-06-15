/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduque-a <fduque-a@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:04:23 by fduque-a          #+#    #+#             */
/*   Updated: 2023/05/12 09:42:03 by fduque-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == (unsigned char) c)
		return ((char *)s + i);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *static_buffer, char *temp)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!static_buffer)
	{
		static_buffer = malloc(sizeof(char) * 1);
		static_buffer[0] = '\0';
	}
	len = ft_strlen_gnl(static_buffer) + ft_strlen_gnl(temp) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	while (static_buffer[++i])
		dest[i] = static_buffer[i];
	while (temp[++j])
		dest[i + j] = temp[j];
	dest[i + j] = '\0';
	free(static_buffer);
	return (dest);
}

char	*ft_firstline(char *string)
{
	char	*firstline;
	size_t	i;
	size_t	j;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	firstline = malloc(sizeof(char) * (i + 2));
	if (!firstline)
		return (NULL);
	j = -1;
	while (++j <= i)
		firstline[j] = string[j];
	firstline[j] = '\0';
	return (firstline);
}

char	*ft_secondline(char *string)
{
	char	*secondline;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	len = ft_strlen_gnl(string);
	secondline = malloc(sizeof(char) * (len - i));
	if (!secondline)
		return (NULL);
	j = -1;
	while (++i < len)
		secondline[++j] = string[i];
	secondline[++j] = '\0';
	free(string);
	return (secondline);
}
