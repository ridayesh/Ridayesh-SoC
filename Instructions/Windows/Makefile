MyLibs = "..\..\SoC Other Files\Libs\glfw3.lib" "opengl32.lib" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" "msvcrt.lib" "msvcmrt.lib"
OTHER_LOC =..\..\SoC Other Files\Other Programs
INC =..\..\SoC Other Files\include
BASIC_ROUTE =..\..\Code Files


Planet.exe: glad.obj ImageLoader.obj Shader.obj Sphere.obj Planet.obj
	link /Machine:x64 /DYNAMICBASE $(MyLibs) Planet.obj glad.obj ImageLoader.obj Shader.obj Sphere.obj
glad.obj: {$(OTHER_LOC)}glad.c
	cl /c /I "$(INC)" /nologo "$(OTHER_LOC)\glad.c"
ImageLoader.obj: {$(OTHER_LOC)}ImageLoader.cpp
	cl /c /I "$(INC)" /nologo /EHsc "$(OTHER_LOC)\ImageLoader.cpp"
Shader.obj: {$(BASIC_ROUTE)\Shader Class}Shader.cpp {$(BASIC_ROUTE)\Shader Class}Shader.h
	cl /c /I "$(INC)" /nologo /EHsc "$(BASIC_ROUTE)\Shader Class\Shader.cpp"
Sphere.obj: {$(BASIC_ROUTE)\Main Code}Sphere.cpp {$(BASIC_ROUTE)\Main Code}Sphere.h
	cl /c /I "$(INC)" /I "$(BASIC_ROUTE)\Shader Class" /nologo /EHsc "$(BASIC_ROUTE)\Main Code\Sphere.cpp"
Planet.obj: {$(BASIC_ROUTE)\Main Code}Planet.cpp
	cl /c /I "$(INC)" /I "$(BASIC_ROUTE)\Shader Class" /nologo /EHsc "$(BASIC_ROUTE)\Main Code\Planet.cpp"
clean:
	del *.obj
	del Planet.exe