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
/// 	sed -ie 's/X/1/g' Cluster1.xyz
///	sed -ie 's/atoms in 1 th largest cluster//g' Cluster1.xyz
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
	std::cout << BOLDYELLOW << "          '_) (_`         ADD BOX SIZE TO XYZ FILES  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    Add box for plumed analysis of NPT simulations   " << RESET << std::endl ;
	std::cout << endl ;

//	PARAMETERS
//---------------------------------------------------------------------------------------------------------
	unsigned int Pace = 10000 ; // frequency at which trajectory is saved to mach with box Pace (that is 1000)
	double factor=0.1 ; // Conversion factor 0.1 => A to nm, 10 => nm to A
//---------------------------------------------------------------------------------------------------------


	// Cleans the trajectory file removes the content in the comment line
	system ("sed 's/Atoms.*//g' traj_all.xyz > traj_clean.xyz") ;

	// Count execution time
	int start_s=clock();

	// Read box into a vector from log.lammps file
	ifstream ThermoFile ;
	ThermoFile.open ("log.lammps", ios::in ) ;
	std::vector<double> BoxVectorX ;
	std::vector<double> BoxVectorY ;
	std::vector<double> BoxVectorZ ;
	unsigned int Frame ;

	// Variables to be read
	int a ;
	double b, c, d, e, f, g, h, i, j ;
	double x, y, z ;

	std::string line ;
//	std::ostringstream BoxString;

	int BoxCounter = 0 ;
	while (getline(ThermoFile, line))
	{
		if (line.length() > 100)
		{	
			BoxCounter++ ;	
			istringstream iss1(line); //procesar primera línea
			iss1 >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j ;
			//std::cout << g << "\t" << h << "\t" << i << std::endl ;
			BoxVectorX.push_back (g) ;
			BoxVectorY.push_back (h) ;
			BoxVectorZ.push_back (i) ;
		}
	}
	ThermoFile.close() ;
	cout << YELLOW << "    -> " << BoxCounter << " box sizes extracted from log.lammps" << RESET << endl ;
	

	// Opening trajectory without box and creating a the same trajectory with box
	ifstream TrajFile ;
	TrajFile.open ("traj_clean.xyz", ios::in ) ;
	ofstream OUT ;
	OUT.open ("traj_all_BOX.xyz", ios::out | ios::trunc); // All computed densities inside cylinders
	

	cout << YELLOW << "    -> Adding box vectors to: " << BOLDYELLOW << "traj_clean.xyz" << RESET << endl ;
		
	unsigned int element, atoms ;
	
	unsigned int FrameCounter = 0 ;
	while (getline(TrajFile, line))
	{
		std::stringstream aa(line) ;

		if (line.length() > 10)
		{		
			aa >> element >> x >> y >> z ;
			OUT << element << "  " << factor*x << "  " << factor*y << "  " << factor*z << std::endl ;
		}
		if ( ( line.length() < 7 ) && ( line.length() > 1 ) )
		{
			aa >> atoms ;
			OUT << atoms << std::endl ;	
			OUT << BoxVectorX[FrameCounter] << "    " << BoxVectorY[FrameCounter] << "    " << BoxVectorZ[FrameCounter] << std::endl ;
			getline(TrajFile, line) ; //procesar segunda línea (sin hacer nada)
			FrameCounter++ ;	
		}
	}
	TrajFile.close() ;
	OUT.close() ;

	

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

