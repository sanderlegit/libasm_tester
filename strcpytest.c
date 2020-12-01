/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strcpytest.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/08 13:05:52 by averheij      #+#    #+#                 */
/*   Updated: 2020/12/01 16:35:23 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libasm.h"
#include "test.h"

void	strcpy_test_rand(char *buf, char *buf2, int *fail, size_t size)
{
	int		i;
	int		testsize;

	i = 0;
	while (i < RTESTS)
	{
		testsize = rand_in_range(1, size);
		(*fail) += strcpy_test(buf2, randa_nfill(buf, testsize), testsize);
		i++;
	}
}

int		strcpy_test(char *dest, const char *src, size_t size)
{
	char 	*ret;
	int		fail;
	int		cmp;

	fail = 0;
	bzero(dest, SIZE);

	ret = _ft_strcpy(dest, src);
	cmp = strncmp(dest, src, strlen(src) + 1);

	if (cmp)
		fail = 1;
	else if (ret != dest)
		fail = 1;
	printf("%-6lu %-3d %d   : %d, %-60.60s\n", size, cmp, ret == dest, fail, dest);
	if (FAILEXIT && fail)
		error_out("Failed strcpy test");
	return (fail);
}
