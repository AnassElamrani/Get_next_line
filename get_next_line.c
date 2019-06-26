/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anelamra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:52:31 by anelamra          #+#    #+#             */
/*   Updated: 2019/06/25 18:56:51 by anelamra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	static char		*rest[10240];
	int				ret;

	RETURN_IF((BUFF_SIZE < 0) || read(fd, buf, 0) < 0 || !line || fd < 0
	|| fd > 10240, -1);
	ret = 0;
	if (!rest[fd])
		RETURN_IF(!(rest[fd] = ft_strnew(0)), -1);
	while (!ft_strchr(rest[fd], '\n') && (ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = 0;
		RETURN_IF(!(tmp = ft_strjoin(rest[fd], buf)), -1);
		free(rest[fd]);
		rest[fd] = tmp;
	}
	RETURN_IF((rest[fd][0] == '\0') && (ret < 1), ret);
	RETURN_IF(!(*line = ft_strsub(rest[fd], 0, ft_n(rest[fd], "\n"))), -1);
	RETURN_IF(!(tmp = ft_strdup(rest[fd][ft_n(rest[fd], "\n")] == '\n' ?
					&rest[fd][ft_n(rest[fd], "\n") + 1] : "\0")), -1);
	free(rest[fd]);
	rest[fd] = tmp;
	return (1);
}