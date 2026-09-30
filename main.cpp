#include <iostream>

#include "MessageBit.h"

const MessageBit T = MessageBit(0x76459CA6);
const MessageBit P = MessageBit(0x57);

int main(void)
{
	std::cout << "CRC: " << std::endl << std::endl;
	std::cout << T << " / " << P << std::endl << std::endl;
	MessageBit FCS = T % P;
	std::cout << std::endl;

	std::cout << "Entrada           = " << T << std::endl;
	std::cout << "Polinomio Gerador = " << P << std::endl;
	std::cout << "FCS               = " << FCS << std::endl;
	std::cout << "CRC               = " << T + FCS << std::endl;

	/*MessageBit testT = MessageBit(0x2B);
	MessageBit testP = MessageBit(0xD);

	testT.LFSR(testP);*/

	std::cout << std::endl << "LFSR: " << std::endl;
	MessageBit LFSR = T.LFSR(P);
	std::cout << std::endl;

	std::cout << "Entrada           = " << T << std::endl;
	std::cout << "Polinomio Gerador = " << P << std::endl;
	std::cout << "FCS               = " << LFSR << std::endl;
	std::cout << "CRC               = " << T + LFSR << std::endl;

	std::cout << std::endl << "Comparacao: " << std::endl << std::endl;
	std::cout << "CRC  = " << T + FCS << std::endl;
	std::cout << "LFSR = " << T + LFSR << std::endl;

	return 0;
}