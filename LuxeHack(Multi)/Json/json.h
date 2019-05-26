#ifndef JSON_AMALGATED_H_INCLUDED
# define JSON_AMALGATED_H_INCLUDED
#define JSON_IS_AMALGAMATION
#ifndef JSON_VERSION_H_INCLUDED
# define JSON_VERSION_H_INCLUDED

# define JSONCPP_VERSION_STRING "1.8.0"
# define JSONCPP_VERSION_MAJOR 1
# define JSONCPP_VERSION_MINOR 7
# define JSONCPP_VERSION_PATCH 7
# define JSONCPP_VERSION_QUALIFIER
# define JSONCPP_VERSION_HEXA ((JSONCPP_VERSION_MAJOR << 24) | (JSONCPP_VERSION_MINOR << 16) | (JSONCPP_VERSION_PATCH << 8))
#ifdef JSONCPP_USING_SECURE_MEMORY
#undef JSONCPP_USING_SECURE_MEMORY
#endif
#define JSONCPP_USING_SECURE_MEMORY 0
#endif // JSON_VERSION_H_INCLUDED

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






  // //////////////////////////////////////////////////////////////////////
  // Beginning of content of file: include/json/features.h
  // //////////////////////////////////////////////////////////////////////

  // Copyright 2007-2010 Baptiste Lepilleur
  // Distributed under MIT license, or public domain if desired and
  // recognized in your jurisdiction.
  // See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef CPPTL_JSON_FEATURES_H_INCLUDED
#define CPPTL_JSON_FEATURES_H_INCLUDED

#if !defined(JSON_IS_AMALGAMATION)
#include "forwards.h"
#endif // if !defined(JSON_IS_AMALGAMATION)

namespace Json {

	/** \brief Configuration passed to reader and writer.
	* This configuration object can be used to force the Reader or Writer
	* to behave in a standard conforming way.
	*/
	class JSON_API Features {
	public:
		/** \brief A configuration that allows all features and assumes all strings
		* are UTF-8.
		* - C & C++ comments are allowed
		* - Root object can be any JSON value
		* - Assumes Value strings are encoded in UTF-8
		*/
		static Features all();

		/** \brief A configuration that is strictly compatible with the JSON
		* specification.
		* - Comments are forbidden.
		* - Root object must be either an array or an object value.
		* - Assumes Value strings are encoded in UTF-8
		*/
		static Features strictMode();

		/** \brief Initialize the configuration like JsonConfig::allFeatures;
		*/
		Features();

		/// \c true if comments are allowed. Default: \c true.
		bool allowComments_;

		/// \c true if root must be either an array or an object value. Default: \c
		/// false.
		bool strictRoot_;

		/// \c true if dropped null placeholders are allowed. Default: \c false.
		bool allowDroppedNullPlaceholders_;

		/// \c true if numeric object key are allowed. Default: \c false.
		bool allowNumericKeys_;
	};

} // namespace Json

#endif // CPPTL_JSON_FEATURES_H_INCLUDED

  // //////////////////////////////////////////////////////////////////////
  // End of content of file: include/json/features.h
  // //////////////////////////////////////////////////////////////////////






  // //////////////////////////////////////////////////////////////////////
  // Beginning of content of file: include/json/value.h
  // //////////////////////////////////////////////////////////////////////

  // Copyright 2007-2010 Baptiste Lepilleur
  // Distributed under MIT license, or public domain if desired and
  // recognized in your jurisdiction.
  // See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef CPPTL_JSON_H_INCLUDED
#define CPPTL_JSON_H_INCLUDED

#if !defined(JSON_IS_AMALGAMATION)
#include "forwards.h"
#endif // if !defined(JSON_IS_AMALGAMATION)
#include <string>
#include <vector>
#include <exception>

#ifndef JSON_USE_CPPTL_SMALLMAP
#include <map>
#else
#include <cpptl/smallmap.h>
#endif
#ifdef JSON_USE_CPPTL
#include <cpptl/forwards.h>
#endif

  //Conditional NORETURN attribute on the throw functions would:
  // a) suppress false positives from static code analysis 
  // b) possibly improve optimization opportunities.
#if !defined(JSONCPP_NORETURN)
#  if defined(_MSC_VER)
#    define JSONCPP_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define JSONCPP_NORETURN __attribute__ ((__noreturn__))
#  else
#    define JSONCPP_NORETURN
#  endif
#endif

  // Disable warning C4251: <data member>: <type> needs to have dll-interface to
  // be used by...
#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

  /** \brief JSON (JavaScript Object Notation).
  */
namespace Json {

	/** Base class for all exceptions we throw.
	*
	* We use nothing but these internally. Of course, STL can throw others.
	*/
	class JSON_API Exception : public std::exception {
	public:
		Exception(JSONCPP_STRING const& msg);
		~Exception() throw() JSONCPP_OVERRIDE;
		char const* what() const throw() JSONCPP_OVERRIDE;
	protected:
		JSONCPP_STRING msg_;
	};

	/** Exceptions which the user cannot easily avoid.
	*
	* E.g. out-of-memory (when we use malloc), stack-overflow, malicious input
	*
	* \remark derived from Json::Exception
	*/
	class JSON_API RuntimeError : public Exception {
	public:
		RuntimeError(JSONCPP_STRING const& msg);
	};

	/** Exceptions thrown by JSON_ASSERT/JSON_FAIL macros.
	*
	* These are precondition-violations (user bugs) and internal errors (our bugs).
	*
	* \remark derived from Json::Exception
	*/
	class JSON_API LogicError : public Exception {
	public:
		LogicError(JSONCPP_STRING const& msg);
	};

	/// used internally
	JSONCPP_NORETURN void throwRuntimeError(JSONCPP_STRING const& msg);
	/// used internally
	JSONCPP_NORETURN void throwLogicError(JSONCPP_STRING const& msg);

	/** \brief Type of the value held by a Value object.
	*/
	enum ValueType {
		nullValue = 0, ///< 'null' value
		intValue,      ///< signed integer value
		uintValue,     ///< unsigned integer value
		realValue,     ///< double value
		stringValue,   ///< UTF-8 string value
		booleanValue,  ///< bool value
		arrayValue,    ///< array value (ordered list)
		objectValue    ///< object value (collection of name/value pairs).
	};

	enum CommentPlacement {
		commentBefore = 0,      ///< a comment placed on the line before a value
		commentAfterOnSameLine, ///< a comment just after a value on the same line
		commentAfter, ///< a comment on the line after a value (only make sense for
					  /// root value)
					  numberOfCommentPlacement
	};

	//# ifdef JSON_USE_CPPTL
	//   typedef CppTL::AnyEnumerator<const char *> EnumMemberNames;
	//   typedef CppTL::AnyEnumerator<const Value &> EnumValues;
	//# endif

	/** \brief Lightweight wrapper to tag static string.
	*
	* Value constructor and objectValue member assignement takes advantage of the
	* StaticString and avoid the cost of string duplication when storing the
	* string or the member name.
	*
	* Example of usage:
	* \code
	* Json::Value aValue( StaticString("some text") );
	* Json::Value object;
	* static const StaticString code("code");
	* object[code] = 1234;
	* \endcode
	*/
	class JSON_API StaticString {
	public:
		explicit StaticString(const char* czstring) : c_str_(czstring) {}

		operator const char*() const { return c_str_; }

		const char* c_str() const { return c_str_; }

	private:
		const char* c_str_;
	};

	/** \brief Represents a <a HREF="http://www.json.org">JSON</a> value.
	*
	* This class is a discriminated union wrapper that can represents a:
	* - signed integer [range: Value::minInt - Value::maxInt]
	* - unsigned integer (range: 0 - Value::maxUInt)
	* - double
	* - UTF-8 string
	* - boolean
	* - 'null'
	* - an ordered list of Value
	* - collection of name/value pairs (javascript object)
	*
	* The type of the held value is represented by a #ValueType and
	* can be obtained using type().
	*
	* Values of an #objectValue or #arrayValue can be accessed using operator[]()
	* methods.
	* Non-const methods will automatically create the a #nullValue element
	* if it does not exist.
	* The sequence of an #arrayValue will be automatically resized and initialized
	* with #nullValue. resize() can be used to enlarge or truncate an #arrayValue.
	*
	* The get() methods can be used to obtain default value in the case the
	* required element does not exist.
	*
	* It is possible to iterate over the list of a #objectValue values using
	* the getMemberNames() method.
	*
	* \note #Value string-length fit in size_t, but keys must be < 2^30.
	* (The reason is an implementation detail.) A #CharReader will raise an
	* exception if a bound is exceeded to avoid security holes in your app,
	* but the Value API does *not* check bounds. That is the responsibility
	* of the caller.
	*/
	class JSON_API Value {
		friend class ValueIteratorBase;
	public:
		typedef std::vector<JSONCPP_STRING> Members;
		typedef ValueIterator iterator;
		typedef ValueConstIterator const_iterator;
		typedef Json::UInt UInt;
		typedef Json::Int Int;
#if defined(JSON_HAS_INT64)
		typedef Json::UInt64 UInt64;
		typedef Json::Int64 Int64;
#endif // defined(JSON_HAS_INT64)
		typedef Json::LargestInt LargestInt;
		typedef Json::LargestUInt LargestUInt;
		typedef Json::ArrayIndex ArrayIndex;

		static const Value& null;  ///< We regret this reference to a global instance; prefer the simpler Value().
		static const Value& nullRef;  ///< just a kludge for binary-compatibility; same as null
		static Value const& nullSingleton(); ///< Prefer this to null or nullRef.

											 /// Minimum signed integer value that can be stored in a Json::Value.
		static const LargestInt minLargestInt;
		/// Maximum signed integer value that can be stored in a Json::Value.
		static const LargestInt maxLargestInt;
		/// Maximum unsigned integer value that can be stored in a Json::Value.
		static const LargestUInt maxLargestUInt;

		/// Minimum signed int value that can be stored in a Json::Value.
		static const Int minInt;
		/// Maximum signed int value that can be stored in a Json::Value.
		static const Int maxInt;
		/// Maximum unsigned int value that can be stored in a Json::Value.
		static const UInt maxUInt;

#if defined(JSON_HAS_INT64)
		/// Minimum signed 64 bits int value that can be stored in a Json::Value.
		static const Int64 minInt64;
		/// Maximum signed 64 bits int value that can be stored in a Json::Value.
		static const Int64 maxInt64;
		/// Maximum unsigned 64 bits int value that can be stored in a Json::Value.
		static const UInt64 maxUInt64;
#endif // defined(JSON_HAS_INT64)

	private:
#ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION
		class CZString {
		public:
			enum DuplicationPolicy {
				noDuplication = 0,
				duplicate,
				duplicateOnCopy
			};
			CZString(ArrayIndex index);
			CZString(char const* str, unsigned length, DuplicationPolicy allocate);
			CZString(CZString const& other);
#if JSON_HAS_RVALUE_REFERENCES
			CZString(CZString&& other);
#endif
			~CZString();
			CZString& operator=(CZString other);
			bool operator<(CZString const& other) const;
			bool operator==(CZString const& other) const;
			ArrayIndex index() const;
			//const char* c_str() const; ///< \deprecated
			char const* data() const;
			unsigned length() const;
			bool isStaticString() const;

		private:
			void swap(CZString& other);

			struct StringStorage {
				unsigned policy_ : 2;
				unsigned length_ : 30; // 1GB max
			};

			char const* cstr_;  // actually, a prefixed string, unless policy is noDup
			union {
				ArrayIndex index_;
				StringStorage storage_;
			};
		};

	public:
#ifndef JSON_USE_CPPTL_SMALLMAP
		typedef std::map<CZString, Value> ObjectValues;
#else
		typedef CppTL::SmallMap<CZString, Value> ObjectValues;
#endif // ifndef JSON_USE_CPPTL_SMALLMAP
#endif // ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION

	public:
		/** \brief Create a default Value of the given type.

		This is a very useful constructor.
		To create an empty array, pass arrayValue.
		To create an empty object, pass objectValue.
		Another Value can then be set to this one by assignment.
		This is useful since clear() and resize() will not alter types.

		Examples:
		\code
		Json::Value null_value; // null
		Json::Value arr_value(Json::arrayValue); // []
		Json::Value obj_value(Json::objectValue); // {}
		\endcode
		*/
		Value(ValueType type = nullValue);
		Value(Int value);
		Value(UInt value);
#if defined(JSON_HAS_INT64)
		Value(Int64 value);
		Value(UInt64 value);
#endif // if defined(JSON_HAS_INT64)
		Value(double value);
		Value(const char* value); ///< Copy til first 0. (NULL causes to seg-fault.)
		Value(const char* begin, const char* end); ///< Copy all, incl zeroes.
												   /** \brief Constructs a value from a static string.

												   * Like other value string constructor but do not duplicate the string for
												   * internal storage. The given string must remain alive after the call to this
												   * constructor.
												   * \note This works only for null-terminated strings. (We cannot change the
												   *   size of this class, so we have nowhere to store the length,
												   *   which might be computed later for various operations.)
												   *
												   * Example of usage:
												   * \code
												   * static StaticString foo("some text");
												   * Json::Value aValue(foo);
												   * \endcode
												   */
		Value(const StaticString& value);
		Value(const JSONCPP_STRING& value); ///< Copy data() til size(). Embedded zeroes too.
#ifdef JSON_USE_CPPTL
		Value(const CppTL::ConstString& value);
#endif
		Value(bool value);
		/// Deep copy.
		Value(const Value& other);
#if JSON_HAS_RVALUE_REFERENCES
		/// Move constructor
		Value(Value&& other);
#endif
		~Value();

		/// Deep copy, then swap(other).
		/// \note Over-write existing comments. To preserve comments, use #swapPayload().
		Value& operator=(Value other);
		/// Swap everything.
		void swap(Value& other);
		/// Swap values but leave comments and source offsets in place.
		void swapPayload(Value& other);

		ValueType type() const;

		/// Compare payload only, not comments etc.
		bool operator<(const Value& other) const;
		bool operator<=(const Value& other) const;
		bool operator>=(const Value& other) const;
		bool operator>(const Value& other) const;
		bool operator==(const Value& other) const;
		bool operator!=(const Value& other) const;
		int compare(const Value& other) const;

		const char* asCString() const; ///< Embedded zeroes could cause you trouble!
#if JSONCPP_USING_SECURE_MEMORY
		unsigned getCStringLength() const; //Allows you to understand the length of the CString
#endif
		JSONCPP_STRING asString() const; ///< Embedded zeroes are possible.
										 /** Get raw char* of string-value.
										 *  \return false if !string. (Seg-fault if str or end are NULL.)
										 */
		bool getString(
			char const** begin, char const** end) const;
#ifdef JSON_USE_CPPTL
		CppTL::ConstString asConstString() const;
#endif
		Int asInt() const;
		UInt asUInt() const;
#if defined(JSON_HAS_INT64)
		Int64 asInt64() const;
		UInt64 asUInt64() const;
#endif // if defined(JSON_HAS_INT64)
		LargestInt asLargestInt() const;
		LargestUInt asLargestUInt() const;
		float asFloat() const;
		double asDouble() const;
		bool asBool() const;

		bool isNull() const;
		bool isBool() const;
		bool isInt() const;
		bool isInt64() const;
		bool isUInt() const;
		bool isUInt64() const;
		bool isIntegral() const;
		bool isDouble() const;
		bool isNumeric() const;
		bool isString() const;
		bool isArray() const;
		bool isObject() const;

		bool isConvertibleTo(ValueType other) const;

		/// Number of values in array or object
		ArrayIndex size() const;

		/// \brief Return true if empty array, empty object, or null;
		/// otherwise, false.
		bool empty() const;

		/// Return isNull()
		bool operator!() const;

		/// Remove all object members and array elements.
		/// \pre type() is arrayValue, objectValue, or nullValue
		/// \post type() is unchanged
		void clear();

		/// Resize the array to size elements.
		/// New elements are initialized to null.
		/// May only be called on nullValue or arrayValue.
		/// \pre type() is arrayValue or nullValue
		/// \post type() is arrayValue
		void resize(ArrayIndex size);

		/// Access an array element (zero based index ).
		/// If the array contains less than index element, then null value are
		/// inserted
		/// in the array so that its size is index+1.
		/// (You may need to say 'value[0u]' to get your compiler to distinguish
		///  this from the operator[] which takes a string.)
		Value& operator[](ArrayIndex index);

		/// Access an array element (zero based index ).
		/// If the array contains less than index element, then null value are
		/// inserted
		/// in the array so that its size is index+1.
		/// (You may need to say 'value[0u]' to get your compiler to distinguish
		///  this from the operator[] which takes a string.)
		Value& operator[](int index);

		/// Access an array element (zero based index )
		/// (You may need to say 'value[0u]' to get your compiler to distinguish
		///  this from the operator[] which takes a string.)
		const Value& operator[](ArrayIndex index) const;

		/// Access an array element (zero based index )
		/// (You may need to say 'value[0u]' to get your compiler to distinguish
		///  this from the operator[] which takes a string.)
		const Value& operator[](int index) const;

		/// If the array contains at least index+1 elements, returns the element
		/// value,
		/// otherwise returns defaultValue.
		Value get(ArrayIndex index, const Value& defaultValue) const;
		/// Return true if index < size().
		bool isValidIndex(ArrayIndex index) const;
		/// \brief Append value to array at the end.
		///
		/// Equivalent to jsonvalue[jsonvalue.size()] = value;
		Value& append(const Value& value);

		/// Access an object value by name, create a null member if it does not exist.
		/// \note Because of our implementation, keys are limited to 2^30 -1 chars.
		///  Exceeding that will cause an exception.
		Value& operator[](const char* key);
		/// Access an object value by name, returns null if there is no member with
		/// that name.
		const Value& operator[](const char* key) const;
		/// Access an object value by name, create a null member if it does not exist.
		/// \param key may contain embedded nulls.
		Value& operator[](const JSONCPP_STRING& key);
		/// Access an object value by name, returns null if there is no member with
		/// that name.
		/// \param key may contain embedded nulls.
		const Value& operator[](const JSONCPP_STRING& key) const;
		/** \brief Access an object value by name, create a null member if it does not
		exist.

		* If the object has no entry for that name, then the member name used to store
		* the new entry is not duplicated.
		* Example of use:
		* \code
		* Json::Value object;
		* static const StaticString code("code");
		* object[code] = 1234;
		* \endcode
		*/
		Value& operator[](const StaticString& key);
#ifdef JSON_USE_CPPTL
		/// Access an object value by name, create a null member if it does not exist.
		Value& operator[](const CppTL::ConstString& key);
		/// Access an object value by name, returns null if there is no member with
		/// that name.
		const Value& operator[](const CppTL::ConstString& key) const;
#endif
		/// Return the member named key if it exist, defaultValue otherwise.
		/// \note deep copy
		Value get(const char* key, const Value& defaultValue) const;
		/// Return the member named key if it exist, defaultValue otherwise.
		/// \note deep copy
		/// \note key may contain embedded nulls.
		Value get(const char* begin, const char* end, const Value& defaultValue) const;
		/// Return the member named key if it exist, defaultValue otherwise.
		/// \note deep copy
		/// \param key may contain embedded nulls.
		Value get(const JSONCPP_STRING& key, const Value& defaultValue) const;
#ifdef JSON_USE_CPPTL
		/// Return the member named key if it exist, defaultValue otherwise.
		/// \note deep copy
		Value get(const CppTL::ConstString& key, const Value& defaultValue) const;
#endif
		/// Most general and efficient version of isMember()const, get()const,
		/// and operator[]const
		/// \note As stated elsewhere, behavior is undefined if (end-begin) >= 2^30
		Value const* find(char const* begin, char const* end) const;
		/// Most general and efficient version of object-mutators.
		/// \note As stated elsewhere, behavior is undefined if (end-begin) >= 2^30
		/// \return non-zero, but JSON_ASSERT if this is neither object nor nullValue.
		Value const* demand(char const* begin, char const* end);
		/// \brief Remove and return the named member.
		///
		/// Do nothing if it did not exist.
		/// \return the removed Value, or null.
		/// \pre type() is objectValue or nullValue
		/// \post type() is unchanged
		/// \deprecated
		Value removeMember(const char* key);
		/// Same as removeMember(const char*)
		/// \param key may contain embedded nulls.
		/// \deprecated
		Value removeMember(const JSONCPP_STRING& key);
		/// Same as removeMember(const char* begin, const char* end, Value* removed),
		/// but 'key' is null-terminated.
		bool removeMember(const char* key, Value* removed);
		/** \brief Remove the named map member.

		Update 'removed' iff removed.
		\param key may contain embedded nulls.
		\return true iff removed (no exceptions)
		*/
		bool removeMember(JSONCPP_STRING const& key, Value* removed);
		/// Same as removeMember(JSONCPP_STRING const& key, Value* removed)
		bool removeMember(const char* begin, const char* end, Value* removed);
		/** \brief Remove the indexed array element.

		O(n) expensive operations.
		Update 'removed' iff removed.
		\return true iff removed (no exceptions)
		*/
		bool removeIndex(ArrayIndex i, Value* removed);

		/// Return true if the object has a member named key.
		/// \note 'key' must be null-terminated.
		bool isMember(const char* key) const;
		/// Return true if the object has a member named key.
		/// \param key may contain embedded nulls.
		bool isMember(const JSONCPP_STRING& key) const;
		/// Same as isMember(JSONCPP_STRING const& key)const
		bool isMember(const char* begin, const char* end) const;
#ifdef JSON_USE_CPPTL
		/// Return true if the object has a member named key.
		bool isMember(const CppTL::ConstString& key) const;
#endif

		/// \brief Return a list of the member names.
		///
		/// If null, return an empty list.
		/// \pre type() is objectValue or nullValue
		/// \post if type() was nullValue, it remains nullValue
		Members getMemberNames() const;

		//# ifdef JSON_USE_CPPTL
		//      EnumMemberNames enumMemberNames() const;
		//      EnumValues enumValues() const;
		//# endif

		/// \deprecated Always pass len.
		JSONCPP_DEPRECATED("Use setComment(JSONCPP_STRING const&) instead.")
			void setComment(const char* comment, CommentPlacement placement);
		/// Comments must be //... or /* ... */
		void setComment(const char* comment, size_t len, CommentPlacement placement);
		/// Comments must be //... or /* ... */
		void setComment(const JSONCPP_STRING& comment, CommentPlacement placement);
		bool hasComment(CommentPlacement placement) const;
		/// Include delimiters and embedded newlines.
		JSONCPP_STRING getComment(CommentPlacement placement) const;

		JSONCPP_STRING toStyledString() const;

		const_iterator begin() const;
		const_iterator end() const;

		iterator begin();
		iterator end();

		// Accessors for the [start, limit) range of bytes within the JSON text from
		// which this value was parsed, if any.
		void setOffsetStart(ptrdiff_t start);
		void setOffsetLimit(ptrdiff_t limit);
		ptrdiff_t getOffsetStart() const;
		ptrdiff_t getOffsetLimit() const;

	private:
		void initBasic(ValueType type, bool allocated = false);

		Value& resolveReference(const char* key);
		Value& resolveReference(const char* key, const char* end);

		struct CommentInfo {
			CommentInfo();
			~CommentInfo();

			void setComment(const char* text, size_t len);

			char* comment_;
		};

		// struct MemberNamesTransform
		//{
		//   typedef const char *result_type;
		//   const char *operator()( const CZString &name ) const
		//   {
		//      return name.c_str();
		//   }
		//};

		union ValueHolder {
			LargestInt int_;
			LargestUInt uint_;
			double real_;
			bool bool_;
			char* string_;  // actually ptr to unsigned, followed by str, unless !allocated_
			ObjectValues* map_;
		} value_;
		ValueType type_ : 8;
		unsigned int allocated_ : 1; // Notes: if declared as bool, bitfield is useless.
									 // If not allocated_, string_ must be null-terminated.
		CommentInfo* comments_;

		// [start, limit) byte offsets in the source JSON text from which this Value
		// was extracted.
		ptrdiff_t start_;
		ptrdiff_t limit_;
	};

	/** \brief Experimental and untested: represents an element of the "path" to
	* access a node.
	*/
	class JSON_API PathArgument {
	public:
		friend class Path;

		PathArgument();
		PathArgument(ArrayIndex index);
		PathArgument(const char* key);
		PathArgument(const JSONCPP_STRING& key);

	private:
		enum Kind {
			kindNone = 0,
			kindIndex,
			kindKey
		};
		JSONCPP_STRING key_;
		ArrayIndex index_;
		Kind kind_;
	};

	/** \brief Experimental and untested: represents a "path" to access a node.
	*
	* Syntax:
	* - "." => root node
	* - ".[n]" => elements at index 'n' of root node (an array value)
	* - ".name" => member named 'name' of root node (an object value)
	* - ".name1.name2.name3"
	* - ".[0][1][2].name1[3]"
	* - ".%" => member name is provided as parameter
	* - ".[%]" => index is provied as parameter
	*/
	class JSON_API Path {
	public:
		Path(const JSONCPP_STRING& path,
			const PathArgument& a1 = PathArgument(),
			const PathArgument& a2 = PathArgument(),
			const PathArgument& a3 = PathArgument(),
			const PathArgument& a4 = PathArgument(),
			const PathArgument& a5 = PathArgument());

		const Value& resolve(const Value& root) const;
		Value resolve(const Value& root, const Value& defaultValue) const;
		/// Creates the "path" to access the specified node and returns a reference on
		/// the node.
		Value& make(Value& root) const;

	private:
		typedef std::vector<const PathArgument*> InArgs;
		typedef std::vector<PathArgument> Args;

		void makePath(const JSONCPP_STRING& path, const InArgs& in);
		void addPathInArg(const JSONCPP_STRING& path,
			const InArgs& in,
			InArgs::const_iterator& itInArg,
			PathArgument::Kind kind);
		void invalidPath(const JSONCPP_STRING& path, int location);

		Args args_;
	};

	/** \brief base class for Value iterators.
	*
	*/
	class JSON_API ValueIteratorBase {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef unsigned int size_t;
		typedef int difference_type;
		typedef ValueIteratorBase SelfType;

		bool operator==(const SelfType& other) const { return isEqual(other); }

		bool operator!=(const SelfType& other) const { return !isEqual(other); }

		difference_type operator-(const SelfType& other) const {
			return other.computeDistance(*this);
		}

		/// Return either the index or the member name of the referenced value as a
		/// Value.
		Value key() const;

		/// Return the index of the referenced Value, or -1 if it is not an arrayValue.
		UInt index() const;

		/// Return the member name of the referenced Value, or "" if it is not an
		/// objectValue.
		/// \note Avoid `c_str()` on result, as embedded zeroes are possible.
		JSONCPP_STRING name() const;

		/// Return the member name of the referenced Value. "" if it is not an
		/// objectValue.
		/// \deprecated This cannot be used for UTF-8 strings, since there can be embedded nulls.
		JSONCPP_DEPRECATED("Use `key = name();` instead.")
			char const* memberName() const;
		/// Return the member name of the referenced Value, or NULL if it is not an
		/// objectValue.
		/// \note Better version than memberName(). Allows embedded nulls.
		char const* memberName(char const** end) const;

	protected:
		Value& deref() const;

		void increment();

		void decrement();

		difference_type computeDistance(const SelfType& other) const;

		bool isEqual(const SelfType& other) const;

		void copy(const SelfType& other);

	private:
		Value::ObjectValues::iterator current_;
		// Indicates that iterator is for a null value.
		bool isNull_;

	public:
		// For some reason, BORLAND needs these at the end, rather
		// than earlier. No idea why.
		ValueIteratorBase();
		explicit ValueIteratorBase(const Value::ObjectValues::iterator& current);
	};

	/** \brief const iterator for object and array value.
	*
	*/
	class JSON_API ValueConstIterator : public ValueIteratorBase {
		friend class Value;

	public:
		typedef const Value value_type;
		//typedef unsigned int size_t;
		//typedef int difference_type;
		typedef const Value& reference;
		typedef const Value* pointer;
		typedef ValueConstIterator SelfType;

		ValueConstIterator();
		ValueConstIterator(ValueIterator const& other);

	private:
		/*! \internal Use by Value to create an iterator.
		*/
		explicit ValueConstIterator(const Value::ObjectValues::iterator& current);
	public:
		SelfType& operator=(const ValueIteratorBase& other);

		SelfType operator++(int) {
			SelfType temp(*this);
			++*this;
			return temp;
		}

		SelfType operator--(int) {
			SelfType temp(*this);
			--*this;
			return temp;
		}

		SelfType& operator--() {
			decrement();
			return *this;
		}

		SelfType& operator++() {
			increment();
			return *this;
		}

		reference operator*() const { return deref(); }

		pointer operator->() const { return &deref(); }
	};

	/** \brief Iterator for object and array value.
	*/
	class JSON_API ValueIterator : public ValueIteratorBase {
		friend class Value;

	public:
		typedef Value value_type;
		typedef unsigned int size_t;
		typedef int difference_type;
		typedef Value& reference;
		typedef Value* pointer;
		typedef ValueIterator SelfType;

		ValueIterator();
		explicit ValueIterator(const ValueConstIterator& other);
		ValueIterator(const ValueIterator& other);

	private:
		/*! \internal Use by Value to create an iterator.
		*/
		explicit ValueIterator(const Value::ObjectValues::iterator& current);
	public:
		SelfType& operator=(const SelfType& other);

		SelfType operator++(int) {
			SelfType temp(*this);
			++*this;
			return temp;
		}

		SelfType operator--(int) {
			SelfType temp(*this);
			--*this;
			return temp;
		}

		SelfType& operator--() {
			decrement();
			return *this;
		}

		SelfType& operator++() {
			increment();
			return *this;
		}

		reference operator*() const { return deref(); }

		pointer operator->() const { return &deref(); }
	};

} // namespace Json


namespace std {
	/// Specialize std::swap() for Json::Value.
	template<>
	inline void swap(Json::Value& a, Json::Value& b) { a.swap(b); }
}


#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(pop)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

#endif // CPPTL_JSON_H_INCLUDED

// //////////////////////////////////////////////////////////////////////
// End of content of file: include/json/value.h
// //////////////////////////////////////////////////////////////////////






// //////////////////////////////////////////////////////////////////////
// Beginning of content of file: include/json/reader.h
// //////////////////////////////////////////////////////////////////////

// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef CPPTL_JSON_READER_H_INCLUDED
#define CPPTL_JSON_READER_H_INCLUDED

#if !defined(JSON_IS_AMALGAMATION)
#include "features.h"
#include "value.h"
#endif // if !defined(JSON_IS_AMALGAMATION)
#include <deque>
#include <iosfwd>
#include <stack>
#include <string>
#include <istream>

// Disable warning C4251: <data member>: <type> needs to have dll-interface to
// be used by...
#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

namespace Json {

	/** \brief Unserialize a <a HREF="http://www.json.org">JSON</a> document into a
	*Value.
	*
	* \deprecated Use CharReader and CharReaderBuilder.
	*/
	class JSON_API Reader {
	public:
		typedef char Char;
		typedef const Char* Location;

		/** \brief An error tagged with where in the JSON text it was encountered.
		*
		* The offsets give the [start, limit) range of bytes within the text. Note
		* that this is bytes, not codepoints.
		*
		*/
		struct StructuredError {
			ptrdiff_t offset_start;
			ptrdiff_t offset_limit;
			JSONCPP_STRING message;
		};

		/** \brief Constructs a Reader allowing all features
		* for parsing.
		*/
		Reader();

		/** \brief Constructs a Reader allowing the specified feature set
		* for parsing.
		*/
		Reader(const Features& features);

		/** \brief Read a Value from a <a HREF="http://www.json.org">JSON</a>
		* document.
		* \param document UTF-8 encoded string containing the document to read.
		* \param root [out] Contains the root value of the document if it was
		*             successfully parsed.
		* \param collectComments \c true to collect comment and allow writing them
		* back during
		*                        serialization, \c false to discard comments.
		*                        This parameter is ignored if
		* Features::allowComments_
		*                        is \c false.
		* \return \c true if the document was successfully parsed, \c false if an
		* error occurred.
		*/
		bool
			parse(const std::string& document, Value& root, bool collectComments = true);

		/** \brief Read a Value from a <a HREF="http://www.json.org">JSON</a>
		document.
		* \param beginDoc Pointer on the beginning of the UTF-8 encoded string of the
		document to read.
		* \param endDoc Pointer on the end of the UTF-8 encoded string of the
		document to read.
		*               Must be >= beginDoc.
		* \param root [out] Contains the root value of the document if it was
		*             successfully parsed.
		* \param collectComments \c true to collect comment and allow writing them
		back during
		*                        serialization, \c false to discard comments.
		*                        This parameter is ignored if
		Features::allowComments_
		*                        is \c false.
		* \return \c true if the document was successfully parsed, \c false if an
		error occurred.
		*/
		bool parse(const char* beginDoc,
			const char* endDoc,
			Value& root,
			bool collectComments = true);

		/// \brief Parse from input stream.
		/// \see Json::operator>>(std::istream&, Json::Value&).
		bool parse(JSONCPP_ISTREAM& is, Value& root, bool collectComments = true);

		/** \brief Returns a user friendly string that list errors in the parsed
		* document.
		* \return Formatted error message with the list of errors with their location
		* in
		*         the parsed document. An empty string is returned if no error
		* occurred
		*         during parsing.
		* \deprecated Use getFormattedErrorMessages() instead (typo fix).
		*/
		JSONCPP_DEPRECATED("Use getFormattedErrorMessages() instead.")
			JSONCPP_STRING getFormatedErrorMessages() const;

		/** \brief Returns a user friendly string that list errors in the parsed
		* document.
		* \return Formatted error message with the list of errors with their location
		* in
		*         the parsed document. An empty string is returned if no error
		* occurred
		*         during parsing.
		*/
		JSONCPP_STRING getFormattedErrorMessages() const;

		/** \brief Returns a vector of structured erros encounted while parsing.
		* \return A (possibly empty) vector of StructuredError objects. Currently
		*         only one error can be returned, but the caller should tolerate
		* multiple
		*         errors.  This can occur if the parser recovers from a non-fatal
		*         parse error and then encounters additional errors.
		*/
		std::vector<StructuredError> getStructuredErrors() const;

		/** \brief Add a semantic error message.
		* \param value JSON Value location associated with the error
		* \param message The error message.
		* \return \c true if the error was successfully added, \c false if the
		* Value offset exceeds the document size.
		*/
		bool pushError(const Value& value, const JSONCPP_STRING& message);

		/** \brief Add a semantic error message with extra context.
		* \param value JSON Value location associated with the error
		* \param message The error message.
		* \param extra Additional JSON Value location to contextualize the error
		* \return \c true if the error was successfully added, \c false if either
		* Value offset exceeds the document size.
		*/
		bool pushError(const Value& value, const JSONCPP_STRING& message, const Value& extra);

		/** \brief Return whether there are any errors.
		* \return \c true if there are no errors to report \c false if
		* errors have occurred.
		*/
		bool good() const;

	private:
		enum TokenType {
			tokenEndOfStream = 0,
			tokenObjectBegin,
			tokenObjectEnd,
			tokenArrayBegin,
			tokenArrayEnd,
			tokenString,
			tokenNumber,
			tokenTrue,
			tokenFalse,
			tokenNull,
			tokenArraySeparator,
			tokenMemberSeparator,
			tokenComment,
			tokenError
		};

		class Token {
		public:
			TokenType type_;
			Location start_;
			Location end_;
		};

		class ErrorInfo {
		public:
			Token token_;
			JSONCPP_STRING message_;
			Location extra_;
		};

		typedef std::deque<ErrorInfo> Errors;

		bool readToken(Token& token);
		void skipSpaces();
		bool match(Location pattern, int patternLength);
		bool readComment();
		bool readCStyleComment();
		bool readCppStyleComment();
		bool readString();
		void readNumber();
		bool readValue();
		bool readObject(Token& token);
		bool readArray(Token& token);
		bool decodeNumber(Token& token);
		bool decodeNumber(Token& token, Value& decoded);
		bool decodeString(Token& token);
		bool decodeString(Token& token, JSONCPP_STRING& decoded);
		bool decodeDouble(Token& token);
		bool decodeDouble(Token& token, Value& decoded);
		bool decodeUnicodeCodePoint(Token& token,
			Location& current,
			Location end,
			unsigned int& unicode);
		bool decodeUnicodeEscapeSequence(Token& token,
			Location& current,
			Location end,
			unsigned int& unicode);
		bool addError(const JSONCPP_STRING& message, Token& token, Location extra = 0);
		bool recoverFromError(TokenType skipUntilToken);
		bool addErrorAndRecover(const JSONCPP_STRING& message,
			Token& token,
			TokenType skipUntilToken);
		void skipUntilSpace();
		Value& currentValue();
		Char getNextChar();
		void
			getLocationLineAndColumn(Location location, int& line, int& column) const;
		JSONCPP_STRING getLocationLineAndColumn(Location location) const;
		void addComment(Location begin, Location end, CommentPlacement placement);
		void skipCommentTokens(Token& token);

		typedef std::stack<Value*> Nodes;
		Nodes nodes_;
		Errors errors_;
		JSONCPP_STRING document_;
		Location begin_;
		Location end_;
		Location current_;
		Location lastValueEnd_;
		Value* lastValue_;
		JSONCPP_STRING commentsBefore_;
		Features features_;
		bool collectComments_;
	};  // Reader

		/** Interface for reading JSON from a char array.
		*/
	class JSON_API CharReader {
	public:
		virtual ~CharReader() {}
		/** \brief Read a Value from a <a HREF="http://www.json.org">JSON</a>
		document.
		* The document must be a UTF-8 encoded string containing the document to read.
		*
		* \param beginDoc Pointer on the beginning of the UTF-8 encoded string of the
		document to read.
		* \param endDoc Pointer on the end of the UTF-8 encoded string of the
		document to read.
		*        Must be >= beginDoc.
		* \param root [out] Contains the root value of the document if it was
		*             successfully parsed.
		* \param errs [out] Formatted error messages (if not NULL)
		*        a user friendly string that lists errors in the parsed
		* document.
		* \return \c true if the document was successfully parsed, \c false if an
		error occurred.
		*/
		virtual bool parse(
			char const* beginDoc, char const* endDoc,
			Value* root, JSONCPP_STRING* errs) = 0;

		class JSON_API Factory {
		public:
			virtual ~Factory() {}
			/** \brief Allocate a CharReader via operator new().
			* \throw std::exception if something goes wrong (e.g. invalid settings)
			*/
			virtual CharReader* newCharReader() const = 0;
		};  // Factory
	};  // CharReader

		/** \brief Build a CharReader implementation.

		Usage:
		\code
		using namespace Json;
		CharReaderBuilder builder;
		builder["collectComments"] = false;
		Value value;
		JSONCPP_STRING errs;
		bool ok = parseFromStream(builder, std::cin, &value, &errs);
		\endcode
		*/
	class JSON_API CharReaderBuilder : public CharReader::Factory {
	public:
		// Note: We use a Json::Value so that we can add data-members to this class
		// without a major version bump.
		/** Configuration of this builder.
		These are case-sensitive.
		Available settings (case-sensitive):
		- `"collectComments": false or true`
		- true to collect comment and allow writing them
		back during serialization, false to discard comments.
		This parameter is ignored if allowComments is false.
		- `"allowComments": false or true`
		- true if comments are allowed.
		- `"strictRoot": false or true`
		- true if root must be either an array or an object value
		- `"allowDroppedNullPlaceholders": false or true`
		- true if dropped null placeholders are allowed. (See StreamWriterBuilder.)
		- `"allowNumericKeys": false or true`
		- true if numeric object keys are allowed.
		- `"allowSingleQuotes": false or true`
		- true if '' are allowed for strings (both keys and values)
		- `"stackLimit": integer`
		- Exceeding stackLimit (recursive depth of `readValue()`) will
		cause an exception.
		- This is a security issue (seg-faults caused by deeply nested JSON),
		so the default is low.
		- `"failIfExtra": false or true`
		- If true, `parse()` returns false when extra non-whitespace trails
		the JSON value in the input string.
		- `"rejectDupKeys": false or true`
		- If true, `parse()` returns false when a key is duplicated within an object.
		- `"allowSpecialFloats": false or true`
		- If true, special float values (NaNs and infinities) are allowed
		and their values are lossfree restorable.

		You can examine 'settings_` yourself
		to see the defaults. You can also write and read them just like any
		JSON Value.
		\sa setDefaults()
		*/
		Json::Value settings_;

		CharReaderBuilder();
		~CharReaderBuilder() JSONCPP_OVERRIDE;

		CharReader* newCharReader() const JSONCPP_OVERRIDE;

		/** \return true if 'settings' are legal and consistent;
		*   otherwise, indicate bad settings via 'invalid'.
		*/
		bool validate(Json::Value* invalid) const;

		/** A simple way to update a specific setting.
		*/
		Value& operator[](JSONCPP_STRING key);

		/** Called by ctor, but you can use this to reset settings_.
		* \pre 'settings' != NULL (but Json::null is fine)
		* \remark Defaults:
		* \snippet src/lib_json/json_reader.cpp CharReaderBuilderDefaults
		*/
		static void setDefaults(Json::Value* settings);
		/** Same as old Features::strictMode().
		* \pre 'settings' != NULL (but Json::null is fine)
		* \remark Defaults:
		* \snippet src/lib_json/json_reader.cpp CharReaderBuilderStrictMode
		*/
		static void strictMode(Json::Value* settings);
	};

	/** Consume entire stream and use its begin/end.
	* Someday we might have a real StreamReader, but for now this
	* is convenient.
	*/
	bool JSON_API parseFromStream(
		CharReader::Factory const&,
		JSONCPP_ISTREAM&,
		Value* root, std::string* errs);

	/** \brief Read from 'sin' into 'root'.

	Always keep comments from the input JSON.

	This can be used to read a file into a particular sub-object.
	For example:
	\code
	Json::Value root;
	cin >> root["dir"]["file"];
	cout << root;
	\endcode
	Result:
	\verbatim
	{
	"dir": {
	"file": {
	// The input stream JSON would be nested here.
	}
	}
	}
	\endverbatim
	\throw std::exception on parse error.
	\see Json::operator<<()
	*/
	JSON_API JSONCPP_ISTREAM& operator >> (JSONCPP_ISTREAM&, Value&);

} // namespace Json

#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(pop)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

#endif // CPPTL_JSON_READER_H_INCLUDED

  // //////////////////////////////////////////////////////////////////////
  // End of content of file: include/json/reader.h
  // //////////////////////////////////////////////////////////////////////






  // //////////////////////////////////////////////////////////////////////
  // Beginning of content of file: include/json/writer.h
  // //////////////////////////////////////////////////////////////////////

  // Copyright 2007-2010 Baptiste Lepilleur
  // Distributed under MIT license, or public domain if desired and
  // recognized in your jurisdiction.
  // See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef JSON_WRITER_H_INCLUDED
#define JSON_WRITER_H_INCLUDED

#if !defined(JSON_IS_AMALGAMATION)
#include "value.h"
#endif // if !defined(JSON_IS_AMALGAMATION)
#include <vector>
#include <string>
#include <ostream>

  // Disable warning C4251: <data member>: <type> needs to have dll-interface to
  // be used by...
#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

namespace Json {

	class Value;

	/**

	Usage:
	\code
	using namespace Json;
	void writeToStdout(StreamWriter::Factory const& factory, Value const& value) {
	std::unique_ptr<StreamWriter> const writer(
	factory.newStreamWriter());
	writer->write(value, &std::cout);
	std::cout << std::endl;  // add lf and flush
	}
	\endcode
	*/
	class JSON_API StreamWriter {
	protected:
		JSONCPP_OSTREAM* sout_;  // not owned; will not delete
	public:
		StreamWriter();
		virtual ~StreamWriter();
		/** Write Value into document as configured in sub-class.
		Do not take ownership of sout, but maintain a reference during function.
		\pre sout != NULL
		\return zero on success (For now, we always return zero, so check the stream instead.)
		\throw std::exception possibly, depending on configuration
		*/
		virtual int write(Value const& root, JSONCPP_OSTREAM* sout) = 0;

		/** \brief A simple abstract factory.
		*/
		class JSON_API Factory {
		public:
			virtual ~Factory();
			/** \brief Allocate a CharReader via operator new().
			* \throw std::exception if something goes wrong (e.g. invalid settings)
			*/
			virtual StreamWriter* newStreamWriter() const = 0;
		};  // Factory
	};  // StreamWriter

		/** \brief Write into stringstream, then return string, for convenience.
		* A StreamWriter will be created from the factory, used, and then deleted.
		*/
	JSONCPP_STRING JSON_API writeString(StreamWriter::Factory const& factory, Value const& root);


	/** \brief Build a StreamWriter implementation.

	Usage:
	\code
	using namespace Json;
	Value value = ...;
	StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "   ";  // or whatever you like
	std::unique_ptr<Json::StreamWriter> writer(
	builder.newStreamWriter());
	writer->write(value, &std::cout);
	std::cout << std::endl;  // add lf and flush
	\endcode
	*/
	class JSON_API StreamWriterBuilder : public StreamWriter::Factory {
	public:
		// Note: We use a Json::Value so that we can add data-members to this class
		// without a major version bump.
		/** Configuration of this builder.
		Available settings (case-sensitive):
		- "commentStyle": "None" or "All"
		- "indentation":  "<anything>"
		- "enableYAMLCompatibility": false or true
		- slightly change the whitespace around colons
		- "dropNullPlaceholders": false or true
		- Drop the "null" string from the writer's output for nullValues.
		Strictly speaking, this is not valid JSON. But when the output is being
		fed to a browser's Javascript, it makes for smaller output and the
		browser can handle the output just fine.
		- "useSpecialFloats": false or true
		- If true, outputs non-finite floating point values in the following way:
		NaN values as "NaN", positive infinity as "Infinity", and negative infinity
		as "-Infinity".

		You can examine 'settings_` yourself
		to see the defaults. You can also write and read them just like any
		JSON Value.
		\sa setDefaults()
		*/
		Json::Value settings_;

		StreamWriterBuilder();
		~StreamWriterBuilder() JSONCPP_OVERRIDE;

		/**
		* \throw std::exception if something goes wrong (e.g. invalid settings)
		*/
		StreamWriter* newStreamWriter() const JSONCPP_OVERRIDE;

		/** \return true if 'settings' are legal and consistent;
		*   otherwise, indicate bad settings via 'invalid'.
		*/
		bool validate(Json::Value* invalid) const;
		/** A simple way to update a specific setting.
		*/
		Value& operator[](JSONCPP_STRING key);

		/** Called by ctor, but you can use this to reset settings_.
		* \pre 'settings' != NULL (but Json::null is fine)
		* \remark Defaults:
		* \snippet src/lib_json/json_writer.cpp StreamWriterBuilderDefaults
		*/
		static void setDefaults(Json::Value* settings);
	};

	/** \brief Abstract class for writers.
	* \deprecated Use StreamWriter. (And really, this is an implementation detail.)
	*/
	class JSON_API Writer {
	public:
		virtual ~Writer();

		virtual JSONCPP_STRING write(const Value& root) = 0;
	};

	/** \brief Outputs a Value in <a HREF="http://www.json.org">JSON</a> format
	*without formatting (not human friendly).
	*
	* The JSON document is written in a single line. It is not intended for 'human'
	*consumption,
	* but may be usefull to support feature such as RPC where bandwith is limited.
	* \sa Reader, Value
	* \deprecated Use StreamWriterBuilder.
	*/
	class JSON_API FastWriter : public Writer {

	public:
		FastWriter();
		~FastWriter() JSONCPP_OVERRIDE {}

		void enableYAMLCompatibility();

		/** \brief Drop the "null" string from the writer's output for nullValues.
		* Strictly speaking, this is not valid JSON. But when the output is being
		* fed to a browser's Javascript, it makes for smaller output and the
		* browser can handle the output just fine.
		*/
		void dropNullPlaceholders();

		void omitEndingLineFeed();

	public: // overridden from Writer
		JSONCPP_STRING write(const Value& root) JSONCPP_OVERRIDE;

	private:
		void writeValue(const Value& value);

		JSONCPP_STRING document_;
		bool yamlCompatiblityEnabled_;
		bool dropNullPlaceholders_;
		bool omitEndingLineFeed_;
	};

	class JSON_API StyledWriter : public Writer {
	public:
		StyledWriter();
		~StyledWriter() JSONCPP_OVERRIDE {}

	public:
		JSONCPP_STRING write(const Value& root) JSONCPP_OVERRIDE;
	private:
		void writeValue(const Value& value);
		void writeArrayValue(const Value& value);
		bool isMultineArray(const Value& value);
		void pushValue(const JSONCPP_STRING& value);
		void writeIndent();
		void writeWithIndent(const JSONCPP_STRING& value);
		void indent();
		void unindent();
		void writeCommentBeforeValue(const Value& root);
		void writeCommentAfterValueOnSameLine(const Value& root);
		bool hasCommentForValue(const Value& value);
		static JSONCPP_STRING normalizeEOL(const JSONCPP_STRING& text);

		typedef std::vector<JSONCPP_STRING> ChildValues;

		ChildValues childValues_;
		JSONCPP_STRING document_;
		JSONCPP_STRING indentString_;
		unsigned int rightMargin_;
		unsigned int indentSize_;
		bool addChildValues_;
	};

	class JSON_API StyledStreamWriter {
	public:
		StyledStreamWriter(JSONCPP_STRING indentation = "\t");
		~StyledStreamWriter() {}
	public:
		void write(JSONCPP_OSTREAM& out, const Value& root);
	private:
		void writeValue(const Value& value);
		void writeArrayValue(const Value& value);
		bool isMultineArray(const Value& value);
		void pushValue(const JSONCPP_STRING& value);
		void writeIndent();
		void writeWithIndent(const JSONCPP_STRING& value);
		void indent();
		void unindent();
		void writeCommentBeforeValue(const Value& root);
		void writeCommentAfterValueOnSameLine(const Value& root);
		bool hasCommentForValue(const Value& value);
		static JSONCPP_STRING normalizeEOL(const JSONCPP_STRING& text);

		typedef std::vector<JSONCPP_STRING> ChildValues;
		ChildValues childValues_;
		JSONCPP_OSTREAM* document_;
		JSONCPP_STRING indentString_;
		unsigned int rightMargin_;
		JSONCPP_STRING indentation_;
		bool addChildValues_ : 1;
		bool indented_ : 1;
	};
#if defined(JSON_HAS_INT64)
	JSONCPP_STRING JSON_API valueToString(Int value);
	JSONCPP_STRING JSON_API valueToString(UInt value);
#endif // if defined(JSON_HAS_INT64)
	JSONCPP_STRING JSON_API valueToString(LargestInt value);
	JSONCPP_STRING JSON_API valueToString(LargestUInt value);
	JSONCPP_STRING JSON_API valueToString(double value);
	JSONCPP_STRING JSON_API valueToString(bool value);
	JSONCPP_STRING JSON_API valueToQuotedString(const char* value);
	JSON_API JSONCPP_OSTREAM& operator<<(JSONCPP_OSTREAM&, const Value& root);

} 

#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(pop)
#endif

#endif 

#ifndef CPPTL_JSON_ASSERTIONS_H_INCLUDED
#define CPPTL_JSON_ASSERTIONS_H_INCLUDED

#include <stdlib.h>
#include <sstream>

#if !defined(JSON_IS_AMALGAMATION)
#include "config.h"
#endif

#if JSON_USE_EXCEPTION
# define JSON_ASSERT(condition)                                                \
  {if (!(condition)) {Json::throwLogicError( "assert json failed" );}}

# define JSON_FAIL_MESSAGE(message)                                            \
  {                                                                            \
    JSONCPP_OSTRINGSTREAM oss; oss << message;                                    \
    Json::throwLogicError(oss.str());                                          \
    abort();                                                                   \
  }
#else 

# define JSON_ASSERT(condition) assert(condition)

  // The call to assert() will show the failure message in debug builds. In
  // release builds we abort, for a core-dump or debugger.
# define JSON_FAIL_MESSAGE(message)                                            \
  {                                                                            \
    JSONCPP_OSTRINGSTREAM oss; oss << message;                                    \
    assert(false && oss.str().c_str());                                        \
    abort();                                                                   \
  }


#endif

#define JSON_ASSERT_MESSAGE(condition, message)                                \
  if (!(condition)) {                                                          \
    JSON_FAIL_MESSAGE(message);                                                \
  }

#endif 
#endif 
