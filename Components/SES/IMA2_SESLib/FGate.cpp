/* FGate.cpp  */

#include "FGate.h"


//Constructor
FGate::FGate()
{

		inImg = NULL;
		outImg = NULL;
}

//Destructor
FGate::~FGate()
{
	clearInImg();
	clearOutImg();
}


//Clear input image
void FGate::clearInImg()
{
	delete inImg;
	inImg=NULL;
}

//Clear output image
void FGate::clearOutImg()
{
	delete outImg;
	outImg = NULL;
}


//Load an input image from file
void FGate::loadImg(char * filename)
{
	int R, C, i,j;
	//remove 1 px border around the image in case it's empty
	CImg<int> inTemp(filename);
	R = inTemp.dimy();
	C = inTemp.dimx();

	if (inImg != NULL)
		clearInImg();

	inImg = new CImg<int>(C-2, R-2,1,3,0);
	
	for (i=0; i<R-2; i++)
	{
		for(j=0; j<C-2; j++)
		{
			*inImg->ptr(j,i,0,0) = inTemp(j+1, i+1,0,0);
			*inImg->ptr(j,i,0,1) = inTemp(j+1, i+1,0,1);
			*inImg->ptr(j,i,0,2) = inTemp(j+1, i+1,0,2);
		}
	}

	outImg = new CImg<int>(*inImg);
	
}
//Display input image
void FGate::displayInImg()
{
	if (inImg != NULL)
	{
		CImgDisplay main_disp(*inImg,"inputImage");
		while (!main_disp.closed) 
		{
		main_disp.wait();
		}
	}
}

//Save attentionally processed output image	
void FGate::saveOutImg(char * filename)
{
	if (outImg != NULL)
		outImg->save(filename);

}

//Set downsizing factor for new level creation
void FGate::setDownsizeFactor(int d)		
{
	downF = d;
}

//Run FeatureGate Attentional Processing (main function)
CImg<double>* FGate::featureGate(char * filename,int N, short levels)
{

	int R, C,i,j;						//dimensions
	char* outputFile = new char[25];
	char fileNameTemp[100];

	//Load input image
	strcpy(fileNameTemp, dirname);		//directory path
	strcat(fileNameTemp, filename);		//filename
	loadImg(fileNameTemp);
	
	//Blur image with 3x3 blurring filter (so points don't shift around so much)
	//h = ones(3,3);
	//I = spatialconv(I, h);

	//Create all feature modules and activation map
	createModules();

	//Set downsizing factor (set to 2)
	setDownsizeFactor(2);

	//Set salientLocs to the number of desired locations
	//salientLocs = new CImg<double>(3,N,1,1,0);
	salientLocs = new CImg<double>(3,N);

	//set neighborhood size approx. 20x20 (size image is downsampled by 3 in
	//each direction, set to 7x7**
	neighborhood[0] = neighborhood[1] = 15;
	
	//If levels is 1, run FGate as usual, if it is 0, only do 1 pass
	
	//bottom-up function 
	bottomUp();
	//top-down function (if a known feature was passed in)
	//if feature{1,1}(1,1) ~= 0 || feature{1,2}(1,1) ~= 0 || feature{1,3}(1,1) ~= 0
	//	topDown(feature);

	//get dimensions of modules image
	R = color->dimy();
	C = color->dimx();

	if(levels)
	{
		//downsample dimensions
		R = R/downF;
		C = C/downF;
		
		//create new level activation and feature maps
		newLevel();

		//stop when structure size is closest to N but no smaller
		while((R*C >= N) && ((R/2)*(C/2) > N))
		{
			
			//clear out activation
			for(i=0; i<R; i++)
			{
				for(j=0; j<C; j++)
				{
					*activ->ptr(j,i,0,0) = 0;
				}
			}

			//bottom up function
			bottomUp();
			//top down function
			//topDown();
	
			//downsample dimensions
			R = R/downF;
			C = C/downF;
			
			//create new level activation and feature modules
			newLevel();
		}
		
	}
	//store top N attentional locations
	//make sure that there is only 1 per neighborhood
	//put results in salientLocs structure
	getTopNActiv(N,levels);
		
	//display image and top N attentional locations
	displayFOA(N);

	//save output image to file
	strcpy(outputFile, dirname);		//directory path
	strcat(outputFile, "AttnImages\\");	//put in AttnImages folder
	strcat(outputFile, "Attn");			//add ATTN b/c it is a processed image
	strcat(outputFile, filename);		//same filename as original image
	saveOutImg(outputFile);

	return salientLocs;

}

//Find top N attentional locations and sort
void FGate::getTopNActiv(int N,bool levels)
{
	
	int R,C,g,h,i,j, index;				//indices, dimensions
	double max[5] = {-50000,-1,-1,-1,-1};	//act, row & col in original img, row & col in activ
	int row, col, edge;
	row = floor(inImg->dimy()/3);
	col = floor(inImg->dimx()/3);
	bool flag, flagSort;
	double temp;
	CImg<double> salTemp(3,N,1,1,0);
	//if not doing levels, must not take edges
	if(levels==0)
		edge = 0;
	else
		edge= -1;
	
	//get size of activation level
	R = activ->dimy();
	C = activ->dimx();

	for(g=0; g<R; g++)
	{
		for(h=0; h<C; h++)
		{
			if(((*activ->ptr(h,g,0,0)) > max[0]) && (g != edge) && (g != row-1) && (h != edge) && (h != col-1))
			{
				//save maximum value and location
				max[0] = *activ->ptr(h,g,0,0);
				max[1] = *activ->ptr(h,g,0,1);
				max[2] = *activ->ptr(h,g,0,2);
				max[3] = g;
				max[4] = h;

			}
		}
	}
	

	//store in salientLocs
	*salientLocs->ptr(0,0) = max[0]; 
	*salientLocs->ptr(1,0) = max[1];
	*salientLocs->ptr(2,0) = max[2];

	//clear values from activ and max
	*activ->ptr(max[4], max[3], 0, 0) = -50000;
	max[1] = max[2] = max[3] = max[4] = -1;
	max[0] = -50000;

	//now retrieve all other highest activations (only 1 per neighborhood)
	for(i=1; i<N; i++)
	{
		for(g=0; g<R; g++)
		{
			for(h=0; h<C; h++)
			{
			//	if (i == 1)
			//		cout << "row: " << g << " col: " << h << " activ: " << *activ->ptr(h,g,0,0) << endl;

				if((*activ->ptr(h,g,0,0) > max[0]) && (g != edge) && (g != row-1) && (h != edge) && (h != col-1))
				{	
					
					//make sure this point is not too close to another salient point
					flag = 0;
					for(j=0; j<i; j++)
					{
						
						if((abs(*salientLocs->ptr(1,j) - *activ->ptr(h,g,0,1)) < neighborhood[0]) && (abs(*salientLocs->ptr(2,j)-*activ->ptr(h,g,0,2)) < neighborhood[1]))
							flag = 1;
					}
					if(flag == 0)
					{
						max[0] = *activ->ptr(h,g,0,0);
						max[1] = *activ->ptr(h,g,0,1);
						max[2] = *activ->ptr(h,g,0,2);
						max[3] = g;
						max[4] = h;
					}
				}
			}
		

		}

		//store in salientLocs
		*salientLocs->ptr(0,i) = max[0]; 
		*salientLocs->ptr(1,i) = max[1];
		*salientLocs->ptr(2,i) = max[2];
		
		//check to ensure that it found a point
		if (max[0] == -50000)
		{
			flagSort = 1;
			//if not, must reprocess and take a pixel within neighborhood
			for(g=0; g<R; g++)
			{
				for(h=0; h<C; h++)
				{
		
					if((*activ->ptr(h,g,0,0) > max[0]) && (g != edge) && (g != row-1) && (h != edge) && (h != col-1))
					{	
						max[0] = *activ->ptr(h,g,0,0);
						max[1] = *activ->ptr(h,g,0,1);
						max[2] = *activ->ptr(h,g,0,2);
						max[3] = g;
						max[4] = h;
					}
				}
			}
			//store in salientLocs
			*salientLocs->ptr(0,i) = max[0]; 
			*salientLocs->ptr(1,i) = max[1];
			*salientLocs->ptr(2,i) = max[2];
		}

		//clear values from activ and max
		*activ->ptr(max[4], max[3], 0, 0) = -50000;
		max[1] = max[2] = max[3] = max[4] = -1;
		max[0] = -50000;	

	}

	//check if you need to re-sort array
	if(flagSort == 1)
	{
		salTemp(0,0,0,0) = *salientLocs->ptr(0,0);
		salTemp(1,0,0,0) = *salientLocs->ptr(1,0);
		salTemp(2,0,0,0) = *salientLocs->ptr(2,0);
		
		*salientLocs->ptr(0,0,0,0) = -50000;
		
		for(i=1;i<N;i++)
		{
			temp=-50000;
			index = -1;
			for(j=1; j<N; j++)
			{
				if (*salientLocs->ptr(0,j) > temp)
				{
					temp = *salientLocs->ptr(0,j);
					salTemp(0,i,0,0) = temp;
					salTemp(1,i,0,0) = *salientLocs->ptr(1,j);
					salTemp(2,i,0,0) = *salientLocs->ptr(2,j);
					index = j;
				}
			}
			*salientLocs->ptr(0,index) = -50000;
		}

	*salientLocs = salTemp;
	}
				
}			
						
	
//Display FOA and top N attentional locations
void FGate::displayFOA(int N)
{

	int r,c,i;				//indices

	//array of colors for salient location identification
	//ORDER:  ROY G BIV, magenta, black, gray, brown, huntergreen (for the rest)
	int colorarray[12][3] = {{255,0,0}, {255,165,0},{255,255,0}, {0,255,0}, {0, 255,255},
	{0, 0, 255},{160,32,240},{255,0,255}, {0,0,0}, {200,200,200}, {139,69,19},{46,139,87}};

	
	//SalientLocs structure is already sorted in order of most salient to least salient
      
	//TEST
//	for(i = 0; i<N; i++)
//	{
	
//		cout << "Sal: " << (*salientLocs->ptr(0,i)) << "  " <<(*salientLocs->ptr(1,i)) << " " << (*salientLocs->ptr(2,i)) <<endl;
//	}
	//Salient points are displayed from least salient to most salient in case of overlap
	for(i=(N-1); i>=0; i--)
	{
		
		for(r=(int)((*salientLocs->ptr(1,i))*3-3); r<(int)((*salientLocs->ptr(1,i))*3+4); r++)
		{
			for(c =(int)((*salientLocs->ptr(2,i))*3-3); c<(int)((*salientLocs->ptr(2,i))*3+4); c++)
			{
				if((r >= 0) && (c >= 0))
				{
					if(i>11)
					{
						(*outImg->ptr(c,r,0,0)) = colorarray[11][0];
						(*outImg->ptr(c,r,0,1)) = colorarray[11][1];
						(*outImg->ptr(c,r,0,2)) = colorarray[11][2];
					}
					else
					{
						*outImg->ptr(c,r,0,0) = colorarray[i][0];
						*outImg->ptr(c,r,0,1) = colorarray[i][1];
						*outImg->ptr(c,r,0,2) = colorarray[i][2];
					}
				}
			}
		}
	}
	//Display output image
//	CImgDisplay main_disp(*outImg,"Output");
 //   while (!main_disp.closed) {
//		main_disp.wait();}

}

//Create color, luminance, orientation, & activation modules
void FGate::createModules()
{
	
	//declarations
	int i, j, k, h;					 //counters
	int min, max;					// minimum and maximum image values
	double sums[4];					//sums array for downsampling
	int R = inImg->dimy();
	int C = inImg->dimx();
 

	//Downsample by a factor of 3
	int r = floor(R/3);	//r = size(2:3:R+2,2); in matlab
	int c = floor(C/3);	//c = size(2:3:C+2,2); in matlab

	
	//pad original image for computations (initialize to 0)
	CImg<int> Ipad(C+2,R+2, 1, 3,0);
	//fill in with original image values
	for(i=0; i<R; i++)								
	{
		for(j=0; j<C; j++)
		{
			Ipad(j,i,0,0) = *inImg->ptr(j,i,0,0);
			Ipad(j,i,0,1) = *inImg->ptr(j,i,0,1);
			Ipad(j,i,0,2) = *inImg->ptr(j,i,0,2);
		}
	}


	//set size of color and luminance modules
	color = new CImg<int> (c,r,1,3);
	lummap = new CImg<int> (c,r);
	CImg<int> lummapTemp(C,R);
	
	//Extract the luminance
	min = 100000;
	max = -1;

	for(i=0; i<R; i++)									//J = 0.299*I(:,:,1)+0.587*I(:,:,2)+0.114*I(:,:,3);
	{
		for (j=0; j<C; j++)
		{
			
			lummapTemp(j,i) = (int)(0.299*((Ipad(j,i,0,0)))+0.587*((Ipad(j,i,0,1)))+ 0.114*((Ipad(j,i,0,2))));
			//find minimum and maximum values for normalization
			if (lummapTemp(j,i) < min)				
				min = lummapTemp(j,i);
			if (lummapTemp(j,i) > max)					
				max = lummapTemp(j,i);
		
		}
	}

	//normalize
	for(i=0; i<R; i++)	
	{
		for (j=0; j<C; j++)
			lummapTemp(j,i) = (int)(255*(((double)(lummapTemp(j,i)-min))/((double)(max-min))));  //J = uint8(255*((J-m)/(M-m)));
	}	
	
	//Downsample modules by a factor of 3
	for(i=0; i<r; i++)
	{
		for(j=0; j<c; j++)
		{
			
			sums[0]= sums[1] = sums[2] = sums[3] = 0;			
			//calculate sum of 9 pixels
			for(k=i*3; k<(i+1)*3; k++)
			{
				for(h=j*3; h<(j+1)*3; h++)
				{
					sums[0] = sums[0]+(double)(Ipad(h,k,0,0));
					sums[1] = sums[1]+(double)(Ipad(h,k,0,1));
					sums[2] = sums[2]+(double)(Ipad(h,k,0,2));
					sums[3] = sums[3]+(double)lummapTemp(h,k);
				}
			}

			//initialize color and luminance modules (round to nearest int)
			*(color->ptr(j,i,0,0)) = (int)(floor(sums[0]/9 + 0.5));
			*(color->ptr(j,i,0,1)) = (int)(floor(sums[1]/9 + 0.5));
			*(color->ptr(j,i,0,2)) = (int)(floor(sums[2]/9 + 0.5));
			*(lummap->ptr(j,i)) = (int)(floor(sums[3]/9 + 0.5));
		}
	}

	//test
/*
		CImgDisplay main_disp(*color,"colorModule",0),disp(*lummap,"luminanceModule",0);
		while (!main_disp.closed) 
		{
			main_disp.wait();
		}

		while (!disp.closed) 
		{
			disp.wait();
		}
*/
		//Activation module
		 activ = new CImg<double>(c,r,1,3,0);
		 for(i=0; i<r; i++)
		 {
			 for(j=0; j<c; j++)
			 {
				 *(activ->ptr(j,i,0,1)) = i;	//row
				 *(activ->ptr(j,i,0,2)) = j;	//col
			 }
		 }

		 //Orientation Module
		//Perform a Frei-Chen Decomposition of an image
		 FreiChenOrient();

 }


 //Calculates Frei-Chen Basis and makes orientation module
 void FGate::FreiChenOrient()
 {
		
	int i,j,k,x,y,b;				//counters
	int min = 5000;
	int max = 0;
	int R = inImg->dimy();
	int C = inImg->dimx();
	double temp =0;

	//Downsample by a factor of 3
	int r = floor(R/3);	//r = size(2:3:R+2,2); in matlab
	int c = floor(C/3);	//c = size(2:3:C+2,2); in matlab

	//initialize orientation  module
	orient = new CImg<int>(c,r,1,8,0);

	//get Basis
	double sq2 = sqrt(2);
	double dsq2 = 2*sq2;
	double FC1[3][3] = {{1/dsq2,sq2/dsq2,1/dsq2},{0,0,0},{-1/dsq2,-sq2/dsq2,-1/dsq2}};
	double FC2[3][3] = {{1/dsq2,0,-1/dsq2}, {sq2/dsq2, 0, -sq2/dsq2}, {1/dsq2,0,-1/dsq2}};
	double FC3[3][3] = {{0/dsq2,-1/dsq2,sq2/dsq2},{1/dsq2,0/dsq2,-1/dsq2}, {-sq2/dsq2,1/dsq2,0/dsq2}};
	double FC4[3][3] = {{-sq2/dsq2,1/dsq2,0/dsq2},{1/dsq2,0/dsq2,-1/dsq2},{0/dsq2,-1/dsq2,sq2/dsq2}};

	double FC5[3][3] = {{0,0.5,0},{-0.5,0, -0.5},{0, 0.5,0}};
	double FC6[3][3] = {{-0.5,0,0.5},{0,0,0},{0.5,0,-0.5}};
	double FC7[3][3] = {{1.0/6.0, -2.0/6.0,1.0/6.0}, {-2.0/6.0, 4.0/6.0, -2.0/6.0}, {1.0/6.0, -2.0/6.0, 1.0/6.0}};
	double FC8[3][3] = {{-2.0/6.0, 1.0/6.0, -2.0/6.0}, {1.0/6.0, 4.0/6.0, 1.0/6.0}, {-2.0/6.0, 1.0/6.0, -2.0/6.0}};
	//double FC9[3][3] = {{1,1,1}, {1,1,1}, {1,1,1}};

	CImg<double> FCB(3,3,1,8,0);
	for (x = 0; x<3; x++)
	{
		for(y = 0; y<3; y++)
		{
			FCB(y,x,0,0) = FC1[x][y];
			FCB(y,x,0,1) = FC2[x][y];
			FCB(y,x,0,2) = FC3[x][y];
			FCB(y,x,0,3) = FC4[x][y];
			FCB(y,x,0,4) = FC5[x][y];
			FCB(y,x,0,5) = FC6[x][y];
			FCB(y,x,0,6) = FC7[x][y];
			FCB(y,x,0,7) = FC8[x][y];
		}
	}

	//allocate a scratch image, accumulator, and decimated accumulator
	CImg<double> J(c,r,1,3,0);
	CImg<int> T(C+2,R+2,1,9,0);
	CImg<int> smallT(c,r,1,9,0);


	for(k=0; k<8; k++) 
	{
	//	cout << " k = " << k <<endl;

		//for each band
		for(b=0; b<3; b++)
		{
			//for each row of kth basis
			for(i=0; i<3; i++)
			{
				//for each column of kth basis
				for(j=0; j<3; j++)
				{
					//shift a copy of the image into place
					for(x=i; x<R+i; x++)
					{
						for(y=j; y<C+j; y++)
						{
							T(y,x,0,(3*i+j)) = *inImg->ptr(y-j, x-i,0,b);
						}
					}
				}
			
			}
			
		
			
			//decimate the image stack by a factor of 3 in rows and cols
			for(i=0; i<r; i++)
			{
				for(j=0; j<c; j++)
				{
					for(x=0; x<9; x++)
						smallT(j,i,0,x) = T(j*3+1, i*3+1,0,x);
					
				}
			}
			//multiply each layer by the corresponding basis element and sum the layers
			for(x=0; x<r; x++)
			{
				for(y=0; y<c; y++)
				{
					temp = (smallT(y,x,0,0)*FCB(0,0,0,k))+(smallT(y,x,0,1)*FCB(1,0,0,k))+
						 (smallT(y,x,0,2)*FCB(2,0,0,k))+ (smallT(y,x,0,3)*FCB(0,1,0,k))
						 + (smallT(y,x,0,4)*FCB(1,1,0,k))+(smallT(y,x,0,5)*FCB(2,1,0,k))
						 + (smallT(y,x,0,6)*FCB(0,2,0,k))+(smallT(y,x,0,7)*FCB(1,2,0,k))
						 + (smallT(y,x,0,8)*FCB(2,2,0,k));

					J(y,x,0,b) = temp;
				}
			}
							
		} //end b
		
		//assign orientation basis 
		for(i=0; i<r; i++)
		{
			for(j=0; j<c; j++)
			{
				
				*orient->ptr(j,i,0,k) = (int)(floor(J(j,i,0,0) + J(j,i,0,1) + J(j,i,0,2))/3+0.5);
				//find minimum and maximum values for normalization
				if (*orient->ptr(j,i,0,k) < min)				
					min = *orient->ptr(j,i,0,k);
				if (*orient->ptr(j,i,0,k) > max)					
					max = *orient->ptr(j,i,0,k);
			}
		}

		//normalize
		for(i=0; i<r; i++)	
		{
			for (j=0; j<c; j++)
				*orient->ptr(j,i,0,k) = (int)(255*(((double)(*orient->ptr(j,i,0,k)-min))/((double)(max-min))));  //J = uint8(255*((J-m)/(M-m)));
		}	

		//reset values		
		min = 5000;
		max = 0;

		//make sure all edge pixels are white (not black and white)
		for(i=0; i<r; i++)	
		{
			for (j=0; j<c; j++)
			{
				if(*orient->ptr(j,i,0,k) <= 130)
					*orient->ptr(j,i,0,k) = 255 - *orient->ptr(j,i,0,k);
			}
		}
					

	}

/*
	//test
	CImg<int> tempimg(c,r);
	for(k=0; k<8; k++)
	{
		for (i=0; i<r; i++)
		{
			for(j=0; j<c; j++)
			{
				tempimg(j,i) = *orient->ptr(j,i,0,k);
			}
		}
		CImgDisplay main_disp(tempimg,"orient",0);
		while (!main_disp.closed) 
		{
			main_disp.wait();
		}

	}
*/	

	
}	



//Bottom Up processing function
void FGate::bottomUp()
{
	int i, j, R, C, r, c;			//size of modules
	double rho, ovalue;				//accumulators

	//orientation here
	int alpha = 1; //positive constant
	
	//get size of modules
	R = color->dimy();
	C = color->dimx();
	CImg<double> activTemp(C,R,1,3,0);

	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
		{
			//8-connected neighborhood rho calculation for pixel location j,i (col,row)
			rho = 0;
			ovalue = 0;
			if ((*(color->ptr(j,i,0,0)) != 0) || (*(color->ptr(j,i,1)) != 0)||( *(color->ptr(j,i,2)) != 0)) //only alter Activ bin if non-empty
			{
				
				for(r=i-1; r<=i+1; r++)
				{
					for(c=j-1; c<=j+1; c++)
					{
						if((r>= 0) && (r<R-1) && (c >= 0) && (c < C-1))
						{
							//only count non-empty neighbors
							if((*(color->ptr(c,r,0,0)) != 0) || (*(color->ptr(c,r,0,1)) != 0) || (*(color->ptr(c,r,0,2)) != 0))
							{
								//color
								rho += sqrt(pow(abs((*(color->ptr(c,r,0,0)))-(*(color->ptr(j,i,0,0)))),2)
										  + pow(abs((*(color->ptr(c,r,0,1)))-(*(color->ptr(j,i,0,1)))),2)
										  + pow(abs((*(color->ptr(c,r,0,2)))-(*(color->ptr(j,i,0,2)))),2));
							
								//luminance
								rho += abs(*(lummap->ptr(c,r))-(*(lummap->ptr(j,i))));
								
								//orientation
								ovalue = abs(*orient->ptr(c,r,0,0)- *orient->ptr(j,i,0,0)) + abs(*orient->ptr(c,r,0,1)- *orient->ptr(j,i,0,1))
									   + abs(*orient->ptr(c,r,0,2)- *orient->ptr(j,i,0,2)) + abs(*orient->ptr(c,r,0,3)- *orient->ptr(j,i,0,3))
									   + abs(*orient->ptr(c,r,0,4)- *orient->ptr(j,i,0,4)) + abs(*orient->ptr(c,r,0,5)- *orient->ptr(j,i,0,5))
									   + abs(*orient->ptr(c,r,0,6)- *orient->ptr(j,i,0,6)) + abs(*orient->ptr(c,r,0,7)- *orient->ptr(j,i,0,7));
                                
							}
						}
					}
				}
			}
			else
				rho = -100;		//make activation small for empty bins so they don't propagate
			
			//add to activation module bin
			activTemp(j,i,0,0) = *(activ->ptr(j,i,0,0)) + ((rho + ovalue)*alpha);
			activTemp(j,i,0,1) = *(activ->ptr(j,i,0,1)); 
			activTemp(j,i,0,2) = *(activ->ptr(j,i,0,2));
		}
	
	}


	//set old activation modules equal to one
	*activ = activTemp; 

}


//new Level
void FGate::newLevel()
{
	int n, m, i, j,a,b, k;			//size and counter variables 
	int difR, difC;
	int location[2];
	int indices[2];
	double acount;

	n = activ->dimy();			//rows
	m = activ->dimx();			//cols
	
	int R = (int) n/downF;		//rows
	int C = (int) m/downF;		//cols
	
	//cout << "newLev " << R << "  " << C << endl;

	//temporary modules
	CImg<double> activTemp(C,R,1,3,0);	 
	CImg<int> locations(C,R,1,2,0);	//save row/loc in current lev.
	CImg<int> colorTemp(C,R,1,3,0);
	CImg<int> lummapTemp(C,R);
	CImg<int> orientTemp(C,R,1,8,0);

	
	for(i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
		{
			//find highest activation in receptive field & store in activTemp
			acount = -50000;
			location[0] = location[1] = -1;
			indices[0] = indices[1] = -1;
			difR = difC = 0;

			//reached last r, dim div. by row downFactor perfectly
			if ((i==(R-1)) && ((i+1)*downF == n))
			{
				difR = 0;
			
			}
			else if((i==(R-1)) && ((i+1)*downF != n))
			{
				//reached last row, dim. not perfectly div. by downFactor
				//find remainder
				difR = n - (R*downF);
			}
			else
			{
				difR = 0;
			}

			if((j==(C-1)) && ((j+1)*downF == m))
				{
					//reached last c, dim div. by col downFactor perfectly
					difC = 0;
				}
			else if((j==(C-1))  && ((j+1)*downF !=m))
				{
					//reached last c, dim not perfectly div. by downFactor
					//find remainder
					difC = m - (C*downF);
					
				}
			else
			{
				difC = 0;
			}

			for (a=i*downF; a <(i+1)*downF+difR; a++)
			{
				for (b=j*downF; b <(j+1)*downF+difC; b++)
				{
					if (*activ->ptr(b,a,0,0) >= acount)
					{
				
					//if ((*activ->ptr(b,a,0,1) != 0) && (*activ->ptr(b,a,0,2) != 0) && (*activ->ptr(b,a,0,1) != R) && (*activ->ptr(b,a,0,2) != C))
						//set count to highest activation
						acount = *(activ->ptr(b,a,0,0));
						//store location
						location[0] = (int)(*(activ->ptr(b,a,0,1)));
						location[1] = (int)(*(activ->ptr(b,a,0,2)));
						indices[0] = a;
						indices[1] = b;

					}
				}
			}
			
			//store in new activ
            activTemp(j,i,0,0) = acount;
            activTemp(j,i,0,1) = (double)location[0];	//row loc.
			activTemp(j,i,0,2) = (double)location[1];	//col loc.
			locations(j,i,0,0) = indices[0];	//row loc. in current level activ
			locations(j,i,0,1) = indices[1];	//col loc. in current level activ
				
       	}
	}


	//Create new level color,luminance, and orientation feature maps
	for (i=0; i<R; i++)
	{
		for(j=0; j<C; j++)
		{
					
			colorTemp(j,i,0,0) = *color->ptr(locations(j,i,0,1),locations(j,i,0,0),0,0);
			colorTemp(j,i,0,1) = *color->ptr(locations(j,i,0,1),locations(j,i,0,0),0,1);
			colorTemp(j,i,0,2) = *color->ptr(locations(j,i,0,1),locations(j,i,0,0),0,2);
			lummapTemp(j,i) = *lummap->ptr(locations(j,i,0,1), locations(j,i,0,0));
       
			for(k=0; k<8; k++)
			{
				orientTemp(j,i,0,k) = *orient->ptr(locations(j,i,0,1), locations(j,i,0,0),0,k);
			}
		}    
	}

	//set modules equal to temp modules
	//cleared out activation above
	*activ = activTemp; 
	*color = colorTemp;
	*lummap = lummapTemp;
	*orient = orientTemp;

//	cout << "newR: " << R << " newC:  " << C << endl;
//	cout << "done with new Level" << endl;


}

