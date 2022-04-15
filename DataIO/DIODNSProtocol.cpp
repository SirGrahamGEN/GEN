/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIODNSPROTOCOL.cpp
*
* @class      DIODNSPROTOCOL
* @brief      Data Input/Output Domain Network System (DNS) protocol class
* @ingroup    DATAIO
*
* @copyright  GEN Group. All right reserved.
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
#include <stdlib.h>

#include "XBase.h"
#include "XFactory.h"
#include "XDateTime.h"
#include "XTrace.h"
#include "XTimer.h"

#include "DIOFactory.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDP.h"

#include "DIODNSProtocol.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSPROTOCOL::DIODNSPROTOCOL()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL::DIODNSPROTOCOL()
{
  Clean();

  diostreamudpcfg = new DIOSTREAMUDPCONFIG();
  diostreamudp    = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(diostreamudpcfg);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSPROTOCOL::~DIODNSPROTOCOL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL::~DIODNSPROTOCOL()
{
  if(diostreamudpcfg)
    {
      delete diostreamudpcfg;
      diostreamudpcfg = NULL;
    }

  if(diostreamudp)
    {
      GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);
      diostreamudp    = NULL;
    }

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::SetServer(DIOIP& serverIP, XWORD serverport)
* @brief      SetServer
* @ingroup    DATAIO
*
* @param[in]  serverIP :
* @param[in]  serverport :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::SetServer(DIOIP& serverIP, XWORD serverport)
{
  if(!serverIP.Get()) return false;

  this->serverIP.Set(serverIP.Get());

  this->serverport = serverport;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::SetServer(XCHAR* serverIP, XWORD serverport)
* @brief      SetServer
* @ingroup    DATAIO
*
* @param[in]  serverIP :
* @param[in]  serverport :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::SetServer(XCHAR* serverIP, XWORD serverport)
{
  if(!serverIP) return false;

  if(!this->serverIP.Set(serverIP)) return false;

  this->serverport = serverport;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::SetServer(XSTRING& serverIP, XWORD serverport)
* @brief      SetServer
* @ingroup    DATAIO
*
* @param[in]  serverIP :
* @param[in]  serverport :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::SetServer(XSTRING& serverIP, XWORD serverport)
{
  return SetServer(serverIP.Get(), serverport);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::ResolveURL(XCHAR* URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::ResolveURL(XCHAR* URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
{
  if(!diostreamudpcfg)  return false;

  DIOURL _URL;
  bool   status = false;

  _URL = URL;

  if(_URL.IsAURLResolved())
    {
      IPresolved.Set(URL);
      return true;
    }

  XSTRING serverIPDNSstring;
  XBUFFER buffer;

  serverIP.GetXString(serverIPDNSstring);

  diostreamudpcfg->SetMode(DIOSTREAMMODE_CLIENT);
  diostreamudpcfg->SetIsUsedDatagrams(false);
  diostreamudpcfg->GetRemoteURL()->Set(serverIPDNSstring);

  if(!serverport)
          diostreamudpcfg->SetRemotePort(DIODNSPROTOCOL_DEFAULTPORT);
    else  diostreamudpcfg->SetRemotePort(serverport);

  if(diostreamudp->Open())
    {
      DIODNSPROTOCOL_HEADER headerDNS;

      headerDNS.id           = (XWORD)0x55AA55AA;
      headerDNS.qr           = 0;  //  This is a query
      headerDNS.opcode       = 0;  //  This is a standard query
      headerDNS.aa           = 0;  //  Not Authoritative
      headerDNS.tc           = 0;  //  This message is not truncated
      headerDNS.rd           = 1;  //  Recursion Desired
      headerDNS.ra           = 0;  //  Recursion not available! hey we dont have it (lol)
      headerDNS.z            = 0;
      headerDNS.ad           = 0;
      headerDNS.cd           = 0;
      headerDNS.rcode        = 0;
      headerDNS.q_count      = SwapWORD(1);  // htons(1); //we have only 1 question
      headerDNS.ans_count    = 0;
      headerDNS.auth_count   = 0;
      headerDNS.add_count    = 0;

      buffer.Add((XBYTE*)&headerDNS, sizeof(DIODNSPROTOCOL_HEADER));

      XSTRING                   origin;
      XSTRING                   target;
      DIODNSPROTOCOL_QUESTION   question;
      int                       sizeask;

      origin.Set(URL);

      ChangetoDNSNameFormat(origin, target);

      XSTRING_CREATEOEM(target, targetOEM);
      buffer.Add((XBYTE*)targetOEM, target.GetSize()+1);
      XSTRING_DELETEOEM(target, targetOEM);

      question.qtype  = SwapWORD(querytype);   // htons(querytype);
      question.qclass = SwapWORD(1);           // htons(1);

      buffer.Add((XBYTE*)&question, sizeof(DIODNSPROTOCOL_QUESTION));

      sizeask = buffer.GetSize();

      status = diostreamudp->Write(buffer);
      if(status) status = diostreamudp->WaitToFlushOutXBuffer(3);

      if(status)
        {
          buffer.Empty();
          buffer.Resize(65535);

          status = diostreamudp->WaitToFilledReadingBuffer(sizeask, 5);
          if(status) status = diostreamudp->Read(buffer);
        }

      if(status)
        {
          status = false;

          DIODNSPROTOCOL_HEADER* headerDNSanswer = (DIODNSPROTOCOL_HEADER*)buffer.Get();
          if(headerDNSanswer)
            {
            //int questions_count             = SwapWORD(headerDNSanswer->q_count);        // ntohs(headerDNSanswer->q_count);
              int answers_count               = SwapWORD(headerDNSanswer->ans_count);      // ntohs(headerDNSanswer->ans_count);
            //int authoritativeservers_count  = SwapWORD(headerDNSanswer->auth_count);     // ntohs(headerDNSanswer->auth_count);
            //int additionalrecords_count     = SwapWORD(headerDNSanswer->add_count);      // ntohs(headerDNSanswer->add_count);

              //XBYTE* reader = &buffer.Get()[sizeask];
              int    stop   = 0;

              for(int i=0; i<answers_count; i++)
                {
                  RES_RECORD* result = new RES_RECORD();
                  if(result)
                    {
                      XBYTE* reader = &buffer.Get()[sizeask];

                      result->name  = GetBufferName(reader, buffer.Get(), &stop);
                      reader += stop;

                      result->resource = (DIODNSPROTOCOL_R_DATA*)reader;
                      reader += sizeof(DIODNSPROTOCOL_R_DATA);

                      if(SwapWORD(result->resource->type) == 1)
                        {
                          IPresolved.Set((XBYTE*)reader);
                          reader = reader +  SwapWORD(result->resource->data_len);  // ntohs(result->resource->data_len);
                          status = true;
                        }
                        else
                        {
                          result->rdata = GetBufferName(reader, buffer.Get(), &stop);
                          reader += stop;

                          XSTRING URLmore;

                          URLmore = (char*)result->rdata;

                          status = ResolveURL((XCHAR*)URLmore.Get(), IPresolved, querytype, timeout);
                        }

                      free(result->name);
                      delete result;

                      if(status) break;
                    }
                }

              /*
              for(int i=0; i<ntohs(authoritativeservers_count);  i++)
                {
                  RES_RECORD* result = new RES_RECORD();
                  if(result)
                    {
                      result->name = GetBufferName(reader, buffer.Get(), &stop);
                      reader += stop;

                      result->resource = (DIODNSPROTOCOL_R_DATA*)(reader);
                      reader += sizeof(DIODNSPROTOCOL_R_DATA);

                      result->rdata = GetBufferName(reader, buffer.Get(), &stop);
                      reader+=stop;
                    }
                }

              for(int i=0; i<ntohs(additionalrecords_count); i++)
                {
                  RES_RECORD* result = new RES_RECORD();
                  if(result)
                    {
                      result->name = GetBufferName(reader, buffer.Get(), &stop);
                      reader += stop;

                      result->resource = (DIODNSPROTOCOL_R_DATA*)(reader);
                      reader += sizeof(DIODNSPROTOCOL_R_DATA);

                      if(ntohs(result->resource->type) == 1)
                        {
                          XSTRING data;

                          for(int j=0; j<ntohs(result->resource->data_len); j++)
                            {
                              data += reader[j];
                            }

                          reader += ntohs(result->resource->data_len);
                        }
                        else
                        {
                          result->rdata = GetBufferName(reader, buffer.Get(), &stop);
                          reader += stop;
                        }
                    }
                }
              */
            }
        }

      diostreamudp->Close();
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::ResolveURL(DIOURL& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::ResolveURL(DIOURL& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
{
  return ResolveURL(URL.Get(), IPresolved, querytype, timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::ResolveURL(XSTRING& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::ResolveURL(XSTRING& URL, DIOIP& IPresolved, int querytype,  XDWORD timeout)
{
  return ResolveURL(URL.Get(), IPresolved, querytype, timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSPROTOCOL::ChangetoDNSNameFormat(XSTRING& origin, XSTRING& target)
* @brief      ChangetoDNSNameFormat
* @ingroup    DATAIO
*
* @param[in]  origin :
* @param[in]  target :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL::ChangetoDNSNameFormat(XSTRING& origin, XSTRING& target)
{
  XSTRING _origin = origin;
  XCHAR*  _target;
  int     lock    = 0;

  target.Empty();
  target.AdjustSize(_MAXSTR);

  _target = target.Get();

  _origin.Add(__C('.'));

  for(int c=0; c<(int)_origin.GetSize(); c++)
    {
      if(_origin.Get()[c] == __C('.'))
        {
          *_target++ = c-lock;

          for( ;lock<c; lock++)
            {
              *_target++ = _origin.Get()[lock];
            }

          lock++;
        }
    }

  target.AdjustSize();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* DIODNSPROTOCOL::GetBufferName(XBYTE* reader,XBYTE* buffer,int* count)
* @brief      GetBufferName
* @ingroup    DATAIO
*
* @param[in]  reader :
* @param[in]  buffer :
* @param[in]  count :
*
* @return     XBYTE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* DIODNSPROTOCOL::GetBufferName(XBYTE* reader, XBYTE* buffer,int* count)
{
  XBYTE*  name;
  XDWORD  p       = 0;
  XDWORD  jumped  = 0;
  XDWORD  offset;
  int     i;
  int     j;

  *count = 1;
  name = (XBYTE*)malloc(_MAXSTR);

  name[0] = '\0';

  //read the names in 3www6google3com format
  while(*reader != 0)
    {
      if(*reader >= 192)
        {
          offset = (*reader)*256 + *(reader+1) - 49152; //49152 = 11000000 00000000 ;)
          reader = buffer + offset - 1;
          jumped = 1; //we have jumped to another location so counting wont go up!
        }
       else
        {
          name[p++] = *reader;
        }

     reader = reader + 1;

     if(jumped == 0)
       {
         *count = *count + 1; //if we havent jumped to another location then we can count up
       }
    }

  name[p] = '\0'; //string complete
  if(jumped==1)
    {
      *count = *count + 1; //number of steps we actually moved forward in the packet
    }

  //now convert 3www6google3com0 to www.google.com
  for(i=0; i<(int)strlen((const char*)name); i++)
    {
      p = name[i];

      for(j=0; j<(int)p; j++)
        {
          name[i]=name[i+1];
          i = i + 1;
        }

      name[i]='.';
    }

  name[i-1]='\0'; //remove the last dot

  return name;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODNSPROTOCOL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL::Clean()
{
  diostreamudpcfg = NULL;
  diostreamudp    = NULL;

  serverport      = 0;
}
