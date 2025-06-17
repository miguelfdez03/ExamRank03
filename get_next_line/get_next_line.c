/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguel-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:52:14 by miguel-f          #+#    #+#             */
/*   Updated: 2025/06/17 12:52:22 by miguel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


char *ft_strdup(char *line)
{
	char *new;
	int i = 0;
	while(line[i])
		i++;
	new = malloc((i + 1)* sizeof(char *));
	if(!new)
		return(NULL);
	i = 0;
	while(line[i])
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return(new);
}

char *get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	char			line[70000];
	static int 		buffer_read;
	static int		buffer_pos;
	int i = 0;
	if(fd < 0 || BUFFER_SIZE <= 0)//Ojo cuidado el puto fd < 0 //////
		return(NULL);
	while(1)
	{
		if(buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if(buffer_read <= 0)
				break;
		}
		if(line[i - 1] == '\n')
			break;
		line[i] = buffer[buffer_pos];
		i++;
		buffer_pos++;
	}
	line[i] = '\0';
	if(i == 0)
		return(NULL);
	return(ft_strdup(line));
}
