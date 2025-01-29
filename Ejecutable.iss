[Setup]
AppName=Árbol AVL
AppVersion=1.0
DefaultDirName={pf}\ArbolAVL
DefaultGroupName=ArbolAVL
OutputDir=output
OutputBaseFilename=ArbolAVL_Instalador
Compression=lzma
SolidCompression=yes

[Files]
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\main.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_historial.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\propietarios.txt"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\ArbolAVL"; Filename: "{app}\main.exe"

[Run]
Filename: "{app}\main.exe"; Description: "{cm:LaunchProgram,ArbolAVL}"; Flags: nowait postinstall skipifsilent