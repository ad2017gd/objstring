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

#include "objstring.h"

typedef struct _stringcollection {
    string* items;
	size_t length;

	// Free the string collection
	void (*free)();
	// Set string at index
	void (*set)(string string, size_t index);
	// Remove string at index
	void (*remove)(size_t index);
	// Insert string at index
	void (*insert)(string string, size_t index);
    // Append string
    void (*append)(string string);
	// Call passed function with string and index arguments
	void (*foreach)(void (*function)(string string, size_t index));
} stringcollection;


stringcollection objstrcol(string* items, size_t count);

#define initsc stringcollection* _this = (stringcollection*)s_this
