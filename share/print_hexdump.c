//
// Created by Darth Butterwell on 6/5/21.
//

#include <stdlib.h>
#include <stdio.h>

void		print_hexdump(const char *fmt, const void *data, size_t addr, \
	size_t size)
{
	static const char *hex = "0123456789abcdef";
	unsigned char *s;
	size_t cnt;

	cnt = 0;
	s = (unsigned char *) data;
	while (cnt < size)
	{
		if (!(cnt % 16))
		{
			if (cnt > 0)
				printf("\n");
			printf(fmt, addr + cnt);
		}
		printf("%c%c ", hex[s[cnt] >> 4], hex[s[cnt] & 15]);
		cnt++;
	}
	printf("\n");
}