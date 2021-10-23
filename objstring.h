/*
MIT License

Copyright (c) 2021 ad2017

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <ctype.h>

// Alloc block size for strings. Defined in objstring.c
extern const size_t OBJSTRING_BLOCKSIZE;

// Realloc string when it is modified and less memory is required. Defined in objstring.c
extern const bool OBJSTRING_REALLOC;

typedef struct _string string;

typedef struct _stringcollection stringcollection;

typedef struct _string {
	char* string;
	size_t length;
	size_t __size__;

	// Free the string
	void (*free)();
	// Returns true if strings are equal
	bool (*equals)(string string);
	// Append a string to current string
	void (*append)(string string);
	// Append a string and return a new string
	string (*concat)(string string);
	// Get index of substring in string. -1 if not found
	long long (*indexof)(string substring);
	// Split string into multiple parts using string delimiter
	stringcollection(*split)(string delimiter);
	// Set string to another string
	void (*copy)(string string);
	// Get substring of string
	string (*substring)(size_t point1, size_t point2);
	// Prealloc memory for string. Size cannot be less or equal to this.__size__
	void (*prealloc)(size_t size);
	// Repeat string and return new string
	string (*repeat)(size_t count);
	// Convert string to uppercase
	void (*convert_upper)();
	// Convert string to lowercase
	void (*convert_lower)();
	// Convert string to uppercase and return new string
	string (*upper)();
	// Convert string to lowercase and return new string
	string (*lower)();
	// Returns true if substring is found at the start of the string.
	bool (*starts)(string sub);
	// Returns true if substring is found at the end of the string.
	bool (*ends)(string sub);

	// Append a C string to the library string
	void (*c_append)(char* string2);
	// Append a C string and return a new string
	string(*c_concat)(char* string2);
	// Split string into multiple parts using C string delimiter
	stringcollection(*c_split)(char* delimiter);
	// Get index of C substring in string. -1 if not found
	long long (*c_indexof)(char* substring);
	// Set string to another C string
	void (*c_copy)(char* string);
	// Returns true if C substring is found at the start of the string.
	bool (*c_starts)(char* sub);
	// Returns true if C substring is found at the end of the string.
	bool (*c_ends)(char* sub);

} string;

void* s_this;

string objstr(char* str);


// Auto provide "this" parameter to all struct functions.
#ifndef _MSC_VER
#define $(s) (*(typeof(s)*)(s_this = (void*)(&s)))
#elif
#define $(s) (*(string*)(s_this = (void*)(&s)))
#define $c(s) (*(stringcollection*)(s_this = (void*)(&s)))
#endif

#define inits string* _this = (string*)s_this; __stlen();