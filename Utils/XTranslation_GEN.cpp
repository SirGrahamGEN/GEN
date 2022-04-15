/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XTranslation_GEN.cpp
*
* @class      XTRANSLATION_GEN
* @brief      eXtension Translation GEN (sencences within the framework) fram class
* @ingroup    UTILS
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
#include <stdarg.h>
#include <string.h>

#include "XTranslation_GEN.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XTRANSLATION_GEN* XTRANSLATION_GEN::instance  = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------------------*/
/* XTRANSLATION_GEN_SENTENCE                                                                                           */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTRANSLATION_GEN_SENTENCE::XTRANSLATION_GEN_SENTENCE()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN_SENTENCE::XTRANSLATION_GEN_SENTENCE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTRANSLATION_GEN_SENTENCE::~XTRANSLATION_GEN_SENTENCE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN_SENTENCE::~XTRANSLATION_GEN_SENTENCE()
{
  if(sentence) delete [] sentence;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTRANSLATION_GEN_SENTENCE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTRANSLATION_GEN_SENTENCE::Clean()
{
  ID            = 0;
  codelanguage  = 0;
  sentence      = NULL;
  fixed         = 0;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* XTRANSLATION_GEN                                                                                                    */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::GetIsInstanced()
* @brief      Get Is Instanced
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTRANSLATION_GEN& XTRANSLATION_GEN::GetInstance()
* @brief      Get Instance
* @ingroup    UTILS
*
* @return     XTRANSLATION_GEN& : language instance
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN& XTRANSLATION_GEN::GetInstance()
{
  if(!instance) instance = new XTRANSLATION_GEN();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::DelInstance()
* @brief      Del Instance
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::DelInstance()
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
* @fn         XTRANSLATION_GEN::XTRANSLATION_GEN()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN::XTRANSLATION_GEN()
{
  Clean();

  Sentences_AddAll();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTRANSLATION_GEN::~XTRANSLATION_GEN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN::~XTRANSLATION_GEN()
{
  Sentences_DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::IsLanguageAvailable(XDWORD code)
* @brief      IsLanguageAvailable
* @ingroup    UTILS
*
* @param[in]  code :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::IsLanguageAvailable(XDWORD code)
{
  for(XDWORD c=0; c<languageavailables.GetSize(); c++)
    {
      if(code == languageavailables.Get(c)) return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::Sentence_Add(XDWORD ID, XDWORD codelanguage, XCHAR* sentence, XDWORD fixed)
* @brief      Sentence_Add
* @ingroup    UTILS
*
* @param[in]  ID :
* @param[in]  codelanguage :
* @param[in]  sentence :
* @param[in]  fixed :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::Sentence_Add(XDWORD ID, XDWORD codelanguage, XCHAR* sentence, XDWORD fixed)
{
  if(!ID)           return false;
  if(!codelanguage) return false;
  if(!sentence)     return false;

  if(Sentence_Get(ID, codelanguage)) return false;

  XTRANSLATION_GEN_SENTENCE* sentenceGEN = new XTRANSLATION_GEN_SENTENCE();
  if(!sentenceGEN) return false;

  int sizesentence = XSTRING::GetSize(sentence);

  sentenceGEN->ID           = ID;
  sentenceGEN->codelanguage = codelanguage;
  sentenceGEN->sentence     = new XCHAR[sizesentence+1];
  sentenceGEN->fixed        = fixed;
  if(!sentenceGEN->sentence)
    {
      delete sentenceGEN;
      return false;
    }

  memset(sentenceGEN->sentence,        0, (sizesentence+1) * sizeof(XCHAR));
  memcpy(sentenceGEN->sentence, sentence, sizesentence     * sizeof(XCHAR));

  sentences.Add(sentenceGEN);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTRANSLATION_GEN_SENTENCE* XTRANSLATION_GEN::Sentence_Get(XDWORD ID, XDWORD codelanguage)
* @brief      Sentence_Get
* @ingroup    UTILS
*
* @param[in]  ID :
* @param[in]  codelanguage :
*
* @return     XTRANSLATION_GEN_SENTENCE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTRANSLATION_GEN_SENTENCE* XTRANSLATION_GEN::Sentence_Get(XDWORD ID, XDWORD codelanguage)
{
  for(XDWORD c=0; c<sentences.GetSize(); c++)
    {
      XTRANSLATION_GEN_SENTENCE* sentence = sentences.Get(c);
      if(sentence)
        {
          if((sentence->ID == ID) && (sentence->codelanguage == codelanguage)) return sentence;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::Sentences_AddAll()
* @brief      Sentences_AddAll
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::Sentences_AddAll()
{
  languageavailables.DeleteAll();

  languageavailables.Add(XLANGUAGE_ISO_639_3_CODE_ENG);
  languageavailables.Add(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--- MONTHS -------------------------------------------------------------------------------------------------------

  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JANUARY                                      , XLANGUAGE_ISO_639_3_CODE_ENG , __L("January")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_FEBRUARY                                     , XLANGUAGE_ISO_639_3_CODE_ENG , __L("February")                                                        , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_MARCH                                        , XLANGUAGE_ISO_639_3_CODE_ENG , __L("March")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_APRIL                                        , XLANGUAGE_ISO_639_3_CODE_ENG , __L("April")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_MAY                                          , XLANGUAGE_ISO_639_3_CODE_ENG , __L("May")                                                             , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JUNE                                         , XLANGUAGE_ISO_639_3_CODE_ENG , __L("June")                                                            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JULY                                         , XLANGUAGE_ISO_639_3_CODE_ENG , __L("July")                                                            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_AUGUST                                       , XLANGUAGE_ISO_639_3_CODE_ENG , __L("August")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_SEPTEMBER                                    , XLANGUAGE_ISO_639_3_CODE_ENG , __L("September")                                                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_OCTOBER                                      , XLANGUAGE_ISO_639_3_CODE_ENG , __L("October")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_NOVEMBER                                     , XLANGUAGE_ISO_639_3_CODE_ENG , __L("November")                                                        , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_DECEMBER                                     , XLANGUAGE_ISO_639_3_CODE_ENG , __L("December")                                                        , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_PRESEPARATOR                                 , XLANGUAGE_ISO_639_3_CODE_ENG , __L("of")                                                              , 0);

  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JANUARY                                      , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Enero")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_FEBRUARY                                     , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Febrero")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_MARCH                                        , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Marzo")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_APRIL                                        , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Abril")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_MAY                                          , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Mayo")                                                            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JUNE                                         , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Junio")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_JULY                                         , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Julio")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_AUGUST                                       , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Agosto")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_SEPTEMBER                                    , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Septiembre")                                                      , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_OCTOBER                                      , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Octubre")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_NOVEMBER                                     , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Noviembre")                                                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_DECEMBER                                     , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Diciembre")                                                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_MONTH_PRESEPARATOR                                 , XLANGUAGE_ISO_639_3_CODE_SPA , __L("de")                                                              , 0);

  //--- DAYOFWEEK ----------------------------------------------------------------------------------------------------

  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_SUNDAY                                   , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Sunday")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_MONDAY                                   , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Monday")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_TUESDAY                                  , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Tuesday")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_WEDNESDAY                                , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Wednesday")                                                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_THURSDAY                                 , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Thursday")                                                        , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_FRIDAY                                   , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Friday")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_SATURDAY                                 , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Saturday")                                                        , 0);

  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_SUNDAY                                   , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Domingo")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_MONDAY                                   , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Lunes")                                                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_TUESDAY                                  , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Martes")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_WEDNESDAY                                , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Miercoles")                                                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_THURSDAY                                 , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Jueves")                                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_FRIDAY                                   , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Viernes")                                                         , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_XDATETIME_DAYOFWEEK_SATURDAY                                 , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Sabado")                                                          , 0);


  //--- APPLICATION LOG ----------------------------------------------------------------------------------------------

  Sentence_Add(XTRANSLATION_GEN_ID_APPLOG_INITMSG                                               , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Initializing application (ver %d.%d.%d) %s")                      , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY                                           , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Total memory %d Kb, free %d Kb (%d%%).")                          , 0);

  Sentence_Add(XTRANSLATION_GEN_ID_APPLOG_INITMSG                                               , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Inicializando la aplicacion (ver %d.%d.%d) %s")                   , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY                                           , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Memoria total %d Kb, libre %d Kb (%d%%).")                        , 0);
  
  //--- APPLICATION CONSOLE EXIT CODE --------------------------------------------------------------------------------

  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_NOTINFO                                      , XLANGUAGE_ISO_639_3_CODE_ENG , __L("No closing information")                                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SERIOUSERROR                              , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Application closed due to a serious error")                       , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_UPDATE                                    , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Application closed by update")                                    , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_APPLICATION                               , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Execution of the application concluded")                          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_USER                                      , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Application closed by the user")                                  , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SHUTDOWN                                  , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Application closed by shutdown of the operating system")          , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_INVALIDLICENSE                            , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Application closed by invalid license")                           , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_EXPIREDLICENSE                            , XLANGUAGE_ISO_639_3_CODE_ENG , __L("Closed application for expired license")                          , 0);

  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_NOTINFO                                      , XLANGUAGE_ISO_639_3_CODE_SPA , __L("No hay informacion de cierre")                                    , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SERIOUSERROR                              , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplicacion cerrada debido a un error grave")                      , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_UPDATE                                    , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplicacion cerrada por actualizacion")                            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_APPLICATION                               , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Ejecucion de la aplicacion concluida")                            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_USER                                      , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplicacion cerrada por el usuario")                               , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SHUTDOWN                                  , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplicacion cerrada por apagado del sistema operativo")            , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_INVALIDLICENSE                            , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplication cerrada por licencia invalida")                        , 0);
  Sentence_Add(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_EXPIREDLICENSE                            , XLANGUAGE_ISO_639_3_CODE_SPA , __L("Aplication cerrada por licencia vencida")                         , 0);

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::Sentences_DeleteAll()
* @brief      Sentences_DeleteAll
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::Sentences_DeleteAll()
{
  if(sentences.IsEmpty()) return false;

  sentences.DeleteContents();
  sentences.DeleteAll();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTRANSLATION_GEN::Sentences_AddToTranslation(XDWORD codelanguage)
* @brief      Sentences_AddToTranslation
* @ingroup    UTILS
*
* @param[in]  codelanguage :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTRANSLATION_GEN::Sentences_AddToTranslation(XDWORD codelanguage)
{
  bool existsentenceGENlanguage = false;

  for(XDWORD c=0; c<sentences.GetSize(); c++)
    {
      XTRANSLATION_GEN_SENTENCE* sentenceGEN = sentences.Get(c);
      if(sentenceGEN)
        {
          if(sentenceGEN->codelanguage == codelanguage)
            {
              GEN_XTRANSLATION.Translate_Add(sentenceGEN->ID, sentenceGEN->sentence, sentenceGEN->fixed);
              existsentenceGENlanguage = true;
            }
        }
    }

  return existsentenceGENlanguage;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTRANSLATION_GEN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTRANSLATION_GEN::Clean()
{

}

