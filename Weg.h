/*
 * Weg.h
 *
 *  Created on: Nov 9, 2025
 *      Author: cw
 */

#ifndef WEG_H_
#define WEG_H_

#include <list>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Fahrausnahme;
class Fahrzeug;

class Weg: public Simulationsobjekt
{
public:
	Weg();
	Weg(std::string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);

	virtual ~Weg();

	void vSimulieren() override;
	void vAusgeben(std::ostream& out) const override;
	static void vKopf();
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double dStart);

	double getLaenge() const;
	double getTempoLimitWeg() const;

private:
	double p_dLaenge; //distance in km
	std::list <std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // list of vehicles on this 'weg'
	Tempolimit p_eTempolimit;
};

#endif /* WEG_H_ */
