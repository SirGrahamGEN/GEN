/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_PluginsManager.cpp
* 
* @class      DIOWEBSERVER_PLUGINSMANAGER
* @brief      Data Input/Output Web Server Plugings Manager class
* @ingroup    DATAIO
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

#include "DIOWebServer_PluginsManager.h"

#include "DIOWebServer_Plugin.h"

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWEBSERVER_PLUGINSMANAGER::DIOWEBSERVER_PLUGINSMANAGER()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGINSMANAGER::DIOWEBSERVER_PLUGINSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWEBSERVER_PLUGINSMANAGER::~DIOWEBSERVER_PLUGINSMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGINSMANAGER::~DIOWEBSERVER_PLUGINSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_Add(DIOWEBSERVER_PLUGIN* plugin)
* @brief      Plugins add
* @ingroup    DATAIO
*
* @param[in]  plugin :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_Add(DIOWEBSERVER_PLUGIN* plugin)
{
  if(!plugin) return false;

  return plugins.Add(plugin);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGIN* DIOWEBSERVER_PLUGINSMANAGER::Plugins_GetNPlugins()
* @brief      Plugins get N plugins
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_PLUGIN* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOWEBSERVER_PLUGINSMANAGER::Plugins_GetNPlugins()
{
  return plugins.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGIN* DIOWEBSERVER_PLUGINSMANAGER::Plugins_Get(int index)
* @brief      Plugins get
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     DIOWEBSERVER_PLUGIN* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGIN* DIOWEBSERVER_PLUGINSMANAGER::Plugins_Get(int index)
{
  return plugins.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_Delete(DIOWEBSERVER_PLUGIN* plugin)
* @brief      Plugins delete
* @ingroup    DATAIO
*
* @param[in]  plugin :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_Delete(DIOWEBSERVER_PLUGIN* plugin)
{
  return plugins.Delete(plugin);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_DeleteAll()
* @brief      Plugins delete all
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGINSMANAGER::Plugins_DeleteAll()
{
  if(!plugins.GetSize()) return false;

  plugins.DeleteContents();
  plugins.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_PLUGINSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_PLUGINSMANAGER::Clean()
{

}


#pragma endregion

