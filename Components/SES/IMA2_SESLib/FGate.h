/* FGATE.H

 */
#include "CImg.h"
  using namespace cimg_library;

#include <iostream>

  using namespace std;

//#ifndef _NO_NAMESPACE
//using namespace std;

//#define STD std
//#else
//#define STD
//#endif

  //directory name
 const char dirname[100] = "C:\\Images\\";


class FGate {

public:
	FGate();	//constructor
	~FGate(); //destructor
		
	void loadImg(char * filename);
	void clearInImg();
	void clearOutImg();
	void displayInImg();
	void saveOutImg(char * filename);

//	CImg<unsigned char> getinImg();
//	CImg<unsigned char> getoutImg();

	CImg<double>* featureGate(char * filename, int N, short levels);		//run FeatureGate
	void createModules();				//create color, orientation, luminance & activation modules
	void FreiChenOrient();				//perform Frei-Chen decomp to form orientation layer
	void bottomUp();					//bottomUp processing function
	//void topDown();					//topDown processing function
	void newLevel();					//function to create the new downsampled level
	void setDownsizeFactor(int d);		//set downsizing factor for new level creation
	void displayFOA(int N);				//display focus of attention and top N attn locations 
	void getTopNActiv(int N, bool levels);			//Find top N activations
	
private:
	
	CImg<int>* inImg;
	CImg<int>* outImg;
	
	//Feature Modules
	CImg<int>* color;					//color
	CImg<int>* lummap;					//luminance
	CImg<int>* orient;				//orientation
	CImg<double>* activ;				//activation
	CImg<double>* salientLocs;			//salient locations

	int downF;							//downsampling factor for new levels
	int neighborhood[2];				//neighborhood dimensions
	
//matrix<int> nodeArray; (individual images will be processed
	//and the most salient nodes will be displayed using a separated program



};