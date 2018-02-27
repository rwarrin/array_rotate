/**
 * Rotates an array of N elements left by I positions.
 *
 * This program demonstrates a simple technique to rotate an array of n-elements
 * left by i-positions in-place using only one 4-byte integer of additional
 * space.
 *
 * The algorithm to accomplish this looks like this: Divide the range A into two
 * ranges A and B, the first is the amount to shift, and the second is the
 * remaining elements of the array.
 * Thus array A becomes AB.
 *
 * Now we want to shift left so the order becomes BA using as little additional
 * memory as possible and as little extra time as possible.
 *
 * First we reverse range A so our expression becomes ArB
 * Next we reverse range B and we get the expression ArBr
 * Finally we reverse the entire rage ABr
 * 
 * Visualized:
 * abcdefgh => shift 3
 * cbadefgh
 * cbadefgh
 * hgfedabc
 *
 * We also use an efficient Reverse algorithm that makes N/2 swaps.
 **/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
#define GenericReverse(Array, Type, Start, End) { \
	for(int32_t S = Start, E = End - 1; S < E; ++S, --E) { \
		Type Temp = Array[S]; \
		Array[S] = Array[E]; \
		Array[E] = Temp; \
	}\
}

static inline void
Reverse(int32_t *Array, int32_t Start, int32_t End)
{
	for(int32_t Left = Start, Right = End - 1;
		Left < Right;
		++Left, --Right)
	{
		int32_t Temp = Array[Left];
		Array[Left] = Array[Right];
		Array[Right] = Temp;
	}
}

// TODO(rick): Fix rotate bug, 1 rotate is actually rotating 2 and pulling in a
// random value from the end of the array
int main(int Argc, char **Argv)
{
	if(Argc != 3)
	{
		printf("Rotates an array of N elements left by I positions.\n");
		printf("Usage: %s <N> <I>\n", Argv[0]);
		return 1;
	}

	int32_t Elements = atoi(Argv[1]);
	int32_t Rotate = atoi(Argv[2]);

	if(Elements <= 0)
	{
		fprintf(stderr, "Array size cannot be less than or equal to zero.\n");
		return 2;
	}

	if(Rotate < 0)
	{
		fprintf(stderr, "Cannot rotate a negative amount.\n");
		return 3;
	}

	int32_t *Array = malloc(sizeof(int32_t) * Elements);
	if(!Array)
	{
		fprintf(stderr, "Failed to allocate enough space for the list.\n");
		return 4;
	}

	int32_t Index = 0;
	int32_t Number = 0;
	while((scanf("%d", &Number) != EOF) &&
		  (Index < Elements - 1))
	{
		Array[Index++] = Number;
	}

	Reverse(Array, 0, Rotate);
	Reverse(Array, Rotate, Elements);
	Reverse(Array, 0, Elements);

	for(int32_t i = 0; i < Elements; ++i)
	{
		printf("%d ", Array[i]);
	}
	printf("\n");

	free(Array);
	return 0;
}
