#ifndef JSON_FORWARD_AMALGATED_H_INCLUDED
# define JSON_FORWARD_AMALGATED_H_INCLUDED
#define JSON_IS_AMALGAMATION
#ifndef JSON_CONFIG_H_INCLUDED
#define JSON_CONFIG_H_INCLUDED
#include <stddef.h>
#include <string> //typedef String
#include <stdint.h> //typedef int64_t, uint64_t

#ifndef JSON_USE_EXCEPTION
#define JSON_USE_EXCEPTION 1
#endif

#ifdef JSON_IN_CPPTL
#include <cpptl/config.h>
#ifndef JSON_USE_CPPTL
#define JSON_USE_CPPTL 1
#endif
#endif

#ifdef JSON_IN_CPPTL
#define JSON_API CPPTL_API
#elif defined(JSON_DLL_BUILD)
#if defined(_MSC_VER) || defined(__MINGW32__)
#define JSON_API __declspec(dllexport)
#define JSONCPP_DISABLE_DLL_INTERFACE_WARNING
#endif // if defined(_MSC_VER)
#elif defined(JSON_DLL)
#if defined(_MSC_VER) || defined(__MINGW32__)
#define JSON_API __declspec(dllimport)
#define JSONCPP_DISABLE_DLL_INTERFACE_WARNING
#endif // if defined(_MSC_VER)
#endif // ifdef JSON_IN_CPPTL
#if !defined(JSON_API)
#define JSON_API
#endif

#if defined(_MSC_VER) // MSVC
#  if _MSC_VER <= 1200 // MSVC 6
#    define JSON_USE_INT64_DOUBLE_CONVERSION 1
#    pragma warning(disable : 4786)
#  endif // MSVC 6

#  if _MSC_VER >= 1500 // MSVC 2008
#    define JSONCPP_DEPRECATED(message) __declspec(deprecated(message))
#  endif

#endif // defined(_MSC_VER)

#if __cplusplus >= 201103L
# define JSONCPP_OVERRIDE override
#elif defined(_MSC_VER) && _MSC_VER > 1600
# define JSONCPP_OVERRIDE override
#else
# define JSONCPP_OVERRIDE
#endif

#ifndef JSON_HAS_RVALUE_REFERENCES

#if defined(_MSC_VER) && _MSC_VER >= 1600 // MSVC >= 2010
#define JSON_HAS_RVALUE_REFERENCES 1
#endif // MSVC >= 2010

#ifdef __clang__
#if __has_feature(cxx_rvalue_references)
#define JSON_HAS_RVALUE_REFERENCES 1
#endif  // has_feature

#elif defined __GNUC__ // not clang (gcc comes later since clang emulates gcc)
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus >= 201103L)
#define JSON_HAS_RVALUE_REFERENCES 1
#endif  // GXX_EXPERIMENTAL

#endif // __clang__ || __GNUC__

#endif // not defined JSON_HAS_RVALUE_REFERENCES

#ifndef JSON_HAS_RVALUE_REFERENCES
#define JSON_HAS_RVALUE_REFERENCES 0
#endif

#ifdef __clang__
#elif defined __GNUC__ // not clang (gcc comes later since clang emulates gcc)
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#    define JSONCPP_DEPRECATED(message)  __attribute__ ((deprecated(message)))
#  elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#    define JSONCPP_DEPRECATED(message)  __attribute__((__deprecated__))
#  endif  // GNUC version
#endif // __clang__ || __GNUC__

#if !defined(JSONCPP_DEPRECATED)
#define JSONCPP_DEPRECATED(message)
#endif // if !defined(JSONCPP_DEPRECATED)

#if __GNUC__ >= 6
#  define JSON_USE_INT64_DOUBLE_CONVERSION 1
#endif

#if !defined(JSON_IS_AMALGAMATION)

# include "version.h"

# if JSONCPP_USING_SECURE_MEMORY
#  include "allocator.h" //typedef Allocator
# endif

#endif // if !defined(JSON_IS_AMALGAMATION)

namespace Json {
	typedef int Int;
	typedef unsigned int UInt;
#if defined(JSON_NO_INT64)
	typedef int LargestInt;
	typedef unsigned int LargestUInt;
#undef JSON_HAS_INT64
#else                 // if defined(JSON_NO_INT64)
	// For Microsoft Visual use specific types as long long is not supported
#if defined(_MSC_VER) // Microsoft Visual Studio
	typedef __int64 Int64;
	typedef unsigned __int64 UInt64;
#else                 // if defined(_MSC_VER) // Other platforms, use long long
	typedef int64_t Int64;
	typedef uint64_t UInt64;
#endif // if defined(_MSC_VER)
	typedef Int64 LargestInt;
	typedef UInt64 LargestUInt;
#define JSON_HAS_INT64
#endif // if defined(JSON_NO_INT64)
#if JSONCPP_USING_SECURE_MEMORY
#define JSONCPP_STRING        std::basic_string<char, std::char_traits<char>, Json::SecureAllocator<char> >
#define JSONCPP_OSTRINGSTREAM std::basic_ostringstream<char, std::char_traits<char>, Json::SecureAllocator<char> >
#define JSONCPP_OSTREAM       std::basic_ostream<char, std::char_traits<char>>
#define JSONCPP_ISTRINGSTREAM std::basic_istringstream<char, std::char_traits<char>, Json::SecureAllocator<char> >
#define JSONCPP_ISTREAM       std::istream
#else
#define JSONCPP_STRING        std::string
#define JSONCPP_OSTRINGSTREAM std::ostringstream
#define JSONCPP_OSTREAM       std::ostream
#define JSONCPP_ISTRINGSTREAM std::istringstream
#define JSONCPP_ISTREAM       std::istream
#endif // if JSONCPP_USING_SECURE_MEMORY
} // end namespace Json

#endif // JSON_CONFIG_H_INCLUDED

  // //////////////////////////////////////////////////////////////////////
  // End of content of file: include/json/config.h
  // //////////////////////////////////////////////////////////////////////






  // //////////////////////////////////////////////////////////////////////
  // Beginning of content of file: include/json/forwards.h
  // //////////////////////////////////////////////////////////////////////

  // Copyright 2007-2010 Baptiste Lepilleur
  // Distributed under MIT license, or public domain if desired and
  // recognized in your jurisdiction.
  // See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef JSON_FORWARDS_H_INCLUDED
#define JSON_FORWARDS_H_INCLUDED

#if !defined(JSON_IS_AMALGAMATION)
#include "config.h"
#endif // if !defined(JSON_IS_AMALGAMATION)

namespace Json {

	// writer.h
	class FastWriter;
	class StyledWriter;

	// reader.h
	class Reader;

	// features.h
	class Features;

	// value.h
	typedef unsigned int ArrayIndex;
	class StaticString;
	class Path;
	class PathArgument;
	class Value;
	class ValueIteratorBase;
	class ValueIterator;
	class ValueConstIterator;

} // namespace Json

#endif // JSON_FORWARDS_H_INCLUDED

  // //////////////////////////////////////////////////////////////////////
  // End of content of file: include/json/forwards.h
  // //////////////////////////////////////////////////////////////////////





#endif //ifndef JSON_FORWARD_AMALGATED_H_INCLUDED
