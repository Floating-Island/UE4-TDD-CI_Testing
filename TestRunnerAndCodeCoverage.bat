set ue4Location=%~1
set workspace=%~2
set projectFilename=%~3
set testSuiteToRun=%~4
set testReportFolder=%~5
set testsLogName=%~6
set codeCoverageFile=%~7

set testRunnerCommand="%ue4Location%\Engine\Binaries\Win64\UE4Editor-cmd.exe" "%workspace%\%projectFilename%" -nosplash -Unattended -nopause  -NullRHI -nocontentbrowser -ExecCmds="Automation RunTests %testSuiteToRun%;quit" -TestExit="Automation Test Queue Empty" -ReportOutputPath="%workspace%\%testReportFolder%" -log -Log=%testsLogName%

"C:\Program Files\OpenCppCoverage\opencppcoverage.exe" --sources=%workspace%\Source --modules %workspace% --excluded_sources=\Tests --export_type=cobertura:%codeCoverageFile%  -- %testRunnerCommand%