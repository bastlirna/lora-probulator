# Generate icons.h
#
# Warning: This script is call by compiler (see platform.ini) and cannot have any output
#          Otherwise output will be used as build flags and probably brake build!

Push-Location $PSScriptRoot

# generate XBM from BMP images (require ImageMagic in path)
magick mogrify -format xbm *.bmp

# combine all *.xbm to one file icons.h
$icons = "";
Get-ChildItem -filter *.xbm | ForEach-Object {
    $content = Get-Content $_.FullName -Raw
    $icons = $icons + "`n" + $content
}

$icons = $icons -replace "_bits\[\] ", "_bits[] PROGMEM "
$icons | Set-Content "icons.h"

Pop-Location
