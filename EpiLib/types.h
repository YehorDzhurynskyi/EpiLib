#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

using epiChar = char;
using epiBool = bool;
using epiByte = uint8_t;

using epiSize_t = size_t;

using epiU8 = uint8_t;
using epiU16 = uint16_t;
using epiU32 = uint32_t;
using epiU64 = uint64_t;

using epiS8 = int8_t;
using epiS16 = int16_t;
using epiS32 = int32_t;
using epiS64 = int64_t;

using epiString = std::string;

using epiV2F = glm::vec2;
using epiV2S = glm::ivec2;
using epiV3F = glm::vec3;
using epiV4F = glm::vec4;

template<typename T>
using epiV2 = glm::vec<2, T>;
template<typename T>
using epiV3 = glm::vec<3, T>;
template<typename T>
using epiV4 = glm::vec<4, T>;

using epiMat2x2F = glm::mat2x2;
using epiMat3x3F = glm::mat3x3;
using epiMat4x4F = glm::mat4x4;

#ifdef epiDEBUG
#include "EpiLib/Debug/FiniteFloating.h"
using epiFloat = FiniteFloating<float>;
using epiDouble = FiniteFloating<double>;
#else
using epiFloat = float;
using epiDouble = double;
#endif

namespace epi
{

template<typename T>
using Pointer = T*;

}
