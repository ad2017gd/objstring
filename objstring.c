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

#include "objstring.h"
#include "objstringcollection.h"

const size_t OBJSTRING_BLOCKSIZE = 8;
const bool OBJSTRING_REALLOC = true;

void __stlen(){
	string* _this = (string*)s_this;

	_this->length = strlen(_this->string);
}
bool _streq(string str) {
	inits;

	return !strcmp(_this->string, str.string);
}
void _stcappend(char* str) {
	inits;

	size_t len = _this->length + strlen(str);
	if (len >= _this->__size__ - 1) {
		_this->__size__ = (((size_t)(len/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1;
		_this->string = realloc(_this->string, _this->__size__);
	}
	_this->length = len;
	strcat(_this->string, str);
}
void _stappend(string str) {
	_stcappend(str.string);
}
string _stcconcat(char* s1) {
	inits;

	string nw = objstr("");
	$(nw).c_append(_this->string);
	$(nw).c_append(s1);
	return nw;
}
string _stconcat(string s1) {
	return _stcconcat(s1.string);
}
void _stccopy(char* s1) {
	inits;

	size_t len = strlen(s1);
	if (len >= _this->__size__ - 1) {
		_this->__size__ = (((size_t)(len/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1;
		_this->string = realloc(_this->string, _this->__size__);
	}
	if(OBJSTRING_REALLOC && ((((size_t)(len/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1) < _this->__size__ - 1) {
		_this->__size__ = (((size_t)(len/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1;
		_this->string = realloc(_this->string, _this->__size__);
	}
	_this->length = len;
	strcpy(_this->string, s1);
}
void _stcopy(string s1) {
	inits;

	(*_this).c_copy(s1.string);
}
long long _stcindexof(char* s){
	inits;
	long long index = 0;
	index = (uintptr_t)strstr(_this->string,s);
	if(index == 0) return -1;
	index = index - (size_t)(_this->string);

	return index;
}
long long _stindexof(string s){
	return _stcindexof(s.string);
}
string _stsubstring(size_t point1, size_t point2){
	inits;

	string nw = objstr(0);
	char* temp = malloc((point2-point1+1) * sizeof(char));
	memcpy(temp, _this->string+point1, point2-point1);
	temp[point2-point1] = 0;
	$(nw).c_copy(temp);
	free(temp);
	nw.length = point2-point1;

	return nw;
}
stringcollection _stcsplit(char* delimiter){
	inits;
	long long index;
	size_t length = strlen(delimiter);

	stringcollection sc = objstrcol(0,0);
	string temp = objstr(0);
	$(temp).copy((*_this));
	while((index = $(temp).c_indexof(delimiter)) != -1){
		string sub = $(temp).substring(0, index);
		string nw = $(temp).substring(index+length, temp.length);
		$(temp).copy(nw);
		$(sc).append(sub);
	}
	$(sc).append(temp);

	return sc;
}
stringcollection _stsplit(string delimiter){
	return _stcsplit(delimiter.string);
}
void _stprealloc(size_t size){
	inits;

	if(size > _this->__size__){
		_this->string = realloc(_this->string, size);
		_this->__size__ = size;
	}
}
string _strepeat(size_t count){
	inits;

	size_t len = strlen(_this->string) * count;
	_this->__size__ = (((size_t)(len/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1;
	_this->string = realloc(_this->string, _this->__size__);

	string temp = objstr(0);
	string repeat = objstr(0);
	$(temp).copy((*_this));

	for(size_t i = 0; i<count; i++){
		$(repeat).append(temp);
	}
	$(temp).free();

	return repeat;
}
void _stfree() {
	inits;

	free(_this->string);
	memset(_this, 0, sizeof(string));
}
void _stconvert_upper() {
	inits;

	for(size_t i = 0; i<_this->length; i++){
		if(isalpha(_this->string[i])) {
			_this->string[i] = toupper(_this->string[i]);
		}
	}
}
void _stconvert_lower() {
	inits;

	for(size_t i = 0; i<_this->length; i++){
		if(isalpha(_this->string[i])) {
			_this->string[i] = tolower(_this->string[i]);
		}
	}
}
string _stupper() {
	inits;

	string temp = objstr(0);
	$(temp).copy((*_this));
	for(size_t i = 0; i<temp.length; i++){
		if(isalpha(temp.string[i])) {
			temp.string[i] = toupper(temp.string[i]);
		}
	}

	return temp;
}
string _stlower() {
	inits;

	string temp = objstr(0);
	$(temp).copy((*_this));
	for(size_t i = 0; i<temp.length; i++){
		if(isalpha(temp.string[i])) {
			temp.string[i] = tolower(temp.string[i]);
		}
	}

	return temp;
}

bool _stcstartswith(char* sub){
	inits;

	size_t len = strlen(sub);
	if(len > _this->length) return false;
	return !strncmp(_this->string, sub, len);
}
bool _stcendswith(char* sub){
	inits;

	size_t len = strlen(sub);
	if(len > _this->length) return false;
	return !strncmp(_this->string+(_this->length-len), sub, len);
}

string objstr(char* str) {
	string st = { 0 };
	st.__size__ = 0;
	if(str != 0) {
		st.length = strlen(str);
		st.__size__ = (((size_t)(st.length/OBJSTRING_BLOCKSIZE))+1)*OBJSTRING_BLOCKSIZE + 1;
		st.string = malloc(st.length * sizeof(char) + 1);
		strcpy(st.string, str);
	} else {
		st.length = 0;
		st.__size__ = OBJSTRING_BLOCKSIZE + 1;
		st.string = malloc(OBJSTRING_BLOCKSIZE);
		st.string[0] = 0;
	}
	

	st.equals = _streq;
	st.append = _stappend;
	st.concat = _stconcat;
	st.indexof = _stindexof;
	st.copy = _stcopy;
	st.substring = _stsubstring;
	st.split = _stsplit;
	st.prealloc = _stprealloc;
	st.repeat = _strepeat;
	st.convert_lower = _stconvert_lower;
	st.convert_upper = _stconvert_upper;
	st.upper = _stupper;
	st.lower = _stlower;

	st.c_append = _stcappend;
	st.c_concat = _stcconcat;
	st.c_indexof = _stcindexof;
	st.c_copy = _stccopy;
	st.c_split = _stcsplit;
	st.c_starts = _stcstartswith;
	st.c_ends = _stcendswith;

	st.free = _stfree;

	return st;
}

