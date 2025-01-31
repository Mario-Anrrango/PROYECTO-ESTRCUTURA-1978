[Setup]
; Define la ubicación del ejecutable y de los archivos
AppName=Proyecto Arbol AVL
AppVersion=1.0
DefaultDirName={pf}\Proyecto Arbol AVL
OutputDir=C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\Output
OutputBaseFilename=install

[Files]
; Copiar el ejecutable y los archivos de texto a la carpeta de instalación
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\main.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_historial.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\propietarios.txt"; DestDir: "{app}"; Flags: ignoreversion

[Run]
; Ejecutar el archivo main.exe después de la instalación
Filename: "{app}\main.exe"; Description: "{cm:LaunchProgram,main.exe}"; Flags: nowait postinstall

[Code]
function InitializeSetup(): Boolean;
begin
  Result := True;
  // Crear backups de los archivos .txt
  if not FileCopy('C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos.txt', 'C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_backup.txt', False) then
    MsgBox('Error al hacer backup de autos.txt', mbError, MB_OK);
  
  if not FileCopy('C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_historial.txt', 'C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\autos_historial_backup.txt', False) then
    MsgBox('Error al hacer backup de autos_historial.txt', mbError, MB_OK);
  
  if not FileCopy('C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\propietarios.txt', 'C:\REPOSITORIO\PROYECTO-ESTRCUTURA-1978\PROYECTO ARBOL AVL\propietarios_backup.txt', False) then
    MsgBox('Error al hacer backup de propietarios.txt', mbError, MB_OK);
end;
