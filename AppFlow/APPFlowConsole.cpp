/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowConsole.cpp
* 
* @class      APPFLOWCONSOLE
* @brief      Application Flow Console class
* @ingroup    APPFLOW
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

#include "APPFlowConsole.h"

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XConsole.h"
#include "XLog.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"

#include "APPFlowCFG.h"

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
* @fn         APPFLOWCONSOLE::APPFLOWCONSOLE()
* @brief      Constructor of class
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWCONSOLE::APPFLOWCONSOLE()
{
  Clean();

  isprintexitmessageactive = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWCONSOLE::~APPFLOWCONSOLE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWCONSOLE::~APPFLOWCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWCONSOLE::Ini(XSYSTEM* xsystem, XVECTOR<XSTRING*>* execparams)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  execparams : Params of command line (params of exec application)
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::Ini(XVECTOR<XSTRING*>* execparams)
{
  GEN_XFACTORY_CREATE(console, CreateConsole())
  if(!console) return false;

  //console->Clear();

  return APPFLOWBASE::Ini(execparams);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWCONSOLE::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
* @brief      Show line
* @ingroup    APPFLOW
* 
* @param[in]  string : 
* @param[in]  string2 : 
* @param[in]  tab : 
* @param[in]  linefeed : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::Show_Line(XSTRING& string, XSTRING& string2, int tab, bool linefeed)
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
* @fn         bool APPFLOWCONSOLE::Show_BlankLine()
* @brief      Show blank line
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::Show_BlankLine()
{
  XSTRING string;
  XSTRING string2;

  return Show_Line(string, string2);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWCONSOLE::Show_LineDirect(XSTRING& string, bool lf)
* @brief      Show line direct
* @ingroup    APPFLOW
* 
* @param[in]  string : 
* @param[in]  lf : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::Show_LineDirect(XSTRING& string, bool lf)
{
  console->Print(string.Get());
  if(lf) console->Print(__L("\n"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWCONSOLE::Show_Header(bool separator)
* @brief      Show header
* @ingroup    APPFLOW
* 
* @param[in]  separator : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::Show_Header(bool separator)
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
* @fn         bool APPFLOWCONSOLE::End()
* @brief      End
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::End()
{
  XSTRING exittypestring;

  GetExitTypeString(exittypestring);
  if(!exittypestring.IsEmpty()) 
    {
      GEN_XLOG.AddEntry(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_GENERIC, false, exittypestring.Get());
    }

  bool status = APPFLOWBASE::End();

  if(console)
    {
      if(isprintexitmessageactive)
        {
          PrintExitMessage(exittypestring);
        }

      GEN_XFACTORY.DeleteConsole(console);
      console = NULL;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCONSOLE* APPFLOWCONSOLE::GetConsole()
* @brief      Get console
* @ingroup    APPFLOW
* 
* @return     XCONSOLE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCONSOLE* APPFLOWCONSOLE::GetConsole()
{
  return console;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWCONSOLE::PrintExitMessage_Active(bool isprintexitmessageactive)
* @brief      Print exit message active
* @ingroup    APPFLOW
* 
* @param[in]  isprintexitmessageactive : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::PrintExitMessage_Active(bool isprintexitmessageactive)
{
  this->isprintexitmessageactive = isprintexitmessageactive;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWCONSOLE::PrintExitMessage(XSTRING& exitmessage)
* @brief      Print exit message
* @ingroup    APPFLOW
* 
* @param[in]  exitmessage : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCONSOLE::PrintExitMessage(XSTRING& exitmessage)
{
  if(!console)              return false;
  if(exitmessage.IsEmpty()) return false;

  console->PrintMessage(exitmessage.Get(), 1 ,true, true);

  console->PrintMessage(__L(" "), 0 ,false, true);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWCONSOLE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWCONSOLE::Clean()
{
  console                  = NULL;
  isprintexitmessageactive = false;
}


#pragma endregion






