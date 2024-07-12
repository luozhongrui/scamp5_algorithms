# Compiler settings
CC = cl
CFLAGS = /EHsc /Iinclude /Zi /Od /MDd /D "DEBUG"  # Debug info, dynamic linking, disabled optimization
LFLAGS = /link /LIBPATH:lib\\Debug /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:libcmt # ignore lib conficts

# Define the output file name
OUTPUT = app.exe

# Define source and object files./
SOURCES = src\main.cpp
OBJECTS = src\main.obj

# Libraries to link, adjust as necessary for a console application
LIBS = scamp5_sim_lib.lib Kernel32.lib Advapi32.lib User32.lib

# Link the program
$(OUTPUT): $(OBJECTS)
    $(CC) $(OBJECTS) $(LIBS) $(LFLAGS) /out:$@

# Compile the source files
src/main.obj: src/main.cpp
    $(CC) $(CFLAGS) /c src/main.cpp /Fo$@

# Clean target
clean:
    del $(OBJECTS) $(OUTPUT)
