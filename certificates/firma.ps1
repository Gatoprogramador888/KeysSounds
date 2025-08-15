# firma.ps1
param(
    [string]$exePath = "C:\Users\gatob\source\repos\Teclado Sonido\x64\Release\installer\Installer.exe",        # ruta del EXE a firmar
    [string]$pfxPath = "C:\Users\gatob\source\repos\Teclado Sonido\certificates\MiCertificado.pfx",  # ruta al PFX
    [string]$pfxPassword = "MiblaCk15"        # contraseña del PFX
)

# Firmar el ejecutable con timestamp
#signtool sign /f $pfxPath /p $pfxPassword /tr http://timestamp.digicert.com /td sha256 /fd sha256 $exePath
& "C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x64\signtool.exe" sign /f $pfxPath /p $pfxPassword /tr http://timestamp.digicert.com /td sha256 /fd sha256 $exePath



Write-Host "Firma completada: $exePath"
#.\firma.ps1 -exePath "C:\MisProyectos\bin\Installer.exe" -pfxPath "C:\Certificados\MiCertificado.pfx" -pfxPassword "MiContraseñaSegura"

#.\firma.ps1 -exePath "C:\Users\gatob\source\repos\Teclado Sonido\x64\Release\installer\Installer.exe" -pfxPath "C:\Users\gatob\source\repos\Teclado Sonido\certificates\MiCertificado.pfx" -pfxPassword "MiblaCk15"  
