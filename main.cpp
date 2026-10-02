#include "iostream"
#include "limits"
#include "vector"
#include "string"
#include "cstdlib"

using namespace std;

// Data structure to store track details cleanly
struct Recommendation {
    string playlist;
    string track;
    string reason;
};

// Global vectors to manage session state
vector<Recommendation> sessionHistory;
vector<Recommendation> favorites;

// Clear screen helper function across platforms
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Visual line separator
void printLine(char symbol = '=', int width = 54) {
    for (int i = 0; i < width; i++) {
        cout << symbol;
    }
    cout << "\n";
}

// Centered banner output
void printCenteredHeader(const string& text, int width = 54) {
    printLine('=', width);
    int padding = (width - text.length()) / 2;
    if (padding > 0) cout << string(padding, ' ');
    cout << text << "\n";
    printLine('=', width);
}

// Robust input handler with option to Quit (0)
int getValidIntInput(int minVal, int maxVal, bool allowQuit = true) {
    int input;
    while (true) {
        cout << "  [?] Enter choice: ";
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  [!] Invalid entry! Please enter a number.\n";
        }
        else if (allowQuit && input == 0) {
            cin.ignore(10000, '\n');
            return 0; // Signal quit command
        }
        else if (input < minVal || input > maxVal) {
            cin.ignore(10000, '\n');
            cout << "  [!] Choice out of range (" << minVal << "-" << maxVal << ")! Try again.\n";
        }
        else {
            cin.ignore(10000, '\n');
            return input;
        }
    }
}

// Display format for a recommendation card
void printRecommendationCard(const Recommendation& rec) {
    printLine('*', 54);
    cout << "             >>> SPOTIFY MATCH FOUND <<<             \n";
    printLine('*', 54);
    cout << "  PLAYLIST : " << rec.playlist << "\n";
    cout << "  TRACK    : " << rec.track << "\n";
    printLine('-', 54);
    cout << "  CONTEXT  : " << rec.reason << "\n";
    printLine('*', 54);
}

// Generate recommendation based on genre and activity choices
Recommendation getRecommendation(int genre, int activity) {
    switch (genre) {
        case 1: // Pop
            if (activity == 1)
                return {"Pop Focus", "Dua Lipa - 'Levitating (Instrumental)'", "Steady upbeat energy without vocal distraction for studying."};
            else if (activity == 2)
                return {"Cardio Pop Party", "The Weeknd - 'Blinding Lights'", "High 171 BPM synth-pop rhythm built for intense cardio."};
            else
                return {"Acoustic Pop Chill", "Taylor Swift - 'Cardigan'", "Soft acoustic arrangement ideal for winding down."};

        case 2: // Hip-Hop
            if (activity == 1)
                return {"Lofi Hip Hop Beats", "J Dilla - 'Time: The Donut of the Heart'", "Warm instrumental soul loops that spark deep focus."};
            else if (activity == 2)
                return {"Beast Mode Rap", "Kendrick Lamar - 'HUMBLE.'", "Aggressive bassline and heavy tempo to drive workout sets."};
            else
                return {"Smooth Sunset Rap", "Drake - 'Passionfruit'", "Melodic dancehall-inspired rhythm perfect for relaxing."};

        case 3: // Rock
            if (activity == 1)
                return {"Post-Rock Focus", "Explosions in the Sky - 'Your Hand in Mine'", "Dynamic instrumental guitars that foster concentration."};
            else if (activity == 2)
                return {"Ultimate Workout Rock", "Queen - 'Don't Stop Me Now'", "Fast-paced classic rock driving peak physical motivation."};
            else
                return {"Acoustic Rock Lounge", "Eagles - 'Hotel California (Acoustic)'", "Laid-back guitar harmonies suited for rest."};

        case 4: // Lo-fi/Chill
        default:
            if (activity == 1)
                return {"Deep Study Lo-Fi", "Nujabes - 'Feather'", "Atmospheric jazz-hop grooves optimized for mental focus."};
            else if (activity == 2)
                return {"Ambient Mobility Flow", "Tycho - 'A Walk'", "Gentle, steady electronic rhythms for warmups and stretching."};
            else
                return {"Late Night Chillout", "Lofi Girl - 'Coffee Shop Beats'", "Relaxing vinyl crackle soundscapes to help you unwind."};
    }
}

// Display Session History
void viewHistory() {
    clearScreen();
    printCenteredHeader("SESSION HISTORY LOG");
    if (sessionHistory.empty()) {
        cout << "\n  [i] No recommendations generated in this session yet.\n\n";
    } else {
        for (size_t i = 0; i < sessionHistory.size(); i++) {
            cout << "\n [# " << (i + 1) << "]\n";
            printRecommendationCard(sessionHistory[i]);
        }
    }
    cout << "\nPress Enter to return to the main menu...";
    cin.get();
}

// Display Saved Favorites
void viewFavorites() {
    clearScreen();
    printCenteredHeader("SAVED FAVORITES");
    if (favorites.empty()) {
        cout << "\n  [i] Your favorites list is currently empty.\n\n";
    } else {
        for (size_t i = 0; i < favorites.size(); i++) {
            cout << "\n [FAVORITE #" << (i + 1) << "]\n";
            printRecommendationCard(favorites[i]);
        }
    }
    cout << "\nPress Enter to return to the main menu...";
    cin.get();
}

int main() {
    bool running = true;

    while (running) {
        clearScreen();
        printCenteredHeader("MUSIC RECOMMENDATION ASSISTANT");
        cout << "  (1) Get a Music Recommendation\n";
        cout << "  (2) View Saved Favorites (" << favorites.size() << " saved)\n";
        cout << "  (3) View Session History (" << sessionHistory.size() << " generated)\n";
        cout << "  (0) Exit Assistant\n";
        printLine('-', 54);

        int mainChoice = getValidIntInput(1, 3, true);

        if (mainChoice == 0) {
            running = false;
            break;
        }

        if (mainChoice == 2) {
            viewFavorites();
            continue;
        }

        if (mainChoice == 3) {
            viewHistory();
            continue;
        }

        // --- STEP 1: GENRE SELECTION ---
        clearScreen();
        printCenteredHeader("STEP 1: SELECT YOUR GENRE");
        cout << "  [1] Pop\n";
        cout << "  [2] Hip-Hop\n";
        cout << "  [3] Rock\n";
        cout << "  [4] Lo-fi / Chill\n";
        cout << "  [0] Back / Quit\n";
        printLine('-', 54);

        int genre = getValidIntInput(1, 4, true);
        if (genre == 0) continue;

        // --- STEP 2: ACTIVITY SELECTION ---
        clearScreen();
        printCenteredHeader("STEP 2: WHAT ARE YOU DOING RIGHT NOW?");
        cout << "  [1] Studying / Deep Focus\n";
        cout << "  [2] Working Out / High Energy\n";
        cout << "  [3] Relaxing / Unwinding\n";
        cout << "  [0] Back / Quit\n";
        printLine('-', 54);

        int activity = getValidIntInput(1, 3, true);
        if (activity == 0) continue;

        // --- GENERATE AND SHOW MATCH ---
        clearScreen();
        Recommendation currentRec = getRecommendation(genre, activity);

        // Log into session history
        sessionHistory.push_back(currentRec);

        printRecommendationCard(currentRec);

        // --- ACTION OPTIONS FOR THIS RESULT ---
        cout << "\nOptions:\n";
        cout << "  (1) Save track to Favorites\n";
        cout << "  (2) Continue to Main Menu\n";
        printLine('-', 54);

        int actionChoice = getValidIntInput(1, 2, false);
        if (actionChoice == 1) {
            favorites.push_back(currentRec);
            cout << "  [+] Track added to your Favorites!\n";
            cout << "Press Enter to return to main menu...";
            cin.get();
        }
    }

    clearScreen();
    printCenteredHeader("THANK YOU FOR USING THE MUSIC ASSISTANT");
    cout << "  Exited successfully. Have a great session!\n\n";
    return 0;
}
