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

void _scremove(size_t idx) {
    initsc;
    
    if (idx < _this->length-1) {
        
        for(size_t i = idx; i<_this->length-1; i++)
        {
            _this->items[i] = _this->items[i + 1];
        }
        memset(&_this->items[_this->length-1], 0, sizeof(string));
    }
    else {
        memset(&_this->items[idx], 0, sizeof(string));
    }
    _this->length--;

    //_this->items = realloc(_this->items, sizeof(string)*(_this->length-1));
}
void _scinsert(string what, size_t idx) {
    initsc;
    
    string nw = objstr(0);
    $(nw).copy(what);
    _this->items = realloc(_this->items, sizeof(string)*(_this->length+1));
    if (idx < _this->length) {
        for (long long i = _this->length; i >= idx; i--){
            _this->items[i] = _this->items[i-1];
        }
        
        _this->items[idx] = nw;

    }
    else {
        _this->items[idx] = nw;
    }
    _this->length++;
}

void _scset(string what, size_t idx) {
    initsc;

    string nw = objstr(0);
    $(nw).copy(what);
    _this->items[idx] = nw;
}

void _scappend(string what){
    initsc;

    string nw = objstr(0);
    $(nw).copy(what);
    _this->items = realloc(_this->items, sizeof(string)*(_this->length+1));
    memcpy(&_this->items[_this->length++], &nw, sizeof(string));
}

void _scfree(){ 
    initsc;

    for(size_t i = 0; i<_this->length; i++){
        string cur = _this->items[i];
        $(cur).free();
    }
    free(_this->items);
    memset(_this, 0, sizeof(stringcollection));
}

void _scforeach(void (*__func)(string,size_t)){
    initsc;

    for(size_t i = 0; i<_this->length; i++){
        __func(_this->items[i], i);
    }
}

stringcollection objstrcol(string* items, size_t count){
	stringcollection sc = {0};
	sc.length = count;
	if(items != 0){
        sc.items = malloc(count * sizeof(string));
		memcpy(sc.items, items, count * sizeof(string));
	} else {
        sc.items = malloc(sizeof(string));
        memset(sc.items, 0, sizeof(string));
    }

    sc.insert = _scinsert;
    sc.remove = _scremove;
    sc.set = _scset;
    sc.append = _scappend;
    sc.foreach = _scforeach;

    sc.free = _scfree;
	return sc;
}