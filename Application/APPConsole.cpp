/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPConsole.cpp
*
* @class      APPCONSOLE
* @brief      Application Console class
* @ingroup    APPLICATION
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

#include "Version.h"

#include "XFactory.h"
#include "XConsole.h"
#include "XLog.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"

#include "APPCFG.h"

#include "APPConsole.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCONSOLE::APPCONSOLE()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCONSOLE::APPCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCONSOLE::~APPCONSOLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCONSOLE::~APPCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCONSOLE::Ini(XSYSTEM* xsystem, XVECTOR<XSTRING*>* execparams)
* @brief      Ini Application console function
* @ingroup    APPLICATION
*
* @param[in]  execparams : Params of command line (params of exec application)
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::Ini(XVECTOR<XSTRING*>* execparams)
{
  GEN_XFACTORY_CREATE(console, CreateConsole())
  if(!console) return false;

  //console->Clear();

  return APPBASE::Ini(execparams);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCONSOLE::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
* @brief      Show_Line
* @ingroup    APPLICATION
* 
* @param[in]  string : 
* @param[in]  string2 : 
* @param[in]  tab : 
* @param[in]  linefeed : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
{
  XSTRING line1;
  XSTRING line2;

  console->Format_Message(string.Get(), tab , false, false, line1);
  if(tab)
    {
      int _tab = tab;

      if(_tab<37) _tab = 37;
      line1.AdjustSize(_tab, false, __L(" "));
    }

  console->Format_Message(string2.Get(), 0 , false, linefeed, line2);

  console->Print(line1.Get());
  console->Print(line2.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCONSOLE::Show_LineDirect(XSTRING& string, bool lf)
* @brief      Show_LineDirect
* @ingroup    APPLICATION
* 
* @param[in]  string : 
* @param[in]  lf : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::Show_LineDirect(XSTRING& string, bool lf)
{
  console->Print(string.Get());
  if(lf) console->Print(__L("\n"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCONSOLE::Show_Header(bool separator)
* @brief      Show_Header
* @ingroup    APPLICATION
* 
* @param[in]  separator : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::Show_Header(bool separator)
{ 
  XSTRING header;

  header = GEN_VERSION.GetAppTitle()->Get();
  
  console->Printf(__L(" %s"),header.Get());
  console->Printf(__L("\n"));
  if(separator) console->Printf(__L("\n"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCONSOLE::End()
* @brief      End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::End()
{
  XSTRING exittypestring;

  GetExitTypeString(exittypestring);
  if(!exittypestring.IsEmpty()) GEN_XLOG.AddEntry(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_GENERIC, false, exittypestring.Get());

  bool status = APPBASE::End();

  if(console)
    {
      PrintExitMessage(exittypestring);

      GEN_XFACTORY.DeleteConsole(console);
      console = NULL;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCONSOLE::PrintExitMessage(XSTRING& exitmessage)
* @brief      PrintExitMessage
* @ingroup    APPLICATION
* 
* @param[in]  exitmessage : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCONSOLE::PrintExitMessage(XSTRING& exitmessage)
{
  if(!console)              return false;
  if(exitmessage.IsEmpty()) return false;

  console->PrintMessage(exitmessage.Get(), 1 ,true, true);

  console->PrintMessage(__L(" "), 0 ,false, true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCONSOLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPCONSOLE::Clean()
{
  console = NULL;
}
