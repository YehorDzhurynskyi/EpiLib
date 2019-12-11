#pragma once

#ifdef _DEBUG
#define epiDEBUG
#else
#define epiRELEASE
#endif

#ifdef epiDEBUG
#define epiDEBUG_ONLY(x) x
#else
#define epiDEBUG_ONLY(x)
#endif

#ifdef _WIN32
#define epiWINDOWS
#endif
