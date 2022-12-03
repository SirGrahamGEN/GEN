/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileTXT.cpp
*
* @class      XFILETXT
* @brief      eXtended TXT (Text) file class
* @ingroup    XUTILS
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

#include <stdio.h>
#include <string.h>

#include "XVector.h"
#include "XTrace.h"
#include "XBuffer.h"

#include "XFileTXT.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILETXT::XFILETXT()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXT::XFILETXT(): XFILECONTAINER()
{
  Clean();

  lines.SetIsMulti(true);

  if(!CreatePrimaryFile()) return;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILETXT::~XFILETXT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXT::~XFILETXT()
{
  if(!DeletePrimaryFile()) return;

  DeleteFormatFile();

  DeleteAllLines();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::Open(XPATH& xpath,bool readonly)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  readonly :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::Open(XPATH& xpath, bool readonly)
{
  if(!file) return false;

  if(!file->Open(xpath,readonly)) return false;

  GetFormatCharFromFile(NULL);

  if(formatchar == XFILETXTFORMATCHAR_UNKNOWN) formatchar = XFILETXTFORMATCHAR_ASCII;
  typeLF = XFILETXTTYPELF_DEFAULT;
  
  lines.SetAddInLimit((int)(file->GetSize()/15));

  if(formatchar == XFILETXTFORMATCHAR_ASCII)
    {
      if(IsBinaryFile()) 
        {
          return false;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::Create(XPATH& xpath, XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  formatchar :
* @param[in]  typeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::Create(XPATH& xpath, XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF)
{
  if(!file) return false;

  SetFormatChar(formatchar);
  SetTypeLF(typeLF);

  if(!file->Create(xpath)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::IsOpen()
* @brief      IsOpen
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::IsOpen()
{
  if(!file) return false;

  return file->IsOpen();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::Close()
{
  if(!file)          return false;
  if(!file->Close()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILETXTFORMATCHAR XFILETXT::GetFormatChar()
* @brief      GetFormatChar
* @ingroup    XUTILS
*
* @return     XFILETXTFORMATCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXTFORMATCHAR XFILETXT::GetFormatChar()
{
  return formatchar;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::SetFormatChar(XFILETXTFORMATCHAR formatchar)
* @brief      SetFormatChar
* @ingroup    XUTILS
*
* @param[in]  formatchar :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::SetFormatChar(XFILETXTFORMATCHAR formatchar)
{
  this->formatchar = formatchar;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILETXTFORMATCHAR XFILETXT::GetFormatCharFromFile(XDWORD* sizeBOM)
* @brief      GetFormatCharFromFile
* @ingroup    XUTILS
*
* @param[in]  sizeBOM :
*
* @return     XFILETXTFORMATCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXTFORMATCHAR XFILETXT::GetFormatCharFromFile(XDWORD* sizeBOM)
{
  XFILETXTFORMATCHAR formatchar;

  XBYTE   BOM[3];
  XQWORD  position = 0;

  file->GetPosition(position);
  file->SetPosition(0);

  if(sizeBOM) (*sizeBOM) = 0;

  if(file->Read((XBYTE*)&BOM,3))
    {
      if((BOM[0]==0xEF)&&(BOM[1]==0xBB)&&(BOM[2]==0xBF))
        {
          formatchar = XFILETXTFORMATCHAR_UTF8;
          if(sizeBOM) (*sizeBOM) = 3;
        }
       else
        {
          if((BOM[0]==0xFE)&&(BOM[1]==0xFF))
            {
              formatchar = XFILETXTFORMATCHAR_UTF16_BE;
              if(sizeBOM) (*sizeBOM) = 2;
            }
           else
            {
              if((BOM[0]==0xFF)&&(BOM[1]==0xFE))
                {
                  formatchar = XFILETXTFORMATCHAR_UTF16_LE;
                  if(sizeBOM) (*sizeBOM) = 2;
                }
               else formatchar = XFILETXTFORMATCHAR_ASCII;
            }
        }

    } else formatchar = XFILETXTFORMATCHAR_ASCII;

  file->SetPosition(position);

  return formatchar;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::CreateBOMFormatChar(XFILETXTFORMATCHAR formatchar, XBYTE* BOM, XDWORD& sizeBOM)
* @brief      CreateBOMFormatChar
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  BOM :
* @param[in]  sizeBOM :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::CreateBOMFormatChar(XFILETXTFORMATCHAR formatchar, XBYTE* BOM, XDWORD& sizeBOM)
{
  if(!BOM) return false;

  switch(formatchar)
    {
      case XFILETXTFORMATCHAR_UNKNOWN   :
      case XFILETXTFORMATCHAR_ASCII     : sizeBOM = 0;
                                          break;

      case XFILETXTFORMATCHAR_UTF8      : BOM[0]  = 0xEF;
                                          BOM[1]  = 0xBB;
                                          BOM[2]  = 0xBF;
                                          sizeBOM = 3;
                                          break;

      case XFILETXTFORMATCHAR_UTF16_BE  : BOM[0]  = 0xFE;
                                          BOM[1]  = 0xFF;
                                          sizeBOM = 2;
                                          break;

      case XFILETXTFORMATCHAR_UTF16_LE  : BOM[0]  = 0xFF;
                                          BOM[1]  = 0xFE;
                                          sizeBOM = 2;
                                          break;
    }

  return sizeBOM?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILETXT::SizeOfCharacter(XFILETXTFORMATCHAR formatchar)
* @brief      SizeOfCharacter
* @ingroup    XUTILS
*
* @param[in]  formatchar :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILETXT::SizeOfCharacter(XFILETXTFORMATCHAR formatchar)
{
  switch(formatchar)
    {
      case XFILETXTFORMATCHAR_UNKNOWN   :
      case XFILETXTFORMATCHAR_ASCII     :
      case XFILETXTFORMATCHAR_UTF8      : return 1;

      case XFILETXTFORMATCHAR_UTF16_BE  :
      case XFILETXTFORMATCHAR_UTF16_LE  : return 2;

    }

  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILETXTTYPELF XFILETXT::GetTypeLF()
* @brief      GetTypeLF
* @ingroup    XUTILS
*
* @return     XFILETXTTYPELF :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILETXTTYPELF XFILETXT::GetTypeLF()
{
  return typeLF;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::SetTypeLF(XFILETXTTYPELF typeLF)
* @brief      SetTypeLF
* @ingroup    XUTILS
*
* @param[in]  typeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::SetTypeLF(XFILETXTTYPELF typeLF)
{
  this->typeLF = typeLF;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::CreateTypeLF(XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF, XBYTE* LF, XDWORD& sizeLF)
* @brief      CreateTypeLF
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  typeLF :
* @param[in]  LF :
* @param[in]  sizeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::CreateTypeLF(XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF, XBYTE* LF, XDWORD& sizeLF)
{
  if(!LF) return false;

  sizeLF = 0;

  switch(formatchar)
    {
      case XFILETXTFORMATCHAR_UNKNOWN   : break;
      case XFILETXTFORMATCHAR_ASCII     :
      case XFILETXTFORMATCHAR_UTF8      : switch(typeLF)
                                            {
                                              case XFILETXTTYPELF_UNKNOWN : break;

                                              case XFILETXTTYPELF_0A      : LF[0]  = 0x0A;
                                                                            sizeLF = 1;
                                                                            break;

                                              case XFILETXTTYPELF_0D      : LF[0]  = 0x0D;
                                                                            sizeLF = 1;
                                                                            break;

                                              case XFILETXTTYPELF_0A0D    : LF[0]  = 0xA0;
                                                                            LF[1]  = 0x0D;
                                                                            sizeLF = 2;
                                                                            break;

                                              case XFILETXTTYPELF_0D0A    : LF[0]  = 0x0D;
                                                                            LF[1]  = 0x0A;
                                                                            sizeLF = 2;
                                                                            break;
                                            }
                                          break;

      case XFILETXTFORMATCHAR_UTF16_BE  : switch(typeLF)
                                            {
                                              case XFILETXTTYPELF_UNKNOWN : break;

                                              case XFILETXTTYPELF_0A      : LF[0]  = 0x00;
                                                                            LF[1]  = 0x0A;
                                                                            sizeLF = 2;
                                                                            break;

                                              case XFILETXTTYPELF_0D      : LF[0]  = 0x00;
                                                                            LF[1]  = 0x0D;
                                                                            sizeLF = 2;
                                                                            break;

                                              case XFILETXTTYPELF_0A0D    : LF[0]  = 0x00;
                                                                            LF[1]  = 0x0A;
                                                                            LF[2]  = 0x00;
                                                                            LF[3]  = 0x0D;
                                                                            sizeLF = 4;
                                                                            break;

                                              case XFILETXTTYPELF_0D0A    : LF[0]  = 0x00;
                                                                            LF[1]  = 0x0D;
                                                                            LF[2]  = 0x00;
                                                                            LF[3]  = 0x0A;
                                                                            sizeLF = 4;
                                                                            break;
                                            }
                                          break;

      case XFILETXTFORMATCHAR_UTF16_LE  : switch(typeLF)
                                            {
                                              case XFILETXTTYPELF_UNKNOWN : break;

                                              case XFILETXTTYPELF_0A      : LF[0]  = 0x0A;
                                                                            LF[1]  = 0x00;
                                                                            sizeLF = 2;
                                                                            break;

                                              case XFILETXTTYPELF_0D      : LF[0]  = 0x0D;
                                                                            LF[1]  = 0x00;
                                                                            sizeLF = 2;
                                                                            break;

                                              case XFILETXTTYPELF_0A0D    : LF[0]  = 0x0A;
                                                                            LF[1]  = 0x00;
                                                                            LF[2]  = 0x0D;
                                                                            LF[3]  = 0x00;
                                                                            sizeLF = 4;
                                                                            break;

                                              case XFILETXTTYPELF_0D0A    : LF[0]  = 0x0D;
                                                                            LF[1]  = 0x00;
                                                                            LF[2]  = 0x0A;
                                                                            LF[3]  = 0x00;
                                                                            sizeLF = 4;
                                                                            break;
                                            }
                                          break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::GetLF(XBUFFER& lfdata)
* @brief      GetLF
* @ingroup    XUTILS
*
* @param[in]  lfdata :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::GetLF(XBUFFER& lfdata)
{
  switch(typeLF)
    {
      case XFILETXTTYPELF_UNKNOWN  : return false;

      case XFILETXTTYPELF_0A      : lfdata.Add((XBYTE)0x0A);
                                    break;

      case XFILETXTTYPELF_0D      : lfdata.Add((XBYTE)0x0D);
                                    break;

      case XFILETXTTYPELF_0A0D    : lfdata.Add((XBYTE)0x0A);
                                    lfdata.Add((XBYTE)0x0D);
                                    break;

      case XFILETXTTYPELF_0D0A    : lfdata.Add((XBYTE)0x0D);
                                    lfdata.Add((XBYTE)0x0A);
                                    break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILETXT::GetLF()
* @brief      GetLF
* @ingroup    XUTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILETXT::GetLF()
{  
  return GetLF(typeLF);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XFILETXT::GetLF(XFILETXTTYPELF typeLF)
* @brief      GetLF
* @ingroup    XUTILS
* 
* @param[in]  typeLF : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILETXT::GetLF(XFILETXTTYPELF typeLF)
{
  LF.Empty();

  switch(typeLF)
    {
      case XFILETXTTYPELF_UNKNOWN : break;
      case XFILETXTTYPELF_0A      : LF = __L("\n");    break;
      case XFILETXTTYPELF_0D      : LF = __L("\r");    break;
      case XFILETXTTYPELF_0A0D    : LF = __L("\n\r");  break;
      case XFILETXTTYPELF_0D0A    : LF = __L("\r\n");  break;
    }

  return &LF;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILETXT::IsBinaryFile()
* @brief      IsBinaryFile
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::IsBinaryFile()
{  
  if(!IsOpen()) return false;
  if(!file)     return false;

  bool istextfile = false;
  
  #define MAX_BUFFER_TEST 1024*5 

  XBUFFER buffer;
  XDWORD  size          = MAX_BUFFER_TEST;
  XDWORD  controlchars  = 0;

  buffer.Resize(MAX_BUFFER_TEST);
  file->Read(buffer.Get(), &size);

  if(size)
    {
      for(XDWORD c=0; c<size; c++)
        {
          if(((buffer.Get()[c] >= 0x00) && (buffer.Get()[c] < 0x09)) ||         
             ((buffer.Get()[c] >  0x0D) && (buffer.Get()[c] < 0x20)))
            {
              controlchars++;
            }
        }

      int percent = (controlchars*100/size);
      if(percent < 10) istextfile = true;
    }     
  
  return !istextfile;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILETXT::GetNLines()
* @brief      GetNLines
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILETXT::GetNLines()
{
  return lines.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILETXT::GetLine(int index)
* @brief      GetLine
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILETXT::GetLine(int index)
{
  //if(index<0)                     return NULL;
  //if(index>=(int)lines.GetSize()) return NULL;
  //si index es <0 o index es >GetSize Get retorna NULL

  //XSTRING* string = (XSTRING*)lines.Get(index); //y ese casting?
  //return string;

  return lines.FastGet(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XFILETXT::GetLineText(int index)
* @brief      GetLineText
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XFILETXT::GetLineText(int index)
{
  XSTRING* string = GetLine(index);
  if(!string) return NULL;

  return string->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILETXT::GetAllInOneLine(XSTRING& alllines, XDWORD start, XDWORD end, XFILETXTTYPELF typeLF)
* @brief      GetAllInOneLine
* @ingroup    XUTILS
* 
* @param[in]  alllines : 
* @param[in]  start : 
* @param[in]  end : 
* @param[in]  typeLF : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::GetAllInOneLine(XSTRING& alllines, XDWORD start, XDWORD end, XFILETXTTYPELF typeLF)
{
  alllines.Empty();

  int _end = end;
  if(_end == XFILETXT_TOLASTLINE) _end = GetNLines();

  for(int c=start; c<_end; c++)
    {      
      XSTRING* line = GetLine(c);
      if(line) 
        {
          XSTRING  LF = GetLF(typeLF)->Get();
          if(!LF.IsEmpty()) 
            {
              line->Add(LF.Get());
            }

          alllines += line->Get();          
        }
    }

  if(alllines.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILETXT::GetAllInBuffer(XBUFFER& xbuffer, XDWORD start, XDWORD end, XFILETXTTYPELF typeLF)
* @brief      GetAllInBuffer
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* @param[in]  start : 
* @param[in]  end : 
* @param[in]  typeLF : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::GetAllInBuffer(XBUFFER& xbuffer, XDWORD start, XDWORD end, XFILETXTTYPELF typeLF)
{
  xbuffer.Delete();

  int _end = end;
  if(_end == XFILETXT_TOLASTLINE) _end = GetNLines();

  for(int c=start; c<_end; c++)
    {
      XSTRING* line = GetLine(c);
      if(line) 
        {
          XSTRING LF = GetLF(typeLF)->Get();
          if(!LF.IsEmpty()) 
            {
              line->Add(LF.Get());
            }

          xbuffer.Add((*line));         
        } 
    }

  if(!xbuffer.GetSize()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::ReadAllFile()
* @brief      ReadAllFile
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::ReadAllFile()
{
  return ReadNLines(XFILETXT_ALLLINES);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::WriteAllFile()
* @brief      WriteAllFile
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::WriteAllFile()
{
  if(!file)           return false;
  if(!file->IsOpen()) return false;

  if(lines.IsEmpty()) return false;

  XBYTE   BOM[3]  = { 0,0,0 };
  XDWORD  sizeBOM = 0;

  XBYTE   LF[4]   = { 0,0,0,0 };
  XDWORD  sizeLF  = 0;

  CreateBOMFormatChar(formatchar, BOM, sizeBOM);

  CreateTypeLF(formatchar, typeLF, LF, sizeLF);

  file->SetPosition(0);
  if(sizeBOM)
    {
      if(!file->Write(BOM,sizeBOM)) return false;
    }

  XBUFFER xbuffer;
  XBYTE*  buffer;
  bool    status    = true;

  buffer  = new XBYTE[XFILETXT_MAXBUFFER];
  if(buffer)
    {
      int bw;
      
      for(int c=0;c<(int)lines.GetSize();c++)
        {
          XSTRING* string = (XSTRING*)lines.Get(c);
          bw = 0;

          memset(buffer, 0, XFILETXT_MAXBUFFER);

          if(string)
            {
              switch(formatchar)
                {
                  case XFILETXTFORMATCHAR_UNKNOWN   : break;

                  case XFILETXTFORMATCHAR_ASCII     : { bw = string->GetSize();

                                                        XSTRING_CREATEOEM((*string), charstr);
                                                        memcpy(buffer,(XBYTE*)charstr, bw);
                                                        XSTRING_DELETEOEM((*string), charstr);                                                        
                                                      }
                                                      break;

                  case XFILETXTFORMATCHAR_UTF8      : string->ConvertToUTF8(buffer,bw);
                                                      break;

                  case XFILETXTFORMATCHAR_UTF16_BE  : { XWORD* bufferw = (XWORD*)buffer;

                                                        bw = (string->GetSize()*2);

                                                        for(int d=0;d<(int)string->GetSize();d++)
                                                          {
                                                            bufferw[d] = (XWORD)string->Get()[d];
                                                            bufferw[d] = (bufferw[d]<<8) | (bufferw[d]>>8);
                                                          }
                                                      }
                                                      break;

                  case XFILETXTFORMATCHAR_UTF16_LE  : { XWORD* bufferw = (XWORD*)buffer;

                                                        bw = (string->GetSize()*2);

                                                        for(int d=0;d<(int)string->GetSize();d++)
                                                          {
                                                            bufferw[d] = (XWORD)string->Get()[d];
                                                          }
                                                      }
                                                      break;
                }

              if(bw) xbuffer.Add(buffer, bw);
              xbuffer.Add(LF, sizeLF);
            }
        }

      status = file->Write(xbuffer);

      delete [] buffer;
    }

  if(status)
    {
      XQWORD position = 0;

      file->GetPosition(position);
      status = file->SetSize(position);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILETXT::ReadNLines(int nlines)
* @brief      ReadNLines
* @ingroup    XUTILS
* 
* @param[in]  nlines : number of lines to read in list. XFILETXT_ALLLINES for all
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::ReadNLines(int nlines)
{
  if(!file)           return false;
  if(!file->IsOpen()) return false;

  DeleteAllLines();

  XDWORD             sizeBOM              = 0;
  XFILETXTFORMATCHAR formatchar           = GetFormatCharFromFile(&sizeBOM);
  XDWORD             sizebytescharacter   = SizeOfCharacter(formatchar);

  if(this->formatchar==XFILETXTFORMATCHAR_UNKNOWN) this->formatchar = formatchar;

  file->SetPosition(sizeBOM);

  bool    endfile;
  XDWORD  br;
  XBUFFER dataline(false);

  XBYTE*  readbuffer = new XBYTE[XFILETXT_MAXBUFFER];
  if(!readbuffer) return false;

  memset(readbuffer, 0, XFILETXT_MAXBUFFER);

  do{ XDWORD bufferpos = 0;

      br      = XFILETXT_MAXBUFFER;
      endfile = !file->Read(readbuffer, &br);
      if(!br) break;
      
      do{ XFILETXTTYPELF  _typeLF   = XFILETXTTYPELF_UNKNOWN;
          XDWORD          sizeLF    = 0;
          XDWORD          sizeline  = 0;
          bool            endline   = GetSizeOfLine(formatchar, &readbuffer[bufferpos], _typeLF, sizeLF, sizeline, (br-bufferpos));

          if(typeLF == XFILETXTTYPELF_UNKNOWN && _typeLF != XFILETXTTYPELF_UNKNOWN) typeLF = _typeLF;

          if(endline)
            {
              dataline.Add(&readbuffer[bufferpos], sizebytescharacter*sizeline);
              AddLine(formatchar, dataline.Get(), (int)(dataline.GetSize()/sizebytescharacter));
              dataline.Delete();

              sizeline  *= sizebytescharacter;
              sizeline  += (sizeLF*sizebytescharacter);
              bufferpos += sizeline;
            }
           else
            {
              int lack = (br-bufferpos);
              dataline.Add(&readbuffer[bufferpos], lack);
              bufferpos += lack;

              if(endfile && (bufferpos == br))
                {
                  AddLine(formatchar, dataline.Get(), (int)(lack/sizebytescharacter));
                  dataline.Delete();
                }
            }

          if(nlines != XFILETXT_ALLLINES)
            {
              if(lines.GetSize() > (XDWORD)nlines)
                {
                  break;
                }
            }
          
        } while(bufferpos < br);

    } while(!endfile);

  delete [] readbuffer;

  return true;

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::DeleteFormatFile()
* @brief      DeleteFormatFile
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::DeleteFormatFile()
{
  formatchar = XFILETXTFORMATCHAR_UNKNOWN;
  typeLF     = XFILETXTTYPELF_UNKNOWN;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddLine(XCHAR* line)
* @brief      AddLine
* @ingroup    XUTILS
*
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddLine(XCHAR* line)
{
  if(!line) return false;

  XSTRING string(line);

  return AddLine(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddLine(XSTRING& line)
* @brief      AddLine
* @ingroup    XUTILS
*
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddLine(XSTRING& line)
{
  XSTRING* string = new XSTRING(line);
  if(!string) return false;

  lines.Add(string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::GenerateLineFromBuffer(XFILETXTFORMATCHAR formatchar, XBYTE* line, XDWORD sizeline, XSTRING& string)
* @brief      GenerateLineFromBuffer
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  line :
* @param[in]  sizeline :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::GenerateLineFromBuffer(XFILETXTFORMATCHAR formatchar, XBYTE* line, XDWORD sizeline, XSTRING& string)
{
  if(!line)     return true;
  if(!sizeline) return true;

  switch(formatchar)
    {
      case XFILETXTFORMATCHAR_UNKNOWN     : break;

      case XFILETXTFORMATCHAR_ASCII       :
      case XFILETXTFORMATCHAR_UTF8        :
                                            string.ConvertFromUTF8((XBYTE*)line, sizeline);
                                            break;

      case XFILETXTFORMATCHAR_UTF16_BE    : { XCHAR* unibuffer = new XCHAR[sizeline];
                                              XWORD* wline     = (XWORD*)line;

                                              if(unibuffer)
                                                {
                                                  for(XDWORD c=0; c<sizeline; c++)
                                                    {
                                                      wline[c]     = (wline[c]<<8) | (wline[c]>>8);
                                                      unibuffer[c] = wline[c];
                                                    }

                                                  string.Set(unibuffer,sizeline);

                                                  delete [] unibuffer;
                                                }
                                             }
                                             break;

      case XFILETXTFORMATCHAR_UTF16_LE   :  {  XCHAR* unibuffer = new XCHAR[sizeline];
                                               XWORD*          wline     = (XWORD*)line;
                                               if(unibuffer)
                                                 {
                                                   for(XDWORD c=0; c<sizeline; c++)
                                                     {
                                                       unibuffer[c] = wline[c];
                                                     }

                                                   string.Set(unibuffer,sizeline);

                                                   delete [] unibuffer;
                                                 }
                                            }
                                            break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddLine(XFILETXTFORMATCHAR formatchar, XBYTE* line, XDWORD sizeline)
* @brief      AddLine
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  line :
* @param[in]  sizeline :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddLine(XFILETXTFORMATCHAR formatchar, XBYTE* line, XDWORD sizeline)
{
  XSTRING* string = new XSTRING();
  if(!string) return false;

  if(GenerateLineFromBuffer(formatchar, line, sizeline, (*string)))
    {
      lines.Add(string);
    }
   else
    {
      delete string;
      string = NULL;
    }

  return string?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddLineAlready(XCHAR* line, XDWORD* resultsizeline, XDWORD* resultsizeLF)
* @brief      AddLineAlready
* @ingroup    XUTILS
*
* @param[in]  line :
* @param[in]  resultsizeline :
* @param[in]  resultsizeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddLineAlready(XCHAR* line, XDWORD* resultsizeline, XDWORD* resultsizeLF)
{
  if(!line) return false;

  XSTRING string(line);

  return AddLineAlready(string, resultsizeline, resultsizeLF);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddLineAlready(XSTRING& line, XDWORD* resultsizeline, XDWORD* resultsizeLF)
* @brief      AddLineAlready
* @ingroup    XUTILS
*
* @param[in]  line :
* @param[in]  resultsizeline :
* @param[in]  resultsizeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddLineAlready(XSTRING& line, XDWORD* resultsizeline, XDWORD* resultsizeLF)
{
  XBYTE   LF[4]   = { 0,0,0,0 };
  XDWORD  sizeLF  = 0;

  CreateTypeLF(formatchar, typeLF, LF, sizeLF);

  file->SetPosition((XDWORD)XFILE_SEEKEND);

  bool status = true;

  XBYTE* buffer = new XBYTE[XFILETXT_MAXBUFFER];
  if(buffer)
    {
      int bw = 0;
      memset(buffer,0,XFILETXT_MAXBUFFER);

      switch(formatchar)
        {
          case XFILETXTFORMATCHAR_UNKNOWN   : break;

          case XFILETXTFORMATCHAR_ASCII     : { bw = line.GetSize();

                                                XSTRING_CREATEOEM(line, charstr)
                                                memcpy(buffer, (XBYTE*)charstr, bw);
                                                XSTRING_DELETEOEM(line, charstr)
                                              }
                                              break;

          case XFILETXTFORMATCHAR_UTF8      : line.ConvertToUTF8(buffer,bw);
                                              break;

          case XFILETXTFORMATCHAR_UTF16_BE  : { XWORD* bufferw = (XWORD*)buffer;

                                                bw = (line.GetSize()*2);

                                                for(XDWORD d=0; d<line.GetSize(); d++)
                                                  {
                                                    bufferw[d] = (XWORD)line.Get()[d];
                                                    bufferw[d] = (bufferw[d]<<8) | (bufferw[d]>>8);
                                                  }
                                              }
                                              break;

          case XFILETXTFORMATCHAR_UTF16_LE  : { XWORD* bufferw = (XWORD*)buffer;

                                                bw = (line.GetSize()*2);

                                                for(XDWORD d=0; d<line.GetSize(); d++)
                                                  {
                                                    bufferw[d] = (XWORD)line.Get()[d];
                                                  }
                                              }
                                              break;
        }

      if(bw)
        {
          if(file->Write(buffer,bw))
            {
              if(file->Write(LF,sizeLF))
                {
                  if(resultsizeline) (*resultsizeline) = bw;
                  if(resultsizeLF)   (*resultsizeLF)   = sizeLF;

                }  else status = false;

            } else status = false;
        }

      delete [] buffer;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::InsertLine(int index, XCHAR* line)
* @brief      InsertLine
* @ingroup    XUTILS
*
* @param[in]  index :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::InsertLine(int index, XCHAR* line)
{
  if(!line) return false;

  XSTRING string(line);

  return InsertLine(index, string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::InsertLine(int index, XSTRING& line)
* @brief      InsertLine
* @ingroup    XUTILS
*
* @param[in]  index :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::InsertLine(int index, XSTRING& line)
{
  XSTRING* string = new XSTRING(line);
  if(!string) return false;

  return lines.Insert(index,string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::DeleteLine(int index)
* @brief      DeleteLine
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::DeleteLine(int index)
{
  if(index<0)         return false;
  if(lines.IsEmpty()) return false;

  XSTRING* line = (XSTRING*)lines.Get(index);
  if(!line) return false;

  lines.Delete(line);

  delete line;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::DeleteAllLines()
* @brief      DeleteAllLines
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::DeleteAllLines()
{
  if(lines.IsEmpty())  return false;

  lines.DeleteContents();
  lines.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::AddBufferLines(XFILETXTFORMATCHAR formatchar, XBUFFER& xbuffer)
* @brief      AddBufferLines
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::AddBufferLines(XFILETXTFORMATCHAR formatchar, XBUFFER& xbuffer)
{
  if(xbuffer.IsEmpty()) return false;

  XBYTE* buffer = xbuffer.Get();
  if(!buffer) return false;

  int br    = xbuffer.GetSize();
  int nchar = 0;

  this->formatchar = formatchar;

  do{ XFILETXTTYPELF typeLF;
      XDWORD         sizeLF   = 0;
      XDWORD         sizeline = 0;

      bool endline = GetSizeOfLine(formatchar, &buffer[nchar], typeLF, sizeLF, sizeline, (br-nchar));

      if(!endline) sizeline = (br-nchar);

      if(this->typeLF == XFILETXTTYPELF_UNKNOWN) this->typeLF = typeLF;

      AddLine(formatchar, (XBYTE*) &buffer[nchar], sizeline);

      switch(formatchar)
        {
          case XFILETXTFORMATCHAR_UNKNOWN   :
          case XFILETXTFORMATCHAR_ASCII     :
          case XFILETXTFORMATCHAR_UTF8      : nchar+=(sizeline+(endline?sizeLF:0));
                                              break;

          case XFILETXTFORMATCHAR_UTF16_BE  :
          case XFILETXTFORMATCHAR_UTF16_LE  : nchar+=((sizeline*2)+(endline?(sizeLF*2):0));
                                              break;
        }

      } while(nchar<br);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::GetSizeOfLine(XFILETXTFORMATCHAR formatchar, XBYTE* buffer, XFILETXTTYPELF& typeLF, XDWORD& sizeLF, XDWORD& size, XDWORD maxsize)
* @brief      GetSizeOfLine
* @ingroup    XUTILS
*
* @param[in]  formatchar :
* @param[in]  buffer :
* @param[in]  typeLF :
* @param[in]  sizeLF :
* @param[in]  size :
* @param[in]  maxsize :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::GetSizeOfLine(XFILETXTFORMATCHAR formatchar, XBYTE* buffer, XFILETXTTYPELF& typeLF, XDWORD& sizeLF, XDWORD& size, XDWORD maxsize)
{
  bool    status = false;
  XDWORD  c      = 0;

  sizeLF = 0;

  typeLF = XFILETXTTYPELF_UNKNOWN;

  XWORD* bufw = (XWORD*) buffer;
  XBYTE* bufb = (XBYTE*) buffer;

  switch(formatchar)
    {
      case XFILETXTFORMATCHAR_UNKNOWN   :
      case XFILETXTFORMATCHAR_ASCII     :
      case XFILETXTFORMATCHAR_UTF8      : for(c=0; c<maxsize; c++)
                                            {
                                              if(bufb[c]==0x0D)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0D;
                                                  if(bufb[c+1]==0x0A)
                                                    {
                                                      typeLF = XFILETXTTYPELF_0D0A;
                                                      sizeLF++;
                                                    }
                                                  break;
                                                }

                                              if(bufb[c]==0x0A)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0A;
                                                  if((c+1) < maxsize)
                                                    {
                                                      if(bufb[c+1]==0x0D)
                                                        {
                                                          typeLF = XFILETXTTYPELF_0A0D;
                                                          sizeLF++;
                                                        }
                                                    }
                                                  break;
                                                }
                                            }
                                          break;

      case XFILETXTFORMATCHAR_UTF16_LE  : for(c=0;c<maxsize/2;c++)
                                            {
                                              if(bufw[c]==0x000D)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0D;
                                                  if(bufw[c+1]==0x000A)
                                                    {
                                                      typeLF = XFILETXTTYPELF_0D0A;
                                                      sizeLF++;
                                                    }
                                                  break;
                                                }

                                              if(bufw[c]==0x000A)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0A;
                                                  if(bufw[c+1]==0x000D)
                                                    {
                                                      typeLF = XFILETXTTYPELF_0A0D;
                                                      sizeLF++;
                                                    }
                                                  break;
                                                }
                                            }
                                          break;

      case XFILETXTFORMATCHAR_UTF16_BE  : for(c=0; c<maxsize/2; c++)
                                            {
                                              if(bufw[c]==0x0D00)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0D;
                                                  if(bufw[c+1]==0x0A00)
                                                    {
                                                      typeLF = XFILETXTTYPELF_0D0A;
                                                      sizeLF++;
                                                    }
                                                  break;
                                                }

                                              if(bufw[c]==0x0A00)
                                                {
                                                  status = true;
                                                  sizeLF = 1;
                                                  typeLF = XFILETXTTYPELF_0A;
                                                  if(bufw[c+1]==0x0D00)
                                                    {
                                                      typeLF = XFILETXTTYPELF_0A0D;
                                                      sizeLF++;
                                                    }
                                                  break;
                                                }
                                            }
                                          break;
    }

  if(status) size = c;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* XFILETXT::GetLines()
* @brief      GetLines
* @ingroup    XUTILS
*
* @return     XVECTOR<XSTRING*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* XFILETXT::GetLines()
{
  return &lines;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::CopyFrom(XFILETXT* filetxt)
* @brief      CopyFrom
* @ingroup    XUTILS
*
* @param[in]  filetxt :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::CopyFrom(XFILETXT* filetxt)
{
  if(!filetxt) return false;

  return filetxt->CopyTo(filetxt);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILETXT::CopyTo(XFILETXT* filetxt)
* @brief      CopyTo
* @ingroup    XUTILS
*
* @param[in]  filetxt :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILETXT::CopyTo(XFILETXT* filetxt)
{
  if(!filetxt) return false;

  filetxt->formatchar = formatchar;
  filetxt->typeLF     = typeLF;
  filetxt->LF         = LF;

  filetxt->lines.DeleteContents();
  filetxt->lines.DeleteAll();

  for(int c=0; c<GetNLines(); c++)
    {
      XSTRING* line  = new XSTRING();
      if(line)
        {
          (*line) = GetLine(c)->Get();
          filetxt->lines.Add(line);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILETXT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILETXT::Clean()
{
  file       = NULL;
  formatchar = XFILETXTFORMATCHAR_UNKNOWN;
  typeLF     = XFILETXTTYPELF_UNKNOWN;
}
