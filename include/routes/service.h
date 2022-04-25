#ifndef _PERCEPTHOR_ROUTES_SERVICE_H_
#define _PERCEPTHOR_ROUTES_SERVICE_H_

struct _HttpReceive;
struct _HttpRequest;

// GET /api/performance
extern void percepthor_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET /api/performance/version
extern void percepthor_version_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

// GET *
extern void percepthor_catch_all_handler (
	const struct _HttpReceive *http_receive,
	const struct _HttpRequest *request
);

#endif