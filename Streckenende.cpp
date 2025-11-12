/*
 * Streckenende.cpp
 *
 *  Created on: Nov 12, 2025
 *      Author: cw
 */

#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"

#include <iostream>

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg) {
	// TODO Auto-generated constructor stub

}

Streckenende::~Streckenende() {
	// TODO Auto-generated destructor stub
}

void Streckenende::vBearbeiten()
{
	std::cout << "Fahrzeug" << fahrzeug.getName() << "ist am Streckenende." << std::endl;
}
