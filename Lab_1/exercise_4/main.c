#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

/* include the correct .h file */


int main(){
	int a;
	char line[100];
	char library_name[100];
	void *handle;
	char *error;

	printf("What version of the functions you whant to use?\n");
	printf("\t1 - Normal    (lib1)\n");
	printf("\t2 - Optimized (lib2)\n");
	if(fgets(line, 100, stdin) == NULL) {
		exit(EXIT_FAILURE);
	}
	sscanf(line,"%d", &a);
	if (a == 1){
		strcpy(library_name, "./lib1.so");
		printf("running the normal versions from %s \n", library_name);
	}else{
		if(a== 2){
			strcpy(library_name, "./lib2.so");
			printf("running the normal versions %s \n", library_name);
		}else{
			printf("Not running anything\n");
			exit(-1);
		}
	}
	/* load library from name library_name */
	handle = dlopen(library_name, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error opening library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

	dlerror();

	/* declare pointers to functions */
	void (*func_1)();
    void (*func_2)();

	// Load func_1 from the loaded library
    *(void **) (&func_1) = dlsym(handle, "func_1");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error loading func_1: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    // Load func_2 from the loaded library
    *(void **) (&func_2) = dlsym(handle, "func_2");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error loading fsunc_2: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    // Call func_1 from whichever library was loaded
    func_1();

    // Call func_2 from whichever library was loaded
    func_2();

    // Close the library
    dlclose(handle);

	exit(0);
}
