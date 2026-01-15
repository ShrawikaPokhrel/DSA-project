#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class music {
public:
    string name;
    music* prev;
    music* next;

    music(string musicName) {
        name = musicName;
        prev = NULL;
        next = NULL;
    }
};

class Playlist {
private:
    music* head;
    music*tail;
    music* current;

public:
    Playlist() {
        head = NULL;
        current = NULL;
    }

    void addmusic(string name,bool preloading=false) {
        music* newmusic = new music(name);

        if (head == NULL) {
            head = newmusic;
            current = newmusic;
        } else {
            music* temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newmusic;
            newmusic->prev = temp;
        }
     if (preloading)
        cout << "Preloaded music stored: " << endl;
    else
        cout << "New music added!\n";
}


    void playNext() {
        if (current && current->next) {
            current = current->next;
            cout << "▶ Now Playing: " << current->name << endl;
        } else {
            cout << " Music Unavailable.\n";
        }
    }

    void playPrevious() {
        if (current && current->prev) {
            current = current->prev;
            cout << "◀ Now Playing: " << current->name << endl;
        } else {
            cout << " Music Unavailable.\n";
        }
    }

    void shufflePlaylist() {
        if (head == NULL || head->next == NULL) {
            cout << "Unable to shuffle \n";
            return;
        }

        vector<string> songs;      
        music* temp = head;

        while (temp != NULL) {
            songs.push_back(temp->name);
            temp = temp->next;
        }

        srand(time(0));
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
        cout << "🔀 Playlist shuffled successfully!\n";
    }

    void displayPlaylist() {
        if (head == NULL) {
            cout << "📭 Playlist is empty.\n";
            return;
        }

        music* temp = head;
        cout << "\n Your Playlist:\n";
        cout << "---------------------------------\n";

        while (temp != NULL) {
            if (temp == current)
                cout << "->" << temp->name << " (Current)\n";
            else
                cout << "   " << temp->name << endl;

            temp = temp->next;
        }
        cout << "---------------------------------\n";
    }

    void showCurrent() {
        if (current)
            cout << " Currently Playing: " << current->name << endl;
        else
            cout << "Playlist is empty.\n";
    }

    void deletemusic(string name) {
        music* temp = head;

        while (temp && temp->name != name)
            temp = temp->next;

        if (!temp) {
            cout << " Music not found.\n";
            return;
        }

        if (temp == head)
            head = temp->next;

        if (temp->prev)
            temp->prev->next = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;

        if (current == temp)
            current = temp->next ? temp->next : temp->prev;

        delete temp;
        cout << " Music deleted successfully.\n";
    }
};

void printMenu() {
    cout << "\n.-.-.-.-.-.-.-.-.-\n";
cout << " TuneIn\n";
cout << ".-.-.-.-.-.-.-.-.-\n";
cout << "Music Playlist Manager\n";
cout << "1. Add Music [+]\n";
cout << "2. Play Next [>]\n";
cout << "3. Play Previous [<]\n";
cout << "4. Display Playlist\n";
cout << "5. Show Currently Playing\n";
cout << "6. Delete Music [X]\n";
cout << "7. Shuffle Playlist [~]\n";
cout << "8. Exit\n";

}

int main() {
    Playlist p;

    int choice;
    string musicName;

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                 cout << "Enter music name (Title by Artist): ";
    getline(cin, musicName);

    if (musicName.empty()) {
        cout << "[ERROR] Music name cannot be empty.\n";
        break;
    }

    if (musicName.find(" by ") == string::npos) {
        cout << "[ERROR] Please enter what you want to listen and artist name \n";
        break;
    }

    p.addmusic(musicName);
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
                p.deletemusic(musicName);
                break;

            case 7:
                p.shufflePlaylist();
                break;

            case 8:
                cout << " Exiting Music Player...\n";
                break;

            default:
                cout << " Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}