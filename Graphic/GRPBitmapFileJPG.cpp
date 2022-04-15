/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPBitmapFileJPG.cpp
*
* @class      GRPBITMAPFILEJPG
* @brief      Graphic bitmap file JPEG format (JPEG: Joint Photographic Experts Group) class
* @ingroup    GRAPHIC
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

#include "GRPFactory.h"
#include "GRPBitmap.h"

#include "GRPBitmapFileJPG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         METHODDEF(void) GRPBITMAPFILEJPG_ErrorExit(j_common_ptr info)
* @brief      Callback error Exist
* @ingroup    GRAPHIC
*
* @param[in]  j_common_ptr: ptr struct common
*
* @return     METHODDEF(void)
*
*---------------------------------------------------------------------------------------------------------------------*/
METHODDEF(void) GRPBITMAPFILEJPG_ErrorExit(j_common_ptr info)
{
  GRPBITMAPFILEJPG_ERROR_PTR myerr = (GRPBITMAPFILEJPG_ERROR_PTR) info->err;

  (*info->err->output_message)(info);
  longjmp(myerr->setjmp_buffer, 1);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILEJPG::GRPBITMAPFILEJPG()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILEJPG::GRPBITMAPFILEJPG(): GRPBITMAPFILEBASE()
{
  Clean();

  memset(&cinfo, 0, sizeof(struct jpeg_compress_struct));
  memset(&dinfo, 0, sizeof(struct jpeg_decompress_struct));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILEJPG::~GRPBITMAPFILEJPG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILEJPG::~GRPBITMAPFILEJPG()
{
  memset(&cinfo, 0, sizeof(struct jpeg_compress_struct));
  memset(&dinfo, 0, sizeof(struct jpeg_decompress_struct));

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILEJPG::CreateBitmapFromFile(XPATH& xpath, GRPPROPERTYMODE forcemode)
* @brief      CreateBitmapFromFile
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILEJPG::CreateBitmapFromFile(XPATH& xpath, GRPPROPERTYMODE forcemode)
{
  if(!Open(xpath))  return NULL;

  GRPBITMAPFILEJPGHEADER  header;
  GRPBITMAP*              bitmap = NULL;
  bool                    status = true;

  if(!ReadHeaderFile(&header))
    {
      Close();
      return NULL;
    }

  bitmap = GRPFACTORY::GetInstance().CreateBitmap(header.width, header.height, GRPPROPERTYMODE_24_RGB_888);
  if(bitmap)
    {
      XBYTE* databuffer = new XBYTE[header.size];
      if(databuffer)
        {
          if(DecodeToBufferFromFile(databuffer))
            {
              int index = 0;

              for (int y = header.height - 1; y > -1; y--)
              {
                  for (XDWORD x = 0; x < header.width; x++)
                  {
                      GRP2DCOLOR_RGBA8 color(databuffer[index + 0],

                      databuffer[index + 1],
                      databuffer[index + 2], 255);

                      bitmap->PutPixel(x, y, (GRP2DCOLOR*)&color);

                      index += 3;
                  }
              }

            } else status = false;

          delete [] databuffer;

        } else status = false;

    } else status = false;

  if(!status)
    {
      if(bitmap)
        {
          GRPFACTORY::GetInstance().DeleteBitmap(bitmap);
          bitmap = NULL;
        }
    }

  Close();

  return ForceModeOfBitmap(forcemode, bitmap);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILEJPG::CreateBitmapFromBuffer(XBYTE* buffer, XDWORD size, GRPPROPERTYMODE forcemode)
* @brief      CreateBitmapFromBuffer
* @ingroup    GRAPHIC
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILEJPG::CreateBitmapFromBuffer(XBYTE* buffer, XDWORD size, GRPPROPERTYMODE forcemode)
{
  GRPBITMAPFILEJPGHEADER  header;
  GRPBITMAP*              bitmap = NULL;
  bool                    status = true;

  if(!ReadHeaderBuffer(buffer, size, &header))
    {
      Close();
      return NULL;
    }

  bitmap = GRPFACTORY::GetInstance().CreateBitmap(header.width, header.height, GRPPROPERTYMODE_24_RGB_888);
  if(bitmap)
    {
      XBYTE* databuffer = new XBYTE[header.size];
      if(databuffer)
        {
          if(DecodeToBufferFromRawBuffer(buffer, size, databuffer))
            {
              int index = 0;

              for (int y = header.height - 1; y > -1; y--)
              {
                  for (XDWORD x = 0; x < header.width; x++)
                  {
                      GRP2DCOLOR_RGBA8 color(databuffer[index + 0],
                                             databuffer[index + 1],
                                             databuffer[index + 2], 255);

                      bitmap->PutPixel(x, y, (GRP2DCOLOR*)&color);

                      index += 3;
                  }
              }

            } else status = false;

          delete [] databuffer;

        } else status = false;

    } else status = false;

  if(!status)
    {
      if(bitmap)
        {
          GRPFACTORY::GetInstance().DeleteBitmap(bitmap);
          bitmap = NULL;
        }
    }

  Close();

  return ForceModeOfBitmap(forcemode, bitmap);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::CreateFileFromBitmap(XPATH& xpath, GRPBITMAP* bitmap, int quality)
* @brief      CreateFileFromBitmap
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  bitmap :
* @param[in]  quality :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::CreateFileFromBitmap(XPATH& xpath, GRPBITMAP* bitmap, int quality)
{
  if(!bitmap)        return false;

  if(!Create(xpath)) return false;

  int size = bitmap->GetWidth() * bitmap->GetHeight() * 3;
  bool status = true;

  XBYTE* databuffer = new XBYTE[size];
  if(databuffer)
    {
      int index = 0;

      for(int y=(int)(bitmap->GetHeight()-1); y>-1; y--)
        {
          for(int x=0; x<(int)bitmap->GetWidth(); x++)
            {
              GRP2DCOLOR_RGBA8* color = (GRP2DCOLOR_RGBA8*)bitmap->GetPixel(x, y);

              databuffer[index + 0] = color->r;
              databuffer[index + 1] = color->g;
              databuffer[index + 2] = color->b;

              index+=3;
            }
        }

    } else status = false;

  status = EncodeToFile(bitmap->GetWidth(), bitmap->GetHeight(),  databuffer, quality, false);

  delete [] databuffer;

  Close();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFILEJPG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFILEJPG::Clean()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::ReadHeaderFile(GRPBITMAPFILEJPGHEADER* header)
* @brief      ReadHeader
* @ingroup    GRAPHIC
*
* @param[in]  header :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::ReadHeaderFile(GRPBITMAPFILEJPGHEADER* header)
{
  if(!header) return false;

  struct GRPBITMAPFILEJPG_ERROR jerr;

  if(!GetPrimaryFile()) return false;
  GetPrimaryFile()->SetPosition(0);

  dinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = GRPBITMAPFILEJPG_ErrorExit;

  if(setjmp(jerr.setjmp_buffer))
    {
      jpeg_destroy_decompress(&dinfo);
      Close();
      return false;
    }

  jpeg_create_decompress(&dinfo);                                     /* Now we can initialize the JPEG decompression object. */
//  jpeg_stdio_src(&dinfo, GetPrimaryFile()->GetFileStructHandle());        /* Step 2: specify data source (eg, a file) */

  //DIEGO: el uso de la entrada de stdio_src para jpeg tiene mas viejo que espinete. Y crear el dup del handle de fichero de windows era catastrofico con el nuevo VS2015
  //       leo todo el fichero en memoria y lo descomprimo usando el manejador mem_src.

  XQWORD file_size = GetPrimaryFile()->GetSize();
  XBYTE* file_buffer = new XBYTE[(XDWORD)file_size];

  GetPrimaryFile()->SetPosition(0);
  GetPrimaryFile()->Read(file_buffer, (XDWORD)file_size);

  jpeg_mem_src(&dinfo, file_buffer, (XDWORD)file_size);
  jpeg_read_header(&dinfo, TRUE);

  header->width  = dinfo.image_width;
  header->height = dinfo.image_height;
  header->size   = (header->height*header->width*3);

  jpeg_destroy_decompress(&dinfo);

  GetPrimaryFile()->SetPosition(0);

  delete [] file_buffer;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::ReadHeaderBuffer(XBYTE* buffer, XDWORD size, GRPBITMAPFILEJPGHEADER* header)
* @brief      ReadHeaderBuffer
* @ingroup    GRAPHIC
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  header :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::ReadHeaderBuffer(XBYTE* buffer, XDWORD size, GRPBITMAPFILEJPGHEADER* header)
{
  if(!header) return false;

  struct GRPBITMAPFILEJPG_ERROR jerr;

  dinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = GRPBITMAPFILEJPG_ErrorExit;

  if(setjmp(jerr.setjmp_buffer))
    {
      jpeg_destroy_decompress(&dinfo);
      return false;
    }

  jpeg_create_decompress(&dinfo);                                     /* Now we can initialize the JPEG decompression object. */
//  jpeg_stdio_src(&dinfo, GetPrimaryFile()->GetFileStructHandle());        /* Step 2: specify data source (eg, a file) */

  //DIEGO: el uso de la entrada de stdio_src para jpeg tiene mas viejo que espinete. Y crear el dup del handle de fichero de windows era catastrofico con el nuevo VS2015
  //       leo todo el fichero en memoria y lo descomprimo usando el manejador mem_src.

  jpeg_mem_src(&dinfo, buffer, size);
  jpeg_read_header(&dinfo, TRUE);

  header->width  = dinfo.image_width;
  header->height = dinfo.image_height;
  header->size   = (header->height*header->width*3);

  jpeg_destroy_decompress(&dinfo);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::Read(XBYTE* buffer)
* @brief      Read
* @ingroup    GRAPHIC
*
* @param[in]  buffer : buffer read data
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::DecodeToBufferFromFile(XBYTE* buffer)
{
  if(!buffer)           return false;
  if(!GetPrimaryFile()) return false;

  JSAMPARRAY  line;         /* Output row buffer */
  int         rowstride;    /* physical row width in output buffer */

  struct GRPBITMAPFILEJPG_ERROR jerr;

  GetPrimaryFile()->SetPosition(0);

  dinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = GRPBITMAPFILEJPG_ErrorExit;

  if(setjmp(jerr.setjmp_buffer))
    {
      jpeg_destroy_decompress(&dinfo);
      Close();
      return false;
    }

  jpeg_create_decompress(&dinfo);                                     /* Now we can initialize the JPEG decompression object. */
  //jpeg_stdio_src(&dinfo, GetPrimaryFile()->GetFileStructHandle());        /* Step 2: specify data source (eg, a file) */

  //DIEGO: el uso de la entrada de stdio_src para jpeg es mas viejo que espinete. Y crear el dup del handle de fichero de windows era catastrofico con el nuevo VS2015
  //       leo todo el fichero en memoria y lo descomprimo usando el manejador mem_src.
  // es el mismo problema que arriba, por lo que se lee 2 veces. Deberia contenerse en memoria la primera vez que se accede.

  XQWORD file_size = GetPrimaryFile()->GetSize();
  XBYTE* file_buffer=new XBYTE[(XDWORD)file_size];

  GetPrimaryFile()->SetPosition(0);
  GetPrimaryFile()->Read(file_buffer, (XDWORD)file_size);
  jpeg_mem_src(&dinfo, file_buffer, (XDWORD)file_size);

  jpeg_read_header(&dinfo, TRUE);

  jpeg_start_decompress(&dinfo);

  rowstride = dinfo.output_width * dinfo.output_components;

  line = (*dinfo.mem->alloc_sarray)((j_common_ptr) &dinfo, JPOOL_IMAGE, rowstride, 1);

  int size  = dinfo.output_width * dinfo.output_height * dinfo.output_components;
  int index = (size-rowstride);

  memset(buffer, 0 ,size);

  while (dinfo.output_scanline < dinfo.output_height)
    {
      jpeg_read_scanlines(&dinfo, line, 1);

      memcpy((XBYTE*)&buffer[index],(XBYTE*)(*line),rowstride);
      index-=rowstride;
    }

  jpeg_finish_decompress(&dinfo);

  jpeg_destroy_decompress(&dinfo);

  GetPrimaryFile()->SetPosition(0);

  delete [] file_buffer;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::DecodeToBufferFromRawBuffer(XBYTE* buffer, XDWORD size, XBYTE* tobuffer)
* @brief      DecodeToBufferFromRawBuffer
* @ingroup    GRAPHIC
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  tobuffer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::DecodeToBufferFromRawBuffer(XBYTE* buffer, XDWORD size, XBYTE* tobuffer)
{
  if(!buffer)       return false;
  if(!tobuffer)     return false;

  JSAMPARRAY  line;         /* Output row buffer */
  int         rowstride;    /* physical row width in output buffer */

  struct GRPBITMAPFILEJPG_ERROR jerr;

  dinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = GRPBITMAPFILEJPG_ErrorExit;

  if(setjmp(jerr.setjmp_buffer))
    {
      jpeg_destroy_decompress(&dinfo);
      return false;
    }

  jpeg_create_decompress(&dinfo);                                           /* Now we can initialize the JPEG decompression object. */
  //jpeg_stdio_src(&dinfo, GetPrimaryFile()->GetFileStructHandle());        /* Step 2: specify data source (eg, a file) */

  //DIEGO: el uso de la entrada de stdio_src para jpeg es mas viejo que espinete. Y crear el dup del handle de fichero de windows era catastrofico con el nuevo VS2015
  //       leo todo el fichero en memoria y lo descomprimo usando el manejador mem_src.
  // es el mismo problema que arriba, por lo que se lee 2 veces. Deberia contenerse en memoria la primera vez que se accede.

  jpeg_mem_src(&dinfo, buffer, size);

  jpeg_read_header(&dinfo, TRUE);

  jpeg_start_decompress(&dinfo);

  rowstride = dinfo.output_width * dinfo.output_components;

  line = (*dinfo.mem->alloc_sarray)((j_common_ptr) &dinfo, JPOOL_IMAGE, rowstride, 1);

  int resultsize  = dinfo.output_width * dinfo.output_height * dinfo.output_components;
  int index       = (resultsize-rowstride);

  memset(tobuffer, 0, resultsize);

  while(dinfo.output_scanline < dinfo.output_height)
    {
      jpeg_read_scanlines(&dinfo, line, 1);

      memcpy((XBYTE*)&tobuffer[index], (XBYTE*)(*line), rowstride);
      index-=rowstride;
    }

  jpeg_finish_decompress(&dinfo);

  jpeg_destroy_decompress(&dinfo);


  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEJPG::EncodeToFile(int width, int height, XBYTE* buffer, int quality, bool baseline)
* @brief      EncodeToFile
* @ingroup    GRAPHIC
*
* @param[in]  width :
* @param[in]  height :
* @param[in]  buffer :
* @param[in]  quality :
* @param[in]  baseline :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEJPG::EncodeToFile(int width, int height,  XBYTE* buffer, int quality, bool baseline)
{
  if(!buffer)           return false;
  if(!GetPrimaryFile()) return false;

  struct jpeg_error_mgr jerr;

  JSAMPROW rowpointer[1]; /* pointer to JSAMPLE row[s] */
  int      rowstride;     /* physical row width in image buffer */

  GetPrimaryFile()->SetPosition(0);

  cinfo.err = jpeg_std_error(&jerr);

  jpeg_create_compress(&cinfo);

  FILE* filehandle = GetPrimaryFile()->CreateStructHandle();
  if(!filehandle) return false;

  jpeg_stdio_dest(&cinfo, filehandle);

  cinfo.image_width       = width;          /* image width and height, in pixels */
  cinfo.image_height      = height;
  cinfo.input_components  = 3;              /* # of color components per pixel */
  cinfo.in_color_space    = JCS_RGB;        /* colorspace of input image */

  jpeg_set_defaults(&cinfo);

  jpeg_set_quality(&cinfo, quality, baseline);

  jpeg_start_compress(&cinfo, TRUE);

  rowstride = width * 3;  /* JSAMPLEs per row in image_buffer */

  int size  = width * height * 3;

  size -= rowstride;

  while (cinfo.next_scanline < cinfo.image_height)
    {
      rowpointer[0] = &buffer[size-(cinfo.next_scanline * rowstride)];

      jpeg_write_scanlines(&cinfo, rowpointer, 1);
    }

  jpeg_finish_compress(&cinfo);

  jpeg_destroy_compress(&cinfo);

  GetPrimaryFile()->SetPosition(0);

  return true;
}


