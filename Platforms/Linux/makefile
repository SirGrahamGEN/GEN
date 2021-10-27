

#---- COMMON -----------------------------------------------------------------------------------------------------

ifneq (,$(findstring APPMODE_LIBRARY_DINAMIC, $(FLAGS)))	
	FLAGS				    += -fPIC
	FLAGSLINK	 		    += -fPIC -shared  -Wl,-soname,$(TARGET).$(SONAMEVERSION)	  
else
  ifneq (,$(findstring APPMODE_LIBRARY_STATIC, $(FLAGS)))	    
	  FLAGS 		 	    += -c     
  else
	FLAGS 		 			+= -MMD
	FLAGS 		 			+= -MP
	FLAGS 		 			+= -funwind-tables
    FLAGS 		 			+= -rdynamic
    FLAGS	  				+= -D__STDC_CONSTANT_MACROS
    FLAGS				    += -DLUA_C89_NUMBERS
  endif
endif

#---- NATIVE -----------------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTURE)" "NATIVE"
	CC 		 		         = gcc
	CCPP	  			  	 = g++
endif

#---- PC ---------------------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTURE)" "PC"
	CC		   				 = gcc
	CCPP	    			 = g++
	FLAGS			  	    += -DHW_PC	
  FLAGS 		 	  		+= -Wno-psabi    
endif

#---- PC_OLD -----------------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTURE)" "PC_OLD"
	CC		  			  	 = /opt/crosstool/gcc-2.96-20000731-glibc-2.2.4/i386-pc-linux-gnu/bin/i386-pc-linux-gnu-gcc
	CCPP	  			  	 = /opt/crosstool/gcc-2.96-20000731-glibc-2.2.4/i386-pc-linux-gnu/bin/i386-pc-linux-gnu-g++  
   #CC		   				 = gcc
   #CCPP	   			 	 = g++
	FLAGS				    += -DHW_PC
	FLAGS				    += -DHW_PC_OLD
	FLAGS	  	 		    += -D_GNU_SOURCE
	FLAGS				    += -D__GXX_ABI_VERSION=1002
   #FLAGS 		 		  	+= -Wno-newline-eofgcc    
endif

#---- RASPBERRY PI -----------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTURE)" "RASPBERRYPI"  		
	CC					     = /usr/raspberrypi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
	CCPP				     = /usr/raspberrypi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
	FLAGS  			  		+= -D HW_RASPBERRYPI	
   #INCLUDES 			    += -I /usr/raspberrypi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/usr/include/
   #INCLUDES 		   		+= -I /usr/include/
    LIBS					+= -L /usr/raspberrypi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/lib/  
    LIBS				  	+= -L /lib/arm-linux-gnueabihf/
    FLAGSLINK			  	+= -fno-use-linker-plugin
    FLAGSLINK			  	+=   
endif

#---- BLEAGLEBONE ------------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTURE)" "BEAGLEBONE"  		
	CC					     = /usr/bleaglebone/gcc-linaro-6.4.1-2018.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
	CCPP				     = /usr/bleaglebone/gcc-linaro-6.4.1-2018.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
	FLAGS  				    += -DHW_BEAGLEBONE	
	LIBS				    += -L /usr/bleaglebone/gcc-linaro-6.4.1-2018.05-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/lib
	FLAGSLINK			    += -fno-use-linker-plugin	
endif

#---- 32/64Bits  -------------------------------------------------------------------------------------------------

ifeq "$(ARCHITECTUREBITS)" "64"
	FLAGSC  				+= -m64
	FLAGSCPP			  	+= -m64
	FLAGSLINK			  	+= -m64
endif

ifeq "$(ARCHITECTUREBITS)" "32"
	FLAGSC  				+= -m32
	FLAGSCPP				+= -m32
	FLAGSLINK		  		+= -m32
endif	    


#---- DEBUG MODE -------------------------------------------------------------------------------------------------

ifeq "$(DEBUGMODE)" "YES"
	FLAGS 		 			 += -g3 
	FLAGS  					 += -D _DEBUG
	OBJECTSDIR				 = ./debug
	FLAGSLINK				 +=     
 else 
	FLAGS      				+= -g0 
	FLAGS  					+= -D NDEBUG
	OBJECTSDIR  			 = ./release
	FLAGSLINK   			+= -s   
endif	    


#---- C/C++ MODULES ----------------------------------------------------------------------------------------------

	CPPDIR				    += ../../../$(ADDDIRECTORYGEN)GEN/
	CPPDIR				    += ../../../$(ADDDIRECTORYGEN)GEN/MainProc
	CPPDIR				    += ../../../$(ADDDIRECTORYGEN)GEN/Cipher
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Compress
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/DataIO
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/DataIO/I2C
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/DataIO/SPI
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Graphic
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Graphic/2D
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Graphic/3D
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Input
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Interface
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Application
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Utils
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Script
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Script/Lib
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Sound
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/UserInterface
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Video
	CPPDIR				    += ../../../$(ADDDIRECTORYGEN)GEN/Media	
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Databases/SQL
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Databases/SQL/MySQL
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Databases/SQL/PostgreSQL
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Databases/SQL/SQLite
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Platforms/Common/SNDOpenAL
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Platforms/Common/VIDEOCodecH264
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)GEN/Platforms/Linux
	
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/agg/src
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/lua/src
	CPPDIR  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/libpcap
	
	CDIR	  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/zlib
	CDIR	  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/zlib/contrib/minizip
	CDIR	  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/jpeglib
	CDIR	  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/libpng
	CDIR    			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/stb
	CDIR	  			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/sqlite
	CDIR    			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/glew/src
	CDIR    			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/ffmpeg
	CDIR    			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/lua/src 
	CDIR    			    += ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/duktape/src 

#---- INCLUDES ---------------------------------------------------------------------------------------------------
								
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/agg/include				
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/openal-soft/include	
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/mysql-connector-c/include	
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/postgresql/src/interfaces/libpq
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/postgresql/src/include
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/glew/include  
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/lua/src 								
	INCLUDES 			    += -I ../../../$(ADDDIRECTORYGEN)ThirdPartyLibraries/duktape/src 								
								
	INCLUDES 			    += $(addprefix -I, $(CPPDIR))					 					 			   
	INCLUDES 			    += $(addprefix -I, $(CDIR))


#---- ALWAYS -----------------------------------------------------------------------------------------------------    

	SOURCESCPP			  += MainProc.cpp
	SOURCESCPP			  += MainProcLINUX.cpp

#---- GPIO HARDWARE ----------------------------------------------------------------------------------------------    


ifneq (,$(findstring DIOGPIO.cpp, $(SOURCESCPP)))	

	ifeq "$(ARCHITECTURE)" "PC"  
		SOURCESCPP      += DIOLINUXGPIOPC.cpp
	endif	

  ifeq "$(ARCHITECTURE)" "PC_OLD"  
		SOURCESCPP      += DIOLINUXGPIOPC.cpp
	endif	

	ifeq "$(ARCHITECTURE)" "RASPBERRYPI"  
		SOURCESCPP      += DIOLINUXGPIORaspberryPi.cpp	
	endif

	ifeq "$(ARCHITECTURE)" "BEAGLEBONE"  
		SOURCESCPP      += DIOLINUXGPIOBeagleBone.cpp	
	endif


endif



#---- THIRDPARTY MODULES -----------------------------------------------------------------------------------------


#---- ZLIB -------------------------------------------------------------------------------------------------------    

ifneq (,$(findstring CompressZIP.cpp, $(SOURCESCPP)))	

	SOURCESC 			    += adler32.c
	SOURCESC			    += compress.c
	SOURCESC			    += crc32.c
	SOURCESC			    += deflate.c
	SOURCESC			    += infback.c
	SOURCESC			    += inffast.c
	SOURCESC			    += inflate.c
	SOURCESC			    += inftrees.c
	SOURCESC			    += ioapi.c
	SOURCESC			    += trees.c
	SOURCESC			    += uncompr.c
	SOURCESC			    += unzip.c
	SOURCESC			    += zip.c
	SOURCESC			    += zutil.c    
         
endif         
   
#---- SQLLITE ----------------------------------------------------------------------------------------------------    

ifneq (,$(findstring SQLite_Database.cpp, $(SOURCESCPP)))	

	SOURCESC			    += sqlite3.c	
	
endif


#---- AGG --------------------------------------------------------------------------------------------------------    

ifneq (,$(findstring GRPCanvas.cpp, $(SOURCESCPP)))	

	SOURCESCPP		 	  += agg_arc.cpp
	SOURCESCPP  		  += agg_arrowhead.cpp
	SOURCESCPP  		  += agg_bezier_arc.cpp
	SOURCESCPP  		  += agg_bspline.cpp
	SOURCESCPP  		  += agg_curves.cpp
	SOURCESCPP  		  += agg_embedded_raster_fonts.cpp
	SOURCESCPP 			  += agg_gsv_text.cpp
	SOURCESCPP  		  += agg_image_filters.cpp
	SOURCESCPP  		  += agg_line_aa_basics.cpp
	SOURCESCPP  		  += agg_line_profile_aa.cpp
	SOURCESCPP  		  += agg_rounded_rect.cpp
	SOURCESCPP  		  += agg_sqrt_tables.cpp
	SOURCESCPP  		  += agg_trans_affine.cpp
	SOURCESCPP  		  += agg_trans_double_path.cpp
	SOURCESCPP  		  += agg_trans_single_path.cpp              
	SOURCESCPP  		  += agg_trans_warp_magnifier.cpp
	SOURCESCPP  		  += agg_vcgen_bspline.cpp
	SOURCESCPP  		  += agg_vcgen_contour.cpp
	SOURCESCPP  		  += agg_vcgen_dash.cpp
	SOURCESCPP  		  += agg_vcgen_markers_term.cpp
	SOURCESCPP  		  += agg_vcgen_smooth_poly1.cpp
	SOURCESCPP  		  += agg_vcgen_stroke.cpp
	SOURCESCPP  		  += agg_vpgen_clip_polygon.cpp
	SOURCESCPP  		  += agg_vpgen_clip_polyline.cpp
	SOURCESCPP  		  += agg_vpgen_segmentator.cpp      

endif         

         
#---- JPEGLIB ----------------------------------------------------------------------------------------------------    

ifneq (,$(findstring GRPBitmapFileJPG.cpp, $(SOURCESCPP)))	

	SOURCESC			    += jaricom.c
	SOURCESC			    += jcapimin.c
	SOURCESC			    += jcapistd.c
	SOURCESC			    += jcarith.c
	SOURCESC			    += jccoefct.c
	SOURCESC			    += jccolor.c
	SOURCESC			    += jcdctmgr.c
	SOURCESC			    += jchuff.c
	SOURCESC			    += jcinit.c
	SOURCESC			    += jcmainct.c
	SOURCESC			    += jcmarker.c
	SOURCESC			    += jcmaster.c
	SOURCESC			    += jcomapi.c
	SOURCESC			    += jcparam.c
	SOURCESC			    += jcprepct.c
	SOURCESC			    += jcsample.c
	SOURCESC			    += jctrans.c
	SOURCESC			    += jdapimin.c
	SOURCESC			    += jdapistd.c
	SOURCESC			    += jdarith.c
	SOURCESC			    += jdatadst.c
	SOURCESC			    += jdatasrc.c
	SOURCESC			    += jdcoefct.c
	SOURCESC			    += jdcolor.c
	SOURCESC			    += jddctmgr.c
	SOURCESC			    += jdhuff.c
	SOURCESC			    += jdinput.c
	SOURCESC			    += jdmainct.c
	SOURCESC			    += jdmarker.c
	SOURCESC			    += jdmaster.c
	SOURCESC			    += jdmerge.c
	SOURCESC			    += jdpostct.c
	SOURCESC			    += jdsample.c
	SOURCESC			    += jdtrans.c
	SOURCESC			    += jerror.c
	SOURCESC			    += jfdctflt.c
	SOURCESC			    += jfdctfst.c
	SOURCESC			    += jfdctint.c
	SOURCESC			    += jidctflt.c
	SOURCESC			    += jidctfst.c
	SOURCESC			    += jidctint.c
	SOURCESC			    += jmemmgr.c
	SOURCESC			    += jmemnobs.c
	SOURCESC			    += jquant1.c
	SOURCESC			    += jquant2.c
	SOURCESC			    += jutils.c

endif         


#---- LIBPNG -----------------------------------------------------------------------------------------------------    

ifneq (,$(findstring GRPBitmapFilePNG.cpp, $(SOURCESCPP)))		
     
	SOURCESC 			    += png.c
	SOURCESC 			    += pngerror.c
	SOURCESC 			    += pngget.c
	SOURCESC 			    += pngmem.c
	SOURCESC 			    += pngpread.c
	SOURCESC 			    += pngread.c
	SOURCESC 			    += pngrio.c
	SOURCESC 			    += pngrtran.c
	SOURCESC 			    += pngrutil.c
	SOURCESC 			    += pngset.c
	SOURCESC 			    += pngtrans.c
	SOURCESC 			    += pngwio.c
	SOURCESC 			    += pngwrite.c
	SOURCESC 			    += pngwtran.c
	SOURCESC 			    += pngwutil.c
	       
endif                  
  

#---- LUA --------------------------------------------------------------------------------------------------------    

ifneq (,$(findstring Script_Lua.cpp, $(SOURCESCPP)))	

	FLAGS			        += -DLUA_USE_POSIX  
     
	SOURCESC 			    += lapi.c
	SOURCESC 			    += lauxlib.c
	SOURCESC 			    += lbaselib.c
	SOURCESC 			    += lbitlib.c
	SOURCESC 			    += lcode.c
	SOURCESC 			    += lcorolib.c
	SOURCESC 			    += lctype.c
	SOURCESC 			    += ldblib.c
	SOURCESC 			    += ldebug.c
	SOURCESC 			    += ldo.c
	SOURCESC 			    += ldump.c
	SOURCESC 			    += lfunc.c
	SOURCESC 			    += lgc.c
	SOURCESC 			    += linit.c
	SOURCESC 			    += liolib.c
	SOURCESC 			    += llex.c
	SOURCESC 			    += lmathlib.c
	SOURCESC 			    += lmem.c
	SOURCESC 			    += loadlib.c
	SOURCESC 			    += lobject.c
	SOURCESC 			    += lopcodes.c
	SOURCESC 			    += loslib.c
	SOURCESC 			    += lparser.c
	SOURCESC 		  		+= lstate.c
	SOURCESC 		  		+= lstring.c
	SOURCESC 		  		+= lstrlib.c
	SOURCESC 		  		+= ltable.c
	SOURCESC 		  		+= ltablib.c
	SOURCESC 		  		+= ltm.c
	SOURCESC 			    += lundump.c
	SOURCESC 			    += lutf8lib.c
	SOURCESC 			    += lvm.c
	SOURCESC 			    += lzio.c
 
endif      


#---- DATABASE CLIENTS -------------------------------------------------------------------------------------------    

ifneq (,$(findstring DB_SQL_Factory.cpp, $(SOURCESCPP)))	

	ifneq (,$(findstring MySQL_Database.cpp, $(SOURCESCPP)))				

		ifeq "$(ARCHITECTURE)" "RASPBERRYPI"

			LIBS		    += -lmysqlclient_hf

		else

			LIBS  			+= -lmysqlclient

		endif

	endif		

	ifneq (,$(findstring PostgreSQL_Database.cpp, $(SOURCESCPP)))

		LIBS	  		    += -lpq

	endif
	
endif
	

#---- DUKTAPE ----------------------------------------------------------------------------------------------------  

ifneq (,$(findstring Script_Javascript.cpp, $(SOURCESCPP)))	 
	
	SOURCESC 				+= duktape.c	
 
endif      
           
#---- OPENAL -----------------------------------------------------------------------------------------------------

ifneq (,$(findstring SND_ACTIVE, $(FLAGS)))

	LIBS      				+= -lopenal

endif

#---- PCAP -------------------------------------------------------------------------------------------------------

ifneq (,$(findstring DIOLINUXPCap.cpp, $(SOURCESCPP)))	

	LIBS				    += -lpcap 

endif


#---- GENERIC LIBS -----------------------------------------------------------------------------------------------

  LIBS				      += -lstdc++ 
  LIBS				      += -lpthread
  LIBS				      += -lrt	
  LIBS				      += -ldl



ifneq (,$(findstring LINUX_X11_ACTIVE, $(FLAGS)))   				

  LIBS				      += -lX11
  LIBS					  += -lXext
  LIBS      			  += -lXrandr
  LIBS      			  += -lXxf86vm

endif


ifneq (,$(findstring DIOLINUXStreamWifiRemoteEnumDevices.cpp, $(SOURCESCPP)))	

	LIBS			      += -liw		

endif



ifneq (,$(findstring DIOLINUXStreamUSB.cpp, $(SOURCESCPP)))	

   #LIBS			      += -lusb-1.0 
	LIBS				  += -ludev 

endif



ifneq (,$(findstring DIOLINUXStreamBluetooth.cpp, $(SOURCESCPP)))	

	LIBS			      += -lbluetooth

endif

           
#---- ALL -------------------------------------------------------------------------------------------------------      

$(shell mkdir -p $(OBJECTSDIR) 2>/dev/null)

OBJECTS    	  			   = $(SOURCESCPP:.cpp=.o)
OBJECTS    	 		      += $(SOURCESC:.c=.o)
DEPENDENCIES 		       = $(SOURCESCPP:.cpp=.d)
DEPENDENCIES 		      += $(SOURCESC:.c=.d)

OBJECTSLINK  		       = $(patsubst %,$(OBJECTSDIR)/%,$(OBJECTS)) 
         
vpath %.h	$(CPPDIR)         
vpath %.cpp $(CPPDIR)
vpath %.c   $(CDIR)
vpath %.o   $(OBJECTSDIR)
                                                                                                                                                                            
all: $(TARGET) 
	@echo "  "
	@echo "Application  : $(TARGET)"
	@echo "Architecture : $(ARCHITECTURE)"
	@echo "Debug mode   : $(DEBUGMODE)"
	@echo "Compile Bits : $(ARCHITECTUREBITS)"
	@echo "--------------------------------------------------------"
                                                           
%.o : %.c
	@echo "Compiling $(*F).c ..."  	
	$(CC) $(FLAGS) $(FLAGSC) $(INCLUDES) -c -o $(OBJECTSDIR)/$(*F).o $<  
			                                                       
%.o : %.cpp
	@echo "Compiling $(*F).cpp ..."
	$(CCPP) $(FLAGS) $(FLAGSCPP) $(INCLUDES) -c -o $(OBJECTSDIR)/$(*F).o $< 
		           		
ifneq (,$(findstring APPMODE_LIBRARY_STATIC, $(FLAGS)))		 
$(TARGET) : $(OBJECTS) $(HEADERS)
	@echo "Linking   $(TARGET)" 	
	ar -cvq $(TARGET) $(OBJECTSLINK) 
else
$(TARGET) : $(OBJECTS) $(HEADERS)
	@echo "Linking   $(TARGET)" 	
	$(CCPP) $(FLAGSLINK) $(FLAGS)  $(OBJECTSLINK) -o $(TARGET) $(LIBS)
endif



#---- CLEAN -----------------------------------------------------------------------------------------------------      
	                                                         
clean :                                                  

	rm -f $(TARGET) 
	rm -R $(OBJECTSDIR)

    -include $(patsubst %,$(OBJECTSDIR)/%,$(DEPENDENCIES)) 
