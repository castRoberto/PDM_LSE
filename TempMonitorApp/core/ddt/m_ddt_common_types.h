/******************************************************************************
 * Copyright (C) 2024 by Roberto Castro
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Roberto Castro are not liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file m_ddt_common_types.h
 * @brief Definition of common types
 *
 * This header file defines a set of types common to the entire
 * application, it also includes modules from the standard library.
 *
 * @author Roberto Castro
 * @date March 27 2024
 *
 */

#ifndef __M_DDT_COMMON_TYPES_H__
#define __M_DDT_COMMON_TYPES_H__

// Standard library modules
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


// Type refinement for handling boolean values
typedef bool bool_t;

// Time Unit for Non-Blocking delay
typedef uint32_t tick_t;

// Type Redefinition
typedef const char * str_cast;


// General null type definition
#define NULL_VALUE 0


#endif /* __M_DDT_COMMON_TYPES_H__ */
