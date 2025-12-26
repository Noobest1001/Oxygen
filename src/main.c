#include <stdio.h>
#include <stdlib.h>

#include "../helpers/version.h"

int main(void)
{
	const Version temp = Version_Init(1, 0, 0);

	const Version *v = &temp;
	if (v != NULL)
	{
		printf("Oxygen Version: %s\n", print_Version(&temp));
		exit(EXIT_FAILURE);
	}
	// I know that this may never be reached, but it might be nice to have it here just in case
	// ReSharper disable once CppRedundantElseKeywordInsideCompoundStatement
	else
	{
		// ReSharper disable once CppDFAUnreachableCode
		printf("[Error] Version pointer is NULL\n");
		exit(EXIT_FAILURE);
	}
}