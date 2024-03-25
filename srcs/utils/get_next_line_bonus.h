/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:45:35 by jfarkas           #+#    #+#             */
/*   Updated: 2024/03/24 21:56:06 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <stddef.h>
# define MAX_FD 1024
# define BUFFER_SIZE 42

int		ft_strlen(const char *str, char stop_count);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	update_buff(char *buff);
char	*ft_strjoin(char const *s1, char const *s2, char line_end);
void	get_next_buff(int fd, int *rd, char *buff);
char	*get_line(int fd, int *rd, char *buff);
char	*get_next_line(int fd);

#endif
