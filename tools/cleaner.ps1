Get-ChildItem -Path "C:\" -Directory |
ForEach-Object {
    $size = (Get-ChildItem -Recurse -Force -ErrorAction SilentlyContinue -Path $_.FullName |
             Where-Object {!$_.PSIsContainer} |
             Measure-Object -Property Length -Sum).Sum
    [PSCustomObject]@{
        Folder = $_.FullName
        SizeGB = "{0:N2}" -f ($size / 1GB)
    }
} | Sort-Object SizeGB -Descending
