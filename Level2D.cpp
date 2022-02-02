/*
 * Copyright 2020~2022 SYSON, MICHAEL B.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @company: USBONG
 * @author: SYSON, MICHAEL B.
 * @date created: 20200926
 * @date updated: 20220130; from 20220128
 * @website address: http://www.usbong.ph
 *
 * Reference:
 * 1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
 *
 * 2) https://www.mathsisfun.com/sine-cosine-tangent.html;
 *	 last accessed: 20210803
 *
 * 3) https://www.libsdl.org/download-2.0.php;
 * 	 last accessed: 20210816
 * --> SDL Installation Intructions on LUBUNTU (20.04); 
 * --> https://askubuntu.com/questions/786300/how-to-install-all-sdl-libraries-in-ubuntu-14-04;
 * --> last accessed: 20210816
 *
 * Note:
 * 1) SDL installation on Linux machine; 
 * --> Terminal Commands (select Libraries, version Downgrade to Insall)
 * --> sudo apt-get install aptitude
 * --> sudo aptitude install libsdl2-dev
 *
 * 2) SDL Image Tool installtion on Linux machine;
 * --> Terminal Commands (select Libraries, version Downgrade to Insall)
 * --> sudo aptitude install libsdl2-image-dev
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007):
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//added by Mike, 20210901
//note: re-verify: SUZUKI, YU and team @SEGA 1993~; DAYTONA USA with alps?
//create component parts of world as journey; find game inside as surprise...?

 
//added by Mike, 20210130
//reverify: Robotship does not execute correctly
//when down and left buttons are pressed while firing beam down
//AND when up and left buttons are pressed while firing beam up
//in Windows Machine
//problem did not occur on Linux Machine (with external USB keyboard)
//added by Mike, 20210131
//note: add use of external USB keyboard solves the problem

//TO-DO: -update: this

//added by Mike, 20210201
//TO-DO: -delete: excess instructions
//TO-DO: increase lower right arm angle to go up y-axis

//added by Mike, 20210202
//TO-DO: -update: instructions when diagonal movement is combined with attack and defend keys

//added by Mike, 20210807
//added: in draw tile sprite texture image whose width and height is over its tile width and height used in collision detection

//added by Mike, 20210815
//TO-DO: -reverify: cause why on macOS tile positions not exact with OpenGLCanvas.cpp grid lines; Window Width x Height; 1280 x 800

#include <stdio.h>
#include <math.h>

//added by Mike, 20210719
#include <iostream>

/*	//removed by Mike, 20201121
 #include <gl/gl.h>
 #include <gl/glu.h>
 */

/* //removed by Mike, 20220122
//added by Mike, 20201121
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif
*/

/* //removed by Mike, 20220122
//added by Mike, 20210829
#ifdef _WIN32 //Windows machine
    #include <SDL.h>
    #include <SDL_image.h>
#elif defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif
*/

/* //removed by Mike, 20210826
#include "Button.h"
*/

/* //TO-DO: -add: these
 #include "PolygonUtils.h"
 #include "ModelPool.h"
 */

//added by Mike, 20210613
#include "Level2D.h"


//added by Mike, 20210614; removed by Mike, 20210703
//#include "Font.h"

//added by Mike, 20220127
#include "UsbongUtils.h"

#include <string.h>

//added by Mike, 20201217
//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
    #include <windows.h> //Windows Machine
#endif
/*
 #ifdef linux
 printf("In Linux");
 #endif
 */

//#include "ModelPool.h"

//added by Mike, 20210130
//TO-DO: -reverify: fire beam down, move left up not OK
//TO-DO: -reverify: fire beam up, move left down not OK

//edited by Mike, 20201014
//added by Mike, 20201001
enum Keys
{
    /*	//edited by Mike, 20210128
     KEY_UP = 0,
     KEY_DOWN,
     KEY_RIGHT,
     KEY_LEFT,
     KEY_SPACE,
     //edited by Mike, 20201013
     KEY_ENTER,
     //TO-DO: -verify: gamepad
     KEY_A,
     KEY_D,
     KEY_W,
     KEY_S,
     */
    //TO-DO: -verify: gamepad
    /*	//edited by Mike, 20210129
     KEY_A = 0,
     KEY_D,
     KEY_W,
     KEY_S,
     */
    KEY_W = 0,
    KEY_S,
    KEY_D,
    KEY_A,
    /* //removed by Mike, 20210130
     KEY_UP,
     KEY_DOWN,
     KEY_RIGHT,
     KEY_LEFT,
     KEY_SPACE,
     KEY_ENTER,
     */
    KEY_J,
    KEY_L,
    KEY_I,
    KEY_K,
    KEY_H, //added by Mike, 20210111
    KEY_U, //added by Mike, 20210121
    
    //added by Mike, 20201226
    iNumOfKeyTypes
};

//edited by Mike, 20201001
//Level2D::RobotShip(): MyDynamicObject(0,0,300)
//edited by Mike, 20201115
//Level2D::RobotShip(): MyDynamicObject(0,0,0)
//edited by Mike, 20210625
//Level2D::Text(float xPos, float yPos, float zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,0.0f, windowWidth, windowHeight)
//edited by Mike, 20220124
//Level2D::Level2D(float xPos, float yPos, float zPos, float fWindowWidth, float fWindowHeight): MyDynamicObject(xPos,yPos,0.0f, fWindowWidth, fWindowHeight)

Level2D::Level2D(SDL_Renderer* mySDLRendererInput, int xPos, int yPos, int zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{ 

    //edited by Mike, 20201001
    //currentState=IN_TITLE_STATE;//MOVING_STATE;
    currentState=MOVING_STATE;
    //added by Mike, 20201201
    currentMovingState=IDLE_MOVING_STATE;
  
  	//removed by Mike, 20220122  
//    fCountTotalFrames=16.0f; //added by Mike, 20210903
   
    invincibleCounter=0;
    currentDeathFrame=0;
       
    //TO-DO: -update: this
    //note: float xPos as parameter to int myXPosAsPixel not correct output
    //edited by Mike, 20210613
    iMyXPosAsPixel=(int)xPos;//320;//(int)xPos;
    iMyYPosAsPixel=(int)yPos;
    iMyZPosAsPixel=(int)zPos;
    
    //added by Mike, 20210923
    fMyCanvasPosX=0;
    fMyCanvasPosY=0;
    fMyCanvasPosZ=0;
    
    //    printf(">>myXPosAsPixel: %i\n",myXPosAsPixel);
    
    
    /*
     myWidth=0.5f;
     myHeight=0.5f;
     */
    //added by Mike, 20201001; edited again by Mike, 20201001
    //note: initial position, top-left
    /*    myXPos=0.0f;
     myYPos=0+myHeight;//0.1f;
     */

/* //removed by Mike, 20220122    
    myXPos=xPos;
    myYPos=yPos;
    myZPos=zPos;
*/
    
		fMyWindowWidth=windowWidth;
		fMyWindowHeight=windowHeight;
			
/* //removed by Mike, 20220124
      
    //edited by Mike, 20210724; edited by Mike, 20210921
//    iRowCountMax=10;
    iRowCountMax=10+2;
    
    //edited by Mike, 20210920
    //note: column 1 NOT anymore drawn to eliminate noticeable drawing by computer during scroll movement; 
    //start column: 0;
//    iColumnCountMax=18;
//    iColumnCountMax=18+1;
    iColumnCountMax=18+2;

    iHeightCountMax=10;
        
    fGridSquareWidth = (fMyWindowWidth)/iColumnCountMax; //example: 136.60
    fGridSquareHeight = (fMyWindowHeight)/iRowCountMax; //example: 76.80
    
    printf("Level2D.cpp; fGridSquareWidth: %f",fGridSquareWidth); //75.888885, instead of 75.000000
    
    //auto-set width and height based on grid tile
    iMyWidthAsPixel=fGridSquareWidth;
    iMyHeightAsPixel=fGridSquareHeight;    

    iStepXAsPixel=fGridSquareWidth/10;
    iStepYAsPixel=fGridSquareHeight/10;
    iStepZAsPixel=fGridSquareWidth/10;
*/    
    
    //added by Mike, 20210910
    fMyCanvasPosPrevX=0.0f;
    fMyCanvasPosPrevY=0.0f;
    fMyCanvasPosPrevZ=0.0f;
    
    //edited by Mike, 20210918
    iCurrentLevelMapContainerOffsetZ=0;
    iCurrentLevelMapContainerOffsetX=0;
    iCurrentLevelMapContainerOffsetY=0;

/*
		//TO-DO: -update: tile collision instructions due to uses integer,
		//causes incorrect output when movement has fraction using float number classification
		//edited by Mike, 20210920
    iCurrentLevelMapContainerOffsetZ=-1;
    iCurrentLevelMapContainerOffsetX=-1;
    iCurrentLevelMapContainerOffsetY=-1;    
*/

/*
    iCurrentLevelMapContainerOffsetZ=1;
    iCurrentLevelMapContainerOffsetX=1;
    iCurrentLevelMapContainerOffsetY=1;    
*/
    //added by Mike, 20210911
    MAX_X_AXIS_VIEWPORT=iColumnCountMax;//*fGridSquareWidth;
    MAX_Y_AXIS_VIEWPORT=iRowCountMax;//*fGridSquareHeight;
   
/*//removed by Mike, 20210913   
    fPrevX=0.0f;
    fPrevY=0.0f;
    fPrevZ=0.0f;
*/
    
    fStepMovemenGridZ=0;
    fStepMovemenGridX=0;
		fStepMovemenGridY=0;
    
    
    /*
     printf("fGridSquareWidth: %f\n",fGridSquareWidth);
     printf("fGridSquareHeight: %f\n",fGridSquareHeight);
     */
     
/* //removed by Mike, 20220122     
    //added by Mike, 20210626
    fMyWindowWidthAsPixelRatioToHeightPixel=1.0f;
    iMyWindowWidthAsPixelOffset=0; //added by Mike, 20210701
*/
		
		//added by Mike, 20220127
    myUsbongUtils = new UsbongUtils();
    myUsbongUtils->setWindowWidthHeight(fMyWindowWidth, fMyWindowHeight);
    
/*    //edited by Mike, 20210831
    myWidth=16.0f;
    myHeight=16.0f;
*/
/* //edited by Mike, 20220125
    iMyWidthAsPixel=fGridSquareWidth; //64; //16;
    iMyHeightAsPixel=fGridSquareHeight; //64; //16;
*/
    iMyWidthAsPixel=64; //fGridSquareWidth; //64; //16;
    iMyHeightAsPixel=64; //fGridSquareHeight; //64; //16;
        
    
//    printf("Level2D.cpp myWindowWidth: %f\n",myWindowWidth);
    
    //removed by Mike, 20210423
    /*	loadTexture(myBodyTexture, "bodyTexture.tga", &myBodyTextureObject);
     loadTexture(myHeadTexture, "headTexture.tga", &myHeadTextureObject);
     */
    
    //added by Mike, 20210618
    isAtMaxTextCharRow=false;
    idrawPressNextSymbolCount=0;
    
    //removed by Mike, 20201001; added by Mike, 20210423;
    //removed by Mike, 20210722
//    setup();
    
    setCollidable(true);
/*    
    if (checkIsCollidable()) {
    	printf(">>COLLIDABLE");
    }
*/    
    //added: function to be reusable
    //    readInputText("inputHalimbawa.txt");
    //edited by Mike, 20210712
    //    readInputText("inputLevel1.csv");
    
    read((char*)"inputLevel1.csv");
    
    //added by Mike, 20220125
		mySDLRenderer = mySDLRendererInput;
  	texture = loadTexture((char*)"textures/level2D.png");    
    
    //edited by Mike, 20210707; removed by Mike, 20210827
//    setupLevel(LEVEL_2D_TEXTURE); //LEVEL_TEXTURE
    //edited by Mike, 20210831
//    openGLITexture = openGLLoadTexture((char*)"textures/level2D.png", &fMyWindowWidth, &fMyWindowHeight);

		//removed by Mike, 20220122
    //openGLITexture = openGLLoadTexture((char*)"textures/level2D.png", fMyWindowWidth, fMyWindowHeight);

//    printf("openGLITexture: %i",openGLITexture);
}

Level2D::~Level2D()
{
}


//added by Mike, 20210130
//TO-DO: -reverify: this
float* Level2D::getXYZPos()
{
    //float myXYZ[3];
    float* myXYZ;
    myXYZ = (float*) malloc(3*sizeof(float));
    
    myXYZ[0]=iMyXPosAsPixel;
    myXYZ[1]=iMyYPosAsPixel;
    myXYZ[2]=iMyZPosAsPixel;
    
    return myXYZ;
}

//added by Mike, 20220125; edited by Mike, 20220127
//void Level2D::drawTileWithTexture(std::string sTileId) {	
void Level2D::drawTileWithTexture(std::string sTileId, int iColumnCount, int iRowCount) {	
  	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;
  	
		//TO-DO: -add: this  	
/*
	  fTx = 0.0f+0.0625f*(myUsbongUtils->autoIdentifyColumnInputInLevelMapContainer(sTileId)); //column
    fTy = 0.0f+0.0625f*(myUsbongUtils->autoIdentifyRowInputInLevelMapContainer(sTileId)); //row    
*/
			
		//OK
//		printf("myUsbongUtils->autoIdentifyColumnInputInLevelMapContainer(sTileId): %i;\n myUsbongUtils->autoIdentifyRowInputInLevelMapContainer(sTileId): %i\n",myUsbongUtils->autoIdentifyColumnInputInLevelMapContainer(sTileId),myUsbongUtils->autoIdentifyRowInputInLevelMapContainer(sTileId));
  	
/*  	
		iCountAnimationFrame=iCountAnimationFrame+1;		               																				

		if (iCountAnimationFrame>=2) { //2 frames of animation only
			iCountAnimationFrame=0;
		}
	    	
  	SrcR.x = 0+iCountAnimationFrame*iMyWidthAsPixel;
  	SrcR.y = 0+iCurrentKeyInput*iMyHeightAsPixel;
*/
/* //edited by Mike, 20220127
  	SrcR.x = 0;
  	SrcR.y = 0;
*/
  	SrcR.x = 0+iMyWidthAsPixel*(myUsbongUtils->autoIdentifyColumnInputInLevelMapContainer(sTileId));
  	SrcR.y = 0+iMyHeightAsPixel*(myUsbongUtils->autoIdentifyRowInputInLevelMapContainer(sTileId));
	
  	SrcR.w = iMyWidthAsPixel; 
  	SrcR.h = iMyHeightAsPixel; 
	
//	printf("iMyWidthAsPixel: %i\n",iMyWidthAsPixel);

/* //edited by Mike, 20220127	
  	DestR.x = 0; //getXPos();
  	DestR.y = 0; //getYPos();  	
*/

/*
	printf("fGridSquareWidth: %i\n",64); //fGridSquareWidth);
	printf("fGridSquareHeight: %i\n",64);//fGridSquareHeight);
*/

  	DestR.x = 0+getXPos()+iColumnCount*fGridSquareWidth;
  	DestR.y = 0+getYPos()+iRowCount*fGridSquareHeight;

/* //edited by Mike, 20211209  	
  	DestR.w = iMyWidthAsPixel;
  	DestR.h = iMyHeightAsPixel;
*/
  	DestR.w = fGridSquareWidth;
  	DestR.h = fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);
}


//added by Mike, 20210708; edited by Mike, 20210910
//TO-DO: -add: function with tile patterns
void Level2D::drawLevelWithTextureUsingInputFileNoScrollYet()
{
    /*
     for (int iRowCountToSetDefault=0; iRowCountToSetDefault<MAX_TEXT_CHAR_ROW_RAM; iRowCountToSetDefault++) {
     	for (int iColumnCount=0; iColumnCount<MAX_TEXT_CHAR_COLUMN; iColumnCount++) {
     //verified: in macOS, with Japanese keyboard ro-maji input, "¥0", backspace is "¥"
     tempText[iRowCountToSetDefault][iColumnCount]='\0';
     	}
     }
     */
    
/* //removed by Mike, 20210830
    //TO-DO: -update: this
    glPushMatrix();
        drawTileAsQuadWithTexture("0-0");
    glPopMatrix();
    return;
*/
    
    iRowCountMax=MAX_Y_AXIS_MAP; //10
    iColumnCountMax=MAX_X_AXIS_MAP; //14
    iHeightCountMax=MAX_Y_AXIS_MAP; //10
        
    for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
        //iCurrentMaxColumnCountPerRowContainer[iRowCount];
        for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
            //                if (cCurrentTextContainer[iRowCount][iColumnCount]) {
  					//edited by Mike, 20210719
//            if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("\"A1\"") == 0) { //TRUE
    				//note: "0" for empty, instead of "-1"
    				//with "0", no need to add quotation marks
            if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("0") == 0) { //TRUE
            }
            else {
/* //removed by Mike, 20220122 										            
                glPushMatrix();

//                glTranslatef(0.0f+(fGridSquareWidth)*(iColumnCount+1.0f), 0.0f+(fGridSquareHeight)*(iRowCount+1.0f), 0.0f);
								//edited by Mike, 20210920
                myXPos=0.0f+(fGridSquareWidth)*(iColumnCount);//+1.0f);
//                myXPos=0.0f+(fGridSquareWidth)*(iColumnCount-1.0f);

                myYPos=0.0f+(fGridSquareHeight)*(iRowCount);//+1.0f);
                
 										//edited by Mike, 20210719
//                	drawTileA	glBindTexture(GL_TEXTURE_2D, textureid);
										glEnable(GL_TEXTURE_2D);
//	drawTileAsQuadWithTexture();
//note: incorrect output if we use printf(...) with std::string as input to %s
                
                //added by Mike, 20210725
                //note: use this Command to verify if inputLevel1.csv uses correct quotation mark encoding
                //reminder: we use the same quotation mark for opening and closing
                //in macOS, use XCode to edit input file, e.g. inputLevel1.csv;
                //this is instead of TextEdit
//std::cout << "sCurrentLevelMapContainer[iRowCount][iColumnCount]): " << sCurrentLevelMapContainer[iRowCount][iColumnCount] << "\n";
                
                		drawTileAsQuadWithTexture(sCurrentLevelMapContainer[iRowCount][iColumnCount]);
                glPopMatrix();
*/

							//TO-DO: -add: auto-draw Tile image of read inputs

//std::cout << "sCurrentLevelMapContainer[iRowCount][iColumnCount]): " << sCurrentLevelMapContainer[iRowCount][iColumnCount] << "\n";

							//added by Mike, 20220125; edited by Mike, 20220127
//							drawTileWithTexture(sCurrentLevelMapContainer[iRowCount][iColumnCount]);
							drawTileWithTexture(sCurrentLevelMapContainer[iRowCount][iColumnCount],iColumnCount,iRowCount);

            }
        }
    }
}

 //edited by Mike, 20210923
//added by Mike, 20210911
void Level2D::setPilotStep(float fPilotStepX, float fPilotStepY, float fPilotStepZ) {
    
//    printf(">>fPilotStepX: %f",fPilotStepX);
    
    iStepXAsPixel=fPilotStepX;
    iStepYAsPixel=fPilotStepY;
    iStepZAsPixel=fPilotStepZ;
}

/*
void Level2D::setPilot(Pilot* myPilotInput) {
	myPilot = myPilotInput;
}
*/

//added by Mike, 20210708; edited by Mike, 20210712
//TO-DO: -add: function with tile patterns

//added by Mike, 20210916
//TO-DO: -update: instructions to already auto-draw the column after the 1st column or last column of viewport
//This action is to eliminate noticeable drawing of tile during scroll movement, e.g. horizontal scroll action

//edited by Mike, 20210923
//void Level2D::drawLevelMapInViewPort(GLfloat fMyCanvasPosXInput, GLfloat fMyCanvasPosYInput, GLfloat fMyCanvasPosZInput, GLfloat fX, GLfloat fY, GLfloat fZ)
void Level2D::drawLevelMapInViewPort(float fX, float fY, float fZ)
{
/* //removed by Mike, 20210923
	 //added by Mike, 20210916
	  fMyCanvasPosX = fMyCanvasPosXInput;
    fMyCanvasPosY = fMyCanvasPosYInput;
    fMyCanvasPosZ = fMyCanvasPosYInput;
*/
    
    float fMovementGridZ=0.0f;
    float fMovementGridX=0.0f;
    float fMovementGridY=0.0f;
 
    fMovementGridX=0;
    fMovementGridY=0; //added by Mike, 20210921
        
/*	//removed by Mike, 20210914
    printf(">>fMyCanvasPosPrevX: %f; fMyCanvasPosX: %f\n",fMyCanvasPosPrevX,fMyCanvasPosX);
    printf(">>fX: %f\n",fX);    
*/
    
    if (fMyCanvasPosX<=0) {
    		fMyCanvasPosX=0;
        fMyCanvasPosPrevX=0;        
    		iCurrentLevelMapContainerOffsetX=0;
				fStepMovemenGridX=0;        
    }
    
    //added by Mike, 20210921; edited by Mike, 20210924
    if (fMyCanvasPosY<=0) {
//    if (fY<=0) {
				fMyCanvasPosY=0;
        fMyCanvasPosPrevY=0;
    		iCurrentLevelMapContainerOffsetY=0;
				fStepMovemenGridY=0;        
    }
		
		//added by Mike, 20210922
		//TO-DO: -fix: fMyCanvasPosX adds negatively when moving left at left-most border
		//TO-DO: -reverify: fMyCanvasPosY 

//    printf(">>getStepX(): %f\n",getStepX());


		//added by Mike, 20210922		
	  printf(">>fMyCanvasPosPrevX: %f; fMyCanvasPosX: %f\n",fMyCanvasPosPrevX,fMyCanvasPosX);
    printf(">>fX: %f\n",fX);    
//    printf(">>fMyWindowWidth/2: %f\n",fMyWindowWidth/2);    		
    printf(">>fMyWindowWidth/2-getWidth(): %f\n",fMyWindowWidth/2-getWidth());    		
    printf(">>getStepX(): %f\n",getStepX()); //added by Mike, 20210922


/*
	  printf(">>fMyCanvasPosPrevY: %f; fMyCanvasPosY: %f\n",fMyCanvasPosPrevY,fMyCanvasPosY);
    printf(">>fY: %f\n",fY);    
//    printf(">>fMyWindowWidth/2: %f\n",fMyWindowWidth/2);    		
    printf(">>fMyWindowHeight/2-getHeight(): %f\n",fMyWindowHeight/2-getHeight());    		
    printf(">>getStepY(): %f\n",getStepY()); //added by Mike, 20210922
*/
		
		//edited by Mike, 20210924
//		if (fX==(fMyWindowWidth/2-getWidth())) {
		if (fX<=(fMyWindowWidth/2-getWidth())) {
    		if (fMyCanvasPosPrevX!=fMyCanvasPosX) {
/*
	  printf(">>fMyCanvasPosPrevX: %f; fMyCanvasPosX: %f\n",fMyCanvasPosPrevX,fMyCanvasPosX);
    printf(">>fX: %f\n",fX);    
*/

	//edited by Mike, 20210913
   fMovementGridX = (fMyCanvasPosX-fMyCanvasPosPrevX);
 
   //x-axis
   //TO-DO: -update: this to use set value of canvasStepX
   //note: canvasStepX=3.2f (previous); now 3.5...
   if (fMovementGridX < 0) { //moved backward
     fStepMovemenGridX=(fStepMovemenGridX-getStepX());
   }
   else if (fMovementGridX == 0) { //no movement in X-axis
   }
   else {
     fStepMovemenGridX=(fStepMovemenGridX+getStepX());
   }	
   
//    std::cout << "fStepMovemenGridX: " << fStepMovemenGridX << "\n";
//    std::cout << ">>>>fGridSquareWidth: " << fGridSquareWidth << "\n";

    fMovementGridX = 0;
    
    //added by Mike, 20210911; edited by Mike, 20210916
		//TO-DO: -reverify: collision detection and auto-drawn tile object NOT synchronized


		//edited by Mike, 20210914
    if (fStepMovemenGridX>=fGridSquareWidth) {
        fMovementGridX = 1*(fStepMovemenGridX/fGridSquareWidth); //1;
        fStepMovemenGridX=fStepMovemenGridX-fGridSquareWidth;//0;
    }
    else if (fStepMovemenGridX<=-fGridSquareWidth) {    
        fMovementGridX = 1*(fStepMovemenGridX/fGridSquareWidth); //-1
        fStepMovemenGridX=fStepMovemenGridX+fGridSquareWidth;//0;
    }
    

    		std::cout << "fMovementGridX: " << fMovementGridX << "\n";
		
				
    		iCurrentLevelMapContainerOffsetX += (int) fMovementGridX;
                		
    		//added by Mike, 20210916
    		//TO-DO: -reverify: if there exists as input DASH Command
            //edited by Mike, 20210922
		//    if (fX<=0) {
    		if ((fX<=0) || (fX<fGridSquareWidth)){
    			//edited by Mike, 20210922
    			fMyCanvasPosX=0;
//    			fMyCanvasPosX=0+getStepX();
    		    			    			
    			iCurrentLevelMapContainerOffsetX=0;
    			
    			//added by Mike, 20210922
					fX=0;
                
                //edited by Mike, 20210923
                //TO-DO: -reverify: cause of need for Pilot to return to fX <=0
                //to stop excess fMyCanvasPosX + Pilot's stepX for 1 time.
                //afterward, excess stepX canvas movement returns;
                //return to fX <=0 to again stop
					fStepMovemenGridX=0;
//                fStepMovemenGridX=0+getStepX();

            }
		}

   	//added by Mike, 20210922
    else {
//    	   fStepMovemenGridX = fMyWindowWidth/2-myWidth+fX; 

/*	//note: using std::cout, float value trimmed or rounded
    std::cout << ">>>>getFMyCanvasPosX(): " << getFMyCanvasPosX() << "\n";
    std::cout << ">>>>fX: " << fX << "\n";
*/

		printf("getFMyCanvasPosX: %f\n",getFMyCanvasPosX());    
		printf("fX: %f\n",fX);    
/*
		//notes:
>>fMyCanvasPosPrevX: 607.111023; fMyCanvasPosX: 607.111023
>>fX: 607.111084
>>fMyWindowWidth/2: 683.000000
getFMyCanvasPosX: 607.111023 //macOS: 561.777771

--

>>fMyCanvasPosPrevX: 614.699890; fMyCanvasPosX: 614.699890
>>fX: 607.111084
>>fMyWindowWidth/2: 683.000000
getFMyCanvasPosX: 614.699890 //macOS: 554.666687

--

>>getStepX(): 7.588889 //macOS: 7.111112

//excess stepX
*/

        
/*
				if (getFMyCanvasPosX()<=(fMyWindowWidth/2-getWidth())) {
        	if (fX<=(fMyWindowWidth/2-getWidth())) {
						fMyCanvasPosX=fMyCanvasPosX+getStepX();
        	}
				}        	
*/				
/* //removed by Mike, 20210922
        //TO-DO: -reverify: this
				if (getFMyCanvasPosX()==(fMyWfMyWindowWidthindowWidth/2-getWidth())) {
						fMyCanvasPosX=fMyCanvasPosX-getStepX();
				}
*/
    }    
}
//-------------------------------------------------		
/*
	  printf(">>fMyCanvasPosPrevY: %f; fMyCanvasPosY: %f\n",fMyCanvasPosPrevY,fMyCanvasPosY);
    printf(">>fY: %f\n",fY);    
    printf(">>fMyWindowHeight/2: %f\n",fMyWindowHeight/2);    
*/		
		//reminder: TOP-LEFT origin
		//added by Mike, 20210921
		//edited by Mike, 20210921
/*	//edited by Mike, 2fMyCanvasPosX0210922		
		if ((fY==(fMyWindowHeight/2-getHeight())) &&
//		if ((fY==(fMyWindowHeight/2+getHeight())) &&
    		(fMyCanvasPosPrevY!=fMyCanvasPosY)) {
*/
		//edited by Mike, 20210924
//		if (fY==(fMyWindowHeight/2-getHeight())) {		
		if (fY<=(fMyWindowHeight/2-getHeight())) {		
    		if (fMyCanvasPosPrevY!=fMyCanvasPosY) {
/*
	  printf(">>fMyCanvasPosPrevY: %f; fMyCanvasPosY: %f\n",fMyCanvasPosPrevY,fMyCanvasPosY);
    printf(">>fY: %f\n",fY);    
*/

	 //edited by Mike, 20210921; reminder: origin: TOP-LEFT
   fMovementGridY = (fMyCanvasPosY-fMyCanvasPosPrevY);
//   fMovementGridY = (fMyCanvasPosPrevY-fMyCanvasPosY);
 
   //y-axis
   if (fMovementGridY < 0) { //moved upward
     fStepMovemenGridY=(fStepMovemenGridY-getStepY());				
		}
   else if (fMovementGridY == 0) { //no movement in Y-axis
   }
   else {
     fStepMovemenGridY=(fStepMovemenGridY+getStepY());     
   }	
   
//    std::cout << "fStepMovemenGridY: " << fStepMovemenGridY << "\n";
//    std::cout << ">>>>fGridSquareHeight: " << fGridSquareHeight << "\n";

    fMovementGridY = 0;
    
    //TO-DO: -eliminate: excess instructions
    if (fStepMovemenGridY>=fGridSquareHeight) {
        fMovementGridY = 1*(fStepMovemenGridY/fGridSquareHeight); //1;
        fStepMovemenGridY=fStepMovemenGridY-fGridSquareHeight;//0;
//        fStepMovemenGridY=fStepMovemenGridY+fGridSquareHeight;//0;
    }
    else if (fStepMovemenGridY<=-fGridSquareHeight) {    
        fMovementGridY = 1*(fStepMovemenGridY/fGridSquareHeight); //-1
       	fStepMovemenGridY=fStepMovemenGridY+fGridSquareHeight;//0;
//        fStepMovemenGridY=fStepMovemenGridY-fGridSquareHeight;//0;
    }
    

    std::cout << "fMovementGridY: " << fMovementGridY << "\n";

		
    iCurrentLevelMapContainerOffsetY += (int) fMovementGridY;
                   
    //added by Mike, 20210922
    //TO-DO: -reverify: excess fStepMovemenGridY to cause incorrect grids for auto-drawing and collision detection 
    //TO-DO: -reverify: excess fStepMovemenGridX to cause incorrect grids for auto-drawing and collision detection 
                   
    //added by Mike, 20210916
    //TO-DO: -reverify: if there exists as input DASH Command
    //edited by Mike, 20210922
//    if (fY<=0) {
    	if ((fY<=0) || (fY<fGridSquareHeight)){
    		fMyCanvasPosY=0;
    		iCurrentLevelMapContainerOffsetY=0;
    		
    		//added by Mike, 20210922
				fY=0;
				fStepMovemenGridY=0;
    	}    
    }
    //added by Mike, 20210922
    else {
    	
    }    
}
//-------------------------------------------------		
    
	
/*
    //added by Mike, 20210309
   //TO-DO: -reverify: iMovementGridZ, etc value
   std::cout << "iMovementGridZ: " << iMovementGridZ << "\n";
   std::cout << "iMovementGridX: " << iMovementGridX << "\n";
*/
  
/*   	//removed by Mike, 20210921    		
   	iCurrentLevelMapContainerOffsetZ += fMovementGridZ;
    iCurrentLevelMapContainerOffsetY += (int)fMovementGridY;
*/

    //added by Mike, 20210911
    if (iCurrentLevelMapContainerOffsetX<0) {
        iCurrentLevelMapContainerOffsetX=0;
        fMyCanvasPosPrevX=0;
        fMyCanvasPosX=0;
//        fMovementGridX=0; //removed by Mike, 20210915
    }

		//added by Mike, 20210921
    if (iCurrentLevelMapContainerOffsetY<0) {
        iCurrentLevelMapContainerOffsetY=0;
        fMyCanvasPosPrevY=0;
        fMyCanvasPosY=0;
//        fMovementGridY=0; //removed by Mike, 20210915
    }
    
   	int iRowCount=iCurrentLevelMapContainerOffsetY;
   	iCurrentLevelMapContainerOffsetMaxViewPortY=iRowCount+MAX_Y_AXIS_VIEWPORT;
		   
		//added by Mike, 20210921
   	 if ((iRowCount<0) or (iCurrentLevelMapContainerOffsetY<0)) {
	 	 		iRowCount=0;
        //added by Mike, 20210912
        iCurrentLevelMapContainerOffsetMaxViewPortY=iRowCountMax;
		 }
   	 else if (iCurrentLevelMapContainerOffsetY>=MAX_INPUT_TEXT_PER_LINE) {
        //edited by Mike, 20210912
	 			//iColumnCount=MAX_INPUT_TEXT_PER_LINE-1;
        iRowCount=MAX_INPUT_TEXT_PER_LINE-1-iRowCountMax;
         
	 			iCurrentLevelMapContainerOffsetY=MAX_INPUT_TEXT_PER_LINE-1;
   	 }		
		 
		   
 //--
    //added by Mike, 20210912
    //TO-DO: -update: instructions to set Pilot to be at center horizontal and vertical;
    //if at column 0 or at column end, Pilot can move awayGLfloat fX, GLfloat fY, GLfloat fZ,  from center
    //TO-DO: -reverify: scroll movement backward to be OK
    
    //TO-DO: -update: scrolling instructions to be NOT by fGridSquareWidth;
    //--> add: fractions of fGridSquareWidth
    
  	//edited by Mike, 20210910      iCurrentLevelMapContainerOffsetMaxViewPortY
//    for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
		for (;iRowCount<iCurrentLevelMapContainerOffsetMaxViewPortY; iRowCount++) {
		
	 //added by Mike, 20210910; edited by Mike, 20210920
     int iColumnCount=iCurrentLevelMapContainerOffsetX;
     iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCount+MAX_X_AXIS_VIEWPORT;
		        
//        int iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCount+MAX_X_AXIS_VIEWPORT-1;

   	 if ((iColumnCount<0) or (iCurrentLevelMapContainerOffsetX<0)) {
	 	 		iColumnCount=0;
        //added by Mike, 20210912
        iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCountMax;
		 }
   	 else if (iCurrentLevelMapContainerOffsetX>=MAX_INPUT_TEXT_PER_LINE) {
        //edited by Mike, 20210912
	 			//iColumnCount=MAX_INPUT_TEXT_PER_LINE-1;
        iColumnCount=MAX_INPUT_TEXT_PER_LINE-1-iColumnCountMax;
         
	 			iCurrentLevelMapContainerOffsetX=MAX_INPUT_TEXT_PER_LINE-1;
   	 }
       
  			//edited by Mike, 20210920
				for (;iColumnCount<iCurrentLevelMapContainerOffsetMaxViewPortX; iColumnCount++) {
//				for (;iColumnCount<iCurrentLevelMapContainerOffsetMaxViewPortX+1; iColumnCount++) {

            //                if (cCurrentTextContainer[iRowCount][iColumnCount]) {
  					//edited by Mike, 20210719
//            if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("\"A1\"") == 0) { //TRUE
    				//note: "0" for empty, instead of "-1"
    				//with "0", no need to add quotation marks
            if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("0") == 0) { //TRUE
            }
            else {
            
/* //TO-DO: -update: this            
                glPushMatrix();
                	//add +1.0f in x-axis and y-axis due to 3rd quadrant in the draw function
                	//center 0,0,0 origin; vertex positions
  								
								//TO-DO: -reverify: cause of skipping to previous column when executing backward movement
								//edited by Mike, 20210916
//								if (fMovementGridX==fGridSquareWidth) {
								if ((fMovementGridX==fGridSquareWidth) || (fMovementGridX==(fGridSquareWidth*-1))) {								                									myXPos=0.0f+(fGridSquareWidth)*(iColumnCount-iCurrentLevelMapContainerOffsetX);
								}
								else {
                  //edited by Mike, 20210916
                  myXPos=0.0f+(fGridSquareWidth)*(iColumnCount-iCurrentLevelMapContainerOffsetX)-fStepMovemenGridX;
								}

								//edited by Mike, 20210921
                if ((fMovementGridY==fGridSquareHeight) || (fMovementGridY==(fGridSquareHeight*-1))) {                    
                    myYPos=0.0f+(fGridSquareHeight)*(iRowCount-iCurrentLevelMapContainerOffsetY);
								}
								else {
									//edited by Mike, 20210916
                	myYPos=0.0f+(fGridSquareHeight)*(iRowCount-iCurrentLevelMapContainerOffsetY)-fStepMovemenGridY;
								}


 										//edited by Mike, 20210719
//                	drawTileA	glBindTexture(GL_TEXTURE_2D, textureid);
										glEnable(GL_TEXTURE_2D);

                		drawTileAsQuadWithTexture(sCurrentLevelMapContainer[iRowCount][iColumnCount]);
                glPopMatrix();
*/
                
            }
        }
    }
    

	//added by Mike, 20210306; edited by Mike, 20210308	
	//note: does NOT yet include the stepX when there is column movement
	fMyCanvasPosPrevX=fMyCanvasPosX;
	fMyCanvasPosPrevY=fMyCanvasPosY;
	fMyCanvasPosPrevZ=fMyCanvasPosZ;
    
}

void Level2D::update(float dt)
{  
}

void Level2D::changeState(int s)
{
    currentState=s;
}

//added by Mike, 20201226
void Level2D::keyDown(int keyCode) {
    myKeysDown[keyCode] = TRUE;
}

void Level2D::keyUp(int keyCode) {
    myKeysDown[keyCode] = FALSE;
}

/* //removed by Mike, 20220122
//edited by Mike, 20210923
//void Level2D::move(int key)
void Level2D::move(int key, MyDynamicObject* mdoPilot)
{
    switch(key) {
        case KEY_A:
        		//edited by Mike, 20210923
            fMyCanvasPosX = fMyCanvasPosX-stepX;			
            break;
        case KEY_D:
        		//edited by Mike, 20210924
//            fMyCanvasPosX = fMyCanvasPosX+stepX;
            
            if (mdoPilot->getX()<=fMyWindowWidth/2-getWidth()-getStepX()) {
						}
						else {
            	fMyCanvasPosX = fMyCanvasPosX+stepX;
						}
						
            break;
       case KEY_W:
       			//edited by Mike, 20210924
            fMyCanvasPosY = fMyCanvasPosY-stepY;
            break;
        case KEY_S:
        			//edited by Mike, 20210924
        			//TO-DO: -reverify: this due to fMyCanvasPosY 
        			//should be set to zero until Pilot is at center vertically
        			//to correctly execute collision detection with tiles
//            fMyCanvasPosY = fMyCanvasPosY+stepY;
            
            //edited by Mike, 20210924
//            if (mdoPilot->getY()+getStepY()<fMyWindowHeight/2-getHeight()-getStepY()) {
            if (mdoPilot->getY()<=fMyWindowHeight/2-getHeight()-getStepY()) {
						}
						else {
            	fMyCanvasPosY = fMyCanvasPosY+stepY;
						}
            break;            
    }        
}
*/

//edited by Mike, 20220128
bool Level2D::isLevel2DCollideWith(MyDynamicObject* mdo)
{    
    if ((!checkIsCollidable())||(!mdo->checkIsCollidable()))    
    {
    		printf(">>>>>NOT COLLIDABLE");
        return false;
    }

/*     
printf(">>>> iCurrentLevelMapContainerOffsetY: %i;",iCurrentLevelMapContainerOffsetY);
//printf(">>>> iCurrentLevelMapContainerOffsetX: %i;\n",iCurrentLevelMapContainerOffsetX);
  
printf(">>>> iCurrentLevelMapContainerOffsetMaxViewPortY: %i;",iCurrentLevelMapContainerOffsetMaxViewPortY);
//printf(">>>> iCurrentLevelMapContainerOffsetMaxViewPortX: %i;\n",iCurrentLevelMapContainerOffsetMaxViewPortX);
*/

    int iStartRowCount=0; //7;
    int iStartColumnCount=0; //1//6; //7;

/*
		//added by Mike, 20220128					
    iRowCountMax=MAX_Y_AXIS_MAP; //10
    iColumnCountMax=MAX_X_AXIS_MAP; //14
    iHeightCountMax=MAX_Y_AXIS_MAP; //10					
*/

					
//        for (int iRowCount=iStartRowCount+iCurrentLevelMapContainerOffsetY; iRowCount<iCurrentLevelMapContainerOffsetMaxViewPortY; iRowCount++) {
        for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
        
//        for (int iColumnCount=iStartColumnCount+iCurrentLevelMapContainerOffsetX; iColumnCount<iCurrentLevelMapContainerOffsetMaxViewPortX; iColumnCount++) {
        for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
               
//printf(">>>> iRowCount: %i; iColumnCount: %i;",iRowCount,iColumnCount);
    				//note: "0" for empty, instead of "-1"
    				//with "0", no need to add quotation marks
            if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("0") == 0) { //TRUE
            }
            else {
            
            //added by Mike, 20220128; edited by Mike, 20220130
  	
                if (mdo->collideWithLevel2DTileRect(0.0f+fGridSquareWidth*(iColumnCount)-fStepMovemenGridX,0.0f+fGridSquareHeight*(iRowCount)-fStepMovemenGridY, fGridSquareWidth, fGridSquareHeight)) {
                    
//                	printf(">>>>> fGridSquareWidth: %f",fGridSquareWidth); 	
                    return this->hitByAtTile(mdo, sCurrentLevelMapContainer[iRowCount][iColumnCount],
                                             0.0f+fGridSquareWidth*(iColumnCount)-fStepMovemenGridX,
                                             0.0f+fGridSquareHeight*(iRowCount)-fStepMovemenGridY);
  				}  		

/* //removed by Mike, 20220122
                if (mdo->collideWithLevel2DTileRect(0.0f+fGridSquareWidth*(iColumnCount-iCurrentLevelMapContainerOffsetX-1)-fStepMovemenGridX,0.0f+fGridSquareHeight*(iRowCount-iCurrentLevelMapContainerOffsetY-1)-fStepMovemenGridY, fGridSquareWidth, fGridSquareHeight)) {
                    
                printf(">>>>> fGridSquareWidth: %f",fGridSquareWidth);
  	
                    return this->hitByAtTile(mdo, sCurrentLevelMapContainer[iRowCount][iColumnCount],
                                             0.0f+fGridSquareWidth*(iColumnCount-iCurrentLevelMapContainerOffsetX-1)-fStepMovemenGridX,
                                             0.0f+fGridSquareHeight*(iRowCount-iCurrentLevelMapContainerOffsetY-1)-fStepMovemenGridY);

  									}  									
*/  									
		        }		        
		   }
		}
    
    return false;
}

//added by Mike, 20220130
bool Level2D::hitByAtTile(MyDynamicObject* mdo, std::string sTileId, int iTileXPos, int iTileYPos) {
	sTileId = myUsbongUtils->autoDeleteQuotationMark(sTileId);
//    std::cout << "autoDeleted sTileId: " << sTileId << "\n";

		//TO-DO: -set: all tiles in row 0, classifed as wall collision?
    if (sTileId.compare("0-0") == 0) {//True 
    	return true;
  	}
  	
  	return false;
}

void Level2D::hitBy(MyDynamicObject* mdo)
{
    //changeState(DEATH_STATE);
    //setCollidable(false);
//    myOpenGLCanvas->loseLife();
    
    //removed by Mike, 20201001
    /*
     zing = sound->load_sound_clip(RESETSOUND);
     sound->play_sound_clip(zing);
     */
    //removed by Mike, 20210725
    //reset();
}

/*	//removed by Mike, 20210522
 void Level2D::setOpenGLCanvas(OpenGLCanvas* c)
 {
 myOpenGLCanvas = c;
 }
 */

void Level2D::reset()
{
/* //removed by Mike, 20210801
    changeState(INITIALIZING_STATE);
    myXPos=0;
    myYPos=0;
    rotationAngle=0.0f;
    thrust=0.0f;
    setCollidable(false);
    invincibleCounter=0;
*/
}
int Level2D::getState()
{
    return currentState;
}

//added by Mike, 20201016
void Level2D::destroy()
{
    /*
     for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
     }
     delete [] explosionParticle;
     */
}

//added by Mike, 20210712
void Level2D::read(char *inputFilename) {
    int c;
    FILE *file;
    
    
    //added by Mike, 20210712
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Level2D read(...)\n");
    
    
    //TO-DO: update: this
    //	char** iCurrentLevelMapContainer = new char[100][100];
    int iRowCount=0;
    int iColumnCount=0;

    for (iRowCount=0; iRowCount<MAX_Y_AXIS_MAP; iRowCount++) {
        for (iColumnCount=0; iColumnCount<MAX_X_AXIS_MAP; iColumnCount++) {
            //edited by Mike, 20210724
//            sCurrentLevelMapContainer[iRowCount][iColumnCount]=(char*)"-1";//'G';
						//edited by Mike, 20220125
            sCurrentLevelMapContainer[iRowCount][iColumnCount]=(char*)"0";
//            sCurrentLevelMapContainer[iRowCount][iColumnCount]=(char*)"0    "; //add space to make output columns aligned
        }
    }
    
    iRowCount=0;
    iColumnCount=0;
				
    //noted by Mike, 20201210
    //note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
    //I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
    //where memory leaks = not deallocated storage in memory, albeit not used by software application
    //identifying not deallocated storage in memory becomes more difficult with increasing use
    char input[MAX_INPUT_TEXT_PER_LINE]; //max size
    char inputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
    char tempInputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
    
    strcpy(input, "input/");
    strcat(input, inputFilename); //already includes .txt
    //	strcat(input,".txt");
    
//    printf("dito: %s",input);
    
    //	file = fopen("input/"+inputFilename, "r"); //.txt file
    //	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
    file = fopen(input, "r"); //.txt file
    
    //TO-DO: -reverify: tile positions
    int iCount=0;
    
    if (file) {
        //edited by Mike, 20210210
        //		while ((c = getc(file)) != EOF) {
        while (fgets (input, MAX_INPUT_TEXT_PER_LINE, file)) { /* read each line of input */
            //	putchar(c);
            
            /*	//removed by Mike, 20210210
             char sRow[2] = {(char)c};
             */
            //delimited using new line
            /*			char *chRow = strtok(sRow, "\n");
             */
            sscanf (input, "%s", inputTextLine);
            
            
            //			iCount=0;
            //input text per line
            //			printf("%i;\n",iCount);
            //			printf("%i;",iCount);
            
            iCount=iCount+1;
            
            //added by Mike, 20210208
            iColumnCount=0;
            
            //removed by Mike, 20210210
            /*
             //			char s[2] = {0};
             //			*s = c;
             //edited by Mike, 20210209
             //				char s[2] = {c};
             //				char s[2] = {itoa(c)};
             char s[2] = {(char)c};
             
             //delimited using comma
             char *ch = strtok(s, ",");
             */
            strcpy(tempInputTextLine,inputTextLine);
            
            //note: add "-1" for empty
            //otherwise, comma as column is skipped
            char *ch = strtok(tempInputTextLine, ",");
            
            while (ch != NULL) {
                //				printf("%i,",iColumnCount);
                
                //TO-DO: use String, instead of char
                //TO-DO: -reverify: output due to "G" not put in container
                //				sCurrentLevelMapContainer[iRowCount][iColumnCount]=&ch;
                sCurrentLevelMapContainer[iRowCount][iColumnCount]=ch;
                
                /*	//edited by Mike, 20210211
                 printf("%s:",ch);
                 printf("%i,",iColumnCount);
                 */
                 
 								//added by Mike, 20220124
                printf("%i:",iColumnCount);
                printf("%s,",ch);
/*
								if (strcmp(ch,"0")==0) {
									//add space to make output columns aligned
                	printf("%s    ,",ch);
								}
								else {
                	printf("%s,",ch);
								}
*/								                
                iColumnCount=iColumnCount+1;
                ch = strtok(NULL, ",");
            }
            
            if (iRowCount<MAX_X_AXIS_MAP) {
                iRowCount=iRowCount+1;
            }
            else {
                iRowCount=0;
            }
            
            printf("\n");
        }
        fclose(file);
    }
}

//--------------------------------------------
