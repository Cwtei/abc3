/*
 * Parken.cpp
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#include "Parken.h"
#include "Weg.h"

#include "Losfahren.h"

#include<iostream>


Parken::Parken(Weg& weg, double dStart) : Verhalten(weg),p_dStart(dStart)
{}

Parken::~Parken() {
	// TODO Auto-generated destructor stub
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (dGlobaleZeit >= p_dStart)
	{
		throw Losfahren(aFzg, p_rWeg);
		std::cout << "Startzeit ist erreicht." << std::endl;
	}

	return 0.0;
}


