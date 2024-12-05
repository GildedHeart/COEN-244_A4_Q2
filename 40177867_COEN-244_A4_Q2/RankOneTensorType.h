#pragma once

#include "BaseTensor.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

template<class T>
class RankOneTensorType;

template<class T>
std::ostream& operator<<(std::ostream& output, const RankOneTensorType<T>&);

template<class T>
std::istream& operator>>(std::istream& input, RankOneTensorType<T>&);


template<class T>
class RankOneTensorType :
	public BaseTensor
{
private:

	std::vector<T> data;

public:

	// Constructors and destructor

	RankOneTensorType() { data.resize(1); }
	explicit RankOneTensorType(int size) { data.resize(size); }
	RankOneTensorType(const RankOneTensorType& other) : data(other.data) {}
	
	~RankOneTensorType() override {}

	// Methods
	void setData(const std::vector<T>& newData) { data = newData; }

	virtual void loadData() override;

	void setData(std::vector<T>&);
	void push_back(T&);

	RankOneTensorType<T> operator++(); // prefix overload
	RankOneTensorType<T> operator++(int); // postfix overload
	RankOneTensorType<T> operator+(const RankOneTensorType<T>&) const;	// add a tensor's values to another's
	RankOneTensorType<T> operator+(double) const;
	RankOneTensorType<T>& operator=(const RankOneTensorType<T>&);	// assigns the values of one tensor to another if the dimensions are the same
	T& operator[](int);	// checks index and retrieves value
	const T& operator[](int) const;	// checks index and retrieves value for const

	// Friend functions

	friend std::ostream& operator<< <>(std::ostream&, const RankOneTensorType<T>&);	// outputs tensor's element values
	friend std::istream& operator>> <>(std::istream&, RankOneTensorType<T>&);	// inputs tensor's element values
};

template<>
inline void RankOneTensorType<double>::loadData(){
	std::fill(data.begin(), data.end(), valueGen());
}

template<>
inline void RankOneTensorType<std::string>::loadData() {
	std::fill(data.begin(), data.end(), std::to_string(valueGen()));
}

template<class T>
void RankOneTensorType<T>::setData(std::vector<T>& newData) {
	data = newData;
}

template<class  T>
void RankOneTensorType<T>::push_back(T& value) {
	data.push_back(value);
}

template<class T>
RankOneTensorType<T> RankOneTensorType<T>::operator++() {
	if (!(std::is_integral<T>::value) || !(std::is_floating_point<T>::value)) {
		throw std::invalid_argument("Tensor's datatype is invalid for incrementation.\n");
	}

	for (auto& element : data) {
		element += 1;
	}
	return *this;
}

template<class T>
RankOneTensorType<T> RankOneTensorType<T>::operator++(int) {
	if (!(std::is_integral<T>::value) || !(std::is_floating_point<T>::value)) {
		throw std::invalid_argument("Tensor's datatype is invalid for incrementation.\n");
	}

	RankOneTensorType<T> temp(*this);
	for (auto& element : data) {
		element += 1;
	}
	return temp;
}

template <class T>
RankOneTensorType<T> RankOneTensorType<T>::operator+(const RankOneTensorType<T>& rightSide) const {
	if (data.size() != rightSide.data.size()) {
		throw std::invalid_argument("Tensors don't have the same dimentionality.\n");
	}
	if ((typeid(data[0]) != typeid(rightSide.data[0])) && !(std::is_integral<T>::value || std::is_floating_point<T>::value)) {
		throw std::invalid_argument("Tensors' datatypes are incompatible.\n");
	}

	RankOneTensorType temp(data.size());
	for (size_t i = 0; i < data.size(); i++) {
		temp.data[i] = data[i] + rightSide.data[i];
	}
	return temp;
}

template <class T>
RankOneTensorType<T> RankOneTensorType<T>::operator+(double scalar) const {
	if (!(std::is_integral<T>::value) || !(std::is_floating_point<T>::value)) {
		RankOneTensorType temp(data.size());
		for (size_t i = 0; i < data.size(); i++) {
			temp.data[i] = data[i] + std::to_string(scalar);
		}
		return temp;
	}
	RankOneTensorType temp(data.size());
	for (size_t i = 0; i < data.size(); i++) {
		temp.data[i] = data[i] + scalar;
	}
	return temp;
}

template <class T>
RankOneTensorType<T>& RankOneTensorType<T>::operator=(const RankOneTensorType<T>& other) {
	if (this->data.size() != other.data.size()) {
		throw std::invalid_argument("Tensors don't have the same dimentionality.");
	}
	if ((typeid(data[0]) != typeid(other.data[0])) && (!(std::is_integral<T>::value) || !(std::is_floating_point<T>::value))) {
		throw std::invalid_argument("Tensors' datatypes are incompatible.\n");
	}
	if (this != &other) {
		data = other.data;
	}
	return *this;
}

template <class T>
T& RankOneTensorType<T>::operator[](int i) {	
	if (i >= data.size()) {
		throw std::out_of_range("Value is out of range.");
	}
	return data[i];
}

template <class T>
const T& RankOneTensorType<T>::operator[](int i) const {
	if ( i >= data.size()) {
		throw std::out_of_range("Value is out of range.");
	}
	return data[i];
}

template <class T>
std::ostream& operator<<(std::ostream& output, const RankOneTensorType<T>& tensor) {
	output << "Data: [";
	for (int i = 0; i <= tensor.data.size(); i++) {
		output << tensor.data[i];
		if (tensor.data.size() - 1 == i) {

			output << "]\n";
			return output;
		}
		output << ", ";
	}
}

template <class T>
std::istream& operator>>(std::istream& input, RankOneTensorType<T>& tensor) {
	for (auto& element : tensor.data) {
		input >> element;
	}
	return input;
}
