/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLog.cpp
*
* @class      XLOG
* @brief      eXtended LOG class
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "XFactory.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XDir.h"
#include "XFileTXT.h"
#include "XFileZIP.h"
#include "XTrace.h"

#include "XLog.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XLOG* XLOG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOGENTRY::XLOGENTRY()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOGENTRY::XLOGENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOGENTRY::~XLOGENTRY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOGENTRY::~XLOGENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLOGENTRY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLOGENTRY::Clean()
{
  position  = 0;
  size      = 0;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* XLOG                                                                                                                */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOG& XLOG::GetInstance()
* @brief      GetInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XLOG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOG& XLOG::GetInstance()
{
  if(!instance) instance = new XLOG();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::DelInstance()
* @brief      DelInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Ini(XCHAR* pathfile, XCHAR* nameapplication, bool isdumpintrace)
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pathfile :
* @param[in]  nameapplication :
* @param[in]  isdumpintrace :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Ini(XCHAR* pathfile, XCHAR* nameapplication, bool isdumpintrace)
{
  if(isactive) return false;

  this->xpathfile     = pathfile;
  this->isdumpintrace = isdumpintrace;

  if(nameapplication) this->nameapplication = nameapplication;

  if(!filelog) return false;

  bool status = filelog->Open(xpathfile,false);
  if(!status) status = filelog->Create(xpathfile);

  if(status) CalculateInitialStatus();

  isactive = status;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Ini(XPATH& xpathfile, XCHAR* nameapplication, bool isdumpintrace)
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpathfile :
* @param[in]  nameapplication :
* @param[in]  isdumpintrace :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Ini(XPATH& xpathfile, XCHAR* nameapplication, bool isdumpintrace)
{
  return Ini(xpathfile.Get(), nameapplication, isdumpintrace);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Ini(XPATH& xpathfile, XSTRING& nameapplication, bool isdumpintrace)
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpathfile :
* @param[in]  nameapplication :
* @param[in]  isdumpintrace :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Ini(XPATH& xpathfile, XSTRING& nameapplication, bool isdumpintrace)
{
  return Ini(xpathfile.Get(), nameapplication.Get(), isdumpintrace);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::SetLimit(XLOGTYPELIMIT typelimit, int limit, int reductionpercent)
* @brief      SetLimit
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  typelimit :
* @param[in]  limit :
* @param[in]  reductionpercent :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::SetLimit(XLOGTYPELIMIT typelimit, int limit, int reductionpercent)
{
  this->typelimit        = typelimit;
  this->limit            = limit;
  this->reductionpercent = reductionpercent;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::SetBackup(bool isactive, int maxfiles, bool iscompress)
* @brief      SetBackup
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  isactive :
* @param[in]  maxfiles :
* @param[in]  iscompress :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::SetBackup(bool isactive, int maxfiles, bool iscompress)
{
  this->backupisactive    = isactive;
  this->backupmaxfiles    = maxfiles;
  this->backupiscompress  = iscompress;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::SetFilters(XCHAR* sectionsID, XBYTE level)
* @brief      SetFilters
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  sectionsID :
* @param[in]  level :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::SetFilters(XCHAR* sectionsID, XBYTE level)
{
  if(sectionsID) filtersectionsID = sectionsID;
  filterlevel = level;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XLOG::GetPathFile()
* @brief      GetPathFile
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XCHAR* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XCHAR* XLOG::GetPathFile()                                                                    
{ 
  return xpathfile.Get();                 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOG::GetNameApplication()
* @brief      GetNameApplication
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOG::GetNameApplication()
{ 
  return &nameapplication;                
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOG::GetPrevLabel()
* @brief      GetPrevLabel
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOG::GetPrevLabel()                                                                    
{ 
  return &prevlabel;                      
} 



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::IsActive()
* @brief      IsActive
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::IsActive()
{
  if(!filelog)            return false;
  if(!filelog->IsOpen())  return false;
  if(!isactive)           return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLOG::SetIsActive(bool isactive)
* @brief      SetIsActive
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  isactive : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLOG::SetIsActive(bool isactive)                                                 
{ 
  this->isactive = isactive;              
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLOG::GetNEntrys()
* @brief      GetNEntrys
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XLOG::GetNEntrys()
{ 
  return nentrys;                         
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLOG::GetNLines()
* @brief      GetNLines
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XLOG::GetNLines()
{ 
  return nlines;                          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XLOG::GetSize()
* @brief      GetSize
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XQWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XLOG::GetSize()                                                                    
{ 
  return size;                            
}
    


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::GetLevelString(XLOGLEVEL level, XSTRING& strlevel, XDWORD size)
* @brief      GetLevelString
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  level :
* @param[in]  strlevel :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::GetLevelString(XLOGLEVEL level, XSTRING& strlevel, XDWORD size)
{
  strlevel.Empty();

  switch(level)
    {
      case XLOGLEVEL_INFO     : strlevel = __L("INFO");       break;
      case XLOGLEVEL_WARNING  : strlevel = __L("WARNING");    break;
      case XLOGLEVEL_ERROR    : strlevel = __L("ERROR");      break;
      default: break;
    }

  if(strlevel.IsEmpty()) return false;

  if(size>0) strlevel.AdjustSize(size, false, __L(" "));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOG::GetSectionsIDFilter()
* @brief      GetSectionsIDFilter
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOG::GetSectionsIDFilter()
{
  return &filtersectionsID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::PassFilters(XLOGLEVEL level, XCHAR* sectionID)
* @brief      PassFilters
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  level :
* @param[in]  sectionID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::PassFilters(XLOGLEVEL level, XCHAR* sectionID)
{
  if(!(filterlevel&level)) return false;

  if(sectionID) lastsectionID = sectionID;

  if(filtersectionsID.IsEmpty())  return false;

  if(filtersectionsID.Find(sectionID?sectionID:lastsectionID.Get(), true) == XSTRING_NOTFOUND)  return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XCHAR* mask,...)
* @brief      AddEntry
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  level :
* @param[in]  sectionID :
* @param[in]  inmemory :
* @param[in]  mask :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XCHAR* mask,...)
{
  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry %u"),XMEMORY_GETMEMORYUSED);

  if(!IsActive()) return false;
  if(!mask)       return false;
  if(!mutex)      return false;

  mutex->Lock();

  if(sectionID)
    {
      if(!PassFilters(level, sectionID))
        {
          mutex->UnLock();
          return false;
        }
    }

  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry  %u"),XMEMORY_GETMEMORYUSED);

  Backup_ControlLimits();

  XSTRING outstring;
  XSTRING outstringtrace;
  XSTRING string;

  XSTRING datestring;
  XSTRING levelstring;

  if(xdatetime)
    {
      xdatetime->Read();
      xdatetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datestring);
    }

  GetLevelString(level, levelstring, 7);
  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry %u"),XMEMORY_GETMEMORYUSED);
  if(sectionID)
    {
      string = datestring;
      string.AdjustSize(XLOG_MAXDATETIMESIZE, false, __L(" "));
      outstring      += string;      

      string = levelstring.Get();
      string.AdjustSize(XLOG_MAXLEVELSIZE, false, __L(" "));
      outstring      += string;
      outstringtrace += string;

      string = sectionID;
      string.AdjustSize(XLOG_MAXSECTIONIDSIZE, false, __L(" "));
    }
   else
    {
      string = __L(" ");
      string.AdjustSize(XLOG_MAXDATETIMESIZE +  XLOG_MAXLEVELSIZE + XLOG_MAXSECTIONIDSIZE, false, __L(" "));
    }
  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry  %u"),XMEMORY_GETMEMORYUSED);
  outstring      += string;
  outstringtrace += string;
  outstring      += __L(" ");
  outstringtrace += __L(" ");

 if(!prevlabel.IsEmpty())
   {
     outstring += prevlabel.Get();
   }

  va_list arg;

  va_start(arg, mask);

  string.FormatArg(mask, &arg);

  va_end(arg);

  outstring      += string;
  outstringtrace += string;

  if(isdumpintrace)
    {
      int leveldebug = 0;

      switch(level)
        {
          case XLOGLEVEL_WARNING  : leveldebug = 3; break;
          case XLOGLEVEL_ERROR    : leveldebug = 4; break;

          default:
          case XLOGLEVEL_INFO     : leveldebug = 0; break;
        }

     XTRACE_PRINTCOLOR(leveldebug , __L("[Log] %s "), outstringtrace.Get());
    }

  if(inmemory)
    {
      filelog->AddLine(outstring);
    }
   else
    {
      XDWORD resultsizeline = 0;
      XDWORD resultsizeLF   = 0;

      if(filelog->GetNLines()) FlushMemoryEntrys();

      if(outstring.Get()[0] != 0x20)
        {
          XQWORD position;

          filelog->GetPrimaryFile()->GetPosition(position);

          nentrys++;

          lastentry = new XLOGENTRY();
          if(lastentry)
            {
              lastentry->position = position;
              entrys.Add(lastentry);
            }
        }

      filelog->AddLineAlready(outstring.Get(), &resultsizeline, &resultsizeLF);

      if(lastentry) lastentry->size += (resultsizeline + resultsizeLF);

      size += (resultsizeline + resultsizeLF);

      nlines++;
    }

  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry %u"),XMEMORY_GETMEMORYUSED);
  mutex->UnLock();
  //XTRACE_PRINTCOLOR(3,__L(" XLOG::AddEntry  %u"),XMEMORY_GETMEMORYUSED);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XBYTE* data, XDWORD size, XDWORD sizeline, bool showoffset, bool showtext)
* @brief      AddEntry
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  level :
* @param[in]  sectionID :
* @param[in]  inmemory :
* @param[in]  data :
* @param[in]  size :
* @param[in]  sizeline :
* @param[in]  showoffset :
* @param[in]  showtext :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XBYTE* data, XDWORD size, XDWORD sizeline, bool showoffset, bool showtext)
{
  if(!IsActive()) return false;
  if(!mutex)      return false;

  mutex->Lock();

  if(!PassFilters(level, sectionID))
    {
      mutex->UnLock();
      return false;
    }

  XSTRING    strdata;
  XDWORD      _size     = 0;
  XDWORD      _sizeline = sizeline;
  int        index     = 0;
  XDWORD     lines     = 0;

  while(_size<size)
    {
      XSTRING string;

      if(_sizeline > (size - _size)) _sizeline = (size - _size);

      if(showoffset)
        {
          strdata.Format(__L("%04X"),index);
          string += strdata;
          string += __L("   ");
        }

      for(XDWORD c=0; c<_sizeline; c++)
        {
          strdata.Format(__L("%02X "),data[index]);
          string += strdata;
          _size++;
          index++;
        }

      if(_sizeline != sizeline)
        {
          for(XDWORD c=0; c<(sizeline-_sizeline); c++)
            {
              strdata.Format(__L("   "));
              string += strdata;
            }
        }

      if(showtext)
        {
          index -= _sizeline;
          string += __L(" ");

          for(XDWORD c=0; c<_sizeline; c++)
            {
              XCHAR character = (XCHAR)data[index];

              if((character<0x20) || (character>0x80) || (character==__C('%')) || (character==__C('\\'))) character = __C('.');

              strdata.Format(__L("%c"),character);
              string += strdata;
              index++;
            }
        }

      mutex->UnLock();

      AddEntry(level, lines?NULL:sectionID, inmemory, string.Get());

      mutex->Lock();

      lines++;
    }

  mutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XBUFFER& data, XDWORD sizeline, bool showoffset, bool showtext)
* @brief      AddEntry
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  level :
* @param[in]  sectionID :
* @param[in]  inmemory :
* @param[in]  data :
* @param[in]  sizeline :
* @param[in]  showoffset :
* @param[in]  showtext :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::AddEntry(XLOGLEVEL level, XCHAR* sectionID, bool inmemory, XBUFFER& data, XDWORD sizeline, bool showoffset, bool showtext)
{
  return XLOG::AddEntry(level, sectionID, inmemory, data.Get(), data.GetSize(), sizeline, showoffset, showtext);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Flush()
* @brief      Flush
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Flush()
{
  if(!mutex)      return false;
  if(!IsActive()) return false;

  mutex->Lock();

  if(filelog->GetNLines()) FlushMemoryEntrys();

  mutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::End(bool doflush)
* @brief      End
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  doflush :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::End(bool doflush)
{
  if(!isactive) return false;

  if(doflush) Flush();

  if(!filelog) return false;

  filelog->Close();

  isactive = false;

  nentrys = 0;
  nlines  = 0;
  size    = 0;

  entrys.DeleteContents();
  entrys.DeleteAll();

  lastentry = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::CalculateInitialStatus()
* @brief      CalculateInitialStatus
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::CalculateInitialStatus()
{
  XFILE* xfile = filelog->GetPrimaryFile();
  if(!xfile) return false;

  nlines  = 0;
  nentrys = 0;
  size    = xfile->GetSize();

  entrys.DeleteContents();
  entrys.DeleteAll();

  XDWORD             sizeBOM              = 0;
  XFILETXTFORMATCHAR formatchar           = filelog->GetFormatCharFromFile(&sizeBOM);
  int                sizebytescharacter   = filelog->SizeOfCharacter(formatchar);

  xfile->SetPosition(sizeBOM);

  bool    endfile;
  XDWORD  br;
  XBUFFER dataline;
  XBYTE*  readbuffer = new XBYTE[XFILETXT_MAXBUFFER];
  if(!readbuffer) return false;

  memset(readbuffer, 0, XFILETXT_MAXBUFFER);

  do{ XDWORD  bufferpos = 0;

      br      = XFILETXT_MAXBUFFER;
      endfile = !xfile->Read(readbuffer, &br);
      if(!br) break;

      do{ XFILETXTTYPELF typeLF;
          XDWORD         sizeLF   = 0;
          XDWORD         sizeline = 0;
          bool           endline = filelog->GetSizeOfLine(formatchar, &readbuffer[bufferpos], typeLF, sizeLF, sizeline, (br-bufferpos));

          if(endline)
            {
              if(readbuffer[bufferpos] != 0x20)
                {
                  nentrys++;

                  lastentry = new XLOGENTRY();
                  if(lastentry)
                    {
                      lastentry->position = bufferpos;
                      entrys.Add(lastentry);
                    }
                }

              if(lastentry) lastentry->size += (sizeline + sizeLF);
              nlines++;

              sizeline  *= sizebytescharacter;
              sizeline  += (sizeLF*sizebytescharacter);
              bufferpos += sizeline;
            }
           else
            {
              int lack = (br-bufferpos);
              bufferpos += lack;

              if(endfile && (bufferpos == br))
                {
                  if(readbuffer[bufferpos] != 0x20)
                    {
                      nentrys++;

                      lastentry = new XLOGENTRY();
                      if(lastentry)
                        {
                          lastentry->position = bufferpos;
                          entrys.Add(lastentry);
                        }
                    }

                  if(lastentry) lastentry->size += lack;
                  nlines++;
                }
            }

        } while(bufferpos < br);

    } while(!endfile);

  delete [] readbuffer;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::FlushMemoryEntrys()
* @brief      FlushMemoryEntrys
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::FlushMemoryEntrys()
{
  int c=0;
  while(c<filelog->GetNLines())
    {
      XSTRING* line = filelog->GetLine(c);
      if(line)
        {
          XDWORD resultsizeline = 0;
          XDWORD resultsizeLF   = 0;

          if(line->Get()[0] != 0x20)
            {
              XQWORD position;

              filelog->GetPrimaryFile()->GetPosition(position);

              nentrys++;

              lastentry = new XLOGENTRY();
              if(lastentry)
                {
                  lastentry->position = position;
                  entrys.Add(lastentry);
                }
            }

          filelog->AddLineAlready(line->Get(), &resultsizeline, &resultsizeLF);

          if(lastentry) lastentry->size += (resultsizeline + resultsizeLF);

          size += (resultsizeline + resultsizeLF);

          nlines++;
        }

      c++;
    }

  filelog->DeleteAllLines();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLOG::Backup_GetNFiles()
* @brief      Backup_GetNFiles
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XLOG::Backup_GetNFiles()
{
  XPATH         xpathnamelog;
  XPATH         xpath;
  int           nfiles = 0;
  XDIRELEMENT   xdirelement;

  xpathnamelog = xpathfile.Get();

  xpathnamelog.GetPath(xpath);

  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir) return 0;

  if(xdir->FirstSearch(xpath.Get(), XLOG_SEARCHMASKBACKUPFILE , &xdirelement))
    {
      do{ if(xdirelement.GetType() == XDIRELEMENTTYPE_FILE) nfiles++;

        } while(xdir->NextSearch(&xdirelement));
    }

  GEN_XFACTORY.Delete_Dir(xdir);

  return nfiles;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Backup_GetNameFileMoreOld(XPATH& xpathselect)
* @brief      Backup_GetNameFileMoreOld
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpathselect :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Backup_GetNameFileMoreOld(XPATH& xpathselect)
{
  if(!xdatetime) return false;

  XPATH         xpathnamelog;
  XPATH         xpath;
  XPATH         selectnamefile;
  //int           nfiles = 0;
  XDIRELEMENT   xdirelement;
  XQWORD        lastseconds = 0x8FFFFFFFFFFFFFFFULL;

  xpathnamelog = xpathfile.Get();

  xpathnamelog.GetPath(xpath);

  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir) return false;

  if(xdir->FirstSearch(xpath.Get(), XLOG_SEARCHMASKBACKUPFILE, &xdirelement))
    {
      do{ if(xdirelement.GetType() == XDIRELEMENTTYPE_FILE)
            {
              XSTRING* namefile = xdirelement.GetNameFile();
              if(namefile)
                {
                  int day     = 0;
                  int month   = 0;
                  int year    = 0;
                  int hours   = 0;
                  int minutes = 0;
                  int seconds = 0;

                  namefile->UnFormat(XLOG_CREATEMASKBACKUPFILE, &year, &month, &day, &hours, &minutes, &seconds);

                  xdatetime->SetDay(day);
                  xdatetime->SetMonth(month);
                  xdatetime->SetYear(year);
                  xdatetime->SetHours(hours);
                  xdatetime->SetMinutes(minutes);
                  xdatetime->SetSeconds(seconds);

                  if(lastseconds > xdatetime->GetSeconsFromDate())
                    {
                      lastseconds = xdatetime->GetSeconsFromDate();
                      selectnamefile = xdirelement.GetNameFile()->Get();
                    }
                }
            }

        } while(xdir->NextSearch(&xdirelement));
    }

  GEN_XFACTORY.Delete_Dir(xdir);

  xpathselect  = xpath;
  xpathselect += selectnamefile;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Backup_CreateNameZIP(XPATH& xpathzipfile)
* @brief      Backup_CreateNameZIP
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpathzipfile :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Backup_CreateNameZIP(XPATH& xpathzipfile)
{
  xpathzipfile.Empty();

  xpathzipfile  = xpathfile.Get();
  xpathzipfile.SetOnlyPathAndNamefile();
  xpathzipfile += __L(".zip");
  xpathzipfile.AddToNameFile(true, XLOG_PREFIX);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Backup_AdjustNFilesInCompressed()
* @brief      Backup_AdjustNFilesInCompressed
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Backup_AdjustNFilesInCompressed()
{
  XFILEUNZIP xfileunzip;
  XPATH      xpathzipfile;

  Backup_CreateNameZIP(xpathzipfile);

  if(xfileunzip.Open(xpathzipfile))
    {
      if(xfileunzip.GetNFiles()>=backupmaxfiles)
        {
          xfileunzip.DelFile(0);
        }

      xfileunzip.Close();
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Backup_AdjustNFiles(XCHAR* pathnamelog, bool iscompress)
* @brief      Backup_AdjustNFiles
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pathnamelog :
* @param[in]  iscompress :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Backup_AdjustNFiles(XCHAR* pathnamelog, bool iscompress)
{
  XFILE* xfilebackup = GEN_XFACTORY.Create_File();
  if(!xfilebackup)  return false;

  XPATH    xpathnamelog;
  XSTRING  datestr;
  bool     status      = false;
  //int      indexbackup = 0;

  xpathnamelog = pathnamelog;

  if(!iscompress)
    {
      if(Backup_GetNFiles()>backupmaxfiles)
        {
          Backup_GetNameFileMoreOld(xpathnamelog);
          xfilebackup->Erase(xpathnamelog);
        }
    }
   else
    {
      Backup_AdjustNFilesInCompressed();
    }

  if(iscompress)
    {
      XFILEZIP* xfilezip = new XFILEZIP();
      if(xfilezip)
        {
          XPATH xpathzipfile;

          Backup_CreateNameZIP(xpathzipfile);

          if(xfilezip->Open(xpathzipfile))
            {
              XPATH namefileinzip;

              xpathnamelog.GetNamefileExt(namefileinzip);

              if(!xfilezip->AddFile(xpathnamelog, namefileinzip)) status = false;

              xfilezip->Close();
            }

          delete xfilezip;

          status = xfilebackup->Erase(pathnamelog);
        }
    }

  GEN_XFACTORY.Delete_File(xfilebackup);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLOG::Backup_ControlLimits()
* @brief      Backup_ControlLimits
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLOG::Backup_ControlLimits()
{
  if(!IsActive()) return false;

  switch(typelimit)
    {
      case XLOGTYPELIMIT_NENTRYS  : if(nentrys<limit)  return false;
                                    break;

      case XLOGTYPELIMIT_SIZE     : if(size<limit)    return false;
                                    break;
      default: break;
    }

  Flush();

  bool status = true;

  if(backupisactive)
    {
      XPATH    xpathnamelog;
      XSTRING  datestr;

      //  If have backup DON´T HAVE reduction
      //  The actual log file start
      xpathnamelog       = xpathfile.Get();
      backupxpathnamelog = xpathfile.Get();

      xdatetime->Read();
      datestr.Format(XLOG_CREATEMASKBACKUPFILE, xdatetime->GetYear()
                                              , xdatetime->GetMonth()
                                              , xdatetime->GetDay()
                                              , xdatetime->GetHours()
                                              , xdatetime->GetMinutes()
                                              , xdatetime->GetSeconds());

      backupxpathnamelog.AddToNameFile(true, datestr.Get());

      End(false);

      XFILE* xfile = GEN_XFACTORY.Create_File();
      if(xfile)
        {
          xfile->Rename(xpathnamelog, backupxpathnamelog);
          GEN_XFACTORY.Delete_File(xfile);
        }

      status = Ini(xpathnamelog, NULL, isdumpintrace);
      if(status) status = Backup_AdjustNFiles(backupxpathnamelog.Get(), backupiscompress);
    }
   else
    {
      // Reduction control: NOT Backup.

      XDWORD nentrystoerase = nentrys - ((nentrys * reductionpercent) / 100);
      XQWORD sizetocopy = 0;

      for(int c=0; c<(int)nentrystoerase; c++)
        {
          XLOGENTRY* entry = entrys.Get(c);
          if(entry) sizetocopy += entry->size;
        }

      if(!sizetocopy) return false;

      filelog->GetPrimaryFile()->SetPosition(0);
      filelog->GetPrimaryFile()->EraseBlock(sizetocopy);
    }

  if(status) status = CalculateInitialStatus();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOG::XLOG()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOG::XLOG()
{
  Clean();

  xdatetime = GEN_XFACTORY.CreateDateTime();
  xtimer    = GEN_XFACTORY.CreateTimer();
  mutex     = GEN_XFACTORY.Create_Mutex();
  
  XTIMER_MODULE(xtimer)

  filelog = new XFILETXT();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOG::~XLOG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOG::~XLOG()
{
  if (filelog)    filelog->Close();
  if(filelog)     delete filelog;
  if(mutex)       GEN_XFACTORY.Delete_Mutex(mutex);
  if(xtimer)      GEN_XFACTORY.DeleteTimer(xtimer);
  if(xdatetime)   GEN_XFACTORY.DeleteDateTime(xdatetime);

  this->entrys.DeleteContents();
  this->entrys.DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLOG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLOG::Clean()
{
  xdatetime        = NULL;
  xtimer           = NULL;
  mutex            = NULL;
  filelog          = NULL;

  isdumpintrace    = false;

  isactive         = false;
  typelimit        = XLOGTYPELIMIT_NONE;

  backupisactive   = false;
  backupmaxfiles   = 0;
  backupiscompress = false;

  limit            = 0;
  reductionpercent = XLOG_DEFAULTREDUCTIONPERCENT;

  lastsectionID.Empty();

  filtersectionsID.Empty();
  filterlevel      = XLOGLEVEL_ALL;

  nentrys          = 0;
  nlines           = 0;
  size             = 0;
  lastentry        = NULL;
}


