#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Detect platform and define emoji support
#ifdef _WIN32
    #include <windows.h>
    #define USE_EMOJIS true
#else
    #define USE_EMOJIS true  // Unix systems usually support UTF-8
#endif

using namespace std;

// Emoji or ASCII based on platform
#if USE_EMOJIS
    #define ICON_ADD "✅"
    #define ICON_DELETE "🗑️"
    #define ICON_WARN "⚠️"
    #define ICON_PLAY "▶️"
    #define ICON_PREV "◀️"
    #define ICON_SHUFFLE "🔀"
    #define ICON_MUSIC "🎶"
    #define ICON_EMPTY "📭"
    #define ICON_ERROR "❌"
    #define ICON_INFO "✨"
    #define ICON_CURRENT "▶️ "
#else
    #define ICON_ADD "[+]"
    #define ICON_DELETE "[-]"
    #define ICON_WARN "[!]"
    #define ICON_PLAY "[>]"
    #define ICON_PREV "[<]"
    #define ICON_SHUFFLE "[~]"
    #define ICON_MUSIC "[*]"
    #define ICON_EMPTY "[ ]"
    #define ICON_ERROR "[X]"
    #define ICON_INFO "[*]"
    #define ICON_CURRENT ">> "
#endif

class Music {
public:
    string name;
    Music* prev;
    Music* next;

    Music(string musicName) {
        name = musicName;
        prev = NULL;
        next = NULL;
    }
};

class Playlist {
private:
    Music* head;
    Music* tail;
    Music* current;
    int songCount;

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        current = NULL;
        songCount = 0;
    }

    ~Playlist() {
        Music* temp = head;
        while (temp != NULL) {
            Music* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    void addMusic(string name) {
        if (name.empty()) {
            cout << ICON_ERROR << " Song name cannot be empty!\n";
            return;
        }

        Music* newMusic = new Music(name);

        if (head == NULL) {
            head = newMusic;
            tail = newMusic;
            current = newMusic;
        } else {
            tail->next = newMusic;
            newMusic->prev = tail;
            tail = newMusic;
        }
        
        songCount++;
        cout << ICON_ADD << " New music added! (Total: " << songCount << " songs)\n";
    }

    void playNext() {
        if (current == NULL) {
            cout << ICON_WARN << " Playlist is empty.\n";
            return;
        }

        if (current->next != NULL) {
            current = current->next;
            cout << ICON_PLAY << " Now Playing: " << current->name << endl;
        } else {
            cout << ICON_WARN << " End of playlist reached.\n";
        }
    }

    void playPrevious() {
        if (current == NULL) {
            cout << ICON_WARN << " Playlist is empty.\n";
            return;
        }

        if (current->prev != NULL) {
            current = current->prev;
            cout << ICON_PREV << " Now Playing: " << current->name << endl;
        } else {
            cout << ICON_WARN << " Start of playlist reached.\n";
        }
    }

    void shufflePlaylist() {
        if (head == NULL || head->next == NULL) {
            cout << ICON_WARN << " Need at least 2 songs to shuffle.\n";
            return;
        }

        vector<string> songs;      
        Music* temp = head;

        while (temp != NULL) {
            songs.push_back(temp->name);
            temp = temp->next;
        }

        // Fisher-Yates shuffle algorithm
        for (int i = songs.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(songs[i], songs[j]);
        }

        temp = head;
        int index = 0;
        while (temp != NULL) {
            temp->name = songs[index++];
            temp = temp->next;
        }

        current = head;
        cout << ICON_SHUFFLE << " Playlist shuffled successfully!\n";
    }

    void displayPlaylist() {
        if (head == NULL) {
            cout << ICON_EMPTY << " Playlist is empty.\n";
            return;
        }

        Music* temp = head;
        int index = 1;
        
        cout << "\n========================================\n";
        cout << "      YOUR PLAYLIST (" << songCount << " songs)\n";
        cout << "========================================\n";

        while (temp != NULL) {
            cout << index++ << ". ";
            if (temp == current)
                cout << ICON_CURRENT << temp->name << " (Current)\n";
            else
                cout << "   " << temp->name << endl;

            temp = temp->next;
        }
        cout << "========================================\n";
    }

    void showCurrent() {
        if (current == NULL) {
            cout << ICON_EMPTY << " Playlist is empty.\n";
        } else {
            cout << ICON_MUSIC << " Currently Playing: " << current->name << endl;
        }
    }

    void deleteMusic(string name) {
        if (head == NULL) {
            cout << ICON_ERROR << " Playlist is empty.\n";
            return;
        }

        Music* temp = head;

        while (temp != NULL && temp->name != name) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << ICON_ERROR << " Music not found.\n";
            return;
        }

        // Only one song in playlist
        if (head == tail) {
            delete temp;
            head = NULL;
            tail = NULL;
            current = NULL;
        }
        // Deleting head
        else if (temp == head) {
            head = temp->next;
            head->prev = NULL;
            
            if (current == temp) {
                current = head;
            }
            delete temp;
        }
        // Deleting tail
        else if (temp == tail) {
            tail = temp->prev;
            tail->next = NULL;
            
            if (current == temp) {
                current = tail;
            }
            delete temp;
        }
        // Deleting middle node
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            
            if (current == temp) {
                current = temp->next;
            }
            delete temp;
        }

        songCount--;
        cout << ICON_DELETE << " Music deleted successfully. (" << songCount << " songs remaining)\n";
    }

    void preloadMusic() {
        addMusic("About You by The 1975");
        addMusic("Bags by Clairo");
        addMusic("White Ferrari by Frank Ocean");
        cout << "\n" << ICON_INFO << " 3 songs preloaded into your playlist!\n";
    }
};

void printMenu() {
    cout << "\n======================================\n";
    cout << "      MUSIC PLAYLIST MANAGER\n";
    cout << "======================================\n";
    cout << " 1. Add Music            [+]\n";
    cout << " 2. Play Next            [>]\n";
    cout << " 3. Play Previous        [<]\n";
    cout << " 4. Display Playlist     [ ]\n";
    cout << " 5. Show Currently Playing\n";
    cout << " 6. Delete Music         [X]\n";
    cout << " 7. Shuffle Playlist     [~]\n";
    cout << " 8. Exit\n";
    cout << "======================================\n";
    cout << "Enter choice: ";
}

int main() {
    // Enable UTF-8 support on Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    
    srand(time(0));
    
    Playlist p;
    p.preloadMusic();

    int choice;
    string musicName;

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter music name: ";
                getline(cin, musicName);
                p.addMusic(musicName);
                break;

            case 2:
                p.playNext();
                break;

            case 3:
                p.playPrevious();
                break;

            case 4:
                p.displayPlaylist();
                break;

            case 5:
                p.showCurrent();
                break;

            case 6:
                cout << "Enter music to delete: ";
                getline(cin, musicName);
                p.deleteMusic(musicName);
                break;

            case 7:
                p.shufflePlaylist();
                break;

            case 8:
                cout << "\n" << ICON_INFO << " Exiting Music Player...\n";
                cout << "    Thanks for using our playlist manager!\n\n";
                break;

            default:
                cout << ICON_ERROR << " Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}