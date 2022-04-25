#ifndef _PERCEPTHOR_RUNTIME_H_
#define _PERCEPTHOR_RUNTIME_H_

#define RUNTIME_TYPE_MAP(XX)						\
	XX(0,  NONE,      		Undefined)				\
	XX(1,  DEVELOPMENT,     Development)			\
	XX(2,  LOCAL,	     	Local)					\
	XX(3,  TEST,     	 	Test)					\
	XX(4,  PRODUCTION,      Production)

typedef enum RuntimeType {

	#define XX(num, name, string) RUNTIME_TYPE_##name = num,
	RUNTIME_TYPE_MAP(XX)
	#undef XX

} RuntimeType;

extern const char *runtime_to_string (const RuntimeType type);

extern const RuntimeType runtime_from_string (const char *string);

#endif