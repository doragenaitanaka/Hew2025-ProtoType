# SaveAsUTF8.ps1
param (
    [string]$directory = "."
)

# クオートを除去する
$directory = $directory.Trim('"')

Write-Output "Script is running. Processing directory: $directory"

Get-ChildItem -Path $directory -Include *.cpp, *.h -Recurse | ForEach-Object {
    $file = $_.FullName
    $fileContent = [System.IO.File]::ReadAllBytes($file)
    $isUtf8 = $fileContent[0] -eq 0xEF -and $fileContent[1] -eq 0xBB -and $fileContent[2] -eq 0xBF

    if (-not $isUtf8) {
        $content = Get-Content -Path $file -Raw
        $content | Out-File -FilePath $file -Encoding utf8 -Force
        Write-Output "Processed file: $file"
    } else {
        # Write-Output "Skipped file (already UTF-8): $file"
    }
}