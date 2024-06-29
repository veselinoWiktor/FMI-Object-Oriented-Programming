#pragma once
#include <iostream>

#define TTS template<class T, class S>
#define P Pair

TTS
class Pair
{
private:
	T first;
	S second;
public:
	P() = default;
	P(const T&, const S&);

	const T& getFirst() const;
	const S& getSecond() const;
	void setFirst(const T&);
	void setSecond(const S&);

	TTS
		friend std::ostream& operator<<(std::ostream&, const P<T, S> obj);
};

TTS
P<T, S>::P(const T& first, const S& second) : first(first), second(second) {}

TTS
const T& P<T, S>::getFirst() const
{
	return first;
}

TTS
const S& P<T, S>::getSecond() const
{
	return second;
}

TTS
void P<T, S>::setFirst(const T& value)
{
	first = value;
}

TTS
void P<T, S>::setSecond(const S& value)
{
	second = value;
}

TTS
std::ostream& operator<<(std::ostream& os, const P<T, S> obj)
{
	return os << "(" << obj.getFirst() << ", " << obj.getSecond() << ")";
}