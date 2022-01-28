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
 * @date created: 20210613
 * @date updated: 20220128; from 20220127
 * @website address: http://www.usbong.ph
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007):
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//TO-DO: -update: this

//added by Mike, 20210706
#include <stdlib.h>

/* //removed by Mike, 20210826
//added by Mike, 20201130
#include "CTargaImage.h"
*/

//removed by Mike, 20220122
//#include "OpenGLCanvas.h"

#include "MyDynamicObject.h"
//#include "Pilot.h" //added by Mike, 20210923

//added by Mike, 20201019; removed by Mike, 20220122
//#include "PolygonUtils.h"

//added by Mike, 20210614
#include <string>

//added by Mike, 20201226
#define TRUE 1
#define FALSE 0

//added by Mike, 20210129
//+reverified: with Windows Machine; 5 with Linux Machine
//#define MAX_WAIT_COUNT 5 //4 //added by Mike, 20210126; edited by Mike, 20210128

//added by Mike, 20210423
//TO-DO: -add: texture definitions in PolygolUtils
//edited by Mike, 20210514
//#define MIKE_TEXTURE_A 7
//removed by Mike, 20210521
//added in OpenGLCanvas.h
//#define BUTTON_TEXTURE_A 7

/* //removed by Mike, 20210910
//added by Mike, 20210706
//240/4=60 columns and rows per viewport
//reverify: to be excess due to size of fGridSquareWidth
#define MAX_X_AXIS_VIEWPORT 240
#define MAX_Y_AXIS_VIEWPORT 240
#define MAX_Z_AXIS_VIEWPORT 240
*/

//edited by Mike, 20220122
/*
#define MAX_X_AXIS_MAP 240
#define MAX_Y_AXIS_MAP 240
#define MAX_Z_AXIS_MAP 240
*/
#define MAX_X_AXIS_MAP 14
#define MAX_Y_AXIS_MAP 10

#ifdef _WIN32
#define MAX_WAIT_COUNT 5 //Windows Machine
#endif

#ifdef linux
#define MAX_WAIT_COUNT 5
#endif

//added by Mike, 20210522
#if defined(__APPLE__)
#define MAX_WAIT_COUNT 5
#endif

//edited by Mike, 20220124
//#define MAX_INPUT_TEXT_PER_LINE 240
#define MAX_INPUT_TEXT_PER_LINE MAX_X_AXIS_MAP*5 //14x5; due to value can be "2-0"

//edited by Mike, 20210129
//TO-DO: -add: robotship dash background movement animation
//note: start at 0
//edited by Mike, 20210130
//TO-DO: -reverify: cause why value is 6, not 4 in Linux machine
//edited by Mike, 20210130
//#define PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT 6//4 //10 //added by Mike, 20210128

//removed by Mike, 20220122
/*
#ifdef _WIN32
//edited by Mike, 20210203; edited again by Mike, 20210219
#define PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT 4 //10 //added by Mike, 20210128
//	#define MAX_DIRECTIONAL_KEY_DASH_COUNT 6 //10 //added by Mike, 20210128
#endif

#ifdef linux
//edited by Mike, 20210204; edited again by Mike, 20210219
//	#define MAX_DIRECTIONAL_KEY_DASH_COUNT 6//4 //10 //added by Mike, 20210128
#define PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT 4 //added by Mike, 20210128
#endif
*/

/*
//added by Mike, 20210522; removed by Mike, 20220122
#if defined(__APPLE__)
#define PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT 4
#endif
*/

//added by Mike, 20220127
class UsbongUtils;


//TO-DO: -update: this
class Level2D: public MyDynamicObject
{
private:
    int currentState;
    /*	//removed by Mike, 20201001
     Sound *sound;
     SoundClip *zing;
     */
    
    //added by Mike, 20201201
    int currentMovingState;
    
    /*
     float myXPos;
     float myYPos;
     float myZPos;
     */
  
/* //removed by Mike, 20210912
    //added by Mike, 20210505
    float myOpponentXPos;
    float myOpponentYPos;
    float myOpponentZPos;
*/
    
/* //removed by Mike, 20210912; already exists in MyDynamicObject.h
    float stepX;
    float stepY;
    float stepZ;
*/
    /*
     float myWidthX;
     float myWidthZ;
     float myHeightY;
     */
  
/* //edited by Mike, 20210910
		//note: we use this to verify if the position moved forward, backward, etc
		int iPrevX=0;
		int iPrevY=0;
		int iPrevZ=0;
*/

/*	//edited by Mike, 20210913
    float fPrevX;
    float fPrevY;
    float fPrevZ;
*/
    float fMyCanvasPosPrevX;
    float fMyCanvasPosPrevY;
    float fMyCanvasPosPrevZ;
    
/*    
    //added by Mike, 20210916; edited by Mike, 20210922
    GLfloat fMyCanvasPosX;
    GLfloat fMyCanvasPosY;
    GLfloat fMyCanvasPosZ;
*/
    float fMyCanvasPosX;
    float fMyCanvasPosY;
    float fMyCanvasPosZ;
    
    //added by Mike, 20210910
    float fStepMovemenGridZ,
        fStepMovemenGridX,
        fStepMovemenGridY;
		
		int iCurrentLevelMapContainerOffsetX,
			  iCurrentLevelMapContainerOffsetY,
			  iCurrentLevelMapContainerOffsetZ;
		
		int iCurrentLevelMapContainerOffsetMaxViewPortX,
			  iCurrentLevelMapContainerOffsetMaxViewPortY;
    
    //added by Mike, 20210911
    int MAX_X_AXIS_VIEWPORT;
    int MAX_Y_AXIS_VIEWPORT;
    
    //added by Mike, 20210423
    int iCountTaoAnimationFrame;
    float fButtonAnimationFrameOffset;
  
  	//removed by Mike, 20220122  
//    OpenGLCanvas *myOpenGLCanvas;
    
    //added by Mike, 20210923
//    Pilot *myPilot;
    
		//row, column
		//y-axis, instead of z-axis
		std::string sCurrentLevelMapContainer[MAX_Y_AXIS_MAP][MAX_X_AXIS_MAP]; //TO-DO: -add: auto-update max size 
       
    //added by Mike, 20210516; removed to public classification by Mike, 20210523
    //	UsbongUtils *myUsbongUtils;
    
    //float boundary;
    
    //    float rotationAngle;
    float rotationAngleRad;
    float rotationStep;
    
    float thrust;
    float thrustMax;
    float xAccel;
    float yAccel;
    float xVel;
    float yVel;
    
    float maxXVel;
    float maxYVel;
    
    int invincibleCounter;
    
    unsigned int myDeathAnimationImg1,
    myDeathAnimationImg2,
    myDeathAnimationImg3,
    myDeathAnimationImg4,
    myDeathAnimationImg5;
    int currentDeathFrame;
    
    //int previousFacingState;
    //added by Mike, 20201201
    int currentFacingState;
    
    //added by Mike, 20210111
    int iFiringBeamCount;
    
    //added by Mike, 20210122
    int iPunchAnimationCount,
    iPunchAnimationCountDelay;
    
    //added by Mike, 20210616
    int iTextAnimationCount,
    iTextAnimationCountDelay,
    iTextCurrentMaxColumnCount;
    
    //added by Mike, 20201225
    bool bIsFiringBeam;
    bool bHasPressedADirectionalKey; //added by Mike, 20201226
    
    //added by Mike, 20210111
    bool bIsExecutingPunch,
    bIsExecutingDefend, //added by Mike, 20210112; edited by Mike, 20210121
    //removed by Mike, 20210128
    //		 bIsExecutingDash, //added by Mike, 20210126
    bIsDashReady; //added by Mike, 20210126
    
    //added by Mike, 20210128
    //note: exceed size limit at value 7 due to compiler;
    //set to 6 to execute movement
    //Reference: https://stackoverflow.com/questions/216259/is-there-a-max-array-length-limit-in-c;
    //last accessed: 20210128; answer by: Martin York, 20081019T1752; edited 20130125T2158
    //Additional Note: The following do not solve the problem
    //bool* bIsExecutingDashArray;
    //bool* bIsExecutingDashArray = new bool[6];//PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT];
    
/* //removed by Mike, 20220122    
    bool bIsExecutingDashArray[PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT]; //6
    
    //int iInputWaitCount; //we use with dash
    int iInputWaitCountArray[PILOT_MAX_DIRECTIONAL_KEY_DASH_COUNT]; //6
*/
        
    //added by Mike, 20210614; edited by Mike 20210616
    //std::string sCurrentTextContainer[MAX_TEXT_CHAR_COLUMN][MAX_TEXT_CHAR_ROW]; //TO-DO: -add: auto-update max size
    //edited by Mike, 20210618
    //    char cCurrentTextContainer[MAX_TEXT_CHAR_ROW][MAX_TEXT_CHAR_COLUMN];

    //removed by Mike, 20220124
/*    
    char cCurrentTextContainer[MAX_TEXT_CHAR_ROW_RAM][MAX_TEXT_CHAR_COLUMN];
    
    //added by Mike, 20210616
    int iTextCurrentMaxRowCount;
    //added by Mike, 20210617; edited by Mike, 20210619
    int iCurrentMaxColumnCountPerRowContainer[MAX_TEXT_CHAR_ROW];
    //    int iCurrentMaxColumnCountPerRowContainer[MAX_TEXT_CHAR_ROW_RAM];
*/
    
    //added by Mike, 20210618
    int iRowCountPageNumber; //start at zero
    bool isAtMaxTextCharRow;
    int idrawPressNextSymbolCount;
    
/* //removed by Mike, 20210830 to public from private    
    //added by Mike, 20210724
    int iRowCountMax;
    int iColumnCountMax;
    int iHeightCountMax;
*/    
    
/* //removed by Mike, 20220122    
    GLint tricount;
    GLint isMovingForward;
        
		//added by Mike, 20210703
		int iLevelTextureObject;    	
    
    GLboolean test_pow2(GLushort i);
    void load_tga(char *filename);
    void load_png(char *filename); //added by Mike, 20210816
*/
    
/* //removed by Mike, 20210826    
    //draw texture
    //added by Mike, 20201130
    bool loadTexture(CTargaImage *myTexture, const char *filename, unsigned int *myTextureObject);
*/
    
    //edited by Mike, 20210423
    void setupPrev();
    void setup();
    
    // draws a unit cube
    //void drawCube(float xPos, float yPos, float zPos);
    
    //added by Mike, 20201130
    // draw a unit triangle, Mike Dec. 19, 2006
    void drawTriangle(float xPos, float yPos, float zPos);
    void drawTriangledCube(float xPos, float yPos, float zPos);
        
    //added by Mike, 20210127
    //	void autoVerifyDashStateWithKeyDown(int keyCode); //edited by Mike, 20210128
    void autoVerifyDashStateWithKeyDown();
    
    void autoVerifyDashStateWithKeyUp(int keyCode);
    //edited by Mike, 20210128
    //	void setDashStateWithKeyDown();
    void setDashStateWithKeyDown(int keyCode);
    
    //edited by Mike, 20210129
    //	void setDashStateWithKeyUp();
    void setDashStateWithKeyUp(int keyCode);
    
    //added by Mike, 20210618
    void drawPressNextSymbol();

    //added by Mike, 20210710
    void drawTileAsQuadWithoutTexture();
		//edited by Mike, 20210719
//    void drawTileAsQuadWithTexture(); //added by Mike, 20210717
    void drawTileAsQuadWithTexture(std::string sTileId);    
    
    //added by Mike, 20220125; edited by Mike, 20220127
    //void drawTileWithTexture(std::string sTileId);
		void drawTileWithTexture(std::string sTileId, int iColumnCount, int iRowCount);	
    
public:
    //edited by Mike, 20201115
    //RobotShip();
    //edited by Mike, 20210625
    //    Text(float xPos, float yPos, float zPos,int windowWidth,int windowHeight);
    //edited by Mike, 20210815
//    Level2D(float xPos, float yPos, float zPos, float windowWidth, float windowHeight);

    //edited by Mike, 20220124
//    Level2D(float xPos, float yPos, float zPos, float fWindowWidth, float fWindowHeight);  
    Level2D(SDL_Renderer* mySDLRenderer, int xPos, int yPos, int zPos,int windowWidth,int windowHeight);

    
    ~Level2D();
    
    //added by Mike, 20210830
    int iRowCountMax;
    int iColumnCountMax;
    int iHeightCountMax;
    
    //added by Mike, 20220127
		UsbongUtils *myUsbongUtils;
 
 
/*  //added by Mike, 20210916; edited by Mike, 20210922
    GLfloat getFMyCanvasPosX() {
    	return fMyCanvasPosX;
    }

    GLfloat getFMyCanvasPosY() {
    	return fMyCanvasPosY;
    }
    
    GLfloat getFMyCanvasPosZ() {
    	return fMyCanvasPosZ;
    }
*/
    float getFMyCanvasPosX() {
    	return fMyCanvasPosX;
    }

    float getFMyCanvasPosY() {
    	return fMyCanvasPosY;
    }
    
    float getFMyCanvasPosZ() {
    	return fMyCanvasPosZ;
    }
    
    //added by Mike, 20210922
    void setFMyCanvasPosX(float fInput) {
    	fMyCanvasPosX=fInput;
    }
       
    //added by Mike, 20210703
		void setupLevel(int myLevelTextureObject);
		//removed by Mike, 20210922
		//void draw_char(GLfloat x, GLfloat y, GLfloat z, char c);
    
    //added by Mike, 20210917
    void drawGrid();
    
    //added by Mike, 20201226
    //note: we classify this container as public;
    //otherwise; computer notifies us of error when we update value inside container
   	//edited by Mike, 20201227
   	//TO-DO: -update: this to include diagonal directional movement
    //int myKeysDown[4];
    //edited by Mike, 20210102
    //int myKeysDown[10]; //note: does not include KEY_J, KEY_L, KEY_I, KEY_K,
    //edited by Mike, 20210130
    //	int myKeysDown[14]; //note: includes KEY_J, KEY_L, KEY_I, KEY_K,
    int myKeysDown[10]; //note: includes KEY_J, KEY_L, KEY_I, KEY_K,
    
    //virtual ~Robot();
    float rotationAngle;    
    
    //int STANDING_STATE;
    //int WALKING_STATE;
    float getRotationAngle(){
        return rotationAngle;
    }
    
    float* getXYZPos();
    
    //added by Mike, 20201230
    float getCurrentFacingState() {
        return currentFacingState;
    }
    
    //added by Mike, 20210102; edited by Mike, 20210106
    void setCurrentFacingState(int iNewFacingState) {
        currentFacingState = iNewFacingState;
    }
    
    //added by Mike, 20210911; edited by Mike, 20210923
    void setPilotStep(float fPilotStepX, float fPilotStepY, float fPilotStepZ);
//		void setPilot(Pilot* myPilotInput);
    
    //added by Mike, 20210614MAX_TEXT_CHAR_ROW
    void readInputText(char *inputFilename);    	
    void read(char *inputFilename); ////added by Mike, 20210706
    
    virtual void draw() {
        //edited by Mike, 20210712
//        drawLevelWithTexture();
				
				//removed by Mike, 20210910
				drawLevelWithTextureUsingInputFileNoScrollYet();
//				drawTileAsQuadWithTexture("0-0");
    }
        
    //added by Mike, 20210703; edited by Mike, 20210922
//    void drawTileAsQuadWithTexture(GLfloat x, GLfloat y, GLfloat z, char c);
    void drawTileAsQuadWithTexture(float x, float y, float z, char c);

    void drawTileAsQuadWithTexturePrev(std::string sTileId); //added by Mike, 20210828
    void drawLevelWithTexture();
    
		void drawLevelWithTextureUsingInputFileNoScrollYet(); //edited by Mike, 20210910
		 //added by Mike, 20210910; edited by Mike, 20210913
//		void drawLevelMapInViewPort(GLfloat fX, GLfloat fY, GLfloat fZ);
		//edited by Mike, 20210913
//		void drawLevelMapInViewPort(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fMyCanvasPosX, GLfloat fMyCanvasPosY, GLfloat fMyCanvasPosZ);
		//edited by Mike, 20210915
		/*void drawLevelMapInViewPortNoteDrawBasedOnPilotLocationAsWithCollisionDetection
		(GLfloat fMyCanvasPosX, GLfloat fMyCanvasPosY, GLfloat fMyCanvasPosZ, GLfloat fX, GLfloat fY, GLfloat fZ);
*/		
/* //edited by Mike, 20210922
		void drawLevelMapInViewPort(GLfloat fMyCanvasPosX, GLfloat fMyCanvasPosY, GLfloat fMyCanvasPosZ, GLfloat fX, GLfloat fY, GLfloat fZ);
*/
        //edited by Mike, 20210923
//		void drawLevelMapInViewPort(float fMyCanvasPosX, float fMyCanvasPosY, float fMyCanvasPosZ, float fX, float fY, float fZ);
    void drawLevelMapInViewPort(float fX, float fY, float fZ);
		
    //removed by Mike, 20210705
//    void drawLevelMapInViewPort(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fXSize, GLfloat fYSize, GLfloat fZSize);

		//added by Mike, 20210706; edited by Mike, 20210922
//		void drawLevel(GLfloat x, GLfloat y, GLfloat z, char *string);	
		void drawLevel(float x, float y, float z, char *string);	

    //added by Mike, 20210423
    void update(float dt);
    
    //added by Mike, 20210724; edited by Mike, 20210725
    bool isLevel2DCollideWith(MyDynamicObject* mdo);
        
    // changes the robot's state
    void changeState(int s);
    
    //edited by Mike, 20210923
//    void move(int key);
    void move(int key, MyDynamicObject* mdoPilot);
    
    
    
    //added by Mike, 20201226
    void keyDown(int keyCode);	
    void keyUp(int keyCode);	
        
    //added by Mike, 20210828; edited by Mike, 20210830
/*    virtual void openGLDrawTexture(int x, int y, GLuint textureId, int textw, int texth);
*/

/* //removed by Mike, 20220122
		//edited by Mike, 20210830
//    virtual void openGLDrawTexture(float x, float y, float textw, float texth);
    void openGLDrawTexture(float x, float y, float textw, float texth, std::string sTileId);
*/    
    
    /*	//removed by Mike, 20210522	
     void setOpenGLCanvas(OpenGLCanvas* c);
     */	
    virtual void hitBy(MyDynamicObject* mdo);
    
    //added by Mike, 20210725; edited by Mike, 20210728
//    void hitByAtTile(MyDynamicObject* mdo, std::string sTileId);
    //edited by Mike, 20210803
//    void hitByAtTile(MyDynamicObject* mdo, std::string sTileId, int iTileXPos, int iTileYPos);
    bool hitByAtTile(MyDynamicObject* mdo, std::string sTileId, int iTileXPos, int iTileYPos);
    
    //added by Mike, 20201016
    virtual void destroy();
    
    void reset();
    int getState();
};
