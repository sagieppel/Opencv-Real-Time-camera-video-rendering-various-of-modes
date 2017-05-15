#include "opencv2/opencv.hpp"
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include <iostream>
#include <conio.h>
#include "math.h"
//Capture computer camera video stream and transform to various of animation like properties
 using namespace cv;
 using namespace std;
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToEdgeImage();
int VideoToFrameAverage();
int VideoToAnimation();
int VideoToFrameDifference(char* ImageName=NULL);
int VideoToSobble();
int VideoToSobbleOnImage(char* ImageName=NULL);
int VideoOnImage(char* ImageName);
int FlickerRgb();
int Psychodelic();
int PsychodelicDiff();
int PsychodelicDiffDelay();
int PsychodelicDiffDelayCoolAcident1();
int PsychodelicDiffDelayCoolAcident2();
int PsychodelicDiffDelayCoolAcident3();
int PsychodelicDiffDelayCoolAcident4();
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int, char**)
{
	//VideoToAnimation();
	//VideoToEdgeImage();
	//VideoToFrameAverage();
	VideoToFrameDifference("C:/Users/mithycow/Downloads/hubble01.jpg"); //very good
	//VideoToSobble(); 
	//VideoToSobbleOnImage("C:/Users/mithycow/Downloads/hubble01.jpg");
	//VideoOnImage("C:/Users/mithycow/Downloads/hubble01.jpg");
	//FlickerRgb();
	//Psychodelic();
	//PsychodelicDiff();
	//PsychodelicDiffDelay();
	//PsychodelicDiffDelayCoolAcident1();
//	//PsychodelicDiffDelayCoolAcident2();
	//PsychodelicDiffDelayCoolAcident3();
	//PsychodelicDiffDelayCoolAcident4();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToEdgeImage()//Capture deafult camera image and transform to animation and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
	 Mat frame;
        cap >> frame;

    namedWindow("Animation",0);
	 namedWindow("Track",0);
     //Create Track bar to change bvarious of image properties
     int ColorSpace = 50;
     createTrackbar("Color red", "Track", &ColorSpace, 255);
	 int EdgeWidth = 1;
     createTrackbar("Edge With", "Track", &EdgeWidth, 30);
	 int IsColor = 1;
    createTrackbar("Is Color", "Track", &IsColor, 1);


    for(;;)
    {
  //   sigma=double(iSliderValue1)/100.0;
        cap >> frame; // get a new frame from camera

	//----------------------Reduce Color space-----------------------------------------------------------------------------
    frame/=ColorSpace;
	frame*=ColorSpace;

	//------------------------------Draw Edges-------------------------------------------------------------------
	for (int r=EdgeWidth;r<=frame.rows-EdgeWidth;r++) 
			for (int c=EdgeWidth;c<=frame.cols-EdgeWidth;c++) 
			{
				if (frame.at<cv::Vec3b>(r,c)!=frame.at<cv::Vec3b>(r,c+EdgeWidth) || frame.at<cv::Vec3b>(r+EdgeWidth,c)!=frame.at<cv::Vec3b>(r,c) ) frame.at<cv::Vec3b>(r,c)=cv::Vec3b(0,0,0); 
				else if (!IsColor) frame.at<cv::Vec3b>(r,c)=cv::Vec3b(255,255,255);
			}  
			//---------------Show on screen-------------------------------------------------------------------------------------------

        imshow("Animation",frame);
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToFrameAverage() //Capture deafult camera image and transform time average
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int Smooth = 900;
	    namedWindow("Ghost",0);
     createTrackbar("Delay", "Ghost", &Smooth, 1000);
     


    Mat PrevFrame,Frame; 
	 cap >> PrevFrame; // get a new frame from camera
    for(;;)
    {
        cap >> Frame; // get a new frame from camera
       // cvtColor(Frame, Frame, COLOR_BGR2GRAY);//transform to gray
		Frame=(Frame*((1000.0-Smooth)/1000.0)+PrevFrame*(Smooth/1000.0));
		PrevFrame=Frame.clone();
        imshow("Ghost",Frame);
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToFrameDifference(char* ImageName) //Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int Fract = 500;
	    namedWindow("Difference",0);
     createTrackbar("Delay", "Difference", &Fract, 1000);
     Mat BackGround;
	 if (ImageName!=NULL) BackGround=imread(ImageName);


    Mat PrevFrame,DifFrame,Frame; 
	 cap >> PrevFrame; // get a new frame from camera
	 resize(BackGround,BackGround,PrevFrame.size());
	//  cvtColor(PrevFrame, PrevFrame, COLOR_BGR2GRAY);//transform to gray
    for(;;)
    {
        cap >> Frame; // get a new frame from camera
    //    cvtColor(Frame, Frame, COLOR_BGR2GRAY);//transform to gray
		float ff=Fract/1000.0;
		 if(! BackGround.data ) DifFrame=Frame-PrevFrame;
		 else DifFrame=(Frame-PrevFrame)*ff+BackGround*(1-ff);
		PrevFrame=Frame.clone();
         imshow("Difference",DifFrame);
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mat ImageToSobbleAbs(Mat &src)
{
  Mat  src_gray;
  Mat grad;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  int c;




 // GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create window


  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );

  /// Gradient Y
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
   convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );



  return grad;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mat ImageToSobbleOneChannel(Mat &src)
{
  Mat  src_gray;
  Mat grad;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;

  int c;




 // GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

  /// Convert it to gray
  //cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create window


  /// Generate grad_x and grad_y
  Mat grad_x, grad_y;
  Mat abs_grad_x, abs_grad_y;

  /// Gradient X
  //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( grad_x, abs_grad_x );
  print(grad_x);
  /// Gradient Y
  //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
  Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
   convertScaleAbs( grad_y, abs_grad_y );

  /// Total Gradient (approximate)
  addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );



  return grad;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToSobble() //Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
 


    Mat Frame; 
	 cap >> Frame; // get a new frame from camera
	
	//  cvtColor(PrevFrame, PrevFrame, COLOR_BGR2GRAY);//transform to gray
    for(;;)
    {
        cap >> Frame; // get a new frame from camera
    //    cvtColor(Frame, Frame, COLOR_BGR2GRAY);//transform to gray
	//	if(! BackGround.data ) DifFrame=Frame-PrevFrame;
	//	else DifFrame=Frame-PrevFrame+BackGround;
	//	PrevFrame=Frame.cloneFrame
         imshow("Difference",ImageToSobbleAbs(Frame));
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoToSobbleOnImage(char* ImageName) //Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int Inten = 900;
	    namedWindow("Difference",0);
     createTrackbar("Inten", "Difference", &Inten, 1000);
     Mat BackGround;
	 if (ImageName!=NULL) BackGround=imread(ImageName);


    Mat Frame; 
	 cap >> Frame; // get a new frame from camera
	 resize(BackGround,BackGround,Frame.size());
	//cvtColor(BackGround,BackGround, COLOR_BGR2GRAY);
    for(;;)
    {
        cap >> Frame; // get a new frame from camera
    //    cvtColor(Frame, Frame, COLOR_BGR2GRAY);//transform to gray
	//	if(! BackGround.data ) DifFrame=Frame-PrevFrame;
	//	else DifFrame=Frame-PrevFrame+BackGround;
	//	PrevFrame=Frame.cloneFrame
		//Frame=ImageToSobbleAbs(Frame);
		/*  if(BackGround.data ) 
		  {
			  Mat channel[3];
				  split(Frame, channel);
				print(channel[2]);
				  //  imshow("Difference",channel[2]);
				  for (int f=0;f<3;f++) channel[f]=ImageToSobbleOneChannel(channel[f]);
				  print(channel[2]);
				//  imshow("Difference",channel[2]);
				  merge(channel,3,Frame);
				//  Frame=Frame*Inten/1000.0+BackGround*(1000.0-Inten)/1000.0;
				  
		  }*/
		  Frame=ImageToSobbleAbs(Frame);
		  if(BackGround.data ) 
		  {
			  Mat channel[3];
				  split(BackGround, channel);
				  for (int f=0;f<3;f++) channel[f]=Frame*Inten/1000.0+channel[f]*(1000.0-Inten)/1000.0;
				  merge(channel,3,Frame);
		  }

        imshow("Difference",Frame);
		
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VideoOnImage(char* ImageName) //Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int Inten = 1000;
	    namedWindow("Difference",0);
     createTrackbar("Inten", "Difference", &Inten, 1000);
     Mat BackGround;
	 if (ImageName!=NULL) BackGround=imread(ImageName);


    Mat Frame; 
	 cap >> Frame; // get a new frame from camera
	 resize(BackGround,BackGround,Frame.size());
	//cvtColor(BackGround,BackGround, COLOR_BGR2GRAY);
    for(;;)
    {
        cap >> Frame; // get a new frame from camera
    //    cvtColor(Frame, Frame, COLOR_BGR2GRAY);//transform to gray
	//	if(! BackGround.data ) DifFrame=Frame-PrevFrame;
	//	else DifFrame=Frame-PrevFrame+BackGround;
	//	PrevFrame=Frame.cloneFrame
		Frame=Frame*Inten/1000.0+BackGround*(1000.0-Inten)/1000.0;
	
        imshow("Difference",Frame);
		
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FlickerRgb()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int rate = 900;
	    namedWindow("Difference",0);
     createTrackbar("Inten", "Difference", &rate, 1000);
	 Mat Frame;
    for(long t=0;;t++)
    {
        cap >> Frame; // get a new frame from camera
    
		
			  Mat channel[3];
				  split(Frame, channel);
				  for (int f=0;f<3;f++) channel[f]*=((t+f)%3==0);
				  merge(channel,3,Frame);


        imshow("Difference",Frame);
		
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Psychodelic()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	    namedWindow("Roll",0);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=0;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
		GaussianBlur( Frame, Frame, Size(3,3), 0, 0, BORDER_DEFAULT );
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  Frame.begin<Vec3b>(), end =  Frame.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = BlutC[(*it)[0]];
                (*it)[1] = GlutC[(*it)[1]];
                (*it)[2] = RlutC[(*it)[2]];
            }
//===========================Display image============================================================================================


        imshow("Image",Frame);
		
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiff()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	  int Fract = 500;
	    namedWindow("Roll",0);
		createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=30;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
		DifFrame= (Frame-PrevFrame);
		convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		GaussianBlur( Frame, Frame, Size(3,3), 0, 0, BORDER_DEFAULT );

//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  DifFrame.begin<Vec3b>(), end =  DifFrame.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = BlutC[(*it)[0]];
                (*it)[1] = GlutC[(*it)[1]];
                (*it)[2] = RlutC[(*it)[2]];
            }
//===========================Display image============================================================================================


        imshow("Image",DifFrame);
		
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiffDelay()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 7877;
	  int b = 1507;
	  int g = 6000;
	    namedWindow("Roll",0);
		int Fract = 880;
		int Thresh=4;
	 createTrackbar("Thresh", "Roll", &Thresh, 100);
	 createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame,AvFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
	 AvFrame=PrevFrame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=0;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
		DifFrame= (Frame-PrevFrame);
	//	convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		AvFrame=((DifFrame*((1000.0-Fract)/1000.0)+AvFrame*(Fract/1000.0)));//*Dec/1000.0;
		Mat OldAvFrame=AvFrame.clone();
		GaussianBlur( AvFrame, AvFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
	
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
		    MatIterator_<Vec3b> itFrame=Frame.begin<Vec3b>();
            for( it =  AvFrame.begin<Vec3b>(), end = AvFrame.end<Vec3b>(); it != end; ++it,++itFrame)
            {
              // if ((*it)[0]>Thresh) (*it)[0] = BlutC[(*it)[0]];  else (*it)[0]=(*itFrame)[0];
             //if ((*it)[1]>Thresh) (*it)[1] = GlutC[(*it)[1]];  else (*it)[1]=(*itFrame)[1];
           // if ((*it)[2]>Thresh) (*it)[2] = RlutC[(*it)[2]];  else (*it)[2]=(*itFrame)[2];
			    if ((*it)[0]>Thresh) (*it)[0] = BlutC[int(((*itFrame)[0]*0.6+(*it)[0])*0.4)];  else (*it)[0]=(*itFrame)[0];
               if ((*it)[1]>Thresh) (*it)[1] = GlutC[int(((*itFrame)[1]*0.6+(*it)[1])*0.4)];  else (*it)[1]=(*itFrame)[1];
                if ((*it)[2]>Thresh) (*it)[2] = RlutC[int(((*itFrame)[2]*0.6+(*it)[2])*0.4)];  else (*it)[2]=(*itFrame)[2];
            }
//===========================Display image============================================================================================

	//	AvFrame=Frame+AvFrame;
        imshow("Image",AvFrame);
	     AvFrame=OldAvFrame;
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiffDelayCoolAcident1()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	    namedWindow("Roll",0);
		int Fract = 500;
		int Thresh=30;
	 createTrackbar("Thresh", "Roll", &Thresh, 100);
	 createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame,AvFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
	 AvFrame=PrevFrame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=0;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
		DifFrame= (Frame-PrevFrame);
		convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		AvFrame=((DifFrame*((1000.0-Fract)/1000.0)+AvFrame*(Fract/1000.0)));//*Dec/1000.0;
		Mat OldAvFrame=AvFrame.clone();
		GaussianBlur( AvFrame, AvFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
	
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  AvFrame.begin<Vec3b>(), end = AvFrame.end<Vec3b>(); it != end; ++it)
            {
                if ((*it)[0]>Thresh) (*it)[0] = BlutC[(*it)[0]]; else (*it)[0]=0;
                if ((*it)[1]>Thresh) (*it)[1] = GlutC[(*it)[1]];  else (*it)[1]=0;
                if ((*it)[2]>Thresh) (*it)[2] = RlutC[(*it)[2]];  else (*it)[2]=0;
            }
//===========================Display image============================================================================================


        imshow("Image",AvFrame);
	   //AvFrame=OldAvFrame;
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiffDelayCoolAcident2()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	    namedWindow("Roll",0);
		int Fract = 500;
		int Thresh=30;
	 createTrackbar("Thresh", "Roll", &Thresh, 100);
	 createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame,AvFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
	 AvFrame=PrevFrame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=Thresh;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
		DifFrame= (Frame-PrevFrame);
		convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		AvFrame=((DifFrame*((1000.0-Fract)/1000.0)+AvFrame*(Fract/1000.0)));//*Dec/1000.0;
		Mat OldAvFrame=AvFrame.clone();
		GaussianBlur( AvFrame, AvFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
	
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  AvFrame.begin<Vec3b>(), end = AvFrame.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = BlutC[(*it)[0]];
               (*it)[1] = GlutC[(*it)[1]]; 
                 (*it)[2] = RlutC[(*it)[2]];
            }
//===========================Display image============================================================================================


        imshow("Image",AvFrame);
	   AvFrame=OldAvFrame;
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiffDelayCoolAcident3()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	    namedWindow("Roll",0);
		int Fract = 500;
		int Thresh=30;
	 createTrackbar("Thresh", "Roll", &Thresh, 100);
	 createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame,AvFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
	 AvFrame=PrevFrame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=Thresh;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
	//	DifFrame= (Frame-PrevFrame);
		//convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		AvFrame=((Frame*((1000.0-Fract)/1000.0)+AvFrame*(Fract/1000.0)));//*Dec/1000.0;
		Mat OldAvFrame=AvFrame.clone();
		GaussianBlur( AvFrame, AvFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
	
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  AvFrame.begin<Vec3b>(), end = AvFrame.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = BlutC[(*it)[0]];
               (*it)[1] = GlutC[(*it)[1]]; 
                 (*it)[2] = RlutC[(*it)[2]];
            }
//===========================Display image============================================================================================


        imshow("Image",AvFrame);
	   AvFrame=OldAvFrame;
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PsychodelicDiffDelayCoolAcident4()//Capture deafult camera image and transform to canny edge image and display on screen
{

    VideoCapture cap(0); // open the default camera
   if(!cap.isOpened())  // check if we succeeded
      return -1;
      int r = 100;
	  int b = 200;
	  int g = 150;
	    namedWindow("Roll",0);
		int Fract = 500;
		int Thresh=30;
	 createTrackbar("Thresh", "Roll", &Thresh, 100);
	 createTrackbar("Fract", "Roll", &Fract, 1000);
     createTrackbar("red", "Roll", &r, 10000);
     createTrackbar("blue", "Roll", &b, 10000);
	 createTrackbar("green", "Roll", &g, 10000);
	 float RlutF[256], GlutF[256], BlutF[256];//Value of color in the Rgb space
	 unsigned char RlutC[256], GlutC[256], BlutC[256];//Int value for display
	 float RSign[256], GSign[256], BSign[256];//Sign of change
	 for (int f=0;f<256;f++)//intiate lut
	 {
		 RlutC[f]=GlutC[f]=BlutC[f]=RlutF[f]=GlutF[f]=BlutF[f]=f;
		 RSign[f]=GSign[f]=BSign[f]=1;
	 }

	 Mat Frame;
//=================Capture previous frame=====================================================================================
	 
    Mat PrevFrame,DifFrame,AvFrame ; 
	 cap >> PrevFrame; // get a new frame from camera
	 AvFrame=PrevFrame;
//======================================Main display loop===========================================================================================
    for(long t=0;;t++)
    {
		float Dr=(r-5000.0)/100.0;
		float Db=(b-5000.0)/100.0;
		float Dg=(g-5000.0)/100.0;
//================update color mapping================================================================================================
	    for (int f=Thresh;f<256;f++)
	    {
///.................................Red...............................................................................
			RlutF[f]+=Dr*RSign[f];
			if  (RlutF[f]>255 || RlutF[f]<0)
			{
               RSign[f]*=-1;
			   RlutF[f]=RlutF[f]+Dr*RSign[f];
			}
			RlutC[f]=RlutF[f];
//......................................blue................................................................................................
			BlutF[f]+=Db*BSign[f];
			if  (BlutF[f]>255 || BlutF[f]<0)
			{
               BSign[f]*=-1;
			   BlutF[f]=BlutF[f]+Db*BSign[f];
			}
			BlutC[f]=BlutF[f];
//......................................Green................................................................................................
			GlutF[f]+=Dg*GSign[f];
			if  (GlutF[f]>255 || GlutF[f]<0)
			{
               GSign[f]*=-1;
			   GlutF[f]=GlutF[f]+Dg*GSign[f];
			}
			GlutC[f]=GlutF[f];
		}
//==========================Get frame from cammera=================================================================================================
        cap >> Frame; // get a new frame from camera
	//	DifFrame= (Frame-PrevFrame);
		//convertScaleAbs(DifFrame,DifFrame);
		PrevFrame=Frame.clone();
		AvFrame=((Frame*((1000.0-Fract)/1000.0)+AvFrame*(Fract/1000.0)));//*Dec/1000.0;
		//Mat OldAvFrame=AvFrame.clone();
		GaussianBlur( AvFrame, AvFrame, Size(3,3), 0, 0, BORDER_DEFAULT );
	
//===================================Map colors===========================================================================================
		  MatIterator_<Vec3b> it, end;
            for( it =  AvFrame.begin<Vec3b>(), end = AvFrame.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = BlutC[(*it)[0]];
               (*it)[1] = GlutC[(*it)[1]]; 
                 (*it)[2] = RlutC[(*it)[2]];
            }
//===========================Display image============================================================================================


        imshow("Image",AvFrame);
	  // AvFrame=OldAvFrame;
	
        if(waitKey(1)== 27) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}