#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cerver/http/response.h>

#include <cerver/utils/utils.h>

#include "version.h"

HttpResponse *percepthor_works = NULL;
HttpResponse *current_version = NULL;

HttpResponse *catch_all = NULL;

unsigned int percepthor_service_init (void) {

	unsigned int retval = 1;

	percepthor_works = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Percepthor performance works!"
	);

	char *status = c_string_create (
		"%s - %s",
		PERCEPTHOR_VERSION_NAME, PERCEPTHOR_VERSION_DATE
	);

	if (status) {
		current_version = http_response_json_key_value (
			HTTP_STATUS_OK, "version", status
		);

		free (status);
	}

	catch_all = http_response_json_key_value (
		HTTP_STATUS_OK, "msg", "Percepthor performance service!"
	);

	if (
		catch_all
		&& percepthor_works && current_version
	) retval = 0;

	return retval;

}

void percepthor_service_end (void) {

	http_response_delete (percepthor_works);
	http_response_delete (current_version);

	http_response_delete (catch_all);

}
