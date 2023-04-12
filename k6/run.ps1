param (
    [Parameter(Position=0)]
    [string]$suffix
)

if (-not $suffix) {
    Write-Host "Usage: .\run.ps1 <suffix>"
    exit
}

$resultDir = "result"
if (-not (Test-Path -Path $resultDir)) {
    New-Item -ItemType Directory -Path $resultDir | Out-Null
}

$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$outputFile = "${resultDir}\output_${timestamp}${suffix}.txt"

k6 run test01.js | Set-Content -Path $outputFile
