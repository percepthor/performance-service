#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <signal.h>

#include <cerver/version.h>
#include <cerver/cerver.h>

#include <cerver/http/http.h>
#include <cerver/http/route.h>

#include <cerver/utils/log.h>
#include <cerver/utils/utils.h>

#include "percepthor.h"
#include "version.h"

#include "routes/service.h"

static Cerver *performance_service = NULL;

void end (int dummy) {
	
	if (performance_service) {
		cerver_stats_print (performance_service, false, false);
		cerver_log_msg ("\nHTTP Cerver stats:\n");
		http_cerver_all_stats_print ((HttpCerver *) performance_service->cerver_data);
		cerver_log_line_break ();
		cerver_teardown (performance_service);
	}

	(void) percepthor_end ();

	cerver_end ();

	exit (0);

}

static void percepthor_set_percepthor_routes (HttpCerver *http_cerver) {

	/* register top level route */
	// GET /api/performance
	HttpRoute *percepthor_route = http_route_create (REQUEST_METHOD_GET, "api/performance", percepthor_handler);
	http_cerver_route_register (http_cerver, percepthor_route);

	/* register percepthor children routes */
	// GET api/performance/version
	HttpRoute *percepthor_version_route = http_route_create (REQUEST_METHOD_GET, "version", percepthor_version_handler);
	http_route_child_add (percepthor_route, percepthor_version_route);

}

static void start (void) {

	performance_service = cerver_create (
		CERVER_TYPE_WEB,
		"percepthor-api",
		PORT,
		PROTOCOL_TCP,
		false,
		CERVER_CONNECTION_QUEUE
	);

	if (performance_service) {
		/*** cerver configuration ***/
		cerver_set_receive_buffer_size (performance_service, CERVER_RECEIVE_BUFFER_SIZE);
		cerver_set_thpool_n_threads (performance_service, CERVER_TH_THREADS);
		cerver_set_handler_type (performance_service, CERVER_HANDLER_TYPE_THREADS);

		/*** web cerver configuration ***/
		HttpCerver *http_cerver = (HttpCerver *) performance_service->cerver_data;

		percepthor_set_percepthor_routes (http_cerver);

		// add a catch all route
		http_cerver_set_catch_all_route (http_cerver, percepthor_catch_all_handler);

		if (cerver_start (performance_service)) {
			cerver_log_error (
				"Failed to start %s!", performance_service->info->name
			);

			cerver_delete (performance_service);
		}
	}

	else {
		cerver_log_error ("Failed to create cerver!");

		cerver_delete (performance_service);
	}

}

int main (int argc, char const **argv) {

	srand (time (NULL));

	// register to the quit signal
	(void) signal (SIGINT, end);
	(void) signal (SIGTERM, end);

	// to prevent SIGPIPE when writting to socket
	(void) signal (SIGPIPE, SIG_IGN);

	cerver_init ();

	cerver_version_print_full ();

	percepthor_version_print_full ();

	if (!percepthor_init ()) {
		start ();
	}

	else {
		cerver_log_error ("Failed to init percepthor!");
	}

	(void) percepthor_end ();

	cerver_end ();

	return 0;

}
