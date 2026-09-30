#pragma once

#include <iostream>
#include <string>

class MessageBit
{
public:
	MessageBit() : n(0) {}
	MessageBit(long long n) : n(n) {}
	MessageBit(const MessageBit& copy) : n(copy.n) {}

	int size() const;
	MessageBit LFSR(const MessageBit& p) const;
	std::string convertToBit() const;

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
};

