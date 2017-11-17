Push-Location $PSScriptRoot

# generate XBM from BMP images (require ImageMagic in path)
magick mogrify -format xbm *.bmp

# 
$icons = "";

Get-ChildItem -filter *.xbm | ForEach-Object {
    #Write-Host "Loading $_"
    $content = Get-Content $_.FullName -Raw
    $icons = $icons + "`n" + $content
}

$icons = $icons -replace "_bits\[\] ", "_bits[] PROGMEM "

$icons | Set-Content "icons.h"

Pop-Location
