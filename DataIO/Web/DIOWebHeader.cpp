/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebHeader.cpp
* 
* @class      DIOWEBHEADER
* @brief      Data Input/Output Web Server Header class
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

#include "DIOWebHeader.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTrace.h"
#include "XTimer.h"

#include "DIOStreamTCPIP.h"
#include "DIOWebServer.h"

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
* @fn         DIOWEBHEADER::DIOWEBHEADER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER::DIOWEBHEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER::~DIOWEBHEADER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER::~DIOWEBHEADER()
{
  DeleteAllLines();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBHEADER::Read(DIOSTREAMTCPIP* diostream, int timeout)
* @brief      Read
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::Read(DIOSTREAMTCPIP* diostream, int timeout)
{
  if(!diostream) return false;

  XSTRING line;
  bool    status;

  DeleteAllLines();

  XTIMER* GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout) return false;

  do{ status =  diostream->ReadStr(line);
      if(status)
        {
          if(line.IsEmpty())
            {
              break;
            }
            else
            {
              //XTRACE_PRINTCOLOR(3, __L("WEB CLIENT HEADER LINE: %s"), line.Get());
              AddLine(line);
            }
        }

      if(timeout)
        {
          if(xtimerout->GetMeasureSeconds()>(XDWORD)timeout) break;

          GEN_XSLEEP.MilliSeconds(1);
        }

    } while((diostream->GetStatus() == DIOSTREAMSTATUS_CONNECTED) || diostream->GetInXBuffer()->GetSize());

  GEN_XFACTORY.DeleteTimer(xtimerout);


  if(lines.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::Write(DIOSTREAMTCPIP* diostream, int timeout)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  diostream :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::Write(DIOSTREAMTCPIP* diostream, int timeout)
{
  if(!diostream) return false;

  for(int c=0;c<(int)lines.GetSize();c++)
    {
      XSTRING* line = (XSTRING*)lines.Get(c);
      if(line)
        {
          //XTRACE_PRINTCOLOR(2, __L("%s"), line.Get());

          diostream->WriteStr((*line));
          diostream->WriteStr(__L("\r\n"));
        }
    }

  diostream->WriteStr(__L("\r\n"));
  diostream->WaitToFlushOutXBuffer(timeout);

  if(diostream->GetStatus() != DIOSTREAMSTATUS_CONNECTED) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::AddLine(XCHAR* line)
* @brief      Add line
* @ingroup    DATAIO
*
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::AddLine(XCHAR* line)
{
  XSTRING* _line;

  _line  = new XSTRING();
  if(!_line) return false;

  (*_line) = line;

  lines.Add(_line);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::AddLine(XSTRING& line)
* @brief      Add line
* @ingroup    DATAIO
*
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::AddLine(XSTRING& line)
{
  return AddLine(line.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* DIOWEBHEADER::GetLines()
* @brief      Get lines
* @ingroup    DATAIO
*
* @return     XVECTOR<XSTRING*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* DIOWEBHEADER::GetLines()
{
  return &lines;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::GetLines(XSTRING& result)
* @brief      Get lines
* @ingroup    DATAIO
*
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::GetLines(XSTRING& result)
{
  result.Empty();

  if(!lines.GetSize()) return false;

  for(int c=0;c<(int)lines.GetSize();c++)
    {
      XSTRING* line = (XSTRING*)lines.Get(c);
      if(line)
        {
          result += line->Get();
          result += __L("\r\n");
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DIOWEBHEADER::GetFieldValue(XCHAR* field)
* @brief      Get field value
* @ingroup    DATAIO
*
* @param[in]  field :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOWEBHEADER::GetFieldValue(XCHAR* field)
{
  for(int c=0;c<(int)lines.GetSize();c++)
    {
       XSTRING* line = (XSTRING*)lines.Get(c);
       if(line)
         {
           int index = line->Find(field, true);
           if(index!= XSTRING_NOTFOUND)
             {
               XDWORD size = (int)XSTRING::GetSize(field);

               return line->Get() + index + size + 1;
             }
         }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DIOWEBHEADER::GetFieldValue(XSTRING& field)
* @brief      Get field value
* @ingroup    DATAIO
*
* @param[in]  field :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOWEBHEADER::GetFieldValue(XSTRING& field)
{
  return GetFieldValue(field.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::DeleteAllLines()
* @brief      Delete all lines
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::DeleteAllLines()
{
  if(lines.IsEmpty()) return false;

  lines.DeleteContents();

  lines.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBHEADER::GetFormat(bool isserver, int type, void* data)
* @brief      Get format
* @ingroup    DATAIO
*
* @param[in]  isserver :
* @param[in]  type :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBHEADER::GetFormat(bool isserver, int type, void* data)
{
  if(lines.IsEmpty()) return false;

  if(!data) return false;

  XSTRING line;
  int     version    = 0;
  int     subversion = 0;

  line =((XSTRING*)lines.Get(0))->Get();

  if(isserver)
    {
      int     code;
      XSTRING codestring(DIOWEBHEADER_MAXLINE);

      line.UnFormat(__L("HTTP/%d.%d %d %s"),&version,&subversion,&code,codestring.Get());
      codestring.AdjustSize();

      switch(type)
        {
          case  0: (*(int*)data)     = version;     break;
          case  1: (*(int*)data)     = subversion;  break;
          case  2: (*(int*)data)     = code;        break;
          case  3: (*(XSTRING*)data) = codestring;  break;
        }
    }
   else
    {
      XSTRING method(DIOWEBHEADER_MAXLINE);
      XSTRING resource(DIOWEBHEADER_MAXLINE);

      if(line.GetSize())
        {
          int foundindex = line.Find(__L("HTTP/"), true);

          if(foundindex != XSTRING_NOTFOUND) line.UnFormat(__L("%s %s HTTP/%d.%d"), method.Get(), resource.Get(), &version, &subversion);
        }

      method.AdjustSize();
      resource.AdjustSize();

      switch(type)
        {
          case  0: if(data) (*(XSTRING*)data) = method;     break;
          case  1: if(data) (*(XSTRING*)data) = resource;   break;
          case  2: if(data) (*(int*)data)     = version;    break;
          case  3: if(data) (*(int*)data)     = subversion; break;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBHEADER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBHEADER::Clean()
{

}


#pragma endregion

