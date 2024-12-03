#include "test.h"

extern int testArrayList();
extern int testOpengl();

int main(int argc, char **argv) {
	testArrayList();
	testOpengl();
	return 0;
}