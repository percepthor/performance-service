#include <cerver/http/http.h>
#include <cerver/http/request.h>
#include <cerver/http/response.h>

#include "controllers/service.h"

// GET /api/performance
void percepthor_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (percepthor_works, http_receive);

}

// GET /api/performance/version
void percepthor_version_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	(void) http_response_send (current_version, http_receive);

}

// GET *
void percepthor_catch_all_handler (
	const HttpReceive *http_receive,
	const HttpRequest *request
) {

	http_response_send (catch_all, http_receive);

}
