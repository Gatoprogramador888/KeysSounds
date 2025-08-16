# Crear un certificado autofirmado para firmar código
$cert = New-SelfSignedCertificate `
    -Type CodeSigningCert `
    -Subject "CN=KeySoundEditor" `
    -CertStoreLocation Cert:\CurrentUser\My `
    -KeyExportPolicy Exportable `
    -KeyLength 2048 `
    -NotAfter (Get-Date).AddYears(5)

# Exportarlo a un archivo PFX (con clave privada) para poder usarlo en signtool
$pwd = ConvertTo-SecureString -String "MiblaCk15" -Force -AsPlainText
Export-PfxCertificate -Cert $cert -FilePath "C:\Users\gatob\source\repos\Teclado Sonido\certificates\keySoundEditor\KeySoundEditor.pfx" -Password $pwd

# Exportar solo la parte pública (.cer) para que tus amigos puedan instalarlo
Export-Certificate -Cert $cert -FilePath "C:\Users\gatob\source\repos\Teclado Sonido\certificates\keySoundEditor\KeySoundEditor.cer"
