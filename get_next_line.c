/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:54:25 by aait-bou          #+#    #+#             */
/*   Updated: 2023/12/18 21:14:40 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((strlen(left_str) + strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[strlen(left_str) + strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char* process_left(char* result)
{
  int i;
  char *line;

  i = 0;
  if (!result || !result[i])
    return NULL;
  while(result[i] != '\0' && result[i] != '\n')
    i++;
  line = malloc (sizeof(char) * (i + 2));
  if (!line)
    return NULL;
  i = 0;
  while(result[i] && result[i] != '\n')
  {
    line[i] = result[i];
    i++;
  }
  if (result[i] == '\n')
  {
    line[i] = result[i];
    i++;
  }
  line[i] = '\0';
  return line;
}


char* process_right(char* result)
{
  int i;
  char* remaining;
  int j;

  i = 0;
  while(result[i] && result[i] != '\n')
    i++;
  i++;
  remaining = malloc(sizeof(char) * (strlen(result) - i + 1));
  if (!remaining)
    return NULL;
  j = 0;
  while(result[i])
    remaining[j++] = result[i++];
  remaining[j] = '\0';
  return remaining;
}

char* get_next_line(int fd)
{
  char *buffer;
  char* line;
  static char* result = NULL;
  int bytes_read;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);

  buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buffer)
    return NULL;

  bytes_read = 1;
  while (bytes_read != 0 && (!result || !strchr(result, '\n')))
  {
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read == -1)
    {
      free(result);
      free(buffer);
      return (NULL);
    }

    buffer[bytes_read] = '\0';
    result = ft_strjoin(result, buffer);
  }

  line = process_left(result);
  if (!line)
  {
    free(buffer);
    return (NULL);
  }

  result = process_right(result);
  free(buffer);

  return line;
}


int main(void)
{
    int fd;
    char* next_line;
    fd = open("text.txt", O_RDONLY);
    next_line = get_next_line(fd);
    printf ("%s", next_line);
    close(fd);
    return 0;
}





