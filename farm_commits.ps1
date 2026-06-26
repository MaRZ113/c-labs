# Git commit farm script for GitHub green squares (Windows PowerShell)
# Run from repo root: .\farm_commits.ps1

# --- Settings ---
$DaysBack   = 14      # How many days back to commit
$FillRatio  = 100      # Approx % of days with commits
$MaxPerDay  = 3       # Max commits per day
$NotesFile  = "notes.txt"

# --- Commit messages ---
$Messages = @(
    "fix typo",
    "update notes",
    "fix variable",
    "code review fixes",
    "small improvements",
    "remove unused code",
    "update logic",
    "fix formatting",
    "lab progress",
    "fix compilation"
)

# --- Lines to append ---
$Lines = @(
    "// TODO: check this later",
    "// fixed",
    "// work in progress",
    "// reviewed",
    "// updated logic",
    "// minor fix",
    "// edge case handled",
    "/* placeholder */",
    "// step done",
    "// checkpoint"
)

# Create file if missing
if (-not (Test-Path $NotesFile)) {
    "# notes" | Out-File -Encoding utf8 $NotesFile
    git add $NotesFile
}

Write-Host "Starting commit farm for the last $DaysBack days..." -ForegroundColor Cyan

for ($i = $DaysBack; $i -ge 1; $i--) {
    # Skip some days randomly
    if ((Get-Random -Maximum 100) -ge $FillRatio) { continue }

    # How many commits today
    if ((Get-Random -Maximum 100) -lt 30) {
        $Count = Get-Random -Minimum 2 -Maximum ($MaxPerDay + 1)
    } else {
        $Count = 1
    }

    for ($j = 0; $j -lt $Count; $j++) {
        # Evening time: 18:00 - 23:59
        $Hour = Get-Random -Minimum 18 -Maximum 24
        $Min  = Get-Random -Minimum 0  -Maximum 60
        $Sec  = Get-Random -Minimum 0  -Maximum 60

        $Date     = (Get-Date).AddDays(-$i).ToString("yyyy-MM-dd")
        $TimeStr  = "{0:D2}:{1:D2}:{2:D2}" -f $Hour, $Min, $Sec
        $FullDate = "${Date}T${TimeStr}"

        # Append a random line
        $Line = $Lines[(Get-Random -Maximum $Lines.Count)]
        Add-Content -Encoding utf8 -Path $NotesFile -Value $Line

        # Pick a random commit message
        $Msg = $Messages[(Get-Random -Maximum $Messages.Count)]

        git add $NotesFile

        # Commit with custom date
        $env:GIT_AUTHOR_DATE    = $FullDate
        $env:GIT_COMMITTER_DATE = $FullDate
        git commit -m $Msg --quiet
        $env:GIT_AUTHOR_DATE    = $null
        $env:GIT_COMMITTER_DATE = $null

        Write-Host "  [+] $FullDate -- $Msg" -ForegroundColor Green
    }
}

Write-Host ""
Write-Host "Done! Now run: git push" -ForegroundColor Cyan
