/*
 * Fahren.h
 *
 *  Created on: Nov 10, 2025
 *      Author: cw
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren: public Verhalten {
public:
	Fahren(Weg & weg);
	virtual ~Fahren();

	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};

#endif /* FAHREN_H_ */
