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
	std::cout << BOLDYELLOW << "          '_) (_`         HISTOGRAM GENERATOR        " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << endl ;

	// Check the number of arguments (1 means only the name of the program => No argument)
	if ( argc == 1 )
	{
		cout << "\t Wrong usage. You should execute:" << endl ;
		cout << BOLDRED << "\t " << argv[0] << " [File to analyze.dat]" << RESET << endl ;
		cout << " " << endl ;
		return (0) ;
	}
	
	// Check if the file exists
	ifstream file(argv[1]) ;
	if (!file)
	{
    	std::cout << BOLDRED <<"    -> ERROR: File test.xyz does not exist. ABORTING" << RESET << std::endl ;
    	std::cout << std::endl ;
		abort () ;
	}
	file.close() ;
	
	std::cout << YELLOW << "    -> File " << BOLDYELLOW << argv[1] << RESET << YELLOW << " found" << RESET << std::endl ;

	unsigned int bins = 100 ;		// Number of bins default
	
	for ( int k = 1; k < argc ; ++k )
	{
		if ( ( argv[k] == std::string("-h") ) || ( argv[k] == std::string("-HELP") ) || ( argv[k] == std::string("-H") ) || ( argv[k] == std::string("-help") ) )
		{ 
			cout  << BOLDBLACK << "    HELP:" << RESET << std::endl ;
			cout << "    Generates a histogram with the second column of a file containing real data" << std::endl ;
			cout << "    [Column can be changed and also addapted to integer data]" << std::endl ;
			cout << "    ------------------------------------------------" << std::endl ;
			cout << BOLDBLACK << "    Execution: ./a.out file.dat [+flags]" << RESET << std::endl ; 
			cout << BOLDBLACK << "    Mandatory flags:" << RESET << std::endl ; 
			cout << "    -bins" << "\t" << "    to set the number of bins (e.g. ./a.out file.dat -bins 100) default bins=100" << std::endl ;
			cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
			cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ; 
			cout << "    -gle" << "\t" << "    to generate gle graphs of histogram and PDF  (e.g. ./a.out file.dat -bins 100 -gle)" << std::endl ; 
			cout << std::endl ;
			return (0) ;
		}
		if ( ( argv[k] == std::string("-bins") ) || ( argv[k] == std::string("-bin") )  || ( argv[k] == std::string("-b") ) ) { bins = atoi(argv[k+1]) ; }
//		if ( ( argv[k] == std::string("-gle") ) || ( argv[k] == std::string("-g") )  || ( argv[k] == std::string("-GLE") ) ) { Ly = atoi(argv[k+1]) ; }
	}	
	
	double minval ;		// Radius of type 1 atoms.
	double maxval ;		// Radius of type 2 atoms.
	unsigned int n ;
	
	
	// Count execution time
	int start_s=clock();
	
	// Files to store data
	ofstream Histogram ;
	Histogram.open ("Histogram.dat", ios::out | ios::trunc); // All computed densities inside cylinders
	ofstream PDF ;
	PDF.open ("ProbDenFunc.dat", ios::out | ios::trunc); // Number of sea atoms inside cylinders
	
	std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
	

	cout << YELLOW << "    -> Processing file: " << BOLDYELLOW << File << RESET << endl ;
	
	std::ifstream InputFile ;
	InputFile.open( File.c_str(), ios::in );

	std::string line ;			// variable string to read the line
	unsigned int element ;
	double x, y ;

	std::vector<double> DataVector ;

	while (getline(InputFile, line))
	{
		std::stringstream aa(line) ;
		aa >> x >> y ;
		// Assigning the y value to the data vector
		DataVector.push_back (y) ;
	}
	InputFile.close() ;

	maxval = *max_element(DataVector.begin(),DataVector.end()) ;
        minval = *min_element(DataVector.begin(),DataVector.end()) ;

	cout << YELLOW << "    -> Detected " << BOLDYELLOW << DataVector.size () << RESET << YELLOW << " data points" << RESET << endl ;

	cout << BLUE  << "       Minimum value = " << BOLDBLUE  << minval << RESET << endl ;
	cout << BLUE  << "       Maximum value = " << BOLDBLUE  << maxval << RESET << endl ;


	std::vector<int> bin(bins) ;
	std::vector<double> pos ;

	double DX = (maxval-minval)/bins ;

	for ( int k = 0; k < DataVector.size (); ++k )
	{
		n =  int( DataVector[k]/DX ) ; //int( bins*DataVector[k]/(maxval-minval) ) ;
		bin[n]++ ;
	}

	cout << YELLOW << "    -> Histogram generated " << RESET << endl ;
	cout << BLUE  << "       Stored under name: " << BOLDBLUE  << "Histogram.dat" << RESET << endl ;
	Histogram << "! Position Value" << endl ;

	double Integral = 0.0 ;
	for ( int k = 0; k < bins; ++k )
	{
		Histogram << DX/2.0 + k*DX << "\t" << bin[k] << endl ;
		// Integrating the histogram to normalize it:
		Integral = Integral + DX*float(bin[k]) ;
	}
	cout << YELLOW << "    -> Histogram integrated to normalize " << RESET << endl ;
	cout << BLUE  << "       Integral = " << BOLDBLUE  << Integral << RESET << endl ;

	// GLE GRAPH HISTOGRAM
	ofstream GLEHISTO ;
	GLEHISTO.open ("Histogram.gle", ios::out | ios::trunc); // All computed densities inside cylinders
	GLEHISTO << "size 12 8" << std::endl ;
	GLEHISTO << "set texlabels 1" << std::endl ;
	GLEHISTO << "begin graph" << std::endl ;
	GLEHISTO << "title  \"Data Histogram\"" << std::endl ;
	GLEHISTO << "xtitle \"Variable, $X$\"" << std::endl ;
	GLEHISTO << "ytitle \"Frequency, $F(X)$\"" << std::endl ;
	GLEHISTO << "data \"Histogram.dat\"" << std::endl ;
	GLEHISTO << "bar d1 fill red" << std::endl ;
	GLEHISTO << "end graph" << std::endl ;
	GLEHISTO << "set hei 0.2" << std::endl ;
	GLEHISTO << "begin key" << std::endl ;
	GLEHISTO << "pos tr" << std::endl ;
	GLEHISTO << "nobox" << std::endl ;
	GLEHISTO << "text \" Data points = " << DataVector.size () << "\" " << std::endl ;
	GLEHISTO << "text \" Min value = " << minval << "\" " << std::endl ;
	GLEHISTO << "text \" Max value = " << maxval << "\" " << std::endl ;
	GLEHISTO << "text \" Bins = " << bins << "\" " << std::endl ;
	GLEHISTO << "text \" $\\displaystyle \\int_{min}^{max} F(X) dX =$ " << Integral << "\" " << std::endl ;
	GLEHISTO << "end key" << std::endl ;
	cout << YELLOW << "    -> Generated GLE script to plot histogram & rendered" << RESET << endl ;
	// END GLE GRAPH HISTOGRAM

	std::vector<double> BinNorm(bins) ;
	for ( int k = 0; k < bins; ++k ) { BinNorm[k]=float(bin[k])/Integral ; }

	Integral = 0.0 ;
	for ( int k = 0; k < bins; ++k ) 
	{ 
		PDF << DX/2.0 + k*DX << "\t" << BinNorm[k] << endl ; 
		Integral = Integral + DX*float(BinNorm[k]) ;
	}
	cout << YELLOW << "    -> Probability density function (PDF)" << RESET << endl ;
	cout << BLUE  << "       Generated & stored under name: " << BOLDBLUE  << "ProbDenFunc.dat" << RESET << endl ;
	cout << YELLOW << "    -> Checking normalization of the PDF" << RESET << endl ;
	cout << BLUE  << "       Integral = " << BOLDBLUE  << Integral << RESET << endl ;

	// GLE GRAPH PDF
	ofstream GLEPDF ;
	GLEPDF.open ("PDF.gle", ios::out | ios::trunc); // All computed densities inside cylinders
	GLEPDF << "size 12 8" << std::endl ;
	GLEPDF << "set texlabels 1" << std::endl ;
	GLEPDF << "begin graph" << std::endl ;
	GLEPDF << "title  \"Data Probability density function\"" << std::endl ;
	GLEPDF << "xtitle \"Variable, $X$\"" << std::endl ;
	GLEPDF << "ytitle \"PDF[$X$]\"" << std::endl ;
	GLEPDF << "data \"ProbDenFunc.dat\"" << std::endl ;
	GLEPDF << "d1 line color red" << std::endl ;
	GLEPDF << "end graph" << std::endl ;
	GLEPDF << "set hei 0.2" << std::endl ;
	GLEPDF << "begin key" << std::endl ;
	GLEPDF << "pos tr" << std::endl ;
	GLEPDF << "nobox" << std::endl ;
	GLEPDF << "text \" Data points = " << DataVector.size () << "\" " << std::endl ;
	GLEPDF << "text \" Min value = " << minval << "\" " << std::endl ;
	GLEPDF << "text \" Max value = " << maxval << "\" " << std::endl ;
	GLEPDF << "text \" Bins = " << bins << "\" " << std::endl ;
	GLEPDF << "end key" << std::endl ;

	cout << YELLOW << "    -> Generated GLE script to plot histogram & rendered" << RESET << endl ;
	// END GLE GRAPH PDF

	cout << YELLOW << "    -> Generated GLE script to plot PDF & rendered" << RESET << endl ;


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

