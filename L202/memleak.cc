#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	char *ptr;
	ptr = (char *)calloc(sizeof(char), 256);
	ptr = "ahaha";
	printf("%s\n", ptr);
	return 0;
}
