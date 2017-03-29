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
// Pre digest data sed '/FIELD/d' sicv.dat


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
		cout << "    -bins" << "\t" << "    to set the number of kbins (e.g. ./a.out file.dat -bins 100) default bins=1000" << std::endl ;
		cout << BOLDRED << "    Optional flags:" << RESET << std::endl ;
		cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ;
		cout << "    -l" << "\t" << "    to set the number of layers for the iso-frequency (8 by default)" << std::endl ;  
		cout << "    -g" << "\t" << "    To directly generate a graph of the distribution" << std::endl ;
		cout << "    -d" << "\t" << "    To also output distributions at each size i.e D(K|S)" << std::endl ;  
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

	unsigned int Layers = 10 ;
	std::string Graph = "No" ;   // // Default graph no
	std::string Distributions = "No" ;   // // Default graph no
	
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
		if ( ( argv[k] == std::string("-layers") ) || ( argv[k] == std::string("-Layers") )  || ( argv[k] == std::string("-l") )  || ( argv[k] == std::string("-L") ) ) { Layers = atoi(argv[k+1]) ; }
		if ( ( argv[k] == std::string("-g") ) || ( argv[k] == std::string("-graph") ) || ( argv[k] == std::string("-G") )  || ( argv[k] == std::string("-gle") )  || ( argv[k] == std::string("-GLE") ) ) { Graph = "Yes" ; }
		if ( ( argv[k] == std::string("-d") ) || ( argv[k] == std::string("-D") )  || ( argv[k] == std::string("-distributions") ) ) { Distributions = "Yes" ; }
	}

	cout << YELLOW << "    -> Iso-frequency layers set to: " << BOLDYELLOW << Layers << RESET << endl ;
	
	
	if ( Graph == "Yes" ) 
	{
		cout << YELLOW << "    -> Graph option set to yes: " << BOLDYELLOW << RESET << endl ; 
	}
	if ( Distributions == "Yes" ) 
	{
		cout << YELLOW << "    -> Conditional distributions option set to yes: " << BOLDYELLOW << RESET << endl ; 
	}
	
	// Count execution time
	int start_s=clock();
	
	// Files to store data
	ofstream Histogram ;
	Histogram.open ("2DHistogram.dat", ios::out | ios::trunc); // All computed densities inside cylinders
	ofstream PDF ;
	PDF.open ("2DProbDenFunc.dat", ios::out | ios::trunc); // Number of sea atoms inside cylinders

	ofstream GLE_DSK ;
	GLE_DSK.open ("DSK.gle", ios::out | ios::trunc); // File to generate the script to plot DSK

	ofstream SingleFileDKS ;
	SingleFileDKS.open ("SingleFileDKS.dat", ios::out | ios::trunc); // Number of sea atoms inside cylinders
	
	std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
	

	cout << YELLOW << "    -> Processing file: " << BOLDYELLOW << File << RESET << endl ;
	
	


	// BEGIN Read Size, S and Connectivity, K values into vectors. 
	std::ifstream InputFile ;
	InputFile.open( File.c_str(), ios::in );
	std::string line ;				// variable string to read the line
	unsigned int element ;
	double v, w, x, y, z ;

	std::vector<double> SVector ;
	std::vector<double> KVector ;
	std::vector<double> HVector ;

	
	while (getline(InputFile, line))
	{
		if (line.length() > 2)
		{
			std::stringstream aa(line) ;
			aa >> v >> w >> x >> y >> z;
			KVector.push_back (v) ;
			SVector.push_back (w) ;
			HVector.push_back (x) ;
		}
	}
	InputFile.close() ;
	// END Read Size, S and Connectivity, K values into vectors.



	// BEGIN Max value of S, K, and H
	double Smaxval, Sminval, Kmaxval, Kminval, Hmaxval, Hminval ;
	Smaxval = *max_element(SVector.begin(),SVector.end()) ;
        Sminval = *min_element(SVector.begin(),SVector.end()) ;
	Kmaxval = *max_element(KVector.begin(),KVector.end()) ;
        Kminval = *min_element(KVector.begin(),KVector.end()) ;
	Hmaxval = *max_element(HVector.begin(),HVector.end()) ;
        Hminval = *min_element(HVector.begin(),HVector.end()) ;
	// END Max value of S and K


//	cout << YELLOW << "    -> Detected " << BOLDYELLOW << SVector.size () << RESET << YELLOW << " s data points" << RESET << endl ;
//	cout << YELLOW << "    -> Detected " << BOLDYELLOW << KVector.size () << RESET << YELLOW << " k data points" << RESET << endl ;
	cout << YELLOW << "    -> Detected " << BOLDYELLOW << KVector.size () << RESET << YELLOW << " data sites on the grid" << RESET << endl ;

	cout << BLUE  << "       Size Minimum value = " << BOLDBLUE  << Sminval << RESET << endl ;
	cout << BLUE  << "       Size Maximum value = " << BOLDBLUE  << Smaxval << RESET << endl ;
	cout << BLUE  << "       Connectivity Minimum value = " << BOLDBLUE  << Kminval << RESET << endl ;
	cout << BLUE  << "       Connectivity Maximum value = " << BOLDBLUE  << Kmaxval << RESET << endl ;
	cout << BLUE  << "       Histogram Minimum value = " << BOLDBLUE  << Hminval << RESET << endl ;
	cout << BLUE  << "       Histogram Maximum value = " << BOLDBLUE  << Hmaxval << RESET << endl ;

	


	// BEGIN Frequency matrix to store the 2D histogram
	unsigned int Sbins = 100 ;
	unsigned int Kbins = 2250 ;

	cout << YELLOW << "    -> Number of size bins set to: " << BOLDYELLOW << Sbins << RESET << endl ;
	cout << YELLOW << "    -> Number of connectivity degree bins set to: " << BOLDYELLOW << Kbins << RESET << endl ;		

	double KInterval = (Kmaxval-Kminval)/Kbins ;
	double SInterval = (Smaxval-Sminval)/Sbins ;

	cout << YELLOW << "    -> K interval: " << BOLDYELLOW << KInterval << RESET << endl ;
	cout << YELLOW << "    -> S interval: " << BOLDYELLOW << SInterval << RESET << endl ;
	
	std::vector< std::vector<double> > Frequency ;
	Frequency.resize(Sbins+1) ;
	for ( int i = 0; i < Sbins+1; ++i ) { Frequency[i].resize(Kbins+1) ; }

	for ( int i = 0; i < Sbins+1; ++i ) 
	{ 
		for ( int j = 0; j < Kbins+1; ++j ) 
		{
			Frequency[i][j] = 0.0 ;
			if ( HVector[i*(Kbins+1)+j] > 0.0 ) 
			{ 
				Frequency[i][j] =HVector[i*(Kbins+1)+j] ;
//				cout << i*(Kbins+1)+j+1 << " " << i << " " << j << " " <<  HVector[i*(Kbins+1)+j] << endl ;
			}
		}
	}
	std::cout << YELLOW << "    -> Frequency histogram stored " << RESET << endl ;
	//END Frequency matrix to store the 2D histogram



	// BEGIN Max and Min of the 2D array Frequency
	double MaX= Frequency[0][0] ;
	double MiN= Frequency[0][0] ;
	for ( int i = 0; i < Sbins+1; ++i )
	{
		for ( int j = 0; j < Kbins+1; ++j )
		{
			if ( Frequency[i][j] > MaX ) { MaX = Frequency[i][j] ; }
			if ( Frequency[i][j] < MiN ) { MiN = Frequency[i][j] ; }
		}
	}
	cout << BLUE  << "       Max frequency: " << BOLDBLUE  << MaX << RESET << endl ;
	cout << BLUE  << "       Min frequency: " << BOLDBLUE  << MiN << RESET << endl ;
	// END Max and Min of the 2D array Frequency




	// BEGIN Headers for GLE script to plot D(S;K)
	GLE_DSK << "include \"color.gle\"" << std::endl ;
	GLE_DSK << "size 17 10" << std::endl ;
	GLE_DSK << "sub Kmax x" << std::endl ;
	GLE_DSK << "\t" << "return x*(x-1)" << std::endl ;
	GLE_DSK << "end sub" << std::endl ;
	GLE_DSK << "sub Kmin x" << std::endl ;
	GLE_DSK << "\t" << "return 2*(x-2)+2" << std::endl ;
	GLE_DSK << "end sub" << std::endl ;
	GLE_DSK << "Layers = " << Layers << std::endl ;
	GLE_DSK << "set texlabels 1" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "begin graph" << std::endl ;
	GLE_DSK << "\tsize 11 8" << std::endl ;
	GLE_DSK << "\txtitle \"Size, $S$\"" << std::endl ;
	GLE_DSK << "\tytitle \"Connectivity degree, $K$\"" << std::endl ;
	// END Headers for GLE script to plot D(S;K)




	// BEGIN Files to store data by layers
	std::cout << YELLOW << "    -> Layers for heat map plot equal to " << RESET << BOLDYELLOW << Layers << RESET << endl ;
	double LimitDown ;
	double LimitUp ;
	cout << BLUE  << "       Intervals are: " << RESET << endl ;
	cout << BLUE  << "       " ;
	for ( int k = 0; k < Layers; ++k )
	{
		int Control = 0 ;

		LimitDown = k*(MaX-MiN)/Layers ;
		LimitUp = (k+1)*(MaX-MiN)/Layers ;
		std::cout << "[" << LimitDown << "," << LimitUp << "]  " ;

		// Naming different layer levels files to generate the isomap
		std::ostringstream ss;
                std::ofstream LayerFile;
		if (   k+1 <= 9 ) { ss << "Layer_no_000" << k+1 << ".dat" ;}
		if ( ( k+1 > 9 ) && ( k+1 <= 99 ) ) { ss << "Layer_no_00" << k+1 << ".dat" ;}
		if ( ( k+1 > 99 ) && ( k+1 <= 999 ) ) { ss << "Layer_no_0" << k+1 << ".dat" ;}
		if ( ( k+1 > 999 ) && ( k+1 <= 9999 ) ) { ss << "Layer_no_" << k+1 << ".dat" ;}
		
		LayerFile.open(ss.str().c_str());

		for ( int i = 0; i < Sbins+1; ++i )
		{
			for ( int j = 0; j < Kbins+1; ++j )
			{
				if ( ( Frequency[i][j] > LimitDown ) && ( Frequency[i][j] <= LimitUp ) ) 
				{
					LayerFile << SVector[i*(Kbins+1)+j] << "    " << KVector[i*(Kbins+1)+j] << "    " << Frequency[i][j] << std::endl ; // The bins are stored but the interval must be outputed to have real K-Space values
					Control++ ;
					if ( Control == 1 ) // To add this line only once and not repeat d1 d1 d1 in the loop
					{
						GLE_DSK << "\tdata " << ss.str().c_str() << " d" << k+1 << std::endl ;
						double zz = 1.0*k/(1.0*Layers-1.0) ;
						GLE_DSK << "\td" << k+1 << " marker fsquare msize 0.07 color carles(" << zz << ")" << std::endl ;
						GLE_DSK << std::endl ;
					}
				}
			}
		}

		LayerFile.close() ;
	}
	cout << RESET  << std::endl ;
	// END Files to store data by layers


	// BEGIN Feet for GLE script to plot D(S;K)
	GLE_DSK << "\tLayer = " << Layers << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\tlet d[Layer+1] = Kmax(x) from 2.0 to 55" << std::endl ;
	GLE_DSK << "\td[Layer+1] line color black lwidth 0.025 lstyle 9" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\tlet d[Layer+2] = Kmin(x) from 2.0 to 55" << std::endl ;
	GLE_DSK << "\td[Layer+2] line color black lwidth 0.025 lstyle 0" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\tdata Likely_SK_path.dat d[Layer+3]" << std::endl ;
	GLE_DSK << "\td[Layer+3] line color seagreen lwidth 0.025 lstyle 0" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\tdata Expected_SK_path.dat d[Layer+4]=c1,c2" << std::endl ;
	GLE_DSK << "\td[Layer+4] line color orange lwidth 0.025 lstyle 0" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\tdata Expected_SK_path.dat d[Layer+5]=c1,c5" << std::endl ;
	GLE_DSK << "\td[Layer+5] line color gray lwidth 0.025 lstyle 9" << std::endl ;
	GLE_DSK << "\tdata Expected_SK_path.dat d[Layer+6]=c1,c6" << std::endl ;
	GLE_DSK << "\td[Layer+6] line color gray lwidth 0.025 lstyle 9" << std::endl ;
	GLE_DSK << std::endl ;
//	GLE_DSK << "xaxis min 1.5 max 56  log format \"sci 0 10\"" << std::endl ;
//	GLE_DSK << "yaxis min 1.0 max 3500" << std::endl ;

	GLE_DSK << "\txaxis min 1.5 max 56" << std::endl ;
	GLE_DSK << "\tyaxis min 1.0 max 3500 log format \"sci 0 10\"" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "\txplaces 2 3 4 5 6 7 8 9 15 20 30 40 50 55" << std::endl ;
	GLE_DSK << "\txnames \"2\" \"3\" \"4\" \"5\" \"6\" \"7\" \"8\" \"9\" \"15\" \"20\" \"30\" \"40\" \"50\" \"55\"" << std::endl ;
	GLE_DSK << "end graph" << std::endl ;
	GLE_DSK << std::endl ;
	GLE_DSK << "set hei 0.3" << std::endl ;
	GLE_DSK << "!amove xg(xgmax)+0.25 yg(ygmin)" << std::endl ;
//	GLE_DSK << "!color_range_vertical zmin 0 zmax 1 zstep 0.25 pixels Layers palette carles format \"fix 2\"" << std::endl ;
	GLE_DSK << "amove xg(xgmin) yg(ygmax)+0.5" << std::endl ;
	GLE_DSK << "color_range_horizontal zmin 0 zmax 1 zstep 0.25 pixels Layers palette carles format \"fix 2\"" << std::endl ;
	GLE_DSK << "amove xg(0.5*(xgmax+xgmin)) yg(ygmax)+1.15" << std::endl ;
	GLE_DSK << "tex \"$\\displaystyle \\log \\mathcal{D}(S;K)$\"" << std::endl ;
	GLE_DSK << "begin key" << std::endl ;
	GLE_DSK << "pos br" << std::endl ;
	GLE_DSK << "nobox" << std::endl ;
	GLE_DSK << "line color black lwidth 0.05 lstyle 9 text \"$K_{\\rm max}(S)$\"" << std::endl ;
	GLE_DSK << "line color black lwidth 0.05 text \"$K_{\\rm min}(S)$\"" << std::endl ;
	GLE_DSK << "line color seagreen lwidth 0.05 text \"$\\max\\left[D(K|S)\\right]$\"" << std::endl ;
	GLE_DSK << "line color orange lwidth 0.05 text \"$\\left<K\\right>$\"" << std::endl ;
	GLE_DSK << "end key" << std::endl ;

//	GLE_DSK << "begin key" << std::endl ;
//	GLE_DSK << "pos tl" << std::endl ;
//	GLE_DSK << "nobox" << std::endl ;
//	GLE_DSK << "text \"Realizations=1, 4ns\"" << std::endl ;
//	GLE_DSK << "end key" << std::endl ;

	GLE_DSK << "set hei 0.3" << std::endl ;
	GLE_DSK << "amove xg(3) yg(0.4)" << std::endl ;
	GLE_DSK << "text Embryo" << std::endl ;
	GLE_DSK << "amove xg(53) yg(0.4)" << std::endl ;
	GLE_DSK << "text Mature" << std::endl ;

	GLE_DSK << "set hei 0.3" << std::endl ;
	GLE_DSK << "set color black" << std::endl ;
	GLE_DSK << "amove xg(21) yg(20)" << std::endl ;
	GLE_DSK << "text Minimally-connected" << std::endl ;
	GLE_DSK << "amove xg(21) yg(1500)" << std::endl ;
	GLE_DSK << "text Fully-connected" << std::endl ;
	GLE_DSK << "set color black" << std::endl ;

	GLE_DSK << std::endl ;
	GLE_DSK << "! Z goes from 0 to 1" << std::endl ;
	GLE_DSK << "sub carles z" << std::endl ;
	GLE_DSK << "\t" << "! a custom palette ranging from white, yellow, red, black" << std::endl ;
	GLE_DSK << "\t" << "local rr = 0" << std::endl ;
	GLE_DSK << "\t" << "local gg = 0" << std::endl ;
	GLE_DSK << "\t" << "local bb = 0" << std::endl ;
	GLE_DSK << "\t" << "! RED" << std::endl ;
	GLE_DSK << "\t" << "rr = (1-z)^0.5" << std::endl ;
	GLE_DSK << "\t" << "! GREEN" << std::endl ;
	GLE_DSK << "\t" << "gg = 0" << std::endl ;
	GLE_DSK << "\t" << "! BLUE" << std::endl ;
	GLE_DSK << "\t" << "bb = (z-300/500)^2/(300/500)^2" << std::endl ;
	GLE_DSK << "\t" << "return rgb(rr,gg,bb)" << std::endl ;
	GLE_DSK << "end sub" << std::endl ;
	system("gpdf DSK.gle") ; // Notice that: (1) gle needs to be install. (2) This is my own command. (3) Otherwise gle -d pdf DSK.gle
//	system("rm Layer_no_*.dat") ; // Erase anoying layer files
	// END Feet for GLE script to plot D(S;K)





	// BEGIN D(K|S): Conditional probability for each size. Each size in one file, and max probability path over space <K,S>.
	if ( Distributions == "Yes" ) 
	{	
		std::cout << YELLOW << "    -> Storing conditional probability density for each of the " << RESET << BOLDYELLOW << Sbins-1 << " sizes " << RESET << endl ;
		std::vector<double> Ssection ;
		ofstream MAXPPATH ;
		MAXPPATH.open ("Likely_SK_path.dat", ios::out | ios::trunc); // All computed densities inside cylinders

		ofstream EXPECTEDPATH ;
		EXPECTEDPATH.open ("Expected_SK_path.dat", ios::out | ios::trunc); // All computed densities inside cylinders
		EXPECTEDPATH << "!S" << "\t" << "<K>" << "\t" << "<K^2>" << "\t" << "STDK" << "\t" << "<K>+STDK" << "\t" << "<K>-STDK" << std::endl ;

		
		for ( int ns = 1; ns < Sbins+1 ; ++ns )
		{
			// Naming different size distributions
			std::ostringstream dd;
			std::ofstream K_PDF_at_S;
			if (   ns <= 9 ) { dd << "DKatS_no_000" << ns << ".dat" ;}
			if ( ( ns > 9 ) && ( ns <= 99 ) ) { dd << "DKatS_no_00" << ns << ".dat" ;}
			if ( ( ns > 99 ) && ( ns <= 999 ) ) { dd << "DKatS_no_0" << ns << ".dat" ;}
			if ( ( ns > 999 ) && ( ns <= 9999 ) ) { dd << "DKatS_no_" << ns << ".dat" ;}
		
			K_PDF_at_S.open(dd.str().c_str());	

			
			
			// BEGIN Normalization integral
			double IntegralDKS = 0.0 ;

			for ( int nk = 0; nk < Kbins+1 ; ++nk ) { IntegralDKS = IntegralDKS + Frequency[ns][nk]*KInterval ; }
//			cout << "Integral= " << IntegralDKS << endl ;

			// END Normalization integral

			// BEGIN Output normalized distributions only values different from zero
			double LikelyPathK = 0.0 ;
			unsigned int nspath ;
			unsigned int nkpath ;

			for ( int nk = 0; nk < Kbins+1 ; ++nk )
			{
				if ( Frequency[ns][nk] != 0 )
				{
					K_PDF_at_S << KVector[nk] << "\t" << Frequency[ns][nk]/IntegralDKS << std::endl ;
					if ( ns > 2 )
					{
						SingleFileDKS << SVector [ns] << "\t" << KVector [nk] << "\t" << Frequency[ns][nk]/IntegralDKS << std::endl ; // Storing D(K|S)
					}
				}


				if ( Frequency[ns][nk] > LikelyPathK ) 
				{ 
					LikelyPathK = Frequency[ns][nk] ; 
					nspath = ns ;
					nkpath = nk ;
				} // Detecting the max value
			}
			K_PDF_at_S.close () ;

			MAXPPATH << SVector[nspath*(Kbins+1)+nkpath] << "\t" << KVector[nspath*(Kbins+1)+nkpath] << "\t" << LikelyPathK << std::endl ;

			SingleFileDKS << std::endl ; // space between sizes
			// END Output distributions


			// BEGIN Maxpath max[D(K|S)], and Expected path <K>
			double AVK = 0.0 ;
			double AVK2 = 0.0 ;
			for ( int nk = 0; nk < Kbins+1 ; ++nk ) 
			{
//				if ( ( Frequency[ns][nk] == LikelyPathK ) && ( ns > 2 ) ) 
//				{
//					MAXPPATH << ns << "\t" << SVector[ns] << "\t" << KVector[nk] << std::endl ; 
//				}

				AVK = AVK + KVector[ns*(Kbins+1)+nk]*Frequency[ns][nk]/IntegralDKS*KInterval ; // <K>= \int_{Kmin}^{Kmax} K D(K|S) dK
				AVK2 = AVK2 + KVector[ns*(Kbins+1)+nk]*KVector[ns*(Kbins+1)+nk]*Frequency[ns][nk]/IntegralDKS*KInterval ; // <K>= \int_{Kmin}^{Kmax} K^2 D(K|S) dK
			}

			// BEGIN Standard deviation
			double STDK2 = 0.0 ;
			double STDK ;
			for ( int nk = 0; nk < Kbins ; ++nk ) 
			{
				STDK2 = STDK2 + pow(KVector[ns*(Kbins+1)+nk]-AVK,2.0)*Frequency[ns][nk]/IntegralDKS ;
			}
			STDK = sqrt(STDK2) ;
			// END Standard deviation
			
			EXPECTEDPATH << (ns-1)*SInterval << "\t" << AVK << "\t" << AVK2 << "\t" << STDK << "\t" << AVK+STDK << "\t" << AVK-STDK << std::endl ; 

			// END Maxpath max[D(K|S)], and Expected path <K>
		} // ns Size loop ends
		MAXPPATH.close () ;
		EXPECTEDPATH.close () ;
		SingleFileDKS.close () ;
	}
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

