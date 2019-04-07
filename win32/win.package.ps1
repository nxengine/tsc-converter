#prepare

mkdir release
cd release

#prepare and copy data
if ($env:PLATFORM -eq "x86") {
  cp ..\win32\tsc\Release\tsc.exe .\tsc.exe
} else {
  cp ..\x64\tsc\Release\tsc.exe .\tsc.exe
}

if ($env:PLATFORM -eq "x86") {
  #create zip
  $name = "tsc-$env:APPVEYOR_REPO_TAG_NAME-Win32.zip"
  7z a $name .\

  Push-AppveyorArtifact $name
} else {
  #create zip
  $name = "tsc-$env:APPVEYOR_REPO_TAG_NAME-Win64.zip"
  7z a $name .\

  Push-AppveyorArtifact $name
}