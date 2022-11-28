#include "configuration.hpp"
#include "database.hpp"
#include "log.hpp"

#include <iostream>

int main ()
{
	//DataBase db("automaton2000-fr");

	//cerr << db.executeQuery("SELECT * FROM nodes;") << endl;

	shared_ptr<Configuration> configuration = Configuration::getConfiguration();

  	return EXIT_SUCCESS;
}