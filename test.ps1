# Check if a filename is provided
if ($args.Length -eq 0) {
    Write-Host "Please provide a filename."
    return
}

# Get the filename from the command line
$filePath = $args[0]

# Read the bytes from the file
$bytes = Get-Content -Path $filePath -Encoding Byte
$hexStrings = $bytes | ForEach-Object { $_.ToString("X2") }

$rowCount = 16 # specify the number of bytes per row
$rowNumber = 1

for ($i = 0; $i -lt $hexStrings.Length; $i += $rowCount) {
    $row = $hexStrings[$i..($i + $rowCount - 1)]

    # Check if the maximum value in the row is "00"
    $maxValueInRow = $row | ForEach-Object { [Convert]::ToInt32($_, 16) } | Measure-Object -Maximum | Select-Object -ExpandProperty Maximum
    if ($maxValueInRow -eq 0) {
        continue # Skip the row if no value is higher than 0x00
    }
    
    # Calculate the actual row number based on the index $i
    $actualRowNumber = ($i / $rowCount) + 1
    # Print the actual row number
    Write-Host -NoNewline "${actualRowNumber}: "

    # Print the row content with color coding
    foreach ($hex in $row) {
        if ($hex -eq "00") {
            Write-Host -NoNewline -ForegroundColor DarkGray "0x$hex "
        } else {
            # Color the entire "0x.." blue for values above 00
            Write-Host -NoNewline -ForegroundColor Blue "0x$hex "
        }
    }

    # Newline after each row
    Write-Host ""
    
    # Increment the row number
    $rowNumber++
}
