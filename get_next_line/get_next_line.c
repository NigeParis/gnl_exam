/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrobinso <nrobinso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:11:12 by nrobinso          #+#    #+#             */
/*   Updated: 2024/05/29 08:35:35 by nrobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	if (((BUFFER_SIZE < 0) || BUFFER_SIZE > 219000000) || (fd < 0))
		return (NULL);
	static char buff[BUFFER_SIZE + 1];
	char *line;
	char *newline_pos;
	int	 endline_pos;
	int nbytes;

	line = ft_strdup(buff);
	if (!line)
		return (NULL);
	newline_pos = NULL;
	endline_pos = 0;
	nbytes = 1;

	while (!(newline_pos = ft_strchr(line, '\n')) && nbytes)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(line), NULL);
		buff[nbytes] = '\0';
		line = ft_strjoin(line, buff);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);

	if (newline_pos != NULL)
	{
		endline_pos = newline_pos - line + 1;
		ft_strcpy(buff, newline_pos + 1);
	}
	else
	{
		endline_pos = ft_strlen(line);
		buff[0] = '\0';
	}
	line[endline_pos] = '\0';
	return (line);
}



int main(void)
{
	int fd = 0;
	char *str;
	int i = 0;

	fd = open("./test.txt", R_OK);
	
	while (i < 2)
	{
	str = get_next_line(fd);
	
	printf("%s", str);
	free (str);
	i++;
	}

	return (0);
}