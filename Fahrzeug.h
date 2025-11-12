/*
 * Fahrzeug.h
 *
 *  Created on: Nov 3, 2025
 *      Author: cw
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include "Simulationsobjekt.h"

#include <string>
#include <limits>

class Verhalten;
class Weg;

class Fahrzeug: public Simulationsobjekt
{
public:
	Fahrzeug();
	Fahrzeug(std::string sName);
	Fahrzeug(std::string sName, double dMaxGeschw);

	static void vKopf(); //Print out header
	void vSimulieren() override;
	void vAusgeben(std::ostream& out) const override;
	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit() const;
	bool operator < (const Fahrzeug& fahrzeug) const;
	virtual void vNeueStrecke(Weg& weg);
	virtual void vNeueStrecke(Weg& weg, double dStart);

	virtual ~Fahrzeug();

	double getAbschnittStrecke() const;

protected:
	double p_dMaxGeschwindigkeit;
	double p_dGesamtStrecke;
	double p_dGesamtZeit; //Total time travelled
	double p_dAbschnittStrecke;
	double p_dGefahreneStrecke; //not mentioned in the script
	std::unique_ptr<Verhalten> p_pVerhalten;
};



extern double dGlobaleZeit;

#endif /* FAHRZEUG_H_ */
