#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "assert.h"
#include "stdbool.h"
#include "stdint.h"

/***************************************************************************************************
*                                          D E F I N E S                                           *
***************************************************************************************************/
#ifdef __cplusplus
#define UTIL_ASSERT(condition, str) static_assert(condition, str)
#else
#define UTIL_ASSERT(condition, str) _Static_assert(condition, str)
#endif

#define BIT_X(position, size)               ((uint##size##_t)((uint##size##_t)1U << ((uint_least8_t)(position))))
#define GET_BIT_X(data, position, size)     ((bool)(((uint##size##_t)(data) & BIT_X((position), size)) != 0U))
#define SET_BIT_X(data, position, size)     ((uint##size##_t)(data) | BIT_X((position), size))
#define CLEAR_BIT_X(data, position, size)   ((uint##size##_t)(data) & ((uint##size##_t)~BIT_X((position), size)))

// Set the bit at position and return data
#define BIT_U8(position)    BIT_X((position), 8)
#define BIT_U16(position)   BIT_X((position), 16)
#define BIT_U32(position)   BIT_X((position), 32)
#define BIT_U64(position)   BIT_X((position), 64)

// Get the bool result for if the bit at position in data is set
#define GET_BIT_U8(data, position)  GET_BIT_X((data), (position), 8)
#define GET_BIT_U16(data, position) GET_BIT_X((data), (position), 16)
#define GET_BIT_U32(data, position) GET_BIT_X((data), (position), 32)
#define GET_BIT_U64(data, position) GET_BIT_X((data), (position), 64)

// Set the bit at position in data and return data
#define SET_BIT_U8(data, position)  SET_BIT_X((data), (position), 8)
#define SET_BIT_U16(data, position) SET_BIT_X((data), (position), 16)
#define SET_BIT_U32(data, position) SET_BIT_X((data), (position), 32)
#define SET_BIT_U64(data, position) SET_BIT_X((data), (position), 64)

// Clear the bit at position in data and return data
#define CLEAR_BIT_U8(data, position)  CLEAR_BIT_X((data), (position), 8)
#define CLEAR_BIT_U16(data, position) CLEAR_BIT_X((data), (position), 16)
#define CLEAR_BIT_U32(data, position) CLEAR_BIT_X((data), (position), 32)
#define CLEAR_BIT_U64(data, position) CLEAR_BIT_X((data), (position), 64)

// Conditionally set or clear the bit at position in data and return data
#define SET_BIT_BOOL_U8(data, position, set)  ((isEnabled) ? SET_BIT_U8(data, position)  : CLEAR_BIT_U8(data, position))
#define SET_BIT_BOOL_U16(data, position, set) ((isEnabled) ? SET_BIT_U16(data, position) : CLEAR_BIT_U16(data, position))
#define SET_BIT_BOOL_U32(data, position, set) ((isEnabled) ? SET_BIT_U32(data, position) : CLEAR_BIT_U32(data, position))
#define SET_BIT_BOOL_U64(data, position, set) ((isEnabled) ? SET_BIT_U64(data, position) : CLEAR_BIT_U64(data, position))

#define U16(h,l)    ((uint16_t)((uint16_t)((uint16_t)(h) << 8U) | ((uint16_t)(l) & 0x00FFU)))   // pack bytes into uint16_t word
#define U16_MSB(w)  ((uint8_t)(((uint16_t)((w) >> 8)) & 0x00FFU))                               // MSB of uint16_t
#define U16_LSB(w)  ((uint8_t)(((uint16_t)(w)) & 0x00FFU))                                      // LSB of uint16_t
#define U32(h,l)    (((uint32_t)(h) << 16U) | ((uint16_t)(l)))                                  // pack words into uint32_t
#define U32_MSW(w)  ((uint16_t)((w) >> 16U))                                                    // MSW of uint32_t
#define U32_LSW(w)  ((uint16_t)(w))                                                             // LSW of uint32_t

#ifdef __cplusplus
}
#endif

#endif // UTIL_H
