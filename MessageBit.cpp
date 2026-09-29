#include "MessageBit.h"

void repeatPrint(std::ostream& stream, std::string message, int n);

std::string MessageBit::convertToBit() const
{
	std::string bit;
	unsigned long long q, r;

	bit = "";
	q = n;

	do
	{
		r = q % 2;
		bit = std::to_string(r) + bit;
		q = q / 2;
	} while (q != 0);

	return bit;
}

int MessageBit::size() const
{
	unsigned long long q;
	int nBits;

	q = n;
	nBits = 0;

	do
	{
		nBits += 1;
		q /= 2;
	} while (q != 0);

	return nBits;
}

MessageBit& MessageBit::operator=(const MessageBit& bit)
{
	if (this == &bit)
		return *this;

	n = bit.n;

	return *this;
}

MessageBit MessageBit::operator[](int i) const
{
	int shiftAmount = size() - i - 1;
	if (shiftAmount < 0 || shiftAmount > size())
		throw std::out_of_range("index out of range");

	return MessageBit((n >> shiftAmount) & 1);
}

MessageBit MessageBit::operator+(const MessageBit& bit) const
{
	MessageBit sum = MessageBit(n);
	
	sum.n <<= bit.size();
	sum.n += bit.n;

	return sum;
}

MessageBit MessageBit::operator^(const MessageBit& bit) const
{
	return MessageBit(n ^ bit.n);
}

MessageBit MessageBit::operator%(const MessageBit& divident) const
{
	MessageBit quotient = n;
	int shiftAmount;
	
	shiftAmount = divident.size() - 1;
	quotient = quotient << shiftAmount;

	repeatPrint(std::cout, " ", shiftAmount);
	std::cout << "'" << std::endl;
	std::cout << quotient << " | " << divident << std::endl;

	int mask = ~(~0 << divident.size());

	shiftAmount = quotient.size() - divident.size();
	MessageBit currentBits = (quotient >> shiftAmount) & mask;
	for (int i = 0; i < size(); i++)
	{
		if (currentBits.size() == divident.size())
		{
			repeatPrint(std::cout, " ", i);
			std::cout << divident << std::endl;

			currentBits = currentBits ^ divident;
		}
		else
		{
			repeatPrint(std::cout, " ", i);
			repeatPrint(std::cout, "0", divident.size());
			std::cout << std::endl;
		}

		int spaceAmount = 0;
		if (i != size() - 1)
		{
			currentBits = currentBits + quotient[divident.size() + i];
			spaceAmount = i + 1 + divident.size() - currentBits.size();
		}
		else
		{
			spaceAmount = i + divident.size() - currentBits.size();
		}

		repeatPrint(std::cout, " ", i);
		repeatPrint(std::cout, "-", divident.size());
		std::cout << std::endl;
		repeatPrint(std::cout, " ", spaceAmount);
		std::cout << currentBits << std::endl;
	}

	return currentBits;
}

MessageBit MessageBit::operator<<(int shiftAmount) const
{
	return n << shiftAmount;
}

MessageBit MessageBit::operator>>(int shiftAmount) const
{
	return n >> shiftAmount;
}

MessageBit MessageBit::operator&(int mask) const
{
	return n & mask;
}

std::ostream& operator<<(std::ostream& stream, const MessageBit& bit)
{
	stream << bit.convertToBit();
	return stream;
}

void repeatPrint(std::ostream& stream, std::string message, int n)
{
	for (int i = 0; i < n; i++)
	{
		stream << message;
	}
}

int MessageBit::calculateSize(long long n) const
{
	unsigned long long q;
	int nBits;

	q = n;
	nBits = 0;

	do
	{
		nBits += 1;
		q /= 2;
	} while (q != 0);

	return nBits;
}