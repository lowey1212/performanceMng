<#
.SYNOPSIS
  Creates a human-readable delta markdown file (ExternalReferences.delta.md) comparing the current
  ExternalReferences.generated.json with a stored snapshot (ExternalReferences.snapshot.json).

.PARAMETER SnapshotFile
  Path to snapshot JSON (default: docs/ExternalReferences.snapshot.json).

.PARAMETER SkipSnapshot
  If set, does not overwrite the snapshot (useful in CI for a dry diff).

The snapshot is (re)created after run unless -SkipSnapshot provided.
#>
param(
    [string]$RepoRoot = (Resolve-Path "$(Split-Path -Parent $MyInvocation.MyCommand.Path)\..\.."),
    [string]$GeneratedFile = 'docs/ExternalReferences.generated.json',
    [string]$SnapshotFile = 'docs/ExternalReferences.snapshot.json',
    [switch]$SkipSnapshot
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Get-JsonArray {
    param([string]$Path)
    if (-not (Test-Path $Path)) { return @() }
    $data = Get-Content $Path -Raw | ConvertFrom-Json -ErrorAction Stop
    if ($null -eq $data) { return @() }
    if ($data -is [System.Array]) { return $data }
    # If single object somehow returned, wrap it
    return @($data)
}

$genPath = Join-Path $RepoRoot $GeneratedFile
if (-not (Test-Path $genPath)) { throw "Generated index not found: $genPath" }
$snapPath = Join-Path $RepoRoot $SnapshotFile

$current = Get-JsonArray -Path $genPath
$previous = Get-JsonArray -Path $snapPath

function Get-IndexedMap {
    param($Array)
    $map = @{}
    foreach ($e in $Array) { $map[$e.RelativePath] = $e }
    return $map
}

$curMap = Get-IndexedMap -Array $current
$prevMap = Get-IndexedMap -Array $previous

$added = @()
$removed = @()
$changed = @()

foreach ($k in $curMap.Keys) {
    if (-not $prevMap.ContainsKey($k)) { $added += $curMap[$k]; continue }
    $c = $curMap[$k]; $p = $prevMap[$k]
    if ($c.SizeBytes -ne $p.SizeBytes -or $c.TitleGuess -ne $p.TitleGuess) { $changed += $c }
}
foreach ($k in $prevMap.Keys) {
    if (-not $curMap.ContainsKey($k)) { $removed += $prevMap[$k] }
}

$deltaMd = @()
$deltaMd += '# External References Delta'
$deltaMd += "Generated: $(Get-Date -Format o)"
$deltaMd += "Current Entries: $((@($current)).Count) | Previous Snapshot: $((@($previous)).Count)"
$deltaMd += ''
if ($added.Count -gt 0) {
    $deltaMd += '## Added'
    foreach ($a in ($added | Sort-Object TitleGuess)) { $deltaMd += "- + $($a.TitleGuess) ($($a.RelativePath))" }
    $deltaMd += ''
}
if ($removed.Count -gt 0) {
    $deltaMd += '## Removed'
    foreach ($r in ($removed | Sort-Object TitleGuess)) { $deltaMd += "- - $($r.TitleGuess) ($($r.RelativePath))" }
    $deltaMd += ''
}
if ($changed.Count -gt 0) {
    $deltaMd += '## Changed'
    foreach ($c in ($changed | Sort-Object TitleGuess)) { $deltaMd += "- * $($c.TitleGuess) ($($c.RelativePath)) SizeChanged" }
    $deltaMd += ''
}
if ($added.Count -eq 0 -and $removed.Count -eq 0 -and $changed.Count -eq 0) {
    $deltaMd += 'No differences detected.'
}

$deltaPath = Join-Path $RepoRoot 'docs/ExternalReferences.delta.md'
Set-Content -Path $deltaPath -Value ($deltaMd -join [Environment]::NewLine) -Encoding UTF8

if (-not $SkipSnapshot) {
    Copy-Item -Path $genPath -Destination $snapPath -Force
}
Write-Host "Delta written to $deltaPath (Added=$($added.Count) Removed=$($removed.Count) Changed=$($changed.Count))"
