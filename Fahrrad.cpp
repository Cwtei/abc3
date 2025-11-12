/*
 * Fahrrad.cpp
 *
 *  Created on: Nov 4, 2025
 *      Author: cw
 */

#include "Fahrrad.h"
#include <algorithm>
#include <cmath>

Fahrrad::Fahrrad(std::string sName, double dMaxGeschw): Fahrzeug(sName, dMaxGeschw)
{}

Fahrrad::~Fahrrad()
{}


double Fahrrad::dGeschwindigkeit() const
{
	int iMultipleOf20 = static_cast<int> (p_dGesamtStrecke / 20.0);
	double dGeschw = p_dMaxGeschwindigkeit * std::pow(0.9 , iMultipleOf20);
	return std::max(dGeschw , 12.0);
}
