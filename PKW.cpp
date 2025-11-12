/*
 * PKW.cpp
 *
 *  Created on: Nov 4, 2025
 *      Author: cw
 */

#include "PKW.h"
#include "Weg.h"
#include "Verhalten.h"
#include <iomanip>
#include <iostream>


PKW::PKW(std::string sName, double dMaxGeschw, double dVerbrauch, double dTankvolumen):
		Fahrzeug(sName, dMaxGeschw),
		p_dVerbrauch(dVerbrauch),
		p_dTankvolumen (dTankvolumen),
		p_dTankinhalt (0.5 * dTankvolumen)
{}

double PKW::dTanken(double dMenge)
{
	double getankteMenge;
	if (dMenge == std::numeric_limits<double>::infinity() || dMenge + p_dTankinhalt >= p_dTankvolumen)
	{
		getankteMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt = p_dTankvolumen;
	}
	else
	{
		getankteMenge = dMenge;
		p_dTankinhalt += dMenge;
	}
	return getankteMenge;
}

void PKW::vSimulieren()
{
	if (p_dTankinhalt <= 0)
	{
		p_dZeit = dGlobaleZeit;
		return;
	}
	Fahrzeug::vSimulieren();

	//self-edited, not mentioned in script to solve scenario which the car stopped at the end of the street
	p_dTankinhalt -= p_dGefahreneStrecke  * p_dVerbrauch/100.0;
}

void PKW::vAusgeben(std::ostream& out) const
{
	double gesamtverbrauch = p_dGesamtStrecke/100.0 * p_dVerbrauch;
	Fahrzeug::vAusgeben(out);
	out << std::resetiosflags(std::ios::left)
			<< std::setiosflags(std::ios::right)
			<< std::fixed
			<< std::setprecision(2)
			<< std::setw(17) << gesamtverbrauch << "   "
			<< std::setw(12) << p_dTankinhalt;
}

PKW::~PKW()
{}

double PKW::dGeschwindigkeit() const
{
	double dWegLimit = p_pVerhalten->getWeg().getTempoLimitWeg();

	if (p_dMaxGeschwindigkeit <= dWegLimit)
	{
		return p_dMaxGeschwindigkeit;
	}
	return dWegLimit;
}










