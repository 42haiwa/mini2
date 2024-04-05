/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjouenne <cjouenne@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:47:10 by cjouenne          #+#    #+#             */
/*   Updated: 2023/10/29 17:01:38 by cjouenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

void	alloc_line(t_list *list, char **line);
int		is_line(t_list *list);
t_list	*get_last_block(t_list *list);
void	dealloc_list(t_list *list);
size_t	ft_strlen(const char *s);

void	_get_line(t_list *list, char **line);
void	read_and_stack(t_list **list, int *read_return, int fd);
void	clear_list(t_list **list);
char	*get_next_line(int fd);
#endif
