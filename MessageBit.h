#pragma once

#include <iostream>
#include <string>

class MessageBit
{
public:
	MessageBit(long long n) : n(n) {}
	MessageBit(const MessageBit& copy) : n(copy.n) {}

	std::string convertToBit() const;
	int size() const;

	MessageBit& operator=(const MessageBit& bit);
	MessageBit operator[](int i) const;
	MessageBit operator+(const MessageBit& bit) const;
	MessageBit operator^(const MessageBit& bit) const;
	MessageBit operator%(const MessageBit& bit) const;
	MessageBit operator<<(int shiftAmount) const;
	MessageBit operator>>(int shiftAmount) const;
	MessageBit operator&(int mask) const;

	friend std::ostream& operator<<(std::ostream& stream, const MessageBit& bit);

private:
	long long n;
	int calculateSize(long long n) const;
};

