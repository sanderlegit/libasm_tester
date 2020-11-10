/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 13:00:56 by averheij      #+#    #+#                 */
/*   Updated: 2020/11/10 15:48:43 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# define PRINT	1
# define VERBOSE	1
# define RTESTS	100
# define FAILEXIT	1
# define SIZE	999999
# include <stddef.h>

char			*randa_nfill(char *arr, size_t n);
long long		rand_in_range(long long min, long long max);
void			error_out(char *str);

int				strlen_test(char *str);
void			strlen_test_rand(char *buf, int *fail, size_t size);

int				strcpy_test(char *dest, const char *src, size_t size);
void			strcpy_test_rand(char *buf, char *buf2, int *fail, size_t size);

int				strcmp_test(const char *s1, const char *s2);
void			strcmp_test_rand(char *buf, char *buf2, int *fail, size_t size);

int				open_safe(char *filename, int mode, int priv);
void			close_safe(int fd);

int				write_test(char *str, char *ftbuf, char *sysbuf, size_t size);
int				write_fd_test(int fd, char *ftbuf, char *sysbuf);
void			write_test_rand(char *strbuf, char *ftbuf, char *sysbuf,
					int *fail, size_t size);

int				read_test(char *str, char *ftbuf, char *sysbuf, size_t size);
void			read_test_rand(char *strbuf, char *ftbuf, char *sysbuf,
					int *fail, size_t size);
int				read_error_test(int fd, char *ftbuf, char *sysbuf, size_t size);

int				strdup_test(char *src, size_t size);
void			strdup_test_rand(char *buf, int *fail, size_t size);
#endif
