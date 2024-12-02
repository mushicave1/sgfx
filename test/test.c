#include <stdio.h>

extern void testArrayList();
extern void testOpengl();

int main(int argc, char **argv) {
	testArrayList();
	testOpengl();
	return 0;
}