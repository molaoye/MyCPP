#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <exception>
#include <typeinfo>
#include <fstream>

class CommonUtil{
public:
	int stringSplit(char dst[][80], char* str, const char* spl) {
		int n = 0;
		char *result = NULL;
		result = strtok(str, spl);
		while (result != NULL) {
			strcpy(dst[n++], result);
			result = strtok(NULL, spl);
		}
		return n;
	}

};
