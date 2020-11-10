/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writetest.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 12:41:21 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/18 22:59:14 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libasm.h"
#include "test.h"

void	write_test_rand(char *strbuf, char *ftbuf, char *sysbuf, int *fail, size_t size)
{
	int		i;
	int		testsize;

	i = 0;
	while (i < RTESTS)
	{
		testsize = rand_in_range(1, size);
		*fail += write_test(randa_nfill(strbuf, testsize), ftbuf, sysbuf, testsize);
		i++;
	}
}

int		write_fd_test(int fd, char *ftbuf, char *sysbuf)
{
	ssize_t ftret;
	ssize_t sysret;
	int		fterrno;
	int		syserrno;
	int		fail = 0;

	errno = 0;										//Prep
	bzero(ftbuf, SIZE);
	bzero(sysbuf, SIZE);
	if (fd == 2 || fd == 1 || fd == 0)
		write(fd, "\n", 1);

	ftret = ft_write(fd, "test write to fd", 16);	//Write with ft_write
	fterrno = errno;
	if (fd == 2 || fd == 1 || fd == 0)
		write(fd, "\n", 1);

	sysret = write(fd, "test write to fd", 16);		//Write with write
	syserrno = errno;
	if (fd == 2 || fd == 1 || fd == 0)
		write(fd, "\n", 1);

	if (ftret != sysret)							//Check results
		fail = 1;
	if (fterrno != syserrno)
		fail = 1;
	printf("%-6ld %-6ld %-3d %-3d: %d, %-54.54s\n", sysret, ftret, syserrno, fterrno, fail, "test write to fd");
	if (FAILEXIT && fail)
		error_out("Failed write test");
	return (fail);
}

int		write_test(char *str, char *ftbuf, char *sysbuf, size_t size)
{
	int		ftfd;
	int		sysfd;
	ssize_t ftret;
	ssize_t sysret;
	int		fterrno;
	int		syserrno;
	int		fail = 0;

	errno = 0;										//Prep
	bzero(ftbuf, SIZE);
	bzero(sysbuf, SIZE);

	ftfd = open_safe("text1.txt", O_RDWR, 0664);	//Write with ft_write
	ftret = ft_write(ftfd, str, size);
	fterrno = errno;
	close_safe(ftfd);

	sysfd = open_safe("text2.txt", O_RDWR, 0664);	//Write with write
	sysret = write(sysfd, str, size);
	syserrno = errno;
	close_safe(sysfd);

	ftfd = open_safe("text1.txt", O_RDWR, 0664);	//Read results
	read(ftfd, ftbuf, size);
	close_safe(ftfd);
	sysfd = open_safe("text2.txt", O_RDWR, 0664);
	read(sysfd, sysbuf, size);
	close_safe(sysfd);

	if (strcmp(ftbuf, sysbuf))						//Check results
		fail = 1;
	if (ftret != sysret)
		fail = 1;
	if (fterrno != syserrno)
		fail = 1;
	printf("%-6ld %-6ld %-3d %-3d: %d, %-27.27s %-26.26s\n", sysret, ftret, syserrno, fterrno, fail, sysbuf, ftbuf);
	if (FAILEXIT && fail)
		error_out("Failed write test");
	return (fail);
}
