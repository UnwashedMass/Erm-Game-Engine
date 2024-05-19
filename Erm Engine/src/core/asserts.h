#pragma once

#include "defines.h"

#define EASSERTIONS_ENABLED

#ifdef EASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __debugbreak()

#endif // KASSERTIONS_ENABLED

EAPI void Report_assertion_failure(const char* expression, const char* message, const char* file, __int32 line);

#define EASSERT(expr){			\
	if (expr) {					\
								\
								\
	}							\
	else {						\
		Report_assertion_failure(#expr, "", __FILE__, __LINE__);\
		debugBreak();			\
	}							\
}								\

#define EASSERT_MSG(expr,message){\
	if (expr) {					\
								\
								\
	}							\
	else {						\
		Report_assertion_failure(#expr, message, __FILE__, __LINE__);\
		debugBreak();			\
	}							\
}	
#ifdef  _DEBUG
#define EASSERT_DEBUG(expr){\
	if (expr) {					\
								\
								\
	}							\
	else {						\
		Report_assertion_failure(#expr, "", __FILE__, __LINE__);\
		debugBreak();			\
	}							\
}
#else
#define EASSERT_DEBUG(expr)
#endif //  _DEBUG

#else

#define EASSERT(expr) //does nothin
#define EASSERT_MSG(expr,message) //does nothin
#define EASSERT_DEBUG(expr) //does nothin

#endif