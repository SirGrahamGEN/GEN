/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVideoFile.cpp
* 
* @class      GRPVIDEOFILE
* @brief      Graphic Video File class
* @ingroup    GRAPHIC
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPVideoFile.h"

#include "XFactory.h"

#include "GRPProperties.h"
#include "GRPBitmap.h"
#include "GRPBitmapSequence.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_GRPVIDEOFILE_PROPERTYS



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS::GRPVIDEOFILE_PROPERTYS()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS::GRPVIDEOFILE_PROPERTYS()
{
  Clean();
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS::~GRPVIDEOFILE_PROPERTYS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS::~GRPVIDEOFILE_PROPERTYS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVIDEOFILE_PROPERTYS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* ---------------------------------------------------------------------------------------------------------------------*/
void GRPVIDEOFILE_PROPERTYS::Clean()
{
  width     = 0;
  height    = 0;
  nframes   = 0;
  framerate = 0;
}


#pragma endregion


#pragma region CLASS_GRPVIDEOFILE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIDEOFILE::GRPVIDEOFILE()
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE::GRPVIDEOFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIDEOFILE::~GRPVIDEOFILE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE::~GRPVIDEOFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Open(XCHAR* xpath)
* @brief      Open
* @ingroup    GRAPHIC
*
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Open(XCHAR* xpath)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Create(XCHAR* xpath, GRPVIDEOFILE_PROPERTYS& propertys)
* @brief      Create
* @ingroup    GRAPHIC
* 
* @param[in]  xpath : 
* @param[in]  propertys : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Create(XCHAR* xpath, GRPVIDEOFILE_PROPERTYS& propertys)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIDEOFILE_PROPERTYS* GRPVIDEOFILE::GetPropertys()
* @brief      Get propertys
* @ingroup    GRAPHIC
*
* @return     GRPVIDEOFILE_PROPERTYS* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
GRPVIDEOFILE_PROPERTYS*  GRPVIDEOFILE::GetPropertys()
{
  return &propertys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* GRPVIDEOFILE::GetDataFrame(XDWORD index_frame, XDWORD& sizeframe)
* @brief      Get data frame
* @ingroup    GRAPHIC
*
* @param[in]  index_frame : 
* @param[in]  sizeframe : 
* 
* @return     XBYTE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPVIDEOFILE::GetDataFrame(XDWORD index_frame, XDWORD& sizeframe)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::AddFrame(XBYTE* dataframe, XDWORD dataframesize)
* @brief      Add frame
* @ingroup    GRAPHIC
*
* @param[in]  dataframe : 
* @param[in]  dataframesize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::AddFrame(XBYTE* dataframe, XDWORD dataframesize)
{
  return false;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIDEOFILE::Close()
* @brief      Close
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIDEOFILE::Close()
{
 return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIDEOFILE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVIDEOFILE::Clean()
{

}


#pragma endregion


#pragma endregion

