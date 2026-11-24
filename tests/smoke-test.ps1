param(
    [Parameter(Mandatory = $true)]
    [string]$ExecutablePath
)

$resolvedExecutable = (Resolve-Path $ExecutablePath).Path
$testDirectory = Join-Path $env:RUNNER_TEMP "school-task-manager-smoke"
New-Item -ItemType Directory -Path $testDirectory -Force | Out-Null
Copy-Item "SchoolTaskManager/database.txt" $testDirectory

$startInfo = [System.Diagnostics.ProcessStartInfo]::new()
$startInfo.FileName = $resolvedExecutable
$startInfo.WorkingDirectory = $testDirectory
$startInfo.RedirectStandardInput = $true
$startInfo.RedirectStandardOutput = $true
$startInfo.RedirectStandardError = $true
$startInfo.UseShellExecute = $false

$process = [System.Diagnostics.Process]::Start($startInfo)
$process.StandardInput.WriteLine("H")
$process.StandardInput.Close()

if (-not $process.WaitForExit(10000)) {
    $process.Kill()
    throw "The application did not exit after receiving the quit command."
}

$standardOutput = $process.StandardOutput.ReadToEnd()
$standardError = $process.StandardError.ReadToEnd()

if ($process.ExitCode -ne 0) {
    throw "The application exited with code $($process.ExitCode).`n$standardOutput`n$standardError"
}

if ($standardOutput -notmatch "Have a good day! Exiting") {
    throw "The application did not display its expected quit message.`n$standardOutput`n$standardError"
}
