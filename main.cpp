#include <iostream>

#include "MessageBit.h"

const MessageBit T = MessageBit(0x76459CA6);
const MessageBit P = MessageBit(0x57);

int main(void)
{
	std::cout << T << " / " << P << std::endl << std::endl;
	MessageBit FCS = T % P;
	std::cout << std::endl;
	std::cout << "CRC = " << T + FCS << std::endl;

	return 0;
}