#include "MessageBit.h"

#include <vector>

void repeatPrint(std::ostream& stream, std::string message, int n);

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

MessageBit MessageBit::LFSR(const MessageBit& p) const
{
	std::vector<MessageBit> registers = std::vector<MessageBit>(p.size() - 1);
	MessageBit lfsr;
	MessageBit currentBit;

	std::cout << std::endl;
	for (int i = 0; i < registers.size(); i++)
	{
		std::cout << "R" << registers.size() - 1 - i << " | ";
	}
	std::cout << "I | R" << registers.size() - 1 << "^I";
	std::cout << std::endl;
	repeatPrint(std::cout, "-", 40);
	std::cout << std::endl;

	for (int i = 0; i < size(); i++)
	{
		for (MessageBit bit : registers)
		{
			std::cout << " " << bit << " | ";
		}

		currentBit = MessageBit((*this)[i]);
		MessageBit exitBit = (currentBit ^ registers[0]);
		std::cout << currentBit << " |  " << exitBit << std::endl;

		for (int i = 1; i < registers.size(); i++)
		{
			if (p[i].n == 1)
			{
				registers[i - 1] = exitBit ^ registers[i];
			}
			else
			{
				registers[i - 1] = registers[i];
			}
		}
		registers[registers.size() - 1] = exitBit;
	}

	for (MessageBit bit : registers)
	{
		lfsr = lfsr + bit;
		std::cout << " " << bit << " | ";
	}
	std::cout << std::endl;

	return lfsr;
}

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