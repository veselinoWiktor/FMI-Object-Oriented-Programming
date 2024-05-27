#pragma once
#include <iostream>

template<typename T, typename S>
class Pair
{
private:
	T first;
	S second;
public:
	Pair(const T& first, const S& second);
	Pair(T&& first, S&& second);

	const T& getFirst() const;
	const S& getSecond() const;

	void setFirst(const T& newFirst);
	void setFirst(T&& newFirst);
	void setSecond(const S& newSecond);
	void setSecond(S&& newSecond);
};

template<typename T, typename S>
Pair<T, S>::Pair(const T& first, const S& second) : first(first), second(second)
{
}

template<typename T, typename S>
Pair<T, S>::Pair(T&& first, S&& second) : first(std::move(first)), second(std::move(second))
{
}

template<typename T, typename S>
inline const T& Pair<T, S>::getFirst() const
{
	return first;
}

template<typename T, typename S>
inline const S& Pair<T, S>::getSecond() const
{
	return second;
}

template<typename T, typename S>
void Pair<T, S>::setFirst(const T& newFirst)
{
	first = newFirst;
}

template<typename T, typename S>
void Pair<T, S>::setFirst(T&& newFirst)
{
	first = std::move(newFirst);
}

template<typename T, typename S>
void Pair<T, S>::setSecond(const S& newSecond)
{
	second = newSecond;
}

template<typename T, typename S>
void Pair<T, S>::setSecond(S&& newSecond)
{
	second = std::move(second);
}


