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
	std::cout << BOLDYELLOW << "          '_) (_`         2D FREE ENERGY PLOT           " << RESET << std::endl ;
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

	unsigned int Kbins = 1000 ;		// Default Number of Kbins 
	unsigned int Layers = 8 ;
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
	}

	cout << YELLOW << "    -> Iso-frequency layers set to: " << BOLDYELLOW << Layers << RESET << endl ;
	cout << YELLOW << "    -> Number of connectivity degree bins set to: " << BOLDYELLOW << Kbins << RESET << endl ;		
	
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
	ofstream Energy ;
	Energy.open ("Fes.gle", ios::out | ios::trunc); // File to generate the script to plot DSK
	
	std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
	

	cout << YELLOW << "    -> Processing file: " << BOLDYELLOW << File << RESET << endl ;
	
	
	// BEGIN Read cv1, cv2, Energy 
	std::ifstream InputFile ;
	InputFile.open( File.c_str(), ios::in );
	std::string line ;				// variable string to read the line
	unsigned int element ;
	double x, y, z, v, w ;

	std::vector<double> Cv1Vector ;
	std::vector<double> Cv2Vector ;
	std::vector<double> EnergyVector ;

	while (getline(InputFile, line))
	{

		if (line.length() > 5)
		{		
			std::stringstream aa(line) ;
			aa >> x >> y >> z >> v >> w ;
			Cv1Vector.push_back (x) ;
			Cv2Vector.push_back (y) ;
			EnergyVector.push_back (z) ;
//			std::cout << x << " " << y << " " << z << std::endl ;
		}
	}
	InputFile.close() ;
	// END Read cv1, cv2, Energy 



	// BEGIN MaxMin values
	double Cv1Maxval, Cv1Minval, Cv2Maxval, Cv2Minval, EnergyMaxval, EnergyMinval ;
	Cv1Maxval = *max_element(Cv1Vector.begin(),Cv1Vector.end()) ;
        Cv1Minval = *min_element(Cv1Vector.begin(),Cv1Vector.end()) ;
	Cv2Maxval = *max_element(Cv2Vector.begin(),Cv2Vector.end()) ;
        Cv2Minval = *min_element(Cv2Vector.begin(),Cv2Vector.end()) ;
	EnergyMaxval = *max_element(EnergyVector.begin(),EnergyVector.end()) ;
        EnergyMinval = *min_element(EnergyVector.begin(),EnergyVector.end()) ;
	// END MaxMin values


	cout << YELLOW << "    -> Detected " << BOLDYELLOW << EnergyVector.size () << RESET << YELLOW << " energy data points" << RESET << endl ;

	cout << BLUE  << "       Cv1 Minimum value = " << BOLDBLUE  << Cv1Minval << RESET << endl ;
	cout << BLUE  << "       Cv1 Maximum value = " << BOLDBLUE  << Cv1Maxval << RESET << endl ;
	cout << BLUE  << "       Cv2 Minimum value = " << BOLDBLUE  << Cv2Minval << RESET << endl ;
	cout << BLUE  << "       Cv2 Maximum value = " << BOLDBLUE  << Cv2Maxval << RESET << endl ;
	cout << BLUE  << "       Energy Minimum value = " << BOLDBLUE  << EnergyMinval << RESET << endl ;
	cout << BLUE  << "       Energy Maximum value = " << BOLDBLUE  << EnergyMaxval << RESET << endl ;

	


	// BEGIN Headers for GLE script to plot FES(Cv1,Cv2)
	Energy << "include \"color.gle\"" << std::endl ;
	Energy << "size 17 10" << std::endl ;
	Energy << "sub Kmax x" << std::endl ;
	Energy << "\t" << "return x*(x-1)" << std::endl ;
	Energy << "end sub" << std::endl ;
	Energy << "sub Kmin x" << std::endl ;
	Energy << "\t" << "return 2*(x-2)+2" << std::endl ;
	Energy << "end sub" << std::endl ;
	Energy << "Layers = " << Layers << std::endl ;
	Energy << "set texlabels 1" << std::endl ;
	Energy << std::endl ;
	Energy << "begin graph" << std::endl ;
	Energy << "size 11 8" << std::endl ;
	Energy << "xtitle \"Size, $S$\"" << std::endl ;
	Energy << "ytitle \"Connectivity degree, $K$\"" << std::endl ;

	// END Headers for GLE script to plot FES(Cv1,Cv2)



	// BEGIN Files to store data by layers
	std::cout << YELLOW << "    -> Layers for heat map plot equal to " << RESET << BOLDYELLOW << Layers << RESET << endl ;
	unsigned int LimitDown ;
	unsigned int LimitUp ;
	cout << BLUE  << "       Intervals are: " << RESET << endl ;
	cout << BLUE  << "       " ;
	for ( int k = 0; k < Layers; ++k )
	{
		int Control = 0 ;

		LimitDown = k*(EnergyMaxval-EnergyMinval)/Layers+EnergyMinval ;
		LimitUp = (k+1)*(EnergyMaxval-EnergyMinval)/Layers+EnergyMinval ;
		std::cout << "[" << LimitDown << "," << LimitUp << "]  ";

		// Naming different layer levels files to generate the isomap
		std::ostringstream ss;
                std::ofstream LayerFile;
		if (   k+1 <= 9 ) { ss << "eLayer_no_000" << k+1 << ".dat" ;}
		if ( ( k+1 > 9 ) && ( k+1 <= 99 ) ) { ss << "eLayer_no_00" << k+1 << ".dat" ;}
		if ( ( k+1 > 99 ) && ( k+1 <= 999 ) ) { ss << "eLayer_no_0" << k+1 << ".dat" ;}
		if ( ( k+1 > 999 ) && ( k+1 <= 9999 ) ) { ss << "eLayer_no_" << k+1 << ".dat" ;}
		
		LayerFile.open(ss.str().c_str());

		for ( int i = 0; i < EnergyVector.size (); ++i )
		{
			if ( ( EnergyVector[i] > LimitDown ) && (EnergyVector[i] <= LimitUp ) ) 
			{
				LayerFile << Cv2Vector [i] << "\t" << Cv1Vector [i] << "\t" << EnergyVector [i] << std::endl ; // The bins are stored but the interval must be outputed to have real K-Space values
				Control++ ;
				if ( Control == 1 ) // To add this line only once and not repeat d1 d1 d1 in the loop
				{
					Energy << "data " << ss.str().c_str() << " d" << k+1 <<"=c1,c2" << std::endl ;
					Energy << "Layer = " << k+1 << std::endl ;
					Energy << "d[Layer] marker fsquare msize 0.07 color rgb((Layer-1)^0.5/(Layers-1)^0.5+(Layers-Layer-1)^10/(Layers-1)^10,(Layers-Layer-1)^3/(Layers-1)^3,(Layers-Layer-1)^5/(Layers-1)^5)" << std::endl ;
					Energy << std::endl ;
				}
			}	
		}

		LayerFile.close() ;
	}
	cout << RESET  << std::endl ;
	// END Files to store data by layers


	// BEGIN Feet for GLE script to plot FES(Cv1,Cv2)
	Energy << "let d[Layer+1] = Kmax(x) from 2.0 to 55" << std::endl ;
	Energy << "d[Layer+1] line color black lwidth 0.025 lstyle 9" << std::endl ;
	Energy << "let d[Layer+2] = Kmin(x) from 2.0 to 55" << std::endl ;
	Energy << "d[Layer+2] line color black lwidth 0.025 lstyle 0" << std::endl ;
	Energy << "!data Likely_SK_path.dat d[Layer+3]" << std::endl ;
	Energy << "!d[Layer+3] line color seagreen lwidth 0.025 lstyle 0" << std::endl ;
	Energy << "!data Expected_SK_path.dat d[Layer+4]=c1,c2" << std::endl ;
	Energy << "!d[Layer+4] line color orange lwidth 0.025 lstyle 0" << std::endl ;

	Energy << "xaxis min 0.0 max 60" << std::endl ;
//	Energy << "yaxis min 1.0 max 5000 log format \"sci 0 10\"" << std::endl ;
	Energy << "yaxis min -300.0 max 3000" << std::endl ;

	Energy << "xplaces 2 3 4 5 6 7 8 9 15 20 30 40 50 55" << std::endl ;
	Energy << "xnames \"2\" \"3\" \"4\" \"5\" \"6\" \"7\" \"8\" \"9\" \"15\" \"20\" \"30\" \"40\" \"50\" \"55\"" << std::endl ;
	Energy << "end graph" << std::endl ;
	Energy << "set hei 0.3" << std::endl ;
	Energy << "!amove xg(xgmax)+0.25 yg(ygmin)" << std::endl ;
	Energy << "!color_range_vertical zmin 0 zmax 1 zstep 0.25 pixels Layers palette carles format \"fix 2\"" << std::endl ;
	Energy << "amove xg(xgmin) yg(ygmax)+0.5" << std::endl ;
	double Zstep = (EnergyMaxval - EnergyMinval)/5.0 ;
	Energy << "color_range_horizontal zmin " << EnergyMinval << " zmax " << EnergyMaxval << " zstep " << Zstep << " pixels Layers palette carles format \"fix 2\"" << std::endl ;
	Energy << "amove xg(0.5*(xgmax+xgmin)) yg(ygmax)+1.15" << std::endl ;
	Energy << "tex \"Free energy, $\\displaystyle \\mathcal{F}(S;K) [{\\rm eV}]$\"" << std::endl ;

	Energy << "begin key" << std::endl ;
	Energy << "pos tl" << std::endl ;
	Energy << "nobox" << std::endl ;
	Energy << "line color black lwidth 0.05 lstyle 9 text \"$K_{\\rm max}(S)$\"" << std::endl ;
	Energy << "line color black lwidth 0.05 text \"$K_{\\rm min}(S)$\"" << std::endl ;
//	Energy << "line color seagreen lwidth 0.05 text \"$\\max\\left[D(K|S)\\right]$\"" << std::endl ;
//	Energy << "line color orange lwidth 0.05 text \"$\\left<K\\right>$\"" << std::endl ;
	Energy << "end key" << std::endl ;

//	Energy << "begin key" << std::endl ;
//	Energy << "pos tl" << std::endl ;
//	Energy << "nobox" << std::endl ;
//	Energy << "text \"Realizations=1, 4ns\"" << std::endl ;
//	Energy << "end key" << std::endl ;

	Energy << "!set hei 0.3" << std::endl ;
	Energy << "!begin key" << std::endl ;
	Energy << "!pos br" << std::endl ;
	Energy << "!nobox" << std::endl ;
	Energy << "!text \"T-clustering Metadynamics - NPT\"" << std::endl ;
	Energy << "!text \"Histogram over $5.0\\cdot 10^5$ data points\"" << std::endl ;
	Energy << "!end key" << std::endl ;

	Energy << "set hei 0.3" << std::endl ;
	Energy << "amove xg(3) yg(-700.4)" << std::endl ;
	Energy << "text Embryo" << std::endl ;
	Energy << "amove xg(53) yg(-700.4)" << std::endl ;
	Energy << "text Mature" << std::endl ;

	Energy << "set hei 0.3" << std::endl ;
	Energy << "set color black" << std::endl ;
	Energy << "amove xg(21) yg(-200)" << std::endl ;
	Energy << "text Minimally-connected" << std::endl ;
	Energy << "amove xg(21) yg(1500)" << std::endl ;
	Energy << "text Fully-connected" << std::endl ;
	Energy << "set color black" << std::endl ;


	Energy << "! Z goes from 0 to 1" << std::endl ;
	Energy << "sub carles z" << std::endl ;
	Energy << "\t" << "! a custom palette ranging from white, yellow, red, black" << std::endl ;
	Energy << "\t" << "local rr = 0" << std::endl ;
	Energy << "\t" << "local gg = 0" << std::endl ;
	Energy << "\t" << "local bb = 0" << std::endl ;
	Energy << "\t" << "! RED" << std::endl ;
	Energy << "\t" << "rr = (Layers*z)^0.5/(Layers-1)^0.5+(Layers-Layers*z)^10/(Layers-1)^10" << std::endl ;
	Energy << "\t" << "! GREEN" << std::endl ;
	Energy << "\t" << "gg = (Layers-Layers*z)^3/(Layers-1)^3" << std::endl ;
	Energy << "\t" << "! BLUE" << std::endl ;
	Energy << "\t" << "bb = (Layers-Layers*z)^5/(Layers-1)^5" << std::endl ;
	Energy << "\t" << "return rgb(rr,gg,bb)" << std::endl ;
	Energy << "end sub" << std::endl ;

	system("gpdf Fes.gle") ; // Notice that: (1) gle needs to be install. (2) This is my own command. (3) Otherwise gle -d pdf DSK.gle
	system("rm eLayer_no_*.dat") ; // Erase anoying layer files

	// END Feet for GLE script to plot FES(Cv1,Cv2)


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

