/**
 * \file	basic_types.h
 *
 * \brief	This file defines basic types to be used in DSW
 *
 * \author	Jesus Fernandez Conde, <jesus.fc@aut.uah.es>
 *
 * \internal
 * Created: 	07-january-2016
 * Compiler: 	gcc/g++
 * Company:  Space Research Group, Universidad de Alcala.
 * Copyright: Copyright (c) 2016, Jesus Fernandez Conde
 *
 * For further information, please visit http://srg.aut.uah.es
 *
 */

#ifndef __PUBLIC__BASIC_TYPES_H__
#define __PUBLIC__BASIC_TYPES_H__

/**
 *  @addtogroup DSW_COMMON Common
 *  @{
 */
/**
 *  @defgroup DSW_BASIC_TYPES Basic Types
 *  @{
 */


#if !__int8_t_defined
typedef unsigned char			uint8_t;
typedef signed char				int8_t;
#define __int8_t_defined 1
#endif

#if !__int16_t_defined
typedef unsigned short			uint16_t;
typedef signed short			int16_t;
#define __int16_t_defined 1
#endif

#if !__int32_t_defined
typedef unsigned long			uint32_t;
typedef signed long				int32_t;
#define __int32_t_defined 1
#endif

#if !__int64_t_defined
typedef unsigned long long int  uint64_t;
#define __int64_t_defined 1
#endif


typedef unsigned int           bool_t;

#ifndef TRUE
#define	TRUE	(1U)
#endif
#ifndef FALSE
#define FALSE	(0U)
#endif

#ifdef NULL
#undef NULL
#endif

#define NULL (0)

#define SUCCESS (0UL)

/**
 * @}
 */
/**
 * @}
 */

#endif // __PUBLIC__BASIC_TYPES_H__
