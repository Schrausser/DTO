@echo off
cls
echo - 'Nicht senden' clicken ...
dtprm dtren.bat dtrenp.bat _srp+2
echo -
echo -
echo Produziert einen Fehler, da durch automatische Generierung von DTREN.BAT eine Zeile (Zeilenvoschub) zuviel vorliegt.
kopie dtren.bat dtrena.bat
echo -
echo -
echo Erstellt eine um 2 Zeichen verschobene Dateikopie DTRENA.BAT von DTREN.BAT (die letzten 2 Zeichen werden abgschnitten).
dtprm dtrena.bat dtrenp.bat _srp+2
echo -
echo -
echo Funktioniert nun.
echo -
pause