#
# Created by makemake (Darwin Feb 22 2012) on Wed Mar 28 21:50:21 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb -Wall -ansi -pedantic
CFLAGS =	-ggdb -Wall -ansi -pedantic
BINDIR =.
CLIBFLAGS =	-lm
CCLIBFLAGS = -lncurses -lmenu	
########## End of default flags


CPP_FILES =	id3.cpp library.cpp main.cpp main_window.cpp manager.cpp music_list.cpp observable.cpp play_queue.cpp playlist.cpp song.cpp termp3.cpp
C_FILES =	
S_FILES =	
H_FILES =	defines.h id3.h library.h main_window.h manager.h music_list.h observable.h observer.h play_queue.h playlist.h song.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	id3.o library.o main_window.o manager.o music_list.o observable.o play_queue.o playlist.o song.o 

#
# Main targets
#

all:	${BINDIR}/main ${BINDIR}/termp3 

${BINDIR}/main:	main.o $(OBJFILES)
	@mkdir -p ${BINDIR}/
	$(CXX) $(CXXFLAGS) -o ${BINDIR}/main main.o $(OBJFILES) $(CCLIBFLAGS)

${BINDIR}/termp3:	termp3.o $(OBJFILES)
	@mkdir -p ${BINDIR}/
	$(CXX) $(CXXFLAGS) -o ${BINDIR}/termp3 termp3.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

id3.o:	id3.h
library.o:	defines.h id3.h library.h music_list.h song.h
main.o:	defines.h id3.h library.h music_list.h song.h
main_window.o:	defines.h id3.h library.h main_window.h music_list.h observer.h song.h
manager.o:	defines.h id3.h library.h manager.h music_list.h observable.h observer.h play_queue.h playlist.h song.h
music_list.o:	id3.h music_list.h song.h
observable.o:	observable.h observer.h
play_queue.o:	id3.h music_list.h play_queue.h song.h
playlist.o:	id3.h music_list.h playlist.h song.h
song.o:	id3.h song.h
termp3.o:	defines.h id3.h library.h main_window.h music_list.h observer.h song.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) main.o termp3.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf ${BINDIR}/main ${BINDIR}/termp3 
