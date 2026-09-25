# StudyTrack

Ein C++-Konsolenprogramm zum Erfassen von Lernzeiten. Ein Lernprojekt mit
KI-Unterstuetzung, das schrittweise nachvollzogen und weiterentwickelt wird.

## Funktionen

- Faecher hinzufuegen und anzeigen
- Lernzeit in Minuten mit Fach und Datum erfassen
- Alle Lerneintraege anzeigen
- Summen pro Fach und insgesamt berechnen
- Automatisch in `studytrack.txt` speichern und beim Neustart laden
- Zahlen und Kalenderdaten pruefen, inklusive Schaltjahre

Die Lernzeit wird manuell eingegeben; es gibt keine Stoppuhr.
Faecher werden einzeln hinzugefuegt, eine vorherige Anzahl ist nicht erforderlich.

## Voraussetzungen und Start

Ein C++17-Compiler, zum Beispiel ein aktueller GCC mit `g++`.
Im Terminal zuerst in den entpackten Projektordner wechseln.

Windows (PowerShell, wenn g++ installiert und im PATH ist):

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o StudyTrack.exe
.\StudyTrack.exe
```

Linux/macOS (mit geeignetem Compiler):

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o studytrack
./studytrack
```

## Beispiel

1. Menuepunkt 1: Fach `C++` hinzufuegen.
2. Menuepunkt 3: Fachnummer `1`, Dauer `45`, Datum `2026-09-25` eingeben.
3. Menuepunkt 5 zeigt `C++: 45 min` und `Gesamt: 45 min (0 h 45 min)`.
4. Mit 0 beenden. Beim naechsten Start im selben Ordner bleiben die Daten erhalten.

## Dateien

- `main.cpp`: vollstaendiger Quellcode mit deutschen Kommentaren
- `README.md`: Projektbeschreibung und Startanleitung
- `.gitignore`: schliesst erzeugte Programme und persoenliche Lerndaten aus Git aus

Die Datendatei entsteht im aktuellen Arbeitsordner. Das Programm immer aus
demselben Ordner starten. Nur eine Instanz gleichzeitig verwenden.
Bei einer unlesbaren oder beschaedigten Datendatei stoppt das Programm mit einer
Fehlermeldung. Es ist ein einfaches Lernprojekt, keine Datenbank mit
Ausfallsicherheit. Bestehende Eintraege lassen sich noch nicht bearbeiten oder loeschen.

## Lerninhalte

Variablen, string, vector, Schleifen, Bedingungen, Funktionen, struct,
Dateien, Referenzen, Eingabepruefung und Fehlerbehandlung.

## Naechste eigene Erweiterungen

- Eintraege nach Datum filtern
- Eintraege bearbeiten oder loeschen
- Wochenziele anzeigen

## Auf GitHub hochladen

1. Auf https://github.com/new ein Repository `studytrack-cpp` erstellen.
2. Sichtbarkeit waehlen: Public fuer ein sichtbares Portfolio.
3. README initialisieren, damit die Dateiansicht direkt verfuegbar ist.
4. `Add file` > `Upload files` auswaehlen.
5. Die drei Projektdateien hochladen; das vorhandene README wird ersetzt.
6. Commit-Nachricht: `Add StudyTrack learning project`.
7. Upload mit `Commit changes` bestaetigen (bei vorgeschriebenen Branch-Regeln
   stattdessen ueber einen neuen Branch und Pull Request).

Das ZIP vorher entpacken. Nicht die ZIP-Datei, Programme oder persoenliche
`studytrack.txt` hochladen. Beim Browser-Upload verhindert `.gitignore` den
Upload persoenlicher Dateien nicht automatisch: die drei Dateien gezielt auswaehlen.

GitHub-Anleitung: https://docs.github.com/en/repositories/working-with-files/managing-files/adding-a-file-to-a-repository
