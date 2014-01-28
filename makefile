TARGET = cfscc

SOURCES = src/fscc.c src/calculate-clock-bits.c
HEADERS = src/fscc.h

all: $(TARGET).dll
debug: $(TARGET)d.dll
managed: $(TARGET)m.dll

$(TARGET).dll:$(SOURCES) $(HEADERS)
  cl /W4 /WX /D_WIN32_WINNT=0x0502 $(SOURCES) /Fe$@ /LD

$(TARGET)d.dll:$(SOURCES) $(HEADERS)
  cl /W4 /WX /D_WIN32_WINNT=0x0502 $(SOURCES) /Fe$@ /LDd /Zi

$(TARGET)m.dll:$(SOURCES) $(HEADERS)
  cl /W4 /WX /D_WIN32_WINNT=0x0502 $(SOURCES) /Fe$@ /TP /LN /clr
  
clean:
  del *.dll *.lib *.exp *.obj *.pdb *.manifest