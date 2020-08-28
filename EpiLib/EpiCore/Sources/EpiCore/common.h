#pragma once

#include <algorithm>

#define EPI_GENREGION_BEGIN(x)
#define EPI_GENREGION_END(x)

#define EPI_NAMESPACE_BEGIN() namespace epi {
#define EPI_NAMESPACE_END() }

#define epiAssert(_x, _msg) assert(_x && "Function (" __FUNCTION__ "):" #_msg)
#define epiExpect(_x, _msg) assert(_x && "Function (" __FUNCTION__ "):" #_msg)
#define epiValidate(_x, _msg) isValid = isValid && (_x); epiExpect(_x, _msg)

#define epiFor(_n) for (int index = 0; index < _n; ++index)

#define epiTriggerBreakpoint() __debugbreak()

#define epiAs(_T, _V) static_cast<_T>(_V)
#define epiArrLen(_V) (sizeof(_V) / sizeof(_V[0]))

#define epiRand01() ((epiFloat)rand() / RAND_MAX)
#define epiToRadians(_degree) ((epiFloat)(_degree) * (M_PI / 180.0f))
#define epiToDegree(_radians) ((epiFloat)(_radians) * (180.0f / M_PI))
