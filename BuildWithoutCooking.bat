set ue4Location=%~1
set workspace=%~2
set projectFilename=%~3


"%ue4Location%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%workspace%\%projectFilename%" -noP4 -platform=Win64 -clientconfig=Development -build