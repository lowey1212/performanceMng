<#
.SYNOPSIS
  Scans mirrored documentation folders (epic docs/, mutable docs/) and generates a JSON index (ExternalReferences.generated.json)
  with basic metadata (TitleGuess, FileName, RelativePath, Tags[]) for internal tooling.

.USAGE
  Run from repo root (or adjust $RepoRoot). Example:
    powershell -ExecutionPolicy Bypass -File .\docs\tools\GenerateDocIndex.ps1

.NOTES
  Heuristic only: refine tag patterns over time.
#>
param(
    [string]$RepoRoot = (Resolve-Path "$(Split-Path -Parent $MyInvocation.MyCommand.Path)\..\.."),
    [string]$OutputFile = "docs/ExternalReferences.generated.json"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Guess-Tags {
    param([string]$Name)
    $tags = @()
    if ($Name -match 'Ability|GAS') { $tags += 'GameplayAbilitySystem' }
    if ($Name -match 'Tag') { $tags += 'GameplayTags' }
    if ($Name -match 'Navigation|Nav') { $tags += 'Navigation' }
    if ($Name -match 'Smart.?Object') { $tags += 'SmartObjects' }
    if ($Name -match 'Mutable') { $tags += 'Mutable' }
    if ($Name -match 'Save') { $tags += 'SaveSystem' }
    if ($Name -match 'Quest') { $tags += 'Quests' }
    if ($Name -match 'Niagara|FX') { $tags += 'FX' }
    if ($Name -match 'Cloud|Sky|Atmosphere|Weather') { $tags += 'Environment' }
    if ($Name -match 'Profile|Performance|Profiling') { $tags += 'Performance' }
    if ($Name -match 'Replication|Network|Iris') { $tags += 'Networking' }
    if ($Name -match 'Tutorial|Quick.?Start|Guide|Knowledge|Lesson|FAQ|Overview') { $tags += 'Learning' }
    if ($tags.Count -eq 0) { $tags += 'General' }
    return $tags | Sort-Object -Unique
}

$docRoots = @('epic docs', 'mutable docs', 'learning') | ForEach-Object { Join-Path $RepoRoot $_ }
$files = @()
foreach ($root in $docRoots) {
    if (-not (Test-Path $root)) { continue }
    $files += Get-ChildItem -Path $root -Recurse -File -Include *.html, *.pdf | Where-Object { $_.Length -gt 0 }
}

$index = @()
foreach ($f in $files) {
    $titleGuess = [System.IO.Path]::GetFileNameWithoutExtension($f.Name) -replace '_', ' ' -replace '%20', ' ' -replace '-', ' '
    $index += [pscustomobject]@{
        TitleGuess   = $titleGuess.Trim()
        FileName     = $f.Name
        RelativePath = (Resolve-Path -Relative $f.FullName)
        Tags         = (Guess-Tags -Name $titleGuess)
        SizeBytes    = $f.Length
        LastWriteUtc = $f.LastWriteTimeUtc.ToString('o')
    }
}

$json = $index | Sort-Object TitleGuess | ConvertTo-Json -Depth 4
Set-Content -Path (Join-Path $RepoRoot $OutputFile) -Value $json -Encoding UTF8
Write-Host "Generated $($index.Count) entries -> $OutputFile"
