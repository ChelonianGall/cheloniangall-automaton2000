#include "database.hpp"

#include <iostream>

int main ()
{
	DataBase db("automaton2000-fr");

	cerr << db.executeQuery("SELECT * FROM nodes;") << endl;

  	return EXIT_SUCCESS;
}