#------------------------------------------------------------------------------
# File:   Makefile
# Coms:   TrabajoFinal Gsenku
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++                   # compilador
CPPFLAGS = -std=c++11      # opciones de compilación
RM = rm -f                 # comando para borrar ficheros

all: GSenku
#-----------------------------------------------------------
# Compilacion
GSenku.o: GSenku.cpp GSenku.hpp
	${CC} -c GSenku.cpp  ${CPPFLAGS}
mainGSenku.o: mainGSenku.cpp GSenku.cpp GSenku.hpp
	${CC} -c  mainGSenku.cpp ${CPPFLAGS}

# Linkado
GSenku: GSenku.o mainGSenku.o 
	${CC} GSenku.o mainGSenku.o 

#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} GSenku.o mainGSenku.o 