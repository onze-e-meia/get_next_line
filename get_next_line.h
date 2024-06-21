/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:33 by tforster          #+#    #+#             */
/*   Updated: 2023/11/22 11:55:56 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_char
{
	char			content;
	struct s_char	*next;
}					t_char;

typedef struct s_info
{
	char	s_buffer[BUFFER_SIZE + 1];
	t_char	*file;
	int		len_str;
}			t_info;

char	*get_next_line(int fd);
t_char	*ft_newnode(char content);
void	ft_lstadd_front(t_char **lst, t_char *new_node);
void	ft_clear_node(t_char **file);

#endif
