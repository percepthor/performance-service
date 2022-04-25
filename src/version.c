#include <cerver/utils/log.h>

#include "version.h"

// print full percepthor version information
void percepthor_version_print_full (void) {

	cerver_log_msg ("\nPercepthor Performance Version: %s\n", PERCEPTHOR_VERSION_NAME);
	cerver_log_msg ("Release Date & time: %s - %s\n", PERCEPTHOR_VERSION_DATE, PERCEPTHOR_VERSION_TIME);
	cerver_log_msg ("Author: %s\n", PERCEPTHOR_VERSION_AUTHOR);

}

// print the version id
void percepthor_version_print_version_id (void) {

	cerver_log_msg ("\nPercepthor Performance Version ID: %s\n", PERCEPTHOR_VERSION);

}

// print the version name
void percepthor_version_print_version_name (void) {

	cerver_log_msg ("\nPercepthor Performance Version: %s\n", PERCEPTHOR_VERSION_NAME);

}
