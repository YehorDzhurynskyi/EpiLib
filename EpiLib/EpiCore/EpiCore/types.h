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
using epiHash_t = uint32_t;

using epiU8 = uint8_t;
using epiU16 = uint16_t;
using epiU32 = uint32_t;
using epiU64 = uint64_t;

using epiS8 = int8_t;
using epiS16 = int16_t;
using epiS32 = int32_t;
using epiS64 = int64_t;

using epiFloat = float;
using epiDouble = double;

using epiString = std::string;

template<size_t N, typename T>
using epiVec = glm::vec<N, T>;

template<typename T>
using epiVec2 = epiVec<2, T>;
using epiVec2f = epiVec2<epiFloat>;
using epiVec2d = epiVec2<epiDouble>;
using epiVec2s = epiVec2<epiS32>;
using epiVec2u = epiVec2<epiU32>;

template<typename T>
using epiVec3 = epiVec<3, T>;
using epiVec3f = epiVec3<epiFloat>;
using epiVec3d = epiVec3<epiDouble>;
using epiVec3s = epiVec3<epiS32>;
using epiVec3u = epiVec3<epiU32>;

template<typename T>
using epiVec4 = epiVec<4, T>;
using epiVec4f = epiVec4<epiFloat>;
using epiVec4d = epiVec4<epiDouble>;
using epiVec4s = epiVec4<epiS32>;
using epiVec4u = epiVec2<epiU32>;

using epiMat2x2f = glm::mat2x2;
using epiMat3x3f = glm::mat3x3;
using epiMat4x4f = glm::mat4x4;
