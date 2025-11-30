<#!
.SYNOPSIS
  Generates a JSON index (LearningReferences.generated.json) of only the mirrored learning docs (learning/ folder) with minimal tagging.

.USAGE
  powershell -ExecutionPolicy Bypass -File .\docs\tools\GenerateLearningDocIndex.ps1
#>
param(
    [string]$RepoRoot = (Resolve-Path "$(Split-Path -Parent $MyInvocation.MyCommand.Path)\..\.."),
    [string]$OutputFile = 'docs/LearningReferences.generated.json'
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Get-Tags {
    param([string]$Name)
    $t = @()
    if ($Name -match 'Mutable') { $t += 'Mutable' }
    if ($Name -match 'Ability|GAS') { $t += 'GAS' }
    if ($Name -match 'Tag') { $t += 'GameplayTags' }
    if ($Name -match 'Crowd|Population') { $t += 'Crowd' }
    if ($Name -match 'Tutorial|Quick.?Start|Guide|Knowledge|Lesson|FAQ|Overview') { $t += 'Learning' }
    if ($Name -match 'Networking|Replication|Iris') { $t += 'Networking' }
    if ($Name -match 'Performance|Profiling') { $t += 'Performance' }
    if ($t.Count -eq 0) { $t += 'General' }
    return $t | Sort-Object -Unique
}

$learningRoot = Join-Path $RepoRoot 'learning'
if (-not (Test-Path $learningRoot)) { throw "Learning docs folder missing: $learningRoot" }
$files = Get-ChildItem -Path $learningRoot -Recurse -File -Include *.html, *.pdf | Where-Object { $_.Length -gt 0 }

$index = @()
foreach ($f in $files) {
    $title = [System.IO.Path]::GetFileNameWithoutExtension($f.Name) -replace '_', ' ' -replace '%20', ' ' -replace '-', ' '
    $index += [pscustomobject]@{
        TitleGuess   = $title.Trim()
        FileName     = $f.Name
        RelativePath = (Resolve-Path -Relative $f.FullName)
        Tags         = (Get-Tags -Name $title)
        SizeBytes    = $f.Length
        LastWriteUtc = $f.LastWriteTimeUtc.ToString('o')
        Source       = 'Learning'
    }
}
$json = $index | Sort-Object TitleGuess | ConvertTo-Json -Depth 4
Set-Content -Path (Join-Path $RepoRoot $OutputFile) -Value $json -Encoding UTF8
Write-Host "Learning index generated: $($index.Count) entries -> $OutputFile"
