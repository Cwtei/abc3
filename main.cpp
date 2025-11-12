/*
 * main.cpp
 *
 *  Created on: Nov 3, 2025
 *      Author: cw
 */



#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Tempolimit.h"

#include <memory> //for smart pointer
#include <iostream>
#include <vector> //for container vector
#include <utility> //for move()

void vAufgabe_1a();

double dGlobaleZeit = 0.0; //Global variable to be accessible from other classes

int main()
{
	vAufgabe_1a();
}



void vAufgabe_1()
{
	std::cout << "----------------- Raw pointer test -----------------" << std::endl;
	//construct stack object (object created in stack memory will be deleted automatically)
	Fahrzeug stack("stack");

	//construct heap object
	Fahrzeug* heap = new Fahrzeug("heap");

	//clearing heap memory (pointer saved in the heap must be deleted manually)
	delete heap;

	std::cout << "----------------- Smart pointer test -----------------" << std::endl;

	//unique pointer
	//data type: std::unique_ptr<T>
	//declaration: std::make_unique<T>(C)
	//T is the class of the object to be constructed
	//C is the input for the constructor (works with or without input due to the default constructor
	std::unique_ptr <Fahrzeug> unique1_ptr = std::make_unique <Fahrzeug> ("Unique1");
	std::unique_ptr <Fahrzeug> unique2_ptr = std::make_unique <Fahrzeug> ("Unique2");

	std::vector<std::unique_ptr<Fahrzeug>> unique_vector;

	//std::move is required to transfer the pointer
	//unique_ptr are now nullptr and the object is owned by the 'unique_vector'
	unique_vector.push_back(std::move(unique1_ptr));
	unique_vector.push_back(std::move(unique2_ptr));

	//shared pointer
	//data type: std::shared_ptr<T>
	//declaration: std::make_shared<T>(C)
	//T is the class of the object to be constructed
	//C is the input for the constructor (works with or without input due to the default constructor
	std::shared_ptr <Fahrzeug> shared1_ptr = std::make_shared <Fahrzeug> ("Shared1");
	std::shared_ptr <Fahrzeug> shared2_ptr = std::make_shared <Fahrzeug> ("Shared2");

	std::cout << "Count (shared1_ptr): " << shared1_ptr.use_count() << std::endl; //output: 1

	shared2_ptr = shared1_ptr; //count increases as the object is pointed more, shared2_ptr is deleted

	std::cout << "Count (shared1_ptr): " << shared1_ptr.use_count() << std::endl; //output: 2


	std::vector<std::shared_ptr<Fahrzeug>> shared_vector;

	//std::move is not required
	//both shared_vector and shared_ptr own the object and the count increases
	shared_vector.push_back(shared1_ptr);
	shared_vector.push_back(shared2_ptr);
}

void vAufgabe_1a()
{
	std::string name;
	double maxSpeed;
	std::vector<std::unique_ptr<Fahrzeug>> vehicle_vector;

	for (int i=1; i<=3 ; i++)
	{
		std::cout << "Enter the name of the vehicle: " ;
		std:: cin >> name;
		std::cout << "Enter the max speed of the vehicle: " ;
		std:: cin >> maxSpeed;
		std::unique_ptr <Fahrzeug> vehicle_ptr = std::make_unique <Fahrzeug> (name, maxSpeed);
		vehicle_vector.push_back(std::move(vehicle_ptr));
	}

	Fahrzeug::vKopf();
	std::cout << "\n------------------------------------------------------------\n" << std::endl;

	for (int j=1; j<=3; j++)
	{
		dGlobaleZeit += 0.5;

		auto it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			(*it)->vSimulieren();
			std::cout<< (*it);
			std::cout << std::endl;
			it++;
		}
	}
}




/*void vAufgabe_2()
{
	std::string sName;
	double dMaxGeschw;
	std::vector<std::unique_ptr<Fahrzeug>> vehicle_vector;


	std::cout << "How many PKWs are there: ";
	int iNumberOfPKW;
	std::cin >> iNumberOfPKW;

	double dVerbrauch, dTankvolumen;
	for (int i=1; i<=iNumberOfPKW ; i++)
	{
		std::cout << "PKW " << i << std::endl;
		std::cout << "Name: " ;
		std:: cin >> sName;
		std::cout << "Max speed: " ;
		std:: cin >> dMaxGeschw;
		std::cout << "Verbrauch: ";
		std::cin >> dVerbrauch;

		char choice;
		std::cout << "Use default tank volume (55.0)? (y/n)";
		std::cin >> choice;

		if (choice == 'n' || choice == 'N')
		{
			std::cout << "Custom tank volume: " ;
			std::cin >> dTankvolumen;
			std::unique_ptr <PKW> vehicle_ptr = std::make_unique <PKW> (sName, dMaxGeschw, dVerbrauch, dTankvolumen);
			vehicle_vector.push_back(std::move(vehicle_ptr));
		}
		else
		{
			std::unique_ptr <PKW> vehicle_ptr = std::make_unique <PKW> (sName, dMaxGeschw, dVerbrauch);
			vehicle_vector.push_back(std::move(vehicle_ptr));
		}
	}

	std::cout << "How many Fahrrads are there: " ;
	int iNumberOfFahrrad;
	std::cin >> iNumberOfFahrrad;

	for (int i=1; i<=iNumberOfFahrrad; i++)
	{
		std::cout << "Fahrrad " << i << std::endl;
		std::cout << "Name: " ;
		std:: cin >> sName;
		std::cout << "Max speed: " ;
		std:: cin >> dMaxGeschw;

		std::unique_ptr <Fahrrad> vehicle_ptr = std::make_unique <Fahrrad> (sName, dMaxGeschw);
		vehicle_vector.push_back(std::move(vehicle_ptr));
	}

	Fahrzeug::vKopf();
	std::cout << "-----------------------------------------------------------------------------------------\n" ;

	double dDauer = 10;
	double dZeitschritt = 0.5;

	for (dGlobaleZeit = 0; dGlobaleZeit <= dDauer; dGlobaleZeit += dZeitschritt)
	{

		std::cout << "Simulation time: " << dGlobaleZeit << std::endl;

		//simulate the movement
		auto it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			(*it)->vSimulieren();
			it++;
		}

		//refueling
		const double epsilon = 1e-9;

		if (dGlobaleZeit > 3.0 - epsilon && dGlobaleZeit - dZeitschritt < 3.0 - epsilon)
		{
			std::cout << "Refueling" << std::endl;



			for (int i = 0; i < iNumberOfPKW; i++)
			{
				//vehicle_vectors is a sequence of smart pointers
				//vehicle_vector[i] accesses the i-th element, which is an object of type std::unique_ptr<Fahrzeug>
				//std::unique_ptr<Fahrzeug> is a wrapper around a raw memory address a Fahrzeug*
				//get() tells the smart pointer to hand out its inner raw address
				//dynamic casting return the valid pointer if successful, and nullptr if unsuccessful
				PKW* pPKW = dynamic_cast<PKW*> (vehicle_vector[i].get());

				if (pPKW) //anything except nullptr is considered true
				{
					pPKW->dTanken();
				}
			}
		}

		//print out the vector
		it = vehicle_vector.begin();
		while (it != vehicle_vector.end())
		{
			std::cout << *(*it);
			std::cout << std::endl;
			it++;
		}
	}
}*/


/*
void vAufgabe_4()
{
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "AUFGABENBLOCK 2: Test 1 (Task 5.3.3: Weg Class)" << std::endl;
    std::cout << "=======================================================" << std::endl;

    // 1. Create a Weg instance using the parameterized constructor and the default Tempolimit.
    // The name "Weg1" and length 40.0 km are used here.
    std::unique_ptr<Weg> pWeg1 = std::make_unique<Weg>("WegA", 40.0);

    // 2. Create another Weg explicitly setting a different Tempolimit.
    std::unique_ptr<Weg> pWeg2 = std::make_unique<Weg>("WegB", 115.0, Tempolimit::Landstrasse);

    // 3. Output the header line for the Weg table (if implemented in Weg::vKopf()).
    Weg::vKopf();
    std::cout << "--------------------------------------------------------" << std::endl;

    // 4. Test output using the overloaded operator<< (inherited from Simulationsobjekt).
    std::cout << *pWeg1 << std::endl; // Should print ID, Name, Length, and an empty list of vehicles.
    std::cout << *pWeg2 << std::endl;
}
*/


void vAufgabe_5() {
    std::cout << "\n--- Starte Aufgabe 5: Testen von Weg und vAnnahme ---\n" << std::endl;

    // 1. Erzeuge einen Weg (Create a Road)
    // Beispiel: Ein Weg namens "TestWeg" mit 100km Länge und Tempolimit INNERORTS (Annahme: 50 km/h)
    // Verwenden Sie den Tempolimit-Enum, den Sie in 5.3, Punkt 2 definiert haben.
    // Falls Sie Tempolimit noch nicht implementiert haben, verwenden Sie den Standard-Konstruktor.
    // Hier wird ein 'unique_ptr' verwendet, da ein Weg der Hauptfunktion gehört und nicht geteilt wird.
    std::unique_ptr<Weg> p_pTestWeg = std::make_unique<Weg>("TestWeg", 100.0);
    //
    // 2. Erzeuge Fahrzeuge (Create Vehicles)
    // Wir verwenden unique_ptr und move() sie später in den Weg.
    auto p_pBMW = std::make_unique<PKW>("BMW", 120.0, 10.0, 55.0); // Name, MaxSpeed, Consumption, TankVolume
    auto p_pAudi = std::make_unique<PKW>("Audi", 100.0, 8.0, 50.0);
    auto p_pBMX = std::make_unique<Fahrrad>("BMX", 25.0); // Name, MaxSpeed

    // Wir brauchen einen Vektor, um die Fahrzeuge während der Simulation zu verwalten.
    // Da vAnnahme die unique_ptr übernimmt, können wir hier keinen Vektor mit den originalen Pointern verwenden.
    // Die Fahrzeuge werden direkt in den Weg verschoben.

    // 3. Fahrzeuge auf den Weg setzen (Place Vehicles onto the Road)
    // Wie in 5.4, Punkt 4 gefordert, laden wir einen fahrend und zwei parkend.

    // a) Ein fahrendes Fahrzeug annehmen (vAnnahme mit einem Argument) -> hinten in die Liste
    std::cout << "Fahrzeug " << p_pBMW->getName() << " wird FAHREND angenommen." << std::endl;
    p_pTestWeg->vAnnahme(std::move(p_pBMW));

    // b) Ein parkendes Fahrzeug annehmen (vAnnahme mit zwei Argumenten: Fahrzeug und Startzeit) -> vorne in die Liste
    // Das Fahrzeug soll später (z.B. bei Globaler Zeit 3.0) losfahren
    double dStartZeitAudi = 3.0;
    std::cout << "Fahrzeug " << p_pAudi->getName() << " wird PARKEND angenommen (Startzeit: " << dStartZeitAudi << ")." << std::endl;
    p_pTestWeg->vAnnahme(std::move(p_pAudi), dStartZeitAudi);

    // c) Ein weiteres parkendes Fahrzeug (Startzeit 1.0)
    double dStartZeitBMX = 1.0;
    std::cout << "Fahrzeug " << p_pBMX->getName() << " wird PARKEND angenommen (Startzeit: " << dStartZeitBMX << ")." << std::endl;
    p_pTestWeg->vAnnahme(std::move(p_pBMX), dStartZeitBMX);

    // 4. Simulation durchführen (Perform Simulation)
    double dZeitschritt = 0.5;
    double dMaxZeit = 5.0;

    std::cout << "\n--- Starte Simulation ---\n" << std::endl;

    Weg::vKopf();

    // Gib den Startzustand des Weges aus (sollte alle 3 Fahrzeuge anzeigen)
    std::cout << "\nAnfangszustand des Weges: " << *p_pTestWeg << std::endl;

    for (dGlobaleZeit = 0.0; dGlobaleZeit <= dMaxZeit; dGlobaleZeit += dZeitschritt) {
        std::cout << "\n>>> Globale Zeit: " << dGlobaleZeit << " Stunden <<<" << std::endl;

        // Simuliere den Weg. Das sollte alle Fahrzeuge auf dem Weg simulieren.
        p_pTestWeg->vSimulieren();

        // Gib den aktuellen Zustand des Weges und der Fahrzeuge aus.
        std::cout << "Aktueller Zustand des Weges: " << std::endl;
        std::cout << *p_pTestWeg << std::endl;

        // Optional: Wenn Sie die Ausgabe auf der Konsole besser verfolgen wollen.
        // std::cin.get();
    }

    std::cout << "\n--- Ende Aufgabe 5 ---\n" << std::endl;
}


