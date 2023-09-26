/* Copyright (c) 2001-2023 Altia Acquisition Corporation dba Altia, Inc.
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Altia, Inc. The intellectual and technical concepts
 * contained herein are proprietary to Altia, Inc. and may be covered by
 * U.S. and Foreign Patents, patents in process, and are protected by trade
 * secret or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written permission is
 * obtained from Altia, Inc.
 *
 * ALTIA, INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * ALTIA, INC. BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#if !defined(ALTIABASE_H)
#define ALTIABASE_H

/* The following macro is used for alignment of some variables
 * in Altia DeepScreen generated code.  Used when devices
 * require alignment of image data or when accessing data
 * that typecast to a structure (but declared as a non struct).
 */
#ifndef ALTIA_ALIGN
	#if defined(__GNUC__) || defined(GREEN_HILLS)
		#define ALTIA_ALIGN	__attribute__((aligned))
	#else
		#define ALTIA_ALIGN
	#endif
#endif /* ALTIA_ALIGN */

#ifdef ALTIAGL
/* AltiaGL currently requires malloc reguardless if dynamic memory has
 * been specified or not since it needs to create Graphic device
 * contexts, bitmaps, etc.
 */
#include <stdlib.h>

#ifndef ALTIA_MALLOC
    extern void *xalloc(size_t size);
    #define ALTIA_MALLOC(s)     xalloc((size_t)(s))
#endif

#ifndef ALTIA_FREE
    extern void xfree(void *ptr);
    #define ALTIA_FREE(a)       xfree(a)
#endif

#ifndef ALTIA_REALLOC
    extern void *xrealloc(void *ptr, size_t size);
    #define ALTIA_REALLOC(a,s)  xrealloc((a),(size_t)(s))
#endif

/* For enabling defines like ALTIA_USE_INLINE_FX_MATH and
 * ALTIA_USE_DRIVER_FX_MATH, use compile line options.
 * Including target specific headers here is not advised.
 */

#else

/* Dynamic memory requires malloc defines go here */
#include <stdlib.h>

#ifndef ALTIA_MALLOC
    #define ALTIA_MALLOC(s)     malloc((size_t)(s))
#endif

#ifndef ALTIA_FREE
    #define ALTIA_FREE(a)       free(a)
#endif

#ifndef ALTIA_REALLOC
    #define ALTIA_REALLOC(a,s)  realloc((a),(size_t)(s))
#endif


#endif /* ALTIAGL */

/* Code generation options for project */
#ifndef ALTIA_SET_FONT_BASELINE_ADJUST
#define ALTIA_SET_FONT_BASELINE_ADJUST 0
#endif

/* NO_PRELOAD feature */
#ifndef NO_PRELOAD
#define NO_PRELOAD 1
#endif

/* Font File no-preload feature */
#ifndef ALTIA_NO_PRELOAD_FONTS
#define ALTIA_NO_PRELOAD_FONTS 1
#endif

/* Font Character preloading feature */
#ifndef ALTIA_FONT_PRELOAD
#define ALTIA_FONT_PRELOAD 1
#endif

/* NO_PRELOAD maximum raster load count */
#ifndef PRELOAD_CNT
#define PRELOAD_CNT 0
#endif

/* PRELOAD_EVICTION_SAMPLE_SIZE image cache eviction sample size */
#ifndef PRELOAD_EVICTION_SAMPLE_SIZE
    #define PRELOAD_EVICTION_SAMPLE_SIZE 0
#endif

#if (PRELOAD_EVICTION_SAMPLE_SIZE > PRELOAD_CNT)
    /* Sampling from the entire cache is the same as pure LRU */
    #undef PRELOAD_EVICTION_SAMPLE_SIZE
    #define PRELOAD_EVICTION_SAMPLE_SIZE 0
#endif

/* PRELOAD_BYTE_CNT image cache maximum loaded byte size */
#ifndef PRELOAD_BYTE_CNT
    #define PRELOAD_BYTE_CNT 0
#endif

/* ALTIA_RASTER_CACHE defined if managing in-memory rasters with a cache */
#if NO_PRELOAD && (PRELOAD_CNT > 0)
    #define ALTIA_RASTER_CACHE 1
#endif

/* NO_PRELOAD maximum image object load count */
#ifndef PRELOAD_IMAGEOBJ_CNT
#define PRELOAD_IMAGEOBJ_CNT 0
#endif

/* NO_PRELOAD maximum stencil load count */
#ifndef PRELOAD_STENCIL_CNT
#define PRELOAD_STENCIL_CNT 0
#endif

/* NO_PRELOAD image object unloading when hidden feature */
#ifndef PRELOAD_IMAGEOBJ_UNLOAD_ALL_HIDDEN
#define PRELOAD_IMAGEOBJ_UNLOAD_ALL_HIDDEN 0
#endif

/* NO_PRELOAD maximum vector path load count */
#ifndef PRELOAD_PATHOBJ_CNT
#define PRELOAD_PATHOBJ_CNT 0
#endif

/* Altia Tasking Feature */
#ifndef ALTIA_TASKING
#define ALTIA_TASKING 0
#endif

/* Altia Tasking Font Character Priority Queue */
#if ALTIA_TASKING
    #ifndef ALTIA_TASK_PRIORITY_PRELOAD
        #if ALTIA_FONT_PRELOAD
            #define ALTIA_TASK_PRIORITY_PRELOAD 1
        #else
            #define ALTIA_TASK_PRIORITY_PRELOAD 0
        #endif
    #endif
#else
    /* No priority queue when tasking is not enabled */
    #ifdef ALTIA_TASK_PRIORITY_PRELOAD
        #undef ALTIA_TASK_PRIORITY_PRELOAD
    #endif
    #define ALTIA_TASK_PRIORITY_PRELOAD 0
#endif /* ALTIA_TASKING */


/* Altia Tasking animation queue size */
#define ALTIA_TASK_QUEUE_SIZE_OPT 0
#ifndef ALTIA_TASK_QUEUE_SIZE
    #if (ALTIA_TASK_QUEUE_SIZE_OPT > 0)
        #define ALTIA_TASK_QUEUE_SIZE ALTIA_TASK_QUEUE_SIZE_OPT
    #else
        /* Fail-safe case is all animations and text strings in the design */
        #define ALTIA_TASK_QUEUE_SIZE (100 + 703 + (4 * 64))
    #endif
#endif

/* Altia Tasking object render queue size */
#define ALTIA_OBJECT_QUEUE_SIZE_OPT 0
#ifndef ALTIA_OBJECT_QUEUE_SIZE
    #if (ALTIA_OBJECT_QUEUE_SIZE_OPT > 0)
        #define ALTIA_OBJECT_QUEUE_SIZE ALTIA_OBJECT_QUEUE_SIZE_OPT
    #else
        /* Fail-safe case is all objects in the design */
        #define ALTIA_OBJECT_QUEUE_SIZE (312 + 881)
    #endif
#endif

/* Altia Tasking font character priority queue size */
#define ALTIA_PRIORITY_QUEUE_SIZE_OPT 0
#ifndef ALTIA_PRIORITY_QUEUE_SIZE
    #if (ALTIA_PRIORITY_QUEUE_SIZE_OPT > 0)
        #define ALTIA_PRIORITY_QUEUE_SIZE ALTIA_PRIORITY_QUEUE_SIZE_OPT
    #else
        /* Fail-safe case is all TextIOs and MLTOs need to be queued. */
        #define ALTIA_PRIORITY_QUEUE_SIZE (0 + 0)
    #endif
#endif
/* End of project code generation options */

/* Object ID Cross-Reference Table */
#ifndef ALTIA_USE_OBJ_ID_TABLE

    /* Using dynamic built-in animations, DLOs, or Stamps - enable obj id table */
    #define ALTIA_USE_OBJ_ID_TABLE 1


#endif

/* Optionally force dynamic memory allocation of DIB or not by
 * defining ALTIA_DIB_MALLOC as 1 or 0, respectively.  If ALTIA_DIB_MALLOC
 * is not already defined, it is defined based on the code generation option
 * to use dynamic memory.
 */






#ifndef ALTIA_DIB_MALLOC
/* Dynamic memory enabled. Dynamic allocation of DIB data is default mode */
#define ALTIA_DIB_MALLOC 1
#endif


#define ALTIA_DIB_HEADER_MAX            (sizeof(EGL_DIB) + 256 * 4)
#define ALTIA_DIB_BITMAP_SIZE           (0)
#define ALTIA_DIB_MAX_SIZE              (ALTIA_DIB_HEADER_MAX + ALTIA_DIB_BITMAP_SIZE)
#define ALTIA_DIB_SCALED_BITMAP_SIZE    ((923599 + 1) * 4)
#define ALTIA_DIB_SCALED_MAX_SIZE       (ALTIA_DIB_HEADER_MAX + ALTIA_DIB_SCALED_BITMAP_SIZE)


#define ALTIA_CONST const
#define LONG_MINUS_ONE 0xffffffffU

/* Altia's definition of white is red = 0xff, blue = 0xff,
 * and green = 0xff packed into 24-bits (the low order 24-bits
 * if it is being assigned to a 32-bit or larger data type).
 * Altia's definition of black is red = 0x00, blue = 0x00,
 * green = 0x00 also packed into 24-bits.
 */
#ifndef ALTIA_WHITE
#define ALTIA_WHITE 0x0ffffffU
#endif
#ifndef ALTIA_BLACK
#define ALTIA_BLACK 0x0U
#endif
#define ALTIA_RED 0x000000ffU
#define ALTIA_GREEN 0x0000ff00U
#define ALTIA_BLUE 0x00ff0000U

/*
 * For use when a monochrome display is selected.
 */
#define ALTIA_PIXEL_ON 1
#define ALTIA_PIXEL_OFF 0
#define ALTIA_NO_COLOR_SPECIFIED 3

/* NOTE: These types are not safe for 16-bit systems.  However 16-bit systems
**       are not supported for non-miniGL targets.
*/
typedef unsigned int ALTIA_UINT;
typedef int ALTIA_INT;




typedef float ALTIA_FLOAT;
typedef double ALTIA_DOUBLE;
#define FMULT(x,y)      ((ALTIA_DOUBLE)((x) * (y)))
#define FDIV(x,y)       ((ALTIA_DOUBLE)(x) / (ALTIA_DOUBLE)(y))
#define FADD(x,y)       ((x) + (y))
#define FSUB(x,y)       ((x) - (y))
#define FSQRT(x)        (sqrt(x))
#define FSIN(x)         (sin(x))
#define FCOS(x)         (cos(x))
#define FATAN2(x,y)     (atan2((x),(y)))
#define FHYPOT(x,y)     (hypot((x),(y)))
#define FPOW(x,n)       (pow((x),(n)))
/*lint --emacro({9031}, ALTIA_ROUND) --emacro({9033}, ALTIA_ROUND) --emacro({9034}, ALTIA_ROUND) Legacy code - cannot cast correctly in a macro. */
#define ALTIA_ROUND(x)  (((x) > 0.0) ? (ALTIA_INT)((x)+0.5) : -(ALTIA_INT)(-(x)+(0.499999999999999)))


#define ALTIA_CTL_ROUND(x) (((x) > 0.0) ? (ALTIA_INT)((x)+0.5) : -(ALTIA_INT)(-(x)+(0.499999999999999)))

typedef signed char ALTIA_BYTE;
typedef unsigned char ALTIA_UBYTE;
typedef signed short ALTIA_SHORT;
typedef unsigned short ALTIA_USHORT;

#ifdef MISRA_BOOLEAN
    /* PC-Lint MISRA 2012 static analyzer requires _Bool as the boolean type */
    typedef _Bool TYPE_ALTIA_BOOLEAN;
#else
    /* Use signed char as the boolean type by default */
    typedef signed char TYPE_ALTIA_BOOLEAN;
#endif

/* Use a define for ALTIA_BOOLEAN to suppress altiaEx.h from overriding it */
#define ALTIA_BOOLEAN TYPE_ALTIA_BOOLEAN

typedef int ALTIA_INDEX;
typedef int ALTIA_BINDEX;
typedef unsigned char ALTIA_FBINDEX;
typedef signed short ALTIA_COORD;
typedef unsigned int ALTIA_COLOR;

typedef const char * ALTIA_LPCSTR;
typedef char * ALTIA_LPSTR;

#ifdef WIN32
    #ifndef ALTLONGLONG
        #define ALTLONGLONG __int64
    #endif /* ALTLONGLONG */
#else
    #ifndef ALTLONGLONG
        #define ALTLONGLONG long long
    #endif /* ALTLONGLONG */
#endif /* WIN32 */

typedef unsigned char ALTIA_UINT8;
typedef unsigned short ALTIA_UINT16;
typedef unsigned int ALTIA_UINT32;
typedef unsigned ALTLONGLONG ALTIA_UINT64;

typedef signed char ALTIA_INT8;
typedef signed short ALTIA_INT16;
typedef signed int ALTIA_INT32;
typedef signed ALTLONGLONG ALTIA_INT64;

typedef signed int ALTIA_ANIM_ID;

typedef ALTIA_UINT64 ALTIA_CRC;

/* 3D support */
typedef float ALTIA_VEC2[2];
typedef float ALTIA_VEC3[3];
typedef float ALTIA_VEC4[4];
typedef ALTIA_VEC4 ALTIA_MAT4[4];
typedef ALTIA_VEC3 ALTIA_MAT3[3];
typedef float ALTIA_QUAT[4];
typedef ALTIA_INDEX ALTIA_SAMPLER6[6];

/* Dynamic face winding.  This is enabled automatically by
** the code generator when any scene contains at least one
** node of the following types:
**   - External 3D Scene Node
**   - Programmable Scene Node
**   - Instance Node
*/

#ifndef ALTIA_DYNAMIC_FACE_WINDING
    #define ALTIA_DYNAMIC_FACE_WINDING 0
#endif

/* An opaque id/handle may need to hold a pointer.  Use this next type for an
 * opaque id/handle that may be a pointer (very important for 64-bit support).
 */
typedef void * ALTIA_HANDLE;

#define ALTIA_TRUE  ((ALTIA_BOOLEAN)1)
#define ALTIA_FALSE ((ALTIA_BOOLEAN)0)

/* Until code generator auto-adjusts char for
 * different UNICODE targets, just set ALTIA_CHAR
 * based on the definition of preprocessor macros.
 */
#if !defined(UNICODE) && !defined(ALTIA_CHAR_UNICODE)
    typedef char TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UBYTE
#elif defined(ALTIA_CHAR_UNICODE) && defined(WCHAR_IS_WCHAR_T)
    /* For activex integration only */
    typedef wchar_t TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT16
#elif defined(WCHAR_IS_WCHAR_T)
    /* For C99 compliant C compiler */
    #include <wchar.h>
    #include <wctype.h>
    typedef wchar_t TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT16
#elif defined(WIN32) || defined(WCHAR_IS_USHORT)
    typedef unsigned short TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT16
#elif defined(WCHAR_IS_UINT)
    typedef unsigned int TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT32
#elif defined(WCHAR_IS_ULONG)
    typedef unsigned long TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT32
#elif defined(WCHAR_IS_SHORT)
    typedef short TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT16
#elif defined(WCHAR_IS_LONG)
    typedef long TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT32
#else
    typedef int TYPE_ALTIA_CHAR;
    #define TYPE_ALTIA_CHAR_CAST ALTIA_UINT32
#endif
#define ALTIA_CHAR          TYPE_ALTIA_CHAR
#define ALTIA_SHAPE_CHAR    TYPE_ALTIA_CHAR

#ifndef ALTIA_CHAR_CAST
    /* Cast characters to this type before casting to a larger type */
    #define ALTIA_CHAR_CAST TYPE_ALTIA_CHAR_CAST
#endif /* !defined(ALTIA_CHAR_CAST) */

typedef void* ALTIA_WINDOW;

/* This will smartly be a double or integer based upon fixed point settings.
** NOTE: if fixed point is enabled, the event type is a true integer value
**       (not a fixed point representation).
*/
typedef ALTIA_DOUBLE AltiaEventType;

#define VALUE_ERROR_TOL     1e-6
#define ALTIA_MAX_POPS      16
#define ALTIA_MAX_INPUTPOPS (ALTIA_MAX_POPS * 8)
#ifndef false
    #define false 0
#endif
#ifndef true
    #define true 1
#endif
#ifndef nil
    #define nil 0
#endif
#define ALTIA_MIN(a, b)             (((a) < (b)) ? (a) : (b))
#define ALTIA_MAX(a, b)             (((a) > (b)) ? (a) : (b))


#if !defined(ALTIA_ISFINITE)
#define ALTIA_ISFINITE(a)           (isfinite(a))
#endif
#define ALTIA_ISZERO(a)             ((-VALUE_ERROR_TOL <= (double)(a)) && ((double)(a) <= VALUE_ERROR_TOL))
#define ALTIA_EQUAL(a, b)           ((-VALUE_ERROR_TOL <= ((double)(a) - (double)(b))) && (((double)(a) - (double)(b)) <= VALUE_ERROR_TOL))
#define ALTIA_LESS(a, b)            (a < b)
#define ALTIA_LESSEQUAL(a, b)       (a <= b)
#define ALTIA_GREATER(a, b)         (a > b)
#define ALTIA_GREATEREQUAL(a, b)    (a >= b)
#define ALTIA_ABS(a)                (fabs(a))
#define ALTIA_FLOOR(a)              (floor(a))
#define ALTIA_CEIL(a)               (ceil(a))
#define ALTIA_F2I(a)                ((ALTIA_INT)a)
#define ALTIA_D2I(a)                ((ALTIA_INT)a)
#define ALTIA_C2FX(a)                (a)
#define ALTIA_I2D(a)                ((ALTIA_DOUBLE)(a))
#define ALTIA_C2D(a)                ((ALTIA_DOUBLE)(a))
#define ALTIA_C2F(a)                ((ALTIA_FLOAT)(a))
#define ALTIA_E2D(a)                (a)
#define ALTIA_E2F(a)                ((ALTIA_FLOAT)(a))
#define ALTIA_I2F(a)                ((ALTIA_FLOAT)(a))



/* Using ALT_ATOD for atof functionality */
#define ALT_ATOF(x)                 ALT_ATOD((x), NULL)

/*********************************************************************
 * If UNICODE is defined and ALTIA_WCHAR_SUPPORT is defined, Altia
 * DeepScreen's implementation of wide char functions is enabled. This
 * requires compiling the DeepScreen additional wCharStrings.c file.
 * By default, macros below redefine DeepScreen wCharStrings.c funcs
 * to custom names beginning with _altia_ (e.g., _altia_wcscmp).  This
 * allows them to co-exist with C library wide char funcs.  This is
 * necessary if the target C library actually has wide char funcs
 * available and some application code uses them (but not application
 * code interfacing to DeepScreen).  If a #include of wCharStrings.h
 * and/or altia.h is in application code, occurences of wide char
 * function names (e.g., wcscmp) are redefined to be Altia's version
 * (e.g., _altia_wcscmp).  To force Altia wCharStrings.c func names to
 * exactly match standard C library wide char func names (for example,
 * because the target C library really has NO wide char funcs), define
 * ALTIA_WCHAR_NAMES=0 for DeepScreen and application code compilation.
 ********************************************************************/
#ifndef ALTIA_WCHAR_NAMES
    #define ALTIA_WCHAR_NAMES 1
#endif
#if defined(UNICODE) && defined(ALTIA_WCHAR_SUPPORT) && (0 != ALTIA_WCHAR_NAMES) && !defined(ALTIAWCHARNAMES_H)
    #define ALTIAWCHARNAMES_H
    #define _wfopen   _altia_wfopen
    #define fgetwc    _altia_fgetwc
    #define wcscmp    _altia_wcscmp
    #define wcscpy    _altia_wcscpy
    #define wcscat    _altia_wcscat
    #define wcsncpy   _altia_wcsncpy
    #define wcsncmp   _altia_wcsncmp
    #define wcslen    _altia_wcslen
    #define wcschr    _altia_wcschr
    #define wcsrchr   _altia_wcsrchr
    #define wcstod    _altia_wcstod
    #define wcstol    _altia_wcstol
    #define wcstoul   _altia_wcstoul
    #define swprintf  _altia_swprintf
    #define iswspace  _altia_iswspace
    #define iswpunct  _altia_iswpunct
    #define iswprint  _altia_iswprint
    #define iswalpha  _altia_iswalpha
    #define swscanf   _altia_swscanf
    #define wcsstr    _altia_wcsstr
#endif /* UNICODE && ALTIA_WCHAR_SUPPORT && ALTIA_WCHAR_NAMES */

#ifdef UNICODE
    #define ALT_STRCMP      wcscmp
    #define ALT_STRCPY      wcscpy
    #define ALT_STRCAT      wcscat
    #define ALT_STRNCPY     wcsncpy
    #define ALT_STRNCMP     wcsncmp
    #define ALT_STRLEN      wcslen
    #define ALT_STRTOD      wcstod
    #define ALT_STRTOL      wcstol
    #define ALT_STRTOUL     wcstoul
    #define ALT_STRSTR      wcsstr

    #if !defined(WCHAR_IS_WCHAR_T) || defined(ALTIA_CHAR_UNICODE)
        /* WCHAR_IS_WCHART_T is not defined or ALTIA_CHAR_UNICODE (for activex
         * integration) is defined.  In this case, assume compiler is not C99
         * compliant and swprintf() arguments are identical to sprintf() arguments.
         */
        #define ALT_SPRINTF swprintf
    #else
        /* WCHAR_IS_WCHART_T is defined and ALTIA_CHAR_UNICODE is not defined.
         * Assume compiler is compliant with C99 standard for swprintf() func.
         * C99 compliant swprintf(buf, size, format, ...) has extra size arg
         * thereby requiring a custom wrapper function to convert legacy
         * swprintf() argument list to C99 compliant argument list.
         */
        #define ALT_SPRINTF _altiaSwprintf
        extern int _altiaSwprintf(ALTIA_CHAR *buf, ALTIA_CHAR *format, ...);
    #endif /* !defined(WCHAR_IS_WCHAR_T) || defined(ALTIA_CHAR_UNICODE) */

    #define ALT_ISSPACE     iswspace
    #define ALT_ISPUNCT     iswpunct
    #define ALT_ISPRINT     iswprint
    #define ALT_ISASCII     iswascii
    #define ALT_ISALPHA     iswalpha
    #define ALT_STRTOK      wcstok
    #define ALT_STRCHR      wcschr
    #define ALT_FGETC       fgetwc
    #define ALT_FPUTC       fputwc
    #define ALT_FOPEN       _wfopen
    #define ALT_CHARMASK    0x1fffffU
    #define ALT_ATOD        wcstod
    #define ALT_SSCANF      swscanf
    #define ALT_TEXT(x)     L ## x
    #define ALT_STRRCHR     wcsrchr
    #define ALT_STRPBRK     wcspbrk
#else
    #define ALT_STRCMP      strcmp
    #define ALT_STRCPY      strcpy
    #define ALT_STRCAT      strcat
    #define ALT_STRNCPY     strncpy
    #define ALT_STRNCMP     strncmp
    #define ALT_STRLEN      strlen
    #define ALT_STRTOD      strtod
    #define ALT_STRTOL      strtol
    #define ALT_STRTOUL     strtoul
    #define ALT_STRSTR      strstr

    #define ALT_SPRINTF     sprintf
    #define ALT_ISSPACE     isspace
    #define ALT_ISPUNCT     ispunct
    #define ALT_ISPRINT     isprint
    #define ALT_ISASCII     isascii
    #define ALT_ISALPHA     isalpha
    #define ALT_STRTOK      strtok
    #define ALT_STRCHR      strchr
    #define ALT_FGETC       fgetc
    #define ALT_FPUTC       fputc
    #define ALT_FOPEN       fopen
    #define ALT_CHARMASK    0xffU
    #define ALT_ATOD        strtod
    #define ALT_SSCANF      sscanf
    #define ALT_TEXT(x)     x
    #define ALT_STRRCHR     strrchr
    #define ALT_STRPBRK     strpbrk
#endif /* UNICODE */

#define ALT_MEMCPY          memcpy



/* Used to inform font module code that code point macros are available */
#define ALTIA_UTF16_ENGINE


/* Determine if wide char literal x is the first of an UTF-16 surrogate pair */
#define ALTIA_IS_U16_HI_SRRGT(x) ((((ALTIA_UINT16)(x)) >= 0xD800U) && (((ALTIA_UINT16)(x)) <= 0xDBFFU))

/* Determine if wide char literal x is the second of an UTF-16 surrogate pair */
#define ALTIA_IS_U16_LO_SRRGT(x) ((((ALTIA_UINT16)(x)) >= 0xDC00U) && (((ALTIA_UINT16)(x)) <= 0xDFFFU))

/* Macro is for internal use. If surrogate pair at str[idx] and str[idx+1],
   perform op_pair. If not, perform op_single. */
#define ALTIA_U16_TERNARY(str, idx, op_pair, op_single) ((ALTIA_IS_U16_HI_SRRGT(str[(idx)]) && ALTIA_IS_U16_LO_SRRGT(str[(idx)+1U])) ? (op_pair) : (op_single))

/* Macro is for internal use. Decode an UTF-16 surrogate pair located at str[idx]
   and str[idx+1]. Must only be called on a surrogate pair. */
#define ALTIA_DECODE_U16(str, idx) ((((((ALTIA_UINT32)((ALTIA_UINT16)str[idx])) - 0xD800U) << 10U) | (((ALTIA_UINT32)((ALTIA_UINT16)str[idx+1U])) - 0xDC00U)) + 0x10000U)

/* Modify idx to the next Unicode code point after the one at str[idx] in a
   UTF-16 string. That is, if str[idx] is a surrogate pair, add 2 to idx,
   otherwise add 1. This macro is intended to be used as an iterator in for
   and while loops. */
/*lint -emacro(9008,ALTIA_NEXT_CODE_PT) MISRA 2012 Rule 12.3 */
/*lint -emacro(9049,ALTIA_NEXT_CODE_PT) MISRA 2012 Rule 13.3 */
#define ALTIA_NEXT_CODE_PT(str, idx) ALTIA_U16_TERNARY(str, idx, (idx++, idx++), idx++)

/* Modify idx to the next Unicode code point after the one at str[idx + offset]
   in a UTF-16 string. That is, if str[idx + offset] is a surrogate pair, add
   2 to idx, otherwise add 1. This macro is intended to be used as an iterator
   in for and while loops. */
/*lint -emacro(9008,ALTIA_NEXT_CODE_PT_OFFSET) MISRA 2012 Rule 12.3 */
/*lint -emacro(9049,ALTIA_NEXT_CODE_PT_OFFSET) MISRA 2012 Rule 13.3 */
#define ALTIA_NEXT_CODE_PT_OFFSET(str, idx, offset) ALTIA_U16_TERNARY(str, idx + offset, (idx++, idx++), idx++)

/* Return the Unicode code point located at str[idx] in an UTF-16 string. */
#define ALTIA_GET_CODE_PT(str, idx) ALTIA_U16_TERNARY(str, idx, ALTIA_DECODE_U16(str, idx), str[idx])

/* Return the Unicode code point after the code point located at str[idx] in an
   UTF-16 string. */
#define ALTIA_GET_NEXT_CODE_PT(str, idx) ALTIA_U16_TERNARY(str, idx, ALTIA_GET_CODE_PT(str, idx+2U), ALTIA_GET_CODE_PT(str, idx+1U))

/* Encode the Unicode code point value ranging [0x10000, 0x10FFFF] as the the
   first of an UTF-16 surrogate pair. */
#define ALTIA_ENCODE_U16_HI_SRRGT(value) (((value - 0x10000U) >> 10U) + 0xD800U)

/* Encode the Unicode code point value ranging [0x10000, 0x10FFFF] as the the
   second of an UTF-16 surrogate pair. */
#define ALTIA_ENCODE_U16_LO_SRRGT(value) (((value - 0x10000U) & 0x3FFU) + 0xDC00U)

/* Get the logical length of a single code point */
#define ALTIA_CODE_PT_LOGICAL_LEN(str, idx) ALTIA_U16_TERNARY(str, idx, 2, 1)






#endif /* ALTIABASE_H */
