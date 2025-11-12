/*
 * Parken.h
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Parken: public Verhalten {
public:
	Parken(Weg& weg, double dStart);
	virtual ~Parken();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
	double p_dStart; //starting time of parking
};

extern double dGlobaleZeit;

#endif /* PARKEN_H_ */
