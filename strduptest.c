/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strduptest.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 13:12:50 by averheij      #+#    #+#                 */
/*   Updated: 2020/06/23 11:02:58 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "libasm.h"
#include "test.h"

void	strdup_test_rand(char *buf, int *fail, size_t size)
{
	int		i;
	int		testsize;

	i = 0;
	while (i < RTESTS)
	{
		testsize = rand_in_range(1, size);
		(*fail) += strdup_test(randa_nfill(buf, testsize), testsize);
		i++;
	}
}

int		strdup_test(char *src, size_t size)
{
	int		fail = 0;
	char	*ft;
	char	*sys;
	int		fterrno;
	int		syserrno;
	int		cmp;

	errno = 0;
	sys = strdup(src);
	fterrno = errno;
	ft = ft_strdup(src);
	syserrno = errno;

	cmp = strcmp(sys, ft);
	if (cmp)
		fail = 0;
	if (fterrno != syserrno)
		fail = 0;

	printf("%-6lu %-3d %-3d %-3d: %d, %-28.28s %-28.28s\n", size, cmp, syserrno, fterrno, fail, ft, sys);
	if (sys)
		free(sys);
	if (ft)
		free(ft);
	if (FAILEXIT && fail)
		error_out("Failed strdup test");
	return (fail);
}
