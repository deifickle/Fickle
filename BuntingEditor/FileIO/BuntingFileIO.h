#ifndef BUNTING_FILE_IO_H
#define BUNTING_FILE_IO_H

#include "../BuntingObject.h"

template <typename T>
concept is_iterable = requires(T v) {
	{ v.has_next() } -> std::convertible_to<bool>;
	{ v.next() } -> std::same_as<uint32_t>;
	{ v.reset() };
};

template <is_iterable T> size_t count(T& t) {
	t.reset();
	size_t count = 0;
	while (t.has_next()) {
		t.next();
		count++;
	}
	return count;
}

template <typename T>
concept is_listable = requires(T v) {
	{ v.has_next() } -> std::same_as<bool>;
	{ v.has_previous() } -> std::same_as<bool>;

	{ v.next(std::integral<int>) } -> std::derived_from<BuntingObject>;
	{ v.previous(std::integral<int>) } -> std::derived_from<BuntingObject>;

	{ v.insert_after(std::integral<int>, std::derived_from<T, BuntingObject>) } -> std::same_as <bool>;
	{ v.insert_before(std::integral<int>, std::derived_from<T, BuntingObject>) } -> std::same_as<bool>;
	{ v.remove(std::integral<int>) } -> std::same_as<bool>;

	{ v.empty() } -> std::same_as<bool>;
};

template <typename T>
struct Stack {
	int size = 0;
	int top = -1;

	T* stack;
	
	int init() {
		stack = (T*)malloc(size * sizeof(T*));
		if (stack) {
			top = 0;
			return 0; //success
		}
		return -1; // failure/error
	}

	int quash() {
		if (stack) {
			delete stack;
			top = -1;
			return 0;//success
		}
		return -1;//failure. trying to quash a quashed item!
	}

	int push(T* t) {
		if (top == size) {
			return -1;//stack full
		}
		stack[top] = t;
		top++;
		return 0;
	}
	T* pop() {
		if (top == 0) {
			return -1;//stack empty
		}
		top--;
		return stack[top];
	}
};

int bunOpenFile(const char* path, const char* filename, BuntingFile::KOpenMode mode);
BuntingFile* bunGetFile(int index);
#endif // !BUNTING_FILE_IO_H
