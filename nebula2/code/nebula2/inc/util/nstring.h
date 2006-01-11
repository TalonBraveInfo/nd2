#ifndef N_STRING_H
#define N_STRING_H
//------------------------------------------------------------------------------
/**
    @class nString
    @ingroup NebulaDataTypes

    @brief A simple Nebula string class.

    Very handy when strings must be stored or manipulated. Note that many
    Nebula interfaces hand strings around as char pointers, not nString
    objects.

    The current implementation does not allocate extra memory if the
    string has less then 13 characters.

    (C) 2001 RadonLabs GmbH
*/
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#ifdef __WIN32__
#include <malloc.h>
#else
#include <alloca.h>
#endif

#include "kernel/ntypes.h"
#include "util/narray.h"
#include "mathlib/vector.h"
#include "mathlib/matrix.h"

//------------------------------------------------------------------------------
class nString
{
public:
    /// constructor
    nString();
    /// constructor 1
    nString(const char* str);
    /// copy constructor
    nString(const nString& rhs);
    /// set to int val
    nString(int intVal);
    /// set to float val
    nString(float floatVal);
    /// set to bool value
    nString(bool boolVal);
    /// set to vector3 value
    nString(const vector3& v);
    /// set to vector4 value
    nString(const vector4& v);
	/// set to matrix44 value
	nString(const matrix44& m);
    /// destructor
    ~nString();
    /// = operator
    nString& operator=(const nString& rhs);
    /// = operator with string
    nString& operator=(const char* rhs);
    /// += operator with char*
    nString& operator+=(const char* rhs);
    /// += operator with string
    nString& operator+=(const nString& rhs);
    /// Is `a' equal to `b'?
    friend bool operator == (const nString& a, const nString& b);
    /// Is `a' inequal to `b'?
    friend bool operator != (const nString& a, const nString& b);
    /// Subscript operator (read only).
    const char operator[](int i) const;
    /// Subscript operator (writeable).
    char& operator[](int i);
    /// set as char ptr, with explicit length
    void Set(const char* ptr, int length);
    /// set as char ptr
    void Set(const char* str);
    /// set as int value
    void SetInt(int val);
    /// set as float value
    void SetFloat(float val);
    /// set as bool value
    void SetBool(bool val);
    /// set as vector3 value
    void SetVector3(const vector3& v);
    /// set as vector4 value
    void SetVector4(const vector4& v);
	/// set as matrix44 value
	void SetMatrix44(const matrix44& m);
    /// get string as char ptr
    const char* Get() const;
    /// return contents as integer
    int AsInt() const;
    /// return contents as float
    float AsFloat() const;
    /// return contents as bool
    bool AsBool() const;
    /// return contents as vector3
    vector3 AsVector3() const;
    /// return contents as vector4
    vector4 AsVector4() const;
	/// return contents as matrix44
	matrix44 AsMatrix44() const;
    /// return length of string
    int Length() const;
    /// clear the string
    void Clear();
    /// return true if string object is empty
    bool IsEmpty() const;
    /// return true if string object is not empty
    bool IsValid() const;
    /// append character pointer
    void Append(const char* str);
    /// append string
    void Append(const nString& str);
    /// append a range of characters
    void AppendRange(const char* str, uint numChars);
    /// append int value
    void AppendInt(int val);
    /// append float value
    void AppendFloat(float val);
    /// convert string to lower case
    void ToLower();
    /// convert string to upper case
    void ToUpper();
    /// get first token (this will destroy the string)
    const char* GetFirstToken(const char* whiteSpace);
    /// get next token (this will destroy the string)
    const char* GetNextToken(const char* whiteSpace);
    /// tokenize string into a provided nString array
    int Tokenize(const char* whiteSpace, nArray<nString>& tokens) const;
    /// extract substring
    nString ExtractRange(int from, int numChars) const;
    /// terminate string at first occurence of character in set
    void Strip(const char* charSet);
    /// Index of first appearance of `v' starting from index `startIndex'.
    int IndexOf(const nString& v, int startIndex) const;
    /// return index of character in string
    int FindChar(unsigned char c, int startIndex) const;
    /// terminate string at given index
    void TerminateAtIndex(int index);
    /// strip slash at end of path, if exists
    void StripTrailingSlash();
    /// delete characters from charset at left side of string
    nString TrimLeft(const char* charSet) const;
    /// delete characters from charset at right side of string
    nString TrimRight(const char* charSet) const;
    /// trim characters from charset at both sides of string
    nString Trim(const char* charSet) const;
    /// substitute every occurance of a string with another string
    nString Substitute(const char* str, const char* substStr) const;
    /// substiture every occurance of a character with another character
    void SubstituteCharacter(char c, char subst);
    /// convert string inplace from UTF-8 to 8-bit ANSI
    void UTF8toANSI();
    /// convert ANSI to UTF-8 in place
    void ANSItoUTF8();
    /// get pointer to extension (without the dot)
    const char* GetExtension() const;
    /// check if extension matches (no dot in the extension!)
    bool CheckExtension(const char* ext) const;
    /// convert backslashes to slashes
    void ConvertBackslashes();
    /// remove extension
    void StripExtension();
    /// extract the part after the last directory separator
    nString ExtractFileName() const;
    /// extract the last directory of the path
    nString ExtractLastDirName() const;
    /// extract the part before the last directory separator
    nString ExtractDirName() const;
    /// extract path until last slash
    nString ExtractToLastSlash() const;
    /// check if this string matches the given pattern
    bool MatchPattern(const nString& pattern) const;
    /// format string printf-style
    void __cdecl Format(const char* fmtString, ...)
            __attribute__((format(printf,2,3)));
    /// format string printf-style, taking a va_list
    void FormatWithArgs(const char* fmtString, va_list args);
    /// replace illegal filename characters
    void ReplaceIllegalFilenameChars(char replacement);

public:
	/// concatenate array of strings into new string
	static nString Concatenate(const nArray<nString>& strArray, const nString& whiteSpace);

protected:
    /// copy contents
    void Copy(const nString& src);
    /// delete contents
    void Delete();
    /// get pointer to last directory separator
    char* GetLastSlash() const;
    /// calculate required length for the result of a printf-style format
    size_t GetFormattedStringLength(const char* format, va_list argList) const;

    static const nString ConstantTrue;
    static const nString ConstantFalse;

    enum
    {
        LOCALSTRINGSIZE = 14,
    };
    char* string;
    union
    {
        struct
        {
            char localString[LOCALSTRINGSIZE];
            ushort localStrLen;
        };
        uint strLen;
    };
};

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString() :
    string(0),
    strLen(0),
    localStrLen(0)
{
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Delete()
{
    if (this->string)
    {
        n_free((void*) this->string);
        this->string = 0;
    }
    this->localString[0] = 0;
    this->localStrLen = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::~nString()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Set(const char* str, int length)
{
    this->Delete();
    if (str)
    {
        char* ptr = this->localString;
        if (length >= LOCALSTRINGSIZE)
        {
            ptr = (char*) n_malloc(length + 1);
            this->string = ptr;
            this->strLen = length;
        }
        else
        {
            ptr = this->localString;
            this->localStrLen = (ushort)length;
        }
        memcpy(ptr, str, length);
        ptr[length] = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Set(const char* str)
{
    int len = 0;
    if (str)
    {
        len = strlen(str);
    }
    this->Set(str, len);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetInt(int val)
{
    this->Format("%d", val);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetFloat(float val)
{
    this->Format("%.6f", val);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetBool(bool val)
{
    if (val)
    {
        *this = ConstantTrue;
    }
    else
    {
        *this = ConstantFalse;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetVector3(const vector3& v)
{
    this->Format("%.6f,%.6f,%.6f", v.x, v.y, v.z);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetVector4(const vector4& v)
{
    this->Format("%.6f,%.6f,%.6f,%.6f", v.x, v.y, v.z, v.w);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::SetMatrix44(const matrix44& m)
{
	this->Format("%.6f, %.6f, %.6f, %.6f, "
		"%.6f, %.6f, %.6f, %.6f, "
		"%.6f, %.6f, %.6f, %.6f, "
		"%.6f, %.6f, %.6f, %.6f",
		m.M11, m.M12, m.M13, m.M14,
		m.M21, m.M22, m.M23, m.M24,
		m.M31, m.M32, m.M33, m.M34,
		m.M41, m.M42, m.M43, m.M44);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Copy(const nString& src)
{
    n_assert(0 == this->string);
    const char* str = src.Get();
    if (str)
    {
        this->Set(str);
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(const char* str) :
    string(0),
    strLen(0),
    localStrLen(0)
{
    this->Set(str);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(const nString& rhs) :
    string(0),
    strLen(0),
    localStrLen(0)
{
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(int intVal) :
    string(0),
    strLen(0),
    localStrLen(0)
{
    this->SetInt(intVal);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(float floatVal) :
    string(0),
    strLen(0),
    localStrLen(0)
{
    this->SetFloat(floatVal);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(bool boolVal) :
    string(0),
    strLen(0)
{
    this->SetBool(boolVal);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(const vector3& v) :
    string(0),
    strLen(0)
{
    this->SetVector3(v);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString::nString(const vector4& v) :
    string(0),
    strLen(0)
{
    this->SetVector4(v);
}

//------------------------------------------------------------------------------
/**
*/
inline
	nString::nString(const matrix44& m) :
	string(0),
	strLen(0)
{
	this->SetMatrix44(m);
}

//------------------------------------------------------------------------------
/**
*/
inline
const char*
nString::Get() const
{
    if (this->string)
    {
        return this->string;
    }
    else if (this->localString[0])
    {
        return this->localString;
    }
    else
    {
        return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
nString&
nString::operator=(const nString& rhs)
{
    if (&rhs != this)
    {
        this->Delete();
        this->Copy(rhs);
    }
    return *this;
}

//------------------------------------------------------------------------------
/**
*/
inline
nString&
nString::operator=(const char* rhs)
{
    this->Set(rhs);
    return *this;
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::AppendRange(const char* str, uint numChars)
{
    n_assert(str);
    if (numChars > 0)
    {
        uint rlen = numChars;
        uint tlen = this->Length() + rlen;
        if (this->string)
        {
            char* ptr = (char*) n_malloc(tlen + 1);
            strcpy(ptr, this->string);
            strncat(ptr, str, numChars);
            n_free((void*) this->string);
            this->string = ptr;
            this->strLen = tlen;
        }
        else if (this->localString[0])
        {
            if (tlen >= LOCALSTRINGSIZE)
            {
                char* ptr = (char*) n_malloc(tlen + 1);
                strcpy(ptr, this->localString);
                strncat(ptr, str, numChars);
                this->localString[0] = 0;
                this->string = ptr;
                this->strLen = tlen;
            }
            else
            {
                strncat(this->localString, str, numChars);
                this->localStrLen = (ushort)tlen;
            }
        }
        else
        {
            this->Set(str, numChars);
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Append(const char* str)
{
    n_assert(str);
    uint rlen = strlen(str);
    this->AppendRange(str, rlen);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Append(const nString& str)
{
    this->Append(str.Get());
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::AppendInt(int val)
{
    nString str;
    str.SetInt(val);
    this->Append(str);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::AppendFloat(float val)
{
    nString str;
    str.SetFloat(val);
    this->Append(str);
}

//------------------------------------------------------------------------------
/**
*/
inline
nString&
nString::operator+=(const char* rhs)
{
    this->Append(rhs);
    return *this;
}

//------------------------------------------------------------------------------
/**
*/
inline
nString&
nString::operator+=(const nString& rhs)
{
    this->Append(rhs.Get());
    return *this;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
operator == (const nString& a, const nString& b)
{
    return strcmp(a.Get(), b.Get()) == 0;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
operator != (const nString& a, const nString& b)
{
    return strcmp(a.Get(), b.Get()) != 0;
}

//------------------------------------------------------------------------------
/**
     - 21-Sep-04    Johannes        the '\\0' is a valid part of the string
*/
inline
const char
nString::operator[](int i) const
{
    n_assert((0 <= i) && (i <= this->Length()));
    if (this->string != 0)
    {
        return this->string[i];
    }
    else
    {
        return this->localString[i];
    }
}

//------------------------------------------------------------------------------
/**
     - 21-Sep-04    Johannes        the '\\0' is a valid part of the string
*/
inline
char&
nString::operator[](int i)
{
    n_assert((0 <= i) && (i <= this->Length()));
    if (this->string != 0)
    {
        return this->string[i];
    }
    else
    {
        return this->localString[i];
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
int
nString::Length() const
{
    if (this->string != 0)
    {
        return this->strLen;
    }
    else
    {
        return this->localStrLen;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::Clear()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
nString::IsEmpty() const
{
    if (this->string && (this->string[0] != 0))
    {
        return false;
    }
    else if (this->localString[0] != 0)
    {
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
nString::IsValid() const
{
    return !this->IsEmpty();
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::ToLower()
{
    char* str = (char*) (this->string ? this->string : this->localString);
    if (str)
    {
        char c;
        char* ptr = (char*) str;
        while ((c = *ptr))
        {
            *ptr++ = tolower(c);
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::ToUpper()
{
    char* str = (char*) (this->string ? this->string : this->localString);
    if (str)
    {
        char c;
        char* ptr = (char*) str;
        while ((c = *ptr))
        {
            *ptr++ = toupper(c);
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
static
inline
nString
operator+(const nString& s0, const nString& s1)
{
    nString newString = s0;
    newString.Append(s1.Get());
    return newString;
}

//------------------------------------------------------------------------------
/**
    Get the first token in the string, delimited by one or more of the
    character in 'whiteSpace'. This simply invokes the strtok() function
    internally, and will destroy the contained string. After calling
    GetFirstToken(), invoke GetNextToken() until 0 returns.

    ATTENTION: if somebody else calls strtok() while GetFirstToken()/
    GetNextToken() is underway, everything will break apart!
    Check out the Tokenize() method for a better alternative.

    @param  whiteSpace  string containing white space characters
*/
inline
const char*
nString::GetFirstToken(const char* whiteSpace)
{
    n_assert(whiteSpace);
    return strtok((char*) this->Get(), whiteSpace);
}

//------------------------------------------------------------------------------
/**
    Get the next token in the string. Call this after a GetFirstToken()
    or GetNextToken(). Returns 0 if no more tokens in string. This method
    will destroy the original string.

    ATTENTION: if somebody else calls strtok() while GetFirstToken()/
    GetNextToken() is underway, everything will break apart!
    Check out the Tokenize() method for a better alternative.

    @param  whiteSpace  string containing whitespace characters
*/
inline
const char*
nString::GetNextToken(const char* whiteSpace)
{
    n_assert(whiteSpace);
    return strtok(0, whiteSpace);
}

//------------------------------------------------------------------------------
/**
    Tokenize the string into a provided nString array. Returns the number
    of tokens. This method is recommended over GetFirstToken()/GetNextToken(),
    since it is atomic. This nString object will not be destroyed
    (as is the case with GetFirstToken()/GetNextToken().

    @param  whiteSpace      [in] a string containing the whitespace characters
    @param  tokens          [out] nArray<nString> where tokens will be appended
    @return                 number of tokens found
*/
inline
int
nString::Tokenize(const char* whiteSpace, nArray<nString>& tokens) const
{
    int numTokens = 0;

    // create a temporary string, which will be destroyed during the operation
    nString str(*this);
    char* ptr = (char*) str.Get();
    const char* token;
    while (0 != (token = strtok(ptr, whiteSpace)))
    {
        tokens.Append(nString(token));
        ptr = 0;
        numTokens++;
    }
    return numTokens;
}

//------------------------------------------------------------------------------
/**
    Extract sub string.
*/
inline
nString
nString::ExtractRange(int from, int numChars) const
{
    n_assert(from <= this->Length());
    n_assert((from + numChars) <= this->Length());
    const char* str = this->Get();
    nString newString;
    newString.Set(&(str[from]), numChars);
    return newString;
}

//------------------------------------------------------------------------------
/**
    Terminates the string at the first occurance of one of the characters
    in charSet.
*/
inline
void
nString::Strip(const char* charSet)
{
    n_assert(charSet);
    char* str = (char*) this->Get();
    char* ptr = strpbrk(str, charSet);
    if (ptr)
    {
        *ptr = 0;
        if (this->string != 0)
        {
            this->strLen = strlen(str);
        }
        else
        {
            this->localStrLen = strlen(str);
        }
    }
}

//------------------------------------------------------------------------------
/**
    @result Index or -1 if not found.
*/
inline
int
nString::IndexOf(const nString& v, int startIndex) const
{
    n_assert(0 <= startIndex && startIndex <= Length() - 1);
    n_assert(!v.IsEmpty());

    for (int i = startIndex; i < Length(); i++)
    {
        if (Length() - i < v.Length())
        {
            break;
        }

        if (strncmp(&(Get()[i]), v.Get(), v.Length()) == 0)
        {
            return i;
        }
    }

    return -1;
}

//------------------------------------------------------------------------------
/**
    Return index of character in string, or -1 if not found.
*/
inline
int
nString::FindChar(unsigned char c, int startIndex) const
{
    if (this->Length() > 0)
    {
        n_assert(startIndex < this->Length());
        const char* ptr = strchr(this->Get() + startIndex, c);
        if (ptr)
        {
            return ptr - this->Get();
        }
    }
    return -1;
}

//------------------------------------------------------------------------------
/**
    Terminates the string at the given index.
*/
inline
void
nString::TerminateAtIndex(int index)
{
    n_assert(index < this->Length());
    char* ptr = (char*) this->Get();
    ptr[index] = 0;
    if (this->string != 0)
    {
        this->strLen = index;
    }
    else
    {
        this->localStrLen = index;
    }
}

//------------------------------------------------------------------------------
/**
    Strips last slash, if the path name ends on a slash.
*/
inline
void
nString::StripTrailingSlash()
{
    if (this->Length() > 0)
    {
        int pos = Length() - 1;
        char* str = (char*) this->Get();
        if ((str[pos] == '/') || (str[pos] == '\\'))
        {
            str[pos] = 0;
            if (this->string != 0)
            {
                this->strLen--;
            }
            else
            {
                this->localStrLen--;
            }
        }
    }
}

//------------------------------------------------------------------------------
/**
    Returns a new string which is this string, stripped on the left side
    by all characters in the char set.
*/
inline
nString
nString::TrimLeft(const char* charSet) const
{
    n_assert(charSet);
    if (this->IsEmpty())
    {
        return *this;
    }

    int charSetLen = strlen(charSet);
    int thisIndex = 0;
    bool stopped = false;
    while (!stopped && (thisIndex < this->Length()))
    {
        int charSetIndex;
        bool match = false;
        for (charSetIndex = 0; charSetIndex < charSetLen; charSetIndex++)
        {
            if ((*this)[thisIndex] == charSet[charSetIndex])
            {
                // a match
                match = true;
                break;
            }
        }
        if (!match)
        {
            // stop if no match
            stopped = true;
        }
        else
        {
            // a match, advance to next character
            ++thisIndex;
        }
    }
    nString trimmedString(&(this->Get()[thisIndex]));
    return trimmedString;
}

//------------------------------------------------------------------------------
/**
    Returns a new string, which is this string, stripped on the right side
    by all characters in the char set.
*/
inline
nString
nString::TrimRight(const char* charSet) const
{
    n_assert(charSet);
    if (this->IsEmpty())
    {
        return *this;
    }

    int charSetLen = strlen(charSet);
    int thisIndex = this->Length() - 1;
    bool stopped = false;
    while (!stopped && (thisIndex < this->Length()))
    {
        int charSetIndex;
        bool match = false;
        for (charSetIndex = 0; charSetIndex < charSetLen; charSetIndex++)
        {
            if ((*this)[thisIndex] == charSet[charSetIndex])
            {
                // a match
                match = true;
                break;
            }
        }
        if (!match)
        {
            // stop if no match
            stopped = true;
        }
        else
        {
            // a match, advance to next character
            --thisIndex;
        }
    }
    nString trimmedString;
    trimmedString.Set(this->Get(), thisIndex + 1);
    return trimmedString;
}

//------------------------------------------------------------------------------
/**
    Trim both sides of a string.
*/
inline
nString
nString::Trim(const char* charSet) const
{
    return this->TrimLeft(charSet).TrimRight(charSet);
}

//------------------------------------------------------------------------------
/**
    Substitute every occurance of origStr with substStr.
*/
inline
nString
nString::Substitute(const char* matchStr, const char* substStr) const
{
    n_assert(matchStr && substStr);

    const char* ptr = this->Get();
    int matchStrLen = strlen(matchStr);
    nString dest;

    // walk original string for occurances of str
    const char* occur;
    while ((occur = strstr(ptr, matchStr)))
    {
        // append string fragment until match
        dest.AppendRange(ptr, occur - ptr);

        // append replacement string
        dest.Append(substStr);

        // adjust source pointer
        ptr = occur + matchStrLen;
    }
    dest.Append(ptr);
    return dest;
}

//------------------------------------------------------------------------------
/**
    Returns content as integer.
*/
inline
int
nString::AsInt() const
{
    const char* ptr = this->Get();
    return atoi(ptr);
}

//------------------------------------------------------------------------------
/**
    Returns content as float.
*/
inline
float
nString::AsFloat() const
{
    const char* ptr = this->Get();
    return float(atof(ptr));
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
nString::AsBool() const
{
    if (*this == ConstantTrue)
    {
        return true;
    }
    if (*this == ConstantFalse)
    {
        return false;
    }
    n_assert(false);  // String does not contain a bool!
    return false;
}

//------------------------------------------------------------------------------
/**
*/
inline
vector3
nString::AsVector3() const
{
    nArray<nString> tokens;
    this->Tokenize(", \t", tokens);
    n_assert(tokens.Size() == 3);
    vector3 v(tokens[0].AsFloat(), tokens[1].AsFloat(), tokens[2].AsFloat());
    return v;
}

//------------------------------------------------------------------------------
/**
*/
inline
vector4
nString::AsVector4() const
{
    nArray<nString> tokens;
    this->Tokenize(", \t", tokens);
    n_assert(tokens.Size() == 4);
    vector4 v(tokens[0].AsFloat(), tokens[1].AsFloat(), tokens[2].AsFloat(), tokens[3].AsFloat());
    return v;
}

//------------------------------------------------------------------------------
/**
	Returns content as matrix44. Note: this method doesn't check whether the
	contents is actually a valid matrix44. Use the IsValidMatrix44() method
	for this!
*/
inline
matrix44
nString::AsMatrix44() const
{
	nArray<nString> tokens;
	this->Tokenize(", \t", tokens);
	n_assert(tokens.Size() == 16);
	matrix44 m(tokens[0].AsFloat(),  tokens[1].AsFloat(),  tokens[2].AsFloat(),  tokens[3].AsFloat(),
		tokens[4].AsFloat(),  tokens[5].AsFloat(),  tokens[6].AsFloat(),  tokens[7].AsFloat(),
		tokens[8].AsFloat(),  tokens[9].AsFloat(),  tokens[10].AsFloat(), tokens[11].AsFloat(),
		tokens[12].AsFloat(), tokens[13].AsFloat(), tokens[14].AsFloat(), tokens[15].AsFloat());
	return m;
}

//------------------------------------------------------------------------------
/**
    This converts an UTF-8 string to 8-bit-ANSI. Note that only characters
    in the range 0 .. 255 are converted, all other characters will be converted
    to a question mark.

    For conversion rules see http://www.cl.cam.ac.uk/~mgk25/unicode.html#utf-8
*/
inline
void
nString::UTF8toANSI()
{
    uchar* src = (uchar*) this->Get();
    uchar* dst = src;
    uchar c;
    while ((c = *src++))
    {
        if (c >= 0x80)
        {
            if ((c & 0xE0) == 0xC0)
            {
                // a 2 byte sequence with 11 bits of information
                ushort wide = ((c & 0x1F) << 6) | (*src++ & 0x3F);
                if (wide > 0xff)
                {
                    c = '?';
                }
                else
                {
                    c = (uchar) wide;
                }
            }
            else if ((c & 0xF0) == 0xE0)
            {
                // a 3 byte sequence with 16 bits of information
                c = '?';
                src += 2;
            }
            else if ((c & 0xF8) == 0xF0)
            {
                // a 4 byte sequence with 21 bits of information
                c = '?';
                src += 3;
            }
            else if ((c & 0xFC) == 0xF8)
            {
                // a 5 byte sequence with 26 bits of information
                c = '?';
                src += 4;
            }
            else if ((c & 0xFE) == 0xFC)
            {
                // a 6 byte sequence with 31 bits of information
                c = '?';
                src += 5;
            }
        }
        *dst++ = c;
    }
    *dst = 0;
}
//------------------------------------------------------------------------------
/**
    Convert contained ANSI string to UTF-8 in place.
*/
inline
void
nString::ANSItoUTF8()
{
    n_assert(!this->IsEmpty());
    int bufSize = this->Length() * 2 + 1;
    char* buffer = n_new_array(char, bufSize);
    char* dstPtr = buffer;
    const char* srcPtr = this->Get();
    unsigned char c;
    while ((c = *srcPtr++))
    {
        // note: this only covers the 2 cases that the character
        // is between 0 and 127 and between 128 and 255
        if (c < 128)
        {
            *dstPtr++ = c;
        }
        else
        {
            *dstPtr++ = 192 + (c / 64);
            *dstPtr++ = 128 + (c % 64);
        }
    }
    *dstPtr = 0;
    this->Set(buffer);
    n_delete_array(buffer);
}

//------------------------------------------------------------------------------
/**
    Replace character with another.
*/
inline
void
nString::SubstituteCharacter(char c, char subst)
{
    char* ptr = (char*) this->Get();
    int i;
    for (i = 0; i <= this->Length(); i++)
    {
        if (ptr[i] == c)
        {
            ptr[i] = subst;
        }
    }
}

//------------------------------------------------------------------------------
/**
    Converts backslashes to slashes.
*/
inline
void
nString::ConvertBackslashes()
{
    this->SubstituteCharacter('\\', '/');
}

//------------------------------------------------------------------------------
/**
    @return     pointer to extension (without the dot), or 0
*/
inline
const char*
nString::GetExtension() const
{
    const char* str = this->Get();
    const char* ext = strrchr(str, '.');
    if (ext)
    {
        ext++;
        if (ext[0] != 0)
        {
            return ext;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
/**
    Returns true if file extension matches.

    @param  ext     extension string (without the dot)
    @return         true if extension matches
*/
inline
bool
nString::CheckExtension(const char* ext) const
{
    n_assert(ext);
    const char* extStr = this->GetExtension();
    if (0 == extStr)
    {
        return false;
    }
    return (0 == (strcmp(ext, extStr)));
}

//------------------------------------------------------------------------------
/**
    Remove the file extension.
*/
inline
void
nString::StripExtension()
{
    char* ext = (char*) this->GetExtension();
    if (ext)
    {
        ext[-1] = 0;
    }
    if (this->string != 0)
    {
        this->strLen = strlen(this->Get());
    }
    else
    {
        this->localStrLen = strlen(this->Get());
    }
}

//------------------------------------------------------------------------------
/**
    Get a pointer to the last directory separator.
*/
inline
char*
nString::GetLastSlash() const
{
    char* s = (char*) this->Get();
    char* lastSlash = strrchr(s, '/');
    if (0 == lastSlash) lastSlash = strrchr(s, '\\');
    if (0 == lastSlash) lastSlash = strrchr(s, ':');
    return lastSlash;
}

//------------------------------------------------------------------------------
/**
    Return a nString object containing the part after the last
    path separator.
*/
inline
nString
nString::ExtractFileName() const
{
    nString pathString;
    char* lastSlash = this->GetLastSlash();
    if (lastSlash)
    {
        pathString = &(lastSlash[1]);
    }
    else
    {
        pathString = this->Get();
    }
    return pathString;
}

//------------------------------------------------------------------------------
/**
    Return a nString object containing the last directory of the path, i.e.
    a category.

    - 17-Feb-04     floh    fixed a bug when the path ended with a slash
*/
inline
nString
nString::ExtractLastDirName() const
{
    nString pathString(*this);
    char* lastSlash = pathString.GetLastSlash();

    // special case if path ends with a slash
    if (lastSlash)
    {
        if (0 == lastSlash[1])
        {
            *lastSlash = 0;
            lastSlash = pathString.GetLastSlash();
        }

        char* secLastSlash = 0;
        if (0 != lastSlash)
        {
            *lastSlash = 0; // cut filename
            secLastSlash = pathString.GetLastSlash();
            if (secLastSlash)
            {
                *secLastSlash = 0;
                return nString(secLastSlash+1);
            }
        }
    }
    return "";
}

//------------------------------------------------------------------------------
/**
    Return a nString object containing the part before the last
    directory separator.

    NOTE: I left my fix in that returns the last slash (or colon), this was
    necessary to tell if a dirname is a normal directory or an assign.

    - 17-Feb-04     floh    fixed a bug when the path ended with a slash
*/
inline
nString
nString::ExtractDirName() const
{
    nString pathString(*this);
    char* lastSlash = pathString.GetLastSlash();

    // special case if path ends with a slash
    if (lastSlash)
    {
        if (0 == lastSlash[1])
        {
            *lastSlash = 0;
            lastSlash = pathString.GetLastSlash();
        }
        if (lastSlash)
        {
            *++lastSlash = 0;
        }
    }
    return pathString;
}

//------------------------------------------------------------------------------
/**
    Return a path string object which contains of the complete path
    up to the last slash. Returns an empty string if there is no
    slash in the path.
*/
inline
nString
nString::ExtractToLastSlash() const
{
    nString pathString(*this);
    char* lastSlash = pathString.GetLastSlash();
    if (lastSlash)
    {
        lastSlash[1] = 0;
    }
    else
    {
        pathString = "";
    }
    return pathString;
}

//------------------------------------------------------------------------------
/**
*/
inline
bool
nString::MatchPattern(const nString& pattern) const
{
    return n_strmatch(this->Get(), pattern.Get());
}

//------------------------------------------------------------------------------
/**
*/
inline
void __cdecl
nString::Format(const char* fmtString, ...)
{
    va_list argList;
    va_start(argList, fmtString);
    this->FormatWithArgs(fmtString, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::FormatWithArgs(const char* fmtString, va_list args)
{
    va_list argList;

    // First calculate the required length
    va_copy(argList, args);
    size_t requiredLength;
#if defined(__WIN32__) && defined(_MSC_VER)
    #if _MSC_VER < 1300
        // VC6
        requiredLength = this->GetFormattedStringLength(fmtString, argList);
    #else
        // VC7 and later
        requiredLength = _vscprintf(fmtString, argList);
    #endif
#else
    // This is the C99 behavior and works on glibc 2.1 and later on Linux
    // as well as the libc on OS X.
    char sizerBuf[2];
    requiredLength = vsnprintf(sizerBuf, 1, fmtString, argList);
#endif
    requiredLength++; // Account for NULL termination
    va_end(argList);

    // Now we can allocate a buffer of the right length
    char* buf = (char*)alloca(requiredLength);

    // Now do the formatting
    vsnprintf(buf, requiredLength, fmtString, args);
    this->Set(buf);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
nString::ReplaceIllegalFilenameChars(char replacement)
{
    char* ptr = (char*) this->Get();
    char c;
    while (0 != (c = *ptr))
    {
        if ((c == '\\') ||
            (c == '/') ||
            (c == ':') ||
            (c == '*') ||
            (c == '?') ||
            (c == '\"') ||
            (c == '<') ||
            (c == '>') ||
            (c == '|'))
        {
            *ptr = replacement;
        }
        ptr++;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
nString
nString::Concatenate(const nArray<nString>& strArray, const nString& whiteSpace)
{
	nString res;
	int i;
	int num = strArray.Size();
	for (i = 0; i < num; i++)
	{
		res.Append(strArray[i]);
		if ((i + 1) < num)
		{
			res.Append(whiteSpace);
		}
	}
	return res;
}

//-----------------------------------------------------------------------------
#endif

