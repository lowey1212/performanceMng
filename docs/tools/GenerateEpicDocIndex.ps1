<#!
.SYNOPSIS
  Generates a JSON index (EpicReferences.generated.json) of only the mirrored Epic docs (pdf/html) with minimal tagging.

.USAGE
  powershell -ExecutionPolicy Bypass -File .\docs\tools\GenerateEpicDocIndex.ps1
#>
param(
    [string]$RepoRoot = (Resolve-Path "$(Split-Path -Parent $MyInvocation.MyCommand.Path)\..\.."),
    [string]$OutputFile = 'docs/EpicReferences.generated.json'
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Get-Tags {
    param([string]$Name)
    $t = @()
    if ($Name -match 'Tag') { $t += 'GameplayTags' }
    if ($Name -match 'Ability|GAS') { $t += 'GAS' }
    if ($Name -match 'Navigation|Nav') { $t += 'Navigation' }
    if ($Name -match 'Smart.?Object') { $t += 'SmartObjects' }
    if ($Name -match 'Save') { $t += 'Save' }
    if ($Name -match 'Replication|Network|Iris') { $t += 'Networking' }
    if ($Name -match 'Crowd') { $t += 'Crowd' }
    if ($Name -match 'Cloud|Sky|Atmosphere|Weather') { $t += 'Environment' }
    if ($Name -match 'Niagara|FX') { $t += 'FX' }
    if ($Name -match 'Profile|Performance|Profiling') { $t += 'Performance' }
    if ($t.Count -eq 0) { $t += 'General' }
    return $t | Sort-Object -Unique
}

$epicRoot = Join-Path $RepoRoot 'epic docs'
if (-not (Test-Path $epicRoot)) { throw "Epic docs folder missing: $epicRoot" }
$files = Get-ChildItem -Path $epicRoot -Recurse -File -Include *.html, *.pdf | Where-Object { $_.Length -gt 0 }

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
        Source       = 'Epic'
    }
}
$json = $index | Sort-Object TitleGuess | ConvertTo-Json -Depth 4
Set-Content -Path (Join-Path $RepoRoot $OutputFile) -Value $json -Encoding UTF8
Write-Host "Epic index generated: $($index.Count) entries -> $OutputFile"
