#ifndef Template_String_H
#define Template_String_H

#include <iostream>
#include <fstream>
#include <type_traits>
#include <array>

template<typename myChar, typename = typename std::enable_if
	<
	std::is_same<char, myChar>::value ||
	std::is_same<wchar_t, myChar>::value
	>
	::type
>
class MyString;

template <typename myChar>
class MyString<myChar> {
private:
	myChar* arr;
	unsigned size;
public:
	~MyString();
	MyString();
	MyString(const myChar*);
	MyString(const MyString&);
	int DeallocateArr();
	MyString& operator=(const MyString&);
	MyString& operator=(const myChar*);
	MyString& operator=(const myChar);
	MyString& operator+=(const myChar*);
	MyString& operator+=(const MyString&);
	MyString& operator+=(const myChar);

	unsigned Length() const;
	myChar* getArr() const;

	int setSize(unsigned);
	int setArr(const myChar*);


	const myChar& operator[](unsigned) const;
	myChar& operator[](unsigned);

	std::ostream& ext(std::ostream&) const;
	std::istream& ins(std::istream&);
};

template <typename myChar>
int GetLine(std::ifstream&, MyString<myChar>&);

template <typename myChar>
int GetLine(std::istream&, MyString<myChar>&);

template <typename myChar>
std::ostream& operator<<(std::ostream&, const MyString<myChar>&);

template <typename myChar>
std::istream& operator>>(std::istream&, MyString<myChar>&);


template <typename myChar>
inline MyString<myChar>::MyString() {
	this->size = 0;
}

template <typename myChar>
MyString<myChar>::~MyString() {
	this->DeallocateArr();
}

template<typename myChar>
MyString<myChar>::MyString(const MyString<myChar>& b) {
	this->size = b.size;
	this->arr = new myChar[size];
	for (unsigned i = 0; i < size; i++) {
		this->arr[i] = b.arr[i];
	}
}

template<typename myChar>
MyString<myChar>::MyString(const myChar* a) {
	unsigned i = 0;
	while (a[i] != '\0') {
		i++;
	}
	size = i;
	this->arr = new myChar[size];
	for (unsigned i = 0; i < size; i++) {
		this->arr[i] = a[i];
	}
}

template <typename myChar>
int MyString<myChar>::DeallocateArr() {
	if (this->arr != nullptr) {
		delete[] this->arr;
	}
	return 0;
}

template<typename myChar>
MyString<myChar>& MyString<myChar>::operator=(const myChar* a) {
	this->DeallocateArr();
	unsigned i = 0;
	while (a[i] != '\0') {
		i++;
	}
	this->size = i;
	this->arr = new myChar[size];
	for (unsigned j = 0; j < size; j++) {
		this->arr[j] = a[j];
	}
	return *this;
}

template <typename myChar>
MyString<myChar>& MyString<myChar>::operator=(const MyString<myChar>& b) {
	if (this != &b) {
		this->DeallocateArr();
		this->size = b.size;
		this->arr = new myChar[size];
		for (unsigned i = 0; i < size; i++) {
			this->arr[i] = b.arr[i];
		}

		return *this;
	}
}

template <typename myChar>
MyString<myChar>& MyString<myChar>::operator=(const myChar b) {
	this->size = 1;
	this->DeallocateArr();
	this->arr = new myChar[size];
	this->arr[0] = b;
	return *this;
};

template <typename myChar>
MyString<myChar>& MyString<myChar>::operator+=(const myChar* a) {
	int i = 0;
	while (a[i] != '\0') {
		i++;
	}
	int newsz = this->size + i;
	myChar* newarr = new myChar[newsz];

	for (int j = 0; j < this->size; j++) {
		newarr[j] = this->arr[j];
	}
	for (int j = 0; j < i; j++) {
		newarr[size + j] = a[j];
	}
	int j = 0;

	while (newarr[j] != '\0') {
		j++;
	}
	this->DeallocateArr();
	this->arr = newarr;
	this->size = newsz;
	return *this;
};

template <typename myChar>
MyString<myChar>& MyString<myChar>::operator+=(const MyString<myChar>& a) {
	int newsz = this->size + a.Length();
	myChar* newarr = new myChar[newsz];

	for (int i = 0; i < this->size; i++) {
		newarr[i] = this->arr[i];
	}
	for (int i = 0; i < a.Length(); i++) {
		newarr[size + i] = a[i];
	}	

	this->DeallocateArr();
	this->arr = newarr;
	this->size = newsz;
	return *this;

};

template <typename myChar>
MyString<myChar>& MyString<myChar>::operator+=(const myChar a) {
	int newsz = this->size + 1;
	myChar* newarr = new myChar[newsz];
	for (unsigned i = 0; i < this->size; i++) {
		newarr[i] = this->arr[i];
	}
	newarr[newsz - 1] = a;
	this->DeallocateArr();
	this->arr = newarr;
	this->size = newsz;
	return *this;
};

template <typename myChar>
unsigned MyString<myChar>::Length() const {
	return this->size;
}

template <typename myChar>
myChar* MyString<myChar>::getArr() const {
	return this->arr;
};

template <typename myChar>
int MyString<myChar>::setSize(unsigned sz) {
	this->size = sz;
	return 0;
}

template <typename myChar> 
int MyString<myChar>::setArr(const myChar* arr2) {
	this->DeallocateArr();
	this = arr2;
	return 0;
}

template <typename myChar>
int GetLine(std::ifstream& file, MyString<myChar>& str) {
	myChar* newarr = new myChar[1000];
	unsigned k = 0;
	do {
		file.get(newarr[k]);
		k++;
	} while (file.peek() != '\n' && !file.eof() && k < 1000); //&&newarr[k-1]!='\r')
	file.get();
	newarr[k] = '\0';
	str.setArr(newarr);
	return 0;
};

template <typename myChar>
int GetLine(std::istream& in, MyString<myChar>& str) {
	str.ins(in);
	return 0;
};

template <typename myChar>
const myChar& MyString<myChar>::operator[](unsigned i) const {
	return this->arr[i];
};

template <typename myChar>
myChar& MyString<myChar>::operator[](unsigned i) {
	return this->arr[i];
};

template <typename myChar>
std::ostream& MyString<myChar>::ext(std::ostream& out) const {
	if (this->arr!=nullptr) {
		for (unsigned i = 0; i < this->size; i++) {
			out << this->arr[i];
		}
	}
	else { out << "String is Empty."; }
	return out;
}

template <typename myChar>
std::istream& MyString<myChar>::ins(std::istream& in) {
	myChar* arr = new myChar[1000];
	in.getline(arr, 1000);
	if (in.fail()) {
		in.clear();
		in.ignore(100000, '\n');
	}
	this->size = -1;
	for (int i = 0; i < 1000; i++) {
		size++;
		if (arr[i] == '\0') {
			break;
		}
	}
	this->DeallocateArr();
	this->arr = new myChar[size];
	for (int i = 0; i < size; i++) {
		this->arr[i] = arr[i];
	}
	return in;
}

template <typename myChar>
std::ostream& operator<<(std::ostream& out, const MyString<myChar>& a) {
	return a.ext(out);
}

template <typename myChar>
std::istream& operator>>(std::istream& in, MyString<myChar>& a) {
	return a.ins(in);
}

#endif