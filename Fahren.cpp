/*
 * Fahren.cpp
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg) {
	// TODO Auto-generated constructor stub

}

Fahren::~Fahren() {
	// TODO Auto-generated destructor stub
}


double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	double dRest = p_rWeg.getLaenge() - aFzg.getAbschnittStrecke();

	const double epsilon = 1e-9;
	if (dRest < epsilon)
	{
		throw Streckenende(aFzg, p_rWeg);
		return 0.0;
	}
	double dMoeglich = aFzg.dGeschwindigkeit() * dZeitIntervall;
	return(std::min(dMoeglich, dRest));
}
