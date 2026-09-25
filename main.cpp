#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// Ein Lerneintrag verbindet Fach, Datum und Dauer.
struct Session {
    string subject;
    string date;
    int minutes;
};

string readText(const string& prompt) {
    while (true) {
        cout << prompt;
        string text;
        if (!getline(cin, text)) throw runtime_error("Eingabe beendet.");
        const auto first = text.find_first_not_of(" \t\r");
        if (first != string::npos) {
            return text.substr(first, text.find_last_not_of(" \t\r") - first + 1);
        }
        cout << "Bitte etwas eingeben.\n";
    }
}

int readNumber(const string& prompt, int minimum, int maximum) {
    while (true) {
        istringstream input(readText(prompt));
        int value;
        char extra;
        if ((input >> value) && !(input >> extra) && value >= minimum && value <= maximum)
            return value;
        cout << "Bitte eine ganze Zahl von " << minimum << " bis " << maximum << " eingeben.\n";
    }
}

bool validDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i]))) return false;
    }
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (year < 1900 || month < 1 || month > 12) return false;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) days[1] = 29;
    return day >= 1 && day <= days[month - 1];
}

// Alle Daten liegen in einer Textdatei im aktuellen Arbeitsordner.
void loadData(vector<string>& subjects, vector<Session>& sessions) {
    if (!filesystem::exists("studytrack.txt")) return;
    ifstream file("studytrack.txt");
    if (!file) throw runtime_error("Datendatei kann nicht gelesen werden.");
    string line;
    while (getline(file, line)) {
        istringstream row(line);
        char type, extra;
        if (!(row >> type)) continue;
        if (type == 'F') {
            string subject;
            if (!(row >> quoted(subject)) || subject.empty() || (row >> extra))
                throw runtime_error("Ungueltiges Fach in der Datendatei.");
            if (find(subjects.begin(), subjects.end(), subject) == subjects.end())
                subjects.push_back(subject);
        } else if (type == 'S') {
            Session entry;
            if (!(row >> quoted(entry.subject) >> quoted(entry.date) >> entry.minutes)
                || (row >> extra) || !validDate(entry.date) || entry.minutes < 1
                || entry.minutes > 1440
                || find(subjects.begin(), subjects.end(), entry.subject) == subjects.end())
                throw runtime_error("Ungueltiger Lerneintrag in der Datendatei.");
            sessions.push_back(entry);
        } else {
            throw runtime_error("Unbekannter Datensatz in der Datendatei.");
        }
    }
    if (file.bad()) throw runtime_error("Fehler beim Lesen der Datendatei.");
}

// Erst nach erfolgreichem Schreiben wird der Arbeitsspeicher aktualisiert.
void appendRecord(const string& record) {
    ofstream file("studytrack.txt", ios::app);
    if (!file) throw runtime_error("Datendatei kann nicht geoeffnet werden.");
    file << record << '\n';
    file.close();
    if (!file) throw runtime_error("Speichern fehlgeschlagen.");
}

void showSubjects(const vector<string>& subjects) {
    for (size_t i = 0; i < subjects.size(); ++i)
        cout << i + 1 << ". " << subjects[i] << '\n';
}

void addSubject(vector<string>& subjects) {
    string name = readText("Name des Fachs: ");
    if (find(subjects.begin(), subjects.end(), name) != subjects.end()) {
        cout << "Dieses Fach ist bereits vorhanden.\n";
        return;
    }
    ostringstream row;
    row << "F " << quoted(name);
    appendRecord(row.str());
    subjects.push_back(name);
    cout << "Fach gespeichert.\n";
}

void addSession(const vector<string>& subjects, vector<Session>& sessions) {
    if (subjects.empty()) {
        cout << "Bitte zuerst ein Fach hinzufuegen.\n";
        return;
    }
    showSubjects(subjects);
    int choice = readNumber("Fachnummer: ", 1, static_cast<int>(subjects.size()));
    Session entry;
    entry.subject = subjects[choice - 1];
    entry.minutes = readNumber("Lernzeit in Minuten: ", 1, 1440);
    do {
        entry.date = readText("Datum (YYYY-MM-DD): ");
        if (!validDate(entry.date)) cout << "Bitte ein gueltiges Datum eingeben.\n";
    } while (!validDate(entry.date));
    ostringstream row;
    row << "S " << quoted(entry.subject) << ' ' << quoted(entry.date) << ' ' << entry.minutes;
    appendRecord(row.str());
    sessions.push_back(entry);
    cout << "Lerneintrag gespeichert.\n";
}

void showSessions(const vector<Session>& sessions) {
    if (sessions.empty()) cout << "Noch keine Lerneintraege.\n";
    for (const Session& entry : sessions)
        cout << entry.date << " | " << entry.subject << " | " << entry.minutes << " min\n";
}

void showSummary(const vector<string>& subjects, const vector<Session>& sessions) {
    long long total = 0;
    for (const string& subject : subjects) {
        long long minutes = 0;
        for (const Session& entry : sessions)
            if (entry.subject == subject) minutes += entry.minutes;
        cout << subject << ": " << minutes << " min\n";
        total += minutes;
    }
    cout << "Gesamt: " << total << " min (" << total / 60 << " h " << total % 60 << " min)\n";
}

int main() {
    vector<string> subjects;
    vector<Session> sessions;
    try {
        loadData(subjects, sessions);
        while (true) {
            cout << "\n--- StudyTrack ---\n"
                 << "1. Fach hinzufuegen\n2. Faecher anzeigen\n"
                 << "3. Lernzeit eintragen\n4. Lerneintraege anzeigen\n"
                 << "5. Zusammenfassung\n0. Beenden\n";
            int choice = readNumber("Auswahl: ", 0, 5);
            if (choice == 0) break;
            switch (choice) {
                case 1: addSubject(subjects); break;
                case 2:
                    if (subjects.empty()) cout << "Noch keine Faecher.\n";
                    showSubjects(subjects);
                    break;
                case 3: addSession(subjects, sessions); break;
                case 4: showSessions(sessions); break;
                case 5: showSummary(subjects, sessions); break;
            }
        }
    } catch (const exception& error) {
        cerr << "\n" << error.what() << '\n';
        return 1;
    }
    return 0;
}
