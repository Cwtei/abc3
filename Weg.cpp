/*
 * Weg.cpp
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#include "Weg.h"
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include "Fahrausnahme.h"

#include <iomanip>
#include <iostream>

Weg::Weg() :
Simulationsobjekt(),
p_dLaenge(0.0),
p_eTempolimit(Tempolimit::Autobahn)
{}

Weg::Weg(std::string sName, double dLaenge, Tempolimit eTempolimit):
		Simulationsobjekt(sName),
		p_dLaenge(dLaenge),
		p_eTempolimit(eTempolimit)
{}

Weg::~Weg() {}


void Weg::vSimulieren()
{
	for (auto& pFahrzeug : p_pFahrzeuge)
	{
		try
		{
			pFahrzeug->vSimulieren();
		}
		catch (Fahrausnahme& e)
		{
			e.vBearbeiten();
		}
	}
}

void Weg::vAusgeben(std::ostream& out) const
{
	Simulationsobjekt::vAusgeben(out);
	out << " : " << std::resetiosflags(std::ios::left)
				<< std::setiosflags(std::ios::right)
				<< std::fixed
				<< std::setprecision(2)
				<< std::setw(8) << p_dLaenge << "   ("
				<< std::resetiosflags(std::ios::right)
				<< std::setiosflags(std::ios::left);

	auto it = p_pFahrzeuge.begin();
	while (it != p_pFahrzeuge.end())
	{
		out << (*it)->getName();

		if (++it != p_pFahrzeuge.end())
		{
			out << " ";
		}
	}

	out << ")";
}

void Weg::vKopf()
{
	std::cout << std::resetiosflags(std::ios::right)
			<< std::setiosflags(std::ios::left) //aligned to the left
			<<std::setw(3) << "ID" << " | "
			<< std::setw(5) << "Name" << " | "
			<< std::setw(8) << "Laenge" << " | "
			<< std::setw(20) << "Fahrzeuge" << " | "
			<< std::endl;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug)
{
	fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fahrzeug));
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStart)
{
	fahrzeug->vNeueStrecke(*this, dStart);
	p_pFahrzeuge.push_front(std::move(fahrzeug));

}

double Weg::getLaenge() const
{
	return p_dLaenge;
}

double Weg::getTempoLimitWeg() const
{
	return(getTempolimit(p_eTempolimit));
}
