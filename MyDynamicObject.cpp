/*
 * Copyright 2021 SYSON, MICHAEL B.
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
 * @date created: 20211116
 * @date updated: 20220205; from 20220202
 * @website address: http://www.usbong.ph
 *
 */

#include "MyDynamicObject.h"
#include <stdlib.h>

//TO-DO: -add: this
//#include "UsbongUtils.h"

#include <string.h>

//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
	#include <windows.h> //Windows Machine
#endif

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

#include <stdio.h>

MyDynamicObject::~MyDynamicObject()
{
}

/* //TO-DO: -add: this
void MyDynamicObject::setUsbongUtils(UsbongUtils* u)
{
     myUsbongUtils = u;
}
*/

//added by Mike, 2021117
SDL_Texture* MyDynamicObject::loadTexture(char *filename)
{
	SDL_Texture *texture;

	//removed by Mike, 20211129
//	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(mySDLRenderer, filename);

	return texture;
}

void MyDynamicObject::draw() {
}

void MyDynamicObject::hitBy(MyDynamicObject* mdo){
}

bool MyDynamicObject::checkIsCollidable() {
     return isCollidable;
}

void MyDynamicObject::setCollidable(bool c) {
     isCollidable=c;
}

//added by Mike, 20220130
bool MyDynamicObject::collideWithLevel2DTileRect(float fTilePosX, float fTilePosY, float fTileWidth, float fTileHeight)
{
		//TO-DO: -reverify: this using only 1 wall tile
printf("dito\n");
//printf(">>iOffsetXPosAsPixel: %i\n",iOffsetXPosAsPixel);



			//note: we add iOffsetXPosAsPixel and iOffsetYPosAsPixel 
			//to cause need of bigger collision rectangle, before hit
			//tile position at right of object
			//TO-DO: -clarify: to use floating point numbers instead of integers, i.e. whole numbers
		//edited by Mike, 20210831
			if ((fTilePosX > getXPos()+getWidth()-iOffsetXPosAsPixel+getStepX()) || 
			 			//tile position at left of object
            (fTilePosX+fTileWidth < getXPos()+iOffsetXPosAsPixel -getStepX()) ||
            //tile position at top of object
            (fTilePosY+fTileHeight < getYPos()+iOffsetYPosAsPixel -getStepY()) || 
						//tile position at bottom of object            
            (fTilePosY > getYPos()+getHeight()-iOffsetYPosAsPixel +getStepY())) { 
/*
			if ((fTilePosX > getX()+getWidth()+getStepX()) || 
			 			//tile position at left of object
            (fTilePosX+fTileWidth < getX()-getStepX()) ||
            //tile position at top of object
            (fTilePosY+fTileHeight < getY()-getStepY()) || 
						//tile position at bottom of object            
            (fTilePosY > getY()+getHeight()+getStepY())) { 
*/
//			printf("outside tile\n");
			return false;
		}	

		return true;
}


bool MyDynamicObject::isIntersectingRect(MyDynamicObject* mdo1, MyDynamicObject* mdo2)
{     
    if (mdo2->getYPos()+mdo2->getHeight() < mdo1->getYPos() || //is the bottom of mdo2 above the top of mdo1?
        mdo2->getYPos() > mdo1->getYPos()+mdo1->getHeight() || //is the top of mdo2 below bottom of mdo1?
        mdo2->getXPos()+mdo2->getWidth() < mdo1->getXPos()  || //is the right of mdo2 to the left of mdo1?
        mdo2->getXPos() > mdo1->getXPos()+mdo1->getWidth()) { //is the left of mdo2 to the right of mdo1?
        return false;
		}
	
    return true;
}

//edited by Mike, 20211122
//void MyDynamicObject::collideWith(MyDynamicObject* mdo)
bool MyDynamicObject::collideWith(MyDynamicObject* mdo)
{
    if ((!checkIsCollidable())||(!mdo->checkIsCollidable()))    
    {
//    		printf(">>>>>NOT COLLIDABLE");
        return false;
    }

    if (isIntersectingRect(this, mdo))
    {
        this->hitBy(mdo);
        mdo->hitBy(this);
        
        return true;
    }
    
    return false;
}

void MyDynamicObject::destroy()
{
}
