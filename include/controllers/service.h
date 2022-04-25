#ifndef _PERCEPTHOR_SERVICE_H_
#define _PERCEPTHOR_SERVICE_H_

struct _HttpResponse;

extern struct _HttpResponse *percepthor_works;
extern struct _HttpResponse *current_version;

extern struct _HttpResponse *catch_all;

extern unsigned int percepthor_service_init (void);

extern void percepthor_service_end (void);

#endif