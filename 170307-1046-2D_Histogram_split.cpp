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
	std::cout << BOLDYELLOW << "    ____________________________________________________" << std::endl ;
	std::cout << BOLDYELLOW << "            _=_                                         " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          q(-_-)p                                       " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          '_) (_`         2D HISTOGRAM GENERATOR        " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017         " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                     " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    ____________________________________________________" << RESET << std::endl ;
	std::cout << endl ;

	// Check the number of arguments (1 means only the name of the program => No argument)
	if ( argc == 1 )
	{
		cout << "\t Wrong usage. You should execute:" << endl ;
		cout << BOLDRED << "\t " << argv[0] << " [File to analyze.dat] -kbins [number]" << RESET << endl ;
		cout << " " << endl ;
		return (0) ;
	}


	if ( ( argv[1] == std::string("-h") ) || ( argv[1] == std::string("-HELP") ) || ( argv[1] == std::string("-H") ) || ( argv[1] == std::string("-help") ) )
	{ 
		cout  << BOLDRED << "    HELP:" << RESET << std::endl ;
		cout << "    Description of the program:" << std::endl ;
		cout << "    -------------------------------------------------------------------------------------------------------------------" << std::endl ;
		cout << "    (1) Generates a 2D histogram from the at least two column file column of a file containing real data: D(X,Y)" << std::endl ;
		cout << "        [Column can be changed and also addapted to integer data]" << std::endl ;
		cout << "    (2) Outputs the different iso-frequency layers for an easy plot (The number of layers can be chosen, by default 8)." << std::endl ;
		cout << "    (3) Generates the conditional probability for each value of the first random variable: D(Y|X)" << std::endl ;
		cout << "    (4) Calculates the most likely path over the 2D space of random variables: Y(X)" << std::endl ;
		cout << "    -------------------------------------------------------------------------------------------------------------------" << std::endl ;
		cout << BOLDRED << "    Execution: ./a.out file.dat [+flags]" << RESET << std::endl ; 
		cout << BOLDRED << "    Mandatory flags:" << RESET << std::endl ; 
		cout << "    -bins" << "\t" << "    to set the number of kbins (e.g. ./a.out file.dat -bins 100) default bins=100" << std::endl ;
		cout << BOLDRED << "    Optional flags:" << RESET << std::endl ;
		cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ;
		cout << "    -l" << "\t" << "    to set the number of layers for the iso-frequency" << std::endl ;  
		cout << std::endl ;
		return (0) ;
	}
	
	// Check if the file exists
	ifstream file(argv[1]) ;
	if (!file)
	{
    	std::cout << BOLDRED <<"    -> ERROR: File " << argv[1] << " does not exist. ABORTING" << RESET << std::endl ;
    	std::cout << std::endl ;
		abort () ;
	}
	file.close() ;
	
	std::cout << YELLOW << "    -> File " << BOLDYELLOW << argv[1] << RESET << YELLOW << " found" << RESET << std::endl ;

	unsigned int Kbins = 1000 ;		// Default Number of Kbins 
	unsigned int Layers = 8 ;
	
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
			cout << "    -bins" << "\t" << "    to set the number of kbins (e.g. ./a.out file.dat -bins 100) default bins=100" << std::endl ;
			cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
			cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ; 
			cout << std::endl ;
			return (0) ;
		}
		if ( ( argv[k] == std::string("-kbins") ) || ( argv[k] == std::string("-kbin") )  || ( argv[k] == std::string("-kb") )  || ( argv[k] == std::string("-b") ) ) { Kbins = atoi(argv[k+1]) ; }
		if ( ( argv[k] == std::string("-layers") ) || ( argv[k] == std::string("-Layers") )  || ( argv[k] == std::string("-l") )  || ( argv[k] == std::string("-L") ) ) { Layers = atoi(argv[k+1]) ; }
//		if ( ( argv[k] == std::string("-gle") ) || ( argv[k] == std::string("-g") )  || ( argv[k] == std::string("-GLE") ) ) { Ly = atoi(argv[k+1]) ; }
	}

	cout << YELLOW << "    -> Iso-frequency layers set to: " << BOLDYELLOW << Layers << RESET << endl ;
	cout << YELLOW << "    -> Number of connectivity degree bins set to: " << BOLDYELLOW << Kbins << RESET << endl ;		
	
	double Smaxval, Sminval, Kmaxval, Kminval ;
	
	
	// Count execution time
	int start_s=clock();
	
	// Files to store data
	ofstream Histogram ;
	Histogram.open ("2DHistogram.dat", ios::out | ios::trunc); // All computed densities inside cylinders
	ofstream PDF ;
	PDF.open ("2DProbDenFunc.dat", ios::out | ios::trunc); // Number of sea atoms inside cylinders
	
	std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
	

	cout << YELLOW << "    -> Processing file: " << BOLDYELLOW << File << RESET << endl ;
	
	
	// BEGIN Read Size, S and Connectivity, K values into vectors. 
	std::ifstream InputFile ;
	InputFile.open( File.c_str(), ios::in );
	std::string line ;				// variable string to read the line
	unsigned int element ;
	double w, x, y, z ;

	std::vector<double> SVector ;
	std::vector<double> KVector ;

	while (getline(InputFile, line))
	{
		std::stringstream aa(line) ;
		aa >> w >> x >> y >> z ;
		SVector.push_back (x) ;
		KVector.push_back (z) ;
	}
	InputFile.close() ;
	// END Read Size, S and Connectivity, K values into vectors.


	// BEGIN Max value of S and K
	Smaxval = *max_element(SVector.begin(),SVector.end()) ;
        Sminval = *min_element(SVector.begin(),SVector.end()) ;
	Kmaxval = *max_element(KVector.begin(),KVector.end()) ;
        Kminval = *min_element(KVector.begin(),KVector.end()) ;
	// END Max value of S and K


	cout << YELLOW << "    -> Detected " << BOLDYELLOW << SVector.size () << RESET << YELLOW << " s data points" << RESET << endl ;
	cout << YELLOW << "    -> Detected " << BOLDYELLOW << KVector.size () << RESET << YELLOW << " k data points" << RESET << endl ;

	cout << BLUE  << "       Size Minimum value = " << BOLDBLUE  << Sminval << RESET << endl ;
	cout << BLUE  << "       Size Maximum value = " << BOLDBLUE  << Smaxval << RESET << endl ;
	cout << BLUE  << "       Connectivity Minimum value = " << BOLDBLUE  << Kminval << RESET << endl ;
	cout << BLUE  << "       Connectivity Maximum value = " << BOLDBLUE  << Kmaxval << RESET << endl ;




	// BEGIN Frequency matrix to generate the 2D histogram
	int Sbins = Smaxval+1 ;
	double KInterval = (Kmaxval-Kminval)/Kbins ;
	
	std::vector<std::vector<int> > Frequency;
	Frequency.resize(Sbins);
	for ( int i = 0; i < Sbins; ++i ) { Frequency[i].resize(Kbins) ; }
	// Frequency matrix initialization
	for ( int i = 0; i < Sbins; ++i ) 
	{ 
		for ( int j = 0; j < Kbins; ++j ) 
		{
			Frequency[i][j] = 0 ; 
		}
	}
	// END Frequency matrix to generate the 2D histogram


	

	// BEGIN Assigning values to the Frequency matrix
	double KLimitDown ;
	double KLimitUp ;
	for ( int i = 0; i < SVector.size () ; ++i )
	{
		int ns = static_cast<int>(SVector[i]); // partition 1 for Size
		for ( int nk = 0; nk < Kbins; ++nk ) 
		{
			KLimitDown = nk*KInterval ;
			KLimitUp = (nk+1)*KInterval ;
//			cout << "[" << KLimitDown << " " << KLimitUp << "]" << endl ;
			if ( ( KVector[i] > KLimitDown ) && ( KVector[i] <= KLimitUp ) ) 
			{
				Frequency[ns][nk]++ ;
			}
		}
	}
	std::cout << YELLOW << "    -> Frequency histogram built " << RESET << endl ;
	// END Assigning values to the Frequency matrix






	// BEGIN Max and Min of the 2D array Frequency
	unsigned int MaX= Frequency[0][0] ;
	unsigned int MiN= Frequency[0][0] ;
	for ( int i = 0; i < Sbins; ++i )
	{
		for ( int j = 0; j < Kbins; ++j )
		{
			if ( Frequency[i][j] > MaX ) { MaX = Frequency[i][j] ; }
			if ( Frequency[i][j] < MiN ) { MiN = Frequency[i][j] ; }
		}
	}
	cout << BLUE  << "       Max frequency: " << BOLDBLUE  << MaX << RESET << endl ;
	cout << BLUE  << "       Min frequency: " << BOLDBLUE  << MiN << RESET << endl ;
	// END Max and Min of the 2D array Frequency



	// BEGIN Files to store data by layers
	std::cout << YELLOW << "    -> Layers for heat map plot equal to " << RESET << BOLDYELLOW << Layers << RESET << endl ;
	unsigned int LimitDown ;
	unsigned int LimitUp ;
	cout << BLUE  << "       Intervals are: " << RESET << endl ;
	cout << BLUE  << "       " ;
	for ( int k = 0; k < Layers; ++k )
	{
		LimitDown = k*(MaX-MiN)/Layers ;
		LimitUp = (k+1)*(MaX-MiN)/Layers ;
		std::cout << "[" << LimitDown << "," << LimitUp << "]  ";

		// Naming different layer levels files to generate the isomap
		std::ostringstream ss;
                std::ofstream LayerFile;
		if (   k <= 9 ) { ss << "Layer_no_000" << k+1 << ".dat" ;}
		if ( ( k > 9 ) && ( k <= 99 ) ) { ss << "Layer_no_00" << k+1 << ".dat" ;}
		if ( ( k > 99 ) && ( k <= 999 ) ) { ss << "Layer_no_0" << k+1 << ".dat" ;}
		if ( ( k > 999 ) && ( k <= 9999 ) ) { ss << "Layer_no_" << k+1 << ".dat" ;}
		
		LayerFile.open(ss.str().c_str());

		for ( int i = 0; i < Sbins; ++i )
		{
			for ( int j = 0; j < Kbins; ++j )
			{
				if ( ( Frequency[i][j] > LimitDown ) && ( Frequency[i][j] <= LimitUp ) ) 
				{
					LayerFile << i*1.0 << "    " << j*KInterval+KInterval/2.0 << "    " << Frequency[i][j] << std::endl ; // The bins are stored but the interval must be outputed to have real K-Space values
				}
			}
		}

		LayerFile.close() ;
	}
	cout << RESET  << std::endl ;
	// END Files to store data by layers




	// BEGIN D(K|S): Conditional probability for each size. Each size in one file, and max probability path over space <K,S>.
	std::cout << YELLOW << "    -> Storing conditional probability density for each of the " << RESET << BOLDYELLOW << Sbins-1 << " sizes " << RESET << endl ;
	std::vector<double> Ssection ;
	ofstream MAXPPATH ;
	MAXPPATH.open ("Likely_SK_path.dat", ios::out | ios::trunc); // All computed densities inside cylinders
	
	for ( int ns = 1; ns < Sbins ; ++ns )
	{
		// Naming different size distributions
		std::ostringstream dd;
                std::ofstream K_PDF_at_S;
		if (   ns <= 9 ) { dd << "DKatS_no_000" << ns << ".dat" ;}
		if ( ( ns > 9 ) && ( ns <= 99 ) ) { dd << "DKatS_no_00" << ns << ".dat" ;}
		if ( ( ns > 99 ) && ( ns <= 999 ) ) { dd << "DKatS_no_0" << ns << ".dat" ;}
		if ( ( ns > 999 ) && ( ns <= 9999 ) ) { dd << "DKatS_no_" << ns << ".dat" ;}
		
		K_PDF_at_S.open(dd.str().c_str());

		unsigned int LikelyPathK = 0 ;
		
		for ( int nk = 0; nk < Kbins ; ++nk )
		{
			K_PDF_at_S << nk*KInterval+KInterval/2.0 << "\t" << Frequency[ns][nk] << std::endl ;

			if ( Frequency[ns][nk] > LikelyPathK ) { LikelyPathK = Frequency[ns][nk] ; }
		}
		K_PDF_at_S.close () ;
		
		for ( int nk = 0; nk < Kbins ; ++nk ) 
		{
			if ( ( Frequency[ns][nk] == LikelyPathK ) && ( ns > 2 ) ) 
			{
				MAXPPATH << ns << "\t" << nk*KInterval+KInterval/2.0 << std::endl ; 
				cout << nk << "    " << ns << "    " << nk*KInterval+KInterval/2.0 << std::endl ;
			}
		}	
	}
	MAXPPATH.close () ;
	// END D(K|S): Conditional probability for each size. Each size in one file, and max probability path over space <K,S>.







//	cout << YELLOW << "    -> Histogram generated " << RESET << endl ;
//	cout << BLUE  <<  "       Stored under name: " << BOLDBLUE  << "Histogram.dat" << RESET << endl ;
//	//Histogram << "! Position Value" << endl ;

//	for ( int i = 0; i < Sbins; ++i )
//	{
//		for ( int j = 0; j < Kbins; ++j )
//		{
//			Histogram << i << "    " << j << "    " << Frequency[i][j] << std::endl ; 
//		}
//		//Histogram << std::endl ;
//	}

////	double Integral = 0.0 ;
////	for ( int k = 0; k < bins; ++k )
////	{
////		Histogram << DX/2.0 + k*DX << "\t" << bin[k] << endl ;
////		// Integrating the histogram to normalize it:
////		Integral = Integral + DX*float(bin[k]) ;
////	}
////	cout << YELLOW << "    -> Histogram integrated to normalize " << RESET << endl ;
////	cout << BLUE  << "       Integral = " << BOLDBLUE  << Integral << RESET << endl ;

////	// GLE GRAPH HISTOGRAM
////	ofstream GLEHISTO ;
////	GLEHISTO.open ("Histogram.gle", ios::out | ios::trunc); // All computed densities inside cylinders
////	GLEHISTO << "size 12 8" << std::endl ;
////	GLEHISTO << "set texlabels 1" << std::endl ;
////	GLEHISTO << "begin graph" << std::endl ;
////	GLEHISTO << "title  \"Data Histogram\"" << std::endl ;
////	GLEHISTO << "xtitle \"Variable, $X$\"" << std::endl ;
////	GLEHISTO << "ytitle \"Frequency, $F(X)$\"" << std::endl ;
////	GLEHISTO << "data \"Histogram.dat\"" << std::endl ;
////	GLEHISTO << "bar d1 fill red" << std::endl ;
////	GLEHISTO << "end graph" << std::endl ;
////	GLEHISTO << "set hei 0.2" << std::endl ;
////	GLEHISTO << "begin key" << std::endl ;
////	GLEHISTO << "pos tr" << std::endl ;
////	GLEHISTO << "nobox" << std::endl ;
////	GLEHISTO << "text \" Data points = " << DataVector.size () << "\" " << std::endl ;
////	GLEHISTO << "text \" Min value = " << minval << "\" " << std::endl ;
////	GLEHISTO << "text \" Max value = " << maxval << "\" " << std::endl ;
////	GLEHISTO << "text \" Bins = " << bins << "\" " << std::endl ;
////	GLEHISTO << "text \" $\\displaystyle \\int_{min}^{max} F(X) dX =$ " << Integral << "\" " << std::endl ;
////	GLEHISTO << "end key" << std::endl ;
////	cout << YELLOW << "    -> Generated GLE script to plot histogram & rendered" << RESET << endl ;
////	// END GLE GRAPH HISTOGRAM

////	std::vector<double> BinNorm(bins) ;
////	for ( int k = 0; k < bins; ++k ) { BinNorm[k]=float(bin[k])/Integral ; }

////	Integral = 0.0 ;
////	for ( int k = 0; k < bins; ++k ) 
////	{ 
////		PDF << DX/2.0 + k*DX << "\t" << BinNorm[k] << endl ; 
////		Integral = Integral + DX*float(BinNorm[k]) ;
////	}
////	cout << YELLOW << "    -> Probability density function (PDF)" << RESET << endl ;
////	cout << BLUE  << "       Generated & stored under name: " << BOLDBLUE  << "ProbDenFunc.dat" << RESET << endl ;
////	cout << YELLOW << "    -> Checking normalization of the PDF" << RESET << endl ;
////	cout << BLUE  << "       Integral = " << BOLDBLUE  << Integral << RESET << endl ;

////	// GLE GRAPH PDF
////	ofstream GLEPDF ;
////	GLEPDF.open ("PDF.gle", ios::out | ios::trunc); // All computed densities inside cylinders
////	GLEPDF << "size 12 8" << std::endl ;
////	GLEPDF << "set texlabels 1" << std::endl ;
////	GLEPDF << "begin graph" << std::endl ;
////	GLEPDF << "title  \"Data Probability density function\"" << std::endl ;
////	GLEPDF << "xtitle \"Variable, $X$\"" << std::endl ;
////	GLEPDF << "ytitle \"PDF[$X$]\"" << std::endl ;
////	GLEPDF << "data \"ProbDenFunc.dat\"" << std::endl ;
////	GLEPDF << "d1 line color red" << std::endl ;
////	GLEPDF << "end graph" << std::endl ;
////	GLEPDF << "set hei 0.2" << std::endl ;
////	GLEPDF << "begin key" << std::endl ;
////	GLEPDF << "pos tr" << std::endl ;
////	GLEPDF << "nobox" << std::endl ;
////	GLEPDF << "text \" Data points = " << DataVector.size () << "\" " << std::endl ;
////	GLEPDF << "text \" Min value = " << minval << "\" " << std::endl ;
////	GLEPDF << "text \" Max value = " << maxval << "\" " << std::endl ;
////	GLEPDF << "text \" Bins = " << bins << "\" " << std::endl ;
////	GLEPDF << "end key" << std::endl ;

////	cout << YELLOW << "    -> Generated GLE script to plot histogram & rendered" << RESET << endl ;
////	// END GLE GRAPH PDF

////	cout << YELLOW << "    -> Generated GLE script to plot PDF & rendered" << RESET << endl ;


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

