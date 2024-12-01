#include <stdio.h>

extern void testArrayList();

#ifdef USE_GLFW
	extern void testOpengl();
#endif

int main(int argc, char **argv) {
	testArrayList();
	#ifdef USE_GLFW
		testOpengl();
	#endif
	return 0;
}