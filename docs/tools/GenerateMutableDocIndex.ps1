<#!
.SYNOPSIS
  Generates a JSON index (MutableReferences.generated.json) of only the mirrored Mutable docs (pdf/html) with tagging.

.USAGE
  powershell -ExecutionPolicy Bypass -File .\docs\tools\GenerateMutableDocIndex.ps1
#>
param(
    [string]$RepoRoot = (Resolve-Path "$(Split-Path -Parent $MyInvocation.MyCommand.Path)\..\.."),
    [string]$OutputFile = 'docs/MutableReferences.generated.json'
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Get-Tags {
    param([string]$Name)
    $t = @('Mutable')
    if ($Name -match 'Replicat|Network') { $t += 'Networking' }
    if ($Name -match 'Texture|Stream') { $t += 'Streaming' }
    if ($Name -match 'Perform|Profile') { $t += 'Performance' }
    if ($Name -match 'Morph|Deform') { $t += 'Morphing' }
    if ($Name -match 'LOD') { $t += 'LOD' }
    if ($Name -match 'Groom|Hair') { $t += 'Groom' }
    if ($Name -match 'Material|Shader') { $t += 'Materials' }
    return $t | Sort-Object -Unique
}

$mutRoot = Join-Path $RepoRoot 'mutable docs'
if (-not (Test-Path $mutRoot)) { throw "Mutable docs folder missing: $mutRoot" }
$files = Get-ChildItem -Path $mutRoot -Recurse -File -Include *.html, *.pdf | Where-Object { $_.Length -gt 0 }

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
        Source       = 'Mutable'
    }
}
$json = $index | Sort-Object TitleGuess | ConvertTo-Json -Depth 4
Set-Content -Path (Join-Path $RepoRoot $OutputFile) -Value $json -Encoding UTF8
Write-Host "Mutable index generated: $($index.Count) entries -> $OutputFile"
