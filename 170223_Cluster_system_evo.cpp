//
// This program produces a video from a xyz trajectory of LAMMPS
//
// Carles Trigureo 2016
// 
// Version: 160613
// 
// (1) Recognition of each frame
// (2) Writes a povray script
// (3) Renders the script
// (4) Generates a video
//
// Requires having povray installed and running from shell
//
// This is designed for only two types of atoms but can be easily extended adding 
// more atom types and colors associated (see if (element == 1) part of the code)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;


 int main()
    {
	std::ifstream InputFile( "traj_all_clean.xyz" ) ; // file where the extraction is performed
        std::ifstream InputFile1( "Cluster1_Ang.xyz" ) ; // file where the extraction is performed
	std::ifstream InputFile2( "Cluster2_Ang.xyz" ) ; // file where the extraction is performed
	std::ifstream InputFile3( "Cluster3_Ang.xyz" ) ; // file where the extraction is performed
        
        std::string line ;    // variable string to read the line
        
        unsigned int Frame_counter = 0 ;
    
        double Rgas = 2.5 ; // in Angstroms
        double Rliquid = 1.7 ; // in Angstroms	

	unsigned int Natoms ;
	unsigned int element ;
	double x, y, z ;
	unsigned int FrameCounter = 0 ;

	while( std::getline( InputFile, line ) )
	{
		std::stringstream aa(line) ; //process first line

		if (line.length() < 5) // maximum number of digits for the number of atoms is 5
		{
			aa >> Natoms ; // Gets the number of atoms in this specific frame (not constant anymore)
//			cout << "Natoms= " << Natoms << std::endl ;
//			cout << "Frame= " << FrameCounter << std::endl ;
			getline(InputFile, line) ; //process segunda línea comment line (sin hacer nada)

			// BEGIN Build a name for the different frames
			FrameCounter++ ;
			std::ostringstream ss;
			std::ofstream OutputFile;
			if ( FrameCounter <= 9)
			{
				ss << "frame_no_000" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::trunc);
			}

			if ( (FrameCounter > 9) && (FrameCounter <= 99))
			{
				ss << "frame_no_00" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::trunc);
			}

			if ( (FrameCounter > 99) && (FrameCounter <= 999))
			{
				ss << "frame_no_0" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::trunc);
			}

			if ( (FrameCounter > 999) && (FrameCounter <= 9999))
			{
				ss << "frame_no_" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::trunc);
			}
			// END Build a name for the different frames

			// BEGIN POVRAY header
			OutputFile << "// Creating POV-RAY Script to render\n";
			OutputFile << "\n";
			OutputFile << "#include \"colors.inc\"\n";
			OutputFile << "#include \"textures.inc\"\n";
			OutputFile << "#include \"textures.inc\"\n";
			OutputFile << "\n";
			OutputFile << "background{White}\n";
			OutputFile << "camera { up <0,1,0> right <1,0,0> location <0.0,0.0,85.0> look_at <0,0,0> angle 0 rotate <0,clock*360,0>}\n";
			OutputFile << "light_source { <0, 100,0> color White }\n";
			OutputFile << "light_source { <0,-100,0> color White }\n";
			OutputFile << "light_source { < 100,0,0> color White }\n";
			OutputFile << "light_source { <-100,0,0> color White }\n";
			OutputFile << "light_source { <0,0, 100> color White }\n";
			OutputFile << "light_source { <0,0,-100> color White }\n";    
			// END POVRAY header


			for (int i=0; i<Natoms; i++)
			{
				std::getline(InputFile, line);
				std::stringstream cc(line);
				cc >> element >> x >> y >> z ;
				if ( element == 1 ) { OutputFile << "sphere { <" << x << "," << y << "," << z << ">," << Rgas << " pigment { rgbt <0,0,1,0.7>} finish { phong 0.7 phong_size 20 }}" << std::endl ; }
				if ( element == 2 ) { OutputFile << "sphere { <" << x << "," << y << "," << z << ">," << Rliquid << " pigment { rgbt <1,0,0,0.7>} finish { phong 0.7 phong_size 20 }}" << std::endl ; }
			}
			OutputFile.close () ;
		}
	}
	InputFile.close() ;




	// 2nd file
	FrameCounter = 0 ;
	while( std::getline( InputFile1, line ) )
	{
		std::stringstream cc(line) ; //process first line

		if (line.length() < 5) // maximum number of digits for the number of atoms is 5
		{
			cc >> Natoms ; // Gets the number of atoms in this specific frame (not constant anymore)
//			cout << "Natoms= " << Natoms << std::endl ;
//			cout << "Frame= " << FrameCounter << std::endl ;
			getline(InputFile1, line) ; //process segunda línea comment line (sin hacer nada)

			// BEGIN Build the nema of the different povray files
			FrameCounter++ ;
			std::ostringstream ss;
			std::ofstream OutputFile;
			if ( FrameCounter <= 9)
			{
				ss << "frame_no_000" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 9) && (FrameCounter <= 99))
			{
				ss << "frame_no_00" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 99) && (FrameCounter <= 999))
			{
				ss << "frame_no_0" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 999) && (FrameCounter <= 9999))
			{
				ss << "frame_no_" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}
			// END Build the nema of the different povray files
			for (int i=0; i<Natoms; i++)
			{

				std::getline(InputFile1, line);
				std::stringstream bb(line);
				bb >> element >> x >> y >> z ;
				OutputFile << "sphere { <" << x << "," << y << "," << z << ">," << Rgas+0.01 << " pigment { rgbt <0,0,0,0>} finish { phong 0.7 phong_size 20 }}\n";
			}
			OutputFile.close () ;
		}
	}
	InputFile1.close() ;


	// 3rd file
	FrameCounter = 0 ;
	while( std::getline( InputFile2, line ) )
	{
		std::stringstream cc(line) ; //process first line

		if (line.length() < 5) // maximum number of digits for the number of atoms is 5
		{
			cc >> Natoms ; // Gets the number of atoms in this specific frame (not constant anymore)
//			cout << "Natoms= " << Natoms << std::endl ;
//			cout << "Frame= " << FrameCounter << std::endl ;
			getline(InputFile2, line) ; //process segunda línea comment line (sin hacer nada)

			// BEGIN Build the nema of the different povray files
			FrameCounter++ ;
			std::ostringstream ss;
			std::ofstream OutputFile;
			if ( FrameCounter <= 9)
			{
				ss << "frame_no_000" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 9) && (FrameCounter <= 99))
			{
				ss << "frame_no_00" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 99) && (FrameCounter <= 999))
			{
				ss << "frame_no_0" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 999) && (FrameCounter <= 9999))
			{
				ss << "frame_no_" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}
			// END Build the nema of the different povray files
			for (int i=0; i<Natoms; i++)
			{

				std::getline(InputFile2, line);
				std::stringstream bb(line);
				bb >> element >> x >> y >> z ;
				OutputFile << "sphere { <" << x << "," << y << "," << z << ">," << Rgas+0.01 << " pigment { rgbt <0.9,0.5,0.0,0>} finish { phong 0.7 phong_size 20 }}\n";
			}
			OutputFile.close () ;
		}
	}
	InputFile2.close() ;


// 3rd file
	FrameCounter = 0 ;
	while( std::getline( InputFile3, line ) )
	{
		std::stringstream cc(line) ; //process first line

		if (line.length() < 5) // maximum number of digits for the number of atoms is 5
		{
			cc >> Natoms ; // Gets the number of atoms in this specific frame (not constant anymore)
//			cout << "Natoms= " << Natoms << std::endl ;
//			cout << "Frame= " << FrameCounter << std::endl ;
			getline(InputFile3, line) ; //process segunda línea comment line (sin hacer nada)

			// BEGIN Build the nema of the different povray files
			FrameCounter++ ;
			std::ostringstream ss;
			std::ofstream OutputFile;
			if ( FrameCounter <= 9)
			{
				ss << "frame_no_000" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 9) && (FrameCounter <= 99))
			{
				ss << "frame_no_00" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 99) && (FrameCounter <= 999))
			{
				ss << "frame_no_0" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}

			if ( (FrameCounter > 999) && (FrameCounter <= 9999))
			{
				ss << "frame_no_" << FrameCounter << ".pov";
				OutputFile.open(ss.str().c_str(), std::ofstream::app);
			}
			// END Build the nema of the different povray files
			for (int i=0; i<Natoms; i++)
			{

				std::getline(InputFile3, line);
				std::stringstream bb(line);
				bb >> element >> x >> y >> z ;
				OutputFile << "sphere { <" << x << "," << y << "," << z << ">," << Rgas+0.01 << " pigment { rgbt <0.5,0.7,0.2,0>} finish { phong 0.7 phong_size 20 }}\n";
			}
			OutputFile.close () ;

			stringstream pp;
//			pp << "povray " << ss.str().c_str() << " +A Quality=7 +W1000 +H1000"; // Intermediate
			pp << "povray " << ss.str().c_str() << " +W1000 +H1000"; // Intermediate
			system( pp.str().c_str() );
			std::remove(ss.str().c_str()); 
		}
	}
	InputFile2.close() ;





	//system("ffmpeg -i frame_no_%04d.png -c:v libx264 -t 30 -pix_fmt yuv420p out.mp4") ;
        return (0) ;
}
