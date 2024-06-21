/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:01 by tforster          #+#    #+#             */
/*   Updated: 2023/11/22 12:30:35 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	check_nl(t_info *info, int *nl)
{
	char	*new_buffer;
	char	*temp_buffer;

	new_buffer = info->s_buffer;
	temp_buffer = info->s_buffer;
	while (*temp_buffer)
	{
		if (*nl)
		{
			ft_lstadd_front(&(info->file), ft_newnode(*temp_buffer));
			(info->len_str)++;
			if (*temp_buffer == '\n')
				*nl = 0;
			*temp_buffer++ = '\0';
		}
		else
		{
			*new_buffer++ = *temp_buffer;
			*temp_buffer++ = '\0';
		}
	}
	*new_buffer = '\0';
}

char	*get_str(t_info *info)
{
	char	*str;
	char	*temp_str;
	t_char	*temp_file;

	temp_file = info->file;
	str = (char *) malloc((info->len_str + 1) * sizeof(char));
	if (!str)
	{
		while (temp_file)
		{
			temp_file = temp_file->next;
			ft_clear_node(&info->file);
		}
		return (NULL);
	}
	temp_str = str + info->len_str;
	*temp_str-- = '\0';
	while (temp_file)
	{
		*temp_str-- = temp_file->content;
		temp_file = temp_file->next;
		ft_clear_node(&info->file);
	}
	info->len_str = 0;
	return (str);
}

void	read_file(int fd, t_info *info)
{
	int	bytes;
	int	nl;

	bytes = 1;
	nl = 1;
	while (bytes > 0 && nl)
	{
		if (*info->s_buffer)
			check_nl(info, &nl);
		else
		{
			bytes = read(fd, info->s_buffer, BUFFER_SIZE);
			if (bytes > 0)
			{
				*(info->s_buffer + bytes) = '\0';
				check_nl(info, &nl);
			}
		}
	}
}

char	*get_next_line(int fd)
{
	static t_info	info;
	char			*str;
	int				count;

	if (fd < 0 || read(fd, info.s_buffer, 0))
	{
		str = info.s_buffer;
		count = BUFFER_SIZE;
		while (count-- > 0)
			*str++ = '\0';
		return (NULL);
	}
	read_file(fd, &info);
	if (info.file)
	{
		str = get_str(&info);
		free(info.file);
		return (str);
	}
	else
		free(info.file);
	return (NULL);
}
