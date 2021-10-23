# objstring
Object Oriented C String Library

- [Basic usage](#basic-usage)
- [Example](#example)
- [Structs](#structs)

# Basic usage
To create an objstring, use `objstr(char*)`. To create a string collection, use `objstrcol(string*,size_t)`.

To access functions of a string, use `$(string).function(args)`. If your compiler doesn't support `typeof`, you have to use `$c(stringcollection)` separately for string collections.

Use `$(string).free()` to free and zero the string. The same applies to `stringcollection`s, which exist just for easy freeing of all strings contained in it.

# Example
An example is provided in the `test.c` file.

# Structs
```c
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
```

```c
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
```
