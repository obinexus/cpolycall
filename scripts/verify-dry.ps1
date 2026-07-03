$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $PSScriptRoot
$sourcePath = Join-Path $root 'src/cpolycall.c'
$source = Get-Content -Raw $sourcePath
$forbidden = 'fopen|open\(|CreateFile|sscanf|strtok|socket\(|connect\('
$matches = Select-String -Path $sourcePath -Pattern $forbidden

if ($matches) {
    $matches | ForEach-Object { Write-Error $_.Line }
    throw 'cpolycall must not parse configuration or implement runtime logic'
}

if (-not $source.Contains('polycall_ffi_run_config(config_path, 1)')) {
    throw 'cpolycall does not forward through polycall_ffi_run_config'
}

Write-Output 'cpolycall thin-adapter check: PASS'
