// classes example
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>
#include <algorithm> // use abs() needed for sort

//#include <string> // 
//#include<math.h> // use sqrt()



#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;


///
/// This program calculates the distribution of: 
///
/// (1) Number of first neighbours
/// (2) First neighbours distances
///
/// Based on the connectivity criterion imposed by topological clustering and NOT
/// on the distance based clustering
///
	

//**********************************************************************************
// main function
//**********************************************************************************
int main( int argc, const char* argv[] )
{
	std::cout << endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << std::endl ;
	std::cout << BOLDYELLOW << "            _=_                                      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          q(-_-)p                                    " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          '_) (_`         CONFIGURATION GENERATOR    " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << endl ;

	// Parameters:
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------	
	unsigned int Lx ;		// Number of bins
	unsigned int Ly ;		// Number of bins
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------		
	
	
	for ( int k = 1; k < argc ; ++k )
	{
		if ( ( argv[k] == std::string("-h") ) || ( argv[k] == std::string("-HELP") ) || ( argv[k] == std::string("-H") ) || ( argv[k] == std::string("-help") ) )
		{ 
			cout  << BOLDBLACK << "    HELP:" << RESET << std::endl ;
			cout << "    Generates a xyz configuration of A and B species" << std::endl ;
			cout << "    Interpenetrated rectangular 2d lattices" << std::endl ;
			cout << "    Lattice parameter is 1" << std::endl ;
			cout << "    Lattice parameter is 1" << std::endl ;
			cout << "    X-+-X-+-" << std::endl ;
			cout << "    +-O-+-O-" << std::endl ;
			cout << "    X-+-X-+-" << std::endl ;
			cout << "    ------------------------------------------------" << std::endl ;
			cout << BOLDBLACK << "    Mandatory flags:" << RESET << std::endl ; 
			cout << "    -lx" << "\t" << "    to set integer linear Lx size (e.g. ./a.out -lx 10)" << std::endl ;
			cout << "    -ly" << "\t" << "    to set integer linear Lx size  (e.g. ./a.out -ly 5)" << std::endl ; 
			cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
			cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ; 
			cout << std::endl ;
			return (0) ;
		}
		if ( ( argv[k] == std::string("-lx") ) || ( argv[k] == std::string("-Lx") )  || ( argv[k] == std::string("-LX") ) ) { Lx = atoi(argv[k+1]) ; }
		if ( ( argv[k] == std::string("-ly") ) || ( argv[k] == std::string("-Ly") )  || ( argv[k] == std::string("-LY") ) ) { Ly = atoi(argv[k+1]) ; }
	}
	
//	if ( argc < 5 ) 
//	{ 
//		cout << " Wrong ussage man!" << endl ; 
//		return (0) ;
//	}
	
	// Count execution time
	int start_s=clock();
	
	// Files to store data
	ofstream CONFIG ;
	CONFIG.open ("config.xyz", ios::out | ios::trunc); // All computed densities inside cylinders
	
	CONFIG << 2*Lx*Ly << std::endl ;
	CONFIG << std::endl ;
	
	for ( int i = 0; i < Lx; ++i )
	{
		for ( int j = 0; j < Ly; ++j )
		{
			CONFIG << 1 << "\t" << 1.0*i << "\t" << 1.0*j << "\t" << 0.0 << std::endl ; 
		}
	}
	
	for ( int i = 0; i < Lx; ++i )
	{
		for ( int j = 0; j < Ly; ++j )
		{
			CONFIG << 2 << "\t" << 1.0*i+0.5 << "\t" << 1.0*j+0.5 << "\t" << 0.0 << std::endl ; 
		}
	}
	
	

	// End counting time 	
 	int stop_s=clock();
 	
	// Execution time
 	std::cout << endl ;
	std::cout  << YELLOW << "    -> Execution time: " << BOLDYELLOW << ( stop_s - start_s )/double(CLOCKS_PER_SEC) << RESET << YELLOW << " seconds" << std::endl ;
	std::cout << endl ;
	std::cout  << BOLDYELLOW << "    Program finished" << RESET << std::endl ;
	std::cout << endl ;
	
	return (0) ;
}

