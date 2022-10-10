/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIORemoteFileCFG.cpp
*
* @class      DIOREMOTEFILECFG
* @brief      Data Input/Output Remote File CFG class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XFile.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOWebClient.h"

#include "DIORemoteFileCFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOREMOTEFILECFG::DIOREMOTEFILECFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  XCHAR* : name file of config
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOREMOTEFILECFG::DIOREMOTEFILECFG(XCHAR* namefile): XFILECFG(namefile)
{
  Clean();

  webclient = new DIOWEBCLIENT();

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOREMOTEFILECFG::~DIOREMOTEFILECFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOREMOTEFILECFG::~DIOREMOTEFILECFG()
{
  if(webclient) delete webclient;

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOREMOTEFILECFG::Ini()
* @brief      Ini remote file config
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOREMOTEFILECFG::Ini()
{
  if(!webclient)         return false;
  if(namefile.IsEmpty()) return false;

  XPATH  xpathroot;
  XPATH  xpathremotefile;
  DIOURL downloadURL;
  bool   status[2];

  AddValue(XFILECFG_VALUETYPE_STRING, DIOREMOTEFILECFG_SECTIONGENERAL, DIOREMOTEFILECFG_URLREMOTECFG, &URLremoteCFG);

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);
  xpathfile.Set(xpathroot.Get());
  if(!xpathfile.IsEmpty()) xpathfile.Slash_Add();
  xpathfile.Add(namefile.Get());
  xpathfile.Add(XFILECFG_EXTENSIONFILE);

  status[0] = Load();

  if(!URLremoteCFG.IsEmpty())
    {
      downloadURL.Set(URLremoteCFG.Get());      
      if(downloadURL.Find(__L("?"), false) == XSTRING_NOTFOUND)
        {      
          downloadURL.Slash_Add();
          downloadURL.Add(DIOREMOTEFILECFG_PREFIXNAMEFILE);
          downloadURL.Add(namefile.Get());
          downloadURL.Add(XFILECFG_EXTENSIONFILE);
        }

      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);
      xpathremotefile.Set(xpathroot.Get());
      if(!xpathremotefile.IsEmpty()) xpathremotefile.Slash_Add();
      xpathremotefile.Add(DIOREMOTEFILECFG_PREFIXNAMEFILE);
      xpathremotefile.Add(namefile.Get());
      xpathremotefile.Add(XFILECFG_EXTENSIONFILE);

      if(webclient->Get(downloadURL, xpathremotefile))
        {
          status[0] = Load(xpathremotefile);
          if(status[0])
            {
              XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
              if(xfile)
                {
                  xfile->Erase(xpathremotefile, true);
                  GEN_XFACTORY.Delete_File(xfile);
                }
            }
        }
    }

  ReAjustIni();

  status[1] = Save();

  return (status[0] && status[1]);
}


 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         XSTRING* DIOREMOTEFILECFG::GetURLRemoteCFG()
 *  @brief      Get URL Remote CFG
 *  @ingroup    DATAIO
 *
 *  ""
 *  ""
 *
 *  @return     XSTRING* : URL remote Config
 *
 * --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOREMOTEFILECFG::GetURLRemoteCFG()
 {
   return &URLremoteCFG;
 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOREMOTEFILECFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOREMOTEFILECFG::Clean()
{
  webclient   = NULL;
}
