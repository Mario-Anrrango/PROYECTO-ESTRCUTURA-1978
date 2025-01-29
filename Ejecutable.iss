[Setup]
AppName=Mi Aplicación AVL
AppVersion=1.0
DefaultDirName={pf}\Mi Aplicación AVL
DefaultGroupName=Mi Aplicación AVL
OutputDir=C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\instalador
OutputBaseFilename=InstaladorAVL
Compression=lzma
SolidCompression=yes

[Files]
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\main.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_historial.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\propietarios.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{autoprograms}\Mi Aplicación AVL"; Filename: "{app}\main.exe"
Name: "{{desktop}}\Mi Aplicación AVL"; Filename: "{app}\main.exe"
