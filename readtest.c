/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readtest.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/15 14:59:06 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/18 23:02:17 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libasm.h"
#include "test.h"

void	read_test_rand(char *strbuf, char *ftbuf, char *sysbuf, int *fail, size_t size)
{
	int		i;
	int		testsize;

	i = 0;
	while (i < RTESTS)
	{
		testsize = rand_in_range(1, size);
		*fail += read_test(randa_nfill(strbuf, testsize), ftbuf, sysbuf, testsize);
		i++;
	}
}

void	read_stdin_test()
{
	//read from stdin and print out the read in? manually validated
}

int		read_test(char *str, char *ftbuf, char *sysbuf, size_t size)
{
	int		fd;
	ssize_t ftret;
	ssize_t sysret;
	int		fterrno;
	int		syserrno;
	int		cmp;
	int		fail = 0;

	errno = 0;										//Prep
	bzero(ftbuf, SIZE);
	bzero(sysbuf, SIZE);

	fd = open_safe("text1.txt", O_RDWR, 0664);		//Write test data
	if (write(fd, str, size) == -1)
		error_out("Failed to write test data to file");
	close_safe(fd);

	fd = open_safe("text1.txt", O_RDWR, 0664);		//Read with ft_write
	ftret = ft_read(fd, ftbuf, size);
	fterrno = errno;
	ftbuf[ftret] = '\0';
	close_safe(fd);

	fd = open_safe("text1.txt", O_RDWR, 0664);		//Read with write
	sysret = read(fd, sysbuf, size);
	syserrno = errno;
	sysbuf[sysret] = '\0';
	close_safe(fd);

	if (strcmp(ftbuf, sysbuf))						//Check results
		fail = 1;
	if (ftret != sysret)
		fail = 1;
	if (fterrno != syserrno)
		fail = 1;
	printf("%-6ld %-6ld %-3d %-3d: %d, %-27.27s %-26.26s\n", sysret, ftret, syserrno, fterrno, fail, sysbuf, ftbuf);
	if (FAILEXIT && fail)
		error_out("Failed read test");
	return (fail);
}
