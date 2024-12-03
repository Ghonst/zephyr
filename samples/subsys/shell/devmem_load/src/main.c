/*
 * Copyright (c) 2021 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

int main(void)
{
	printf("Test Hello World! %s\n", CONFIG_BOARD_TARGET);
	return 0;
};
