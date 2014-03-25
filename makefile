TARGET = cfscc

SOURCES = src/fscc.c src/calculate-clock-bits.c
HEADERS = src/fscc.h

all: $(TARGET).dll
debug: $(TARGET)d.dll

$(TARGET).dll:$(SOURCES) $(HEADERS)
  rc $(TARGET).rc
  cl /W4 /WX /D_WIN32_WINNT=0x0502 $(SOURCES) /Fe$@ /LD $(TARGET).res

$(TARGET)d.dll:$(SOURCES) $(HEADERS)
  rc /d _DEBUG /fo $(TARGET)d.res $(TARGET).rc
  cl /W4 /WX /D_WIN32_WINNT=0x0502 $(SOURCES) /Fe$@ /LDd /Zi $(TARGET)d.res

clean:
  del *.dll *.lib *.exp *.obj *.pdb *.manifest