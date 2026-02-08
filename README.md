# MUSIC PLAYLIST MANAGER
## Data Structures and Algorithms Mini Project

---

## 1. PROJECT INFORMATION

**Project Title:** Music Playlist Manager

**Group Members:**
- Member 1: Shrawika Pokhrel
- Member 2: Sameer Rajbanshi
- Member 3: Bhavik Shrestha

**Date:** January 2026

**Programming Language:** C++

---

## 2. PROBLEM DESCRIPTION & OBJECTIVE

### Problem Statement
In today's digital age, music streaming and playlist management are essential features of any music application. Users need an efficient way to organize, navigate, and manage their music collections. The challenge is to implement a system that allows users to:

- Add and remove songs dynamically
- Navigate through songs sequentially (forward and backward)
- Shuffle the playlist randomly
- Track the currently playing song
- Display the entire playlist with visual indicators

### Objective
To design and implement a **Music Playlist Manager** using fundamental data structures and algorithms that demonstrates:

1. Dynamic memory management
2. Efficient insertion and deletion operations
3. Bidirectional traversal
4. Random shuffling algorithm
5. Real-world application of DSA concepts

### Real-World Application
This project simulates core functionality found in popular music applications like Spotify, Apple Music, and YouTube Music, where users manage personal playlists.

---

## 3. CHOSEN DATA STRUCTURE(S)

### Primary Data Structure: Doubly Linked List

**Reason for Selection:**

A **Doubly Linked List** is the ideal choice for a music playlist because:

1. **Bidirectional Navigation**: Users can move forward (next song) or backward (previous song), which requires traversal in both directions. A doubly linked list provides `next` and `prev` pointers for this purpose.

2. **Dynamic Size**: The playlist size changes as users add or remove songs. Linked lists handle dynamic memory allocation efficiently without requiring fixed size like arrays.

3. **Efficient Insertion/Deletion**: 
   - With a tail pointer: O(1) insertion at the end
   - O(n) deletion (due to search), but O(1) once node is found
   - No shifting required like in arrays

4. **Current Song Tracking**: The `current` pointer allows us to track which song is playing without additional overhead.

5. **Memory Efficiency**: Only allocates memory for songs that exist, unlike arrays which may waste space.

### Structure Design

```
┌─────────┐      ┌─────────┐      ┌─────────┐
│  Song 1 │ <──> │  Song 2 │ <──> │  Song 3 │
└─────────┘      └─────────┘      └─────────┘
     ▲
     │
  current
```

Each node contains:
- `string name`: Song name
- `Music* prev`: Pointer to previous song
- `Music* next`: Pointer to next song

The Playlist class maintains:
- `Music* head`: First song in playlist
- `Music* tail`: Last song in playlist (for O(1) insertion)
- `Music* current`: Currently playing song
- `int songCount`: Total number of songs

---

## 4. ALGORITHM / WORKING EXPLANATION

### 4.1 Add Music (Insertion at End)

**Algorithm:**
```
1. Create new Music node with given name
2. IF playlist is empty:
     - Set head = new node
     - Set tail = new node
     - Set current = new node
3. ELSE:
     - Link tail->next to new node
     - Link new node->prev to tail
     - Update tail to new node
4. Increment songCount
5. Display success message
```

**Time Complexity:** O(1) - Constant time with tail pointer

**Visualization:**
```
Before: [Song1] <-> [Song2] <-> [Song3]
                                   ↑
                                  tail

After:  [Song1] <-> [Song2] <-> [Song3] <-> [Song4]
                                               ↑
                                              tail
```

---

### 4.2 Play Next (Forward Traversal)

**Algorithm:**
```
1. IF current is NULL:
     - Display "Playlist is empty"
     - Return
2. IF current->next exists:
     - Move current to current->next
     - Display now playing song
3. ELSE:
     - Display "End of playlist reached"
```

**Time Complexity:** O(1) - Direct pointer access

---

### 4.3 Play Previous (Backward Traversal)

**Algorithm:**
```
1. IF current is NULL:
     - Display "Playlist is empty"
     - Return
2. IF current->prev exists:
     - Move current to current->prev
     - Display now playing song
3. ELSE:
     - Display "Start of playlist reached"
```

**Time Complexity:** O(1) - Direct pointer access

---

### 4.4 Shuffle Playlist (Fisher-Yates Algorithm)

**Algorithm:**
```
1. IF playlist has less than 2 songs:
     - Display error and return
2. Create vector to store all song names
3. Traverse linked list and copy all names to vector
4. Apply Fisher-Yates Shuffle:
     FOR i = n-1 down to 1:
         j = random number between 0 and i
         Swap vector[i] with vector[j]
5. Traverse linked list again and assign shuffled names
6. Reset current to head
```

**Time Complexity:** O(n) - Linear traversal + linear shuffle

**Fisher-Yates Shuffle Explanation:**
This algorithm ensures each permutation is equally likely. It works by:
- Starting from the last element
- Swapping it with a random element (including itself)
- Moving to the previous element and repeating

**Example:**
```
Original: [A, B, C, D]

Step 1: Swap D with random(A,B,C,D) → [A, B, D, C]
Step 2: Swap D with random(A,B,D)   → [A, D, B, C]
Step 3: Swap D with random(A,D)     → [D, A, B, C]
Result: [D, A, B, C] (one possible shuffle)
```

---

### 4.5 Delete Music (Node Deletion)

**Algorithm:**
```
1. IF playlist is empty:
     - Display error and return
2. Search for song by name (linear search)
3. IF song not found:
     - Display "Music not found"
     - Return
4. Handle deletion cases:
   
   CASE 1: Only one song (head == tail)
     - Delete node
     - Set head, tail, current to NULL
   
   CASE 2: Deleting head
     - Move head to next node
     - Set new head->prev to NULL
     - Update current if it was the deleted node
     - Delete old head
   
   CASE 3: Deleting tail
     - Move tail to previous node
     - Set new tail->next to NULL
     - Update current if it was the deleted node
     - Delete old tail
   
   CASE 4: Deleting middle node
     - Link prev->next to next node
     - Link next->prev to prev node
     - Update current if it was the deleted node
     - Delete node

5. Decrement songCount
6. Display success message
```

**Time Complexity:** O(n) - Due to linear search for the song

**Visualization of Middle Node Deletion:**
```
Before: [A] <-> [B] <-> [C] <-> [D]
                 ↑
             (delete B)

Step 1: A->next = C
Step 2: C->prev = A
Step 3: delete B

After:  [A] <-> [C] <-> [D]
```

---

### 4.6 Display Playlist (List Traversal)

**Algorithm:**
```
1. IF playlist is empty:
     - Display "Playlist is empty"
     - Return
2. Start from head
3. WHILE node is not NULL:
     - Display song number
     - IF node is current:
          Display with ">> " indicator and "(Current)"
     - ELSE:
          Display normally
     - Move to next node
4. Display separator line
```

**Time Complexity:** O(n) - Must visit each node once

---

## 5. SOURCE CODE

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

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
            cout << "[X] Song name cannot be empty!\n";
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
        cout << "[+] New music added! (Total: " << songCount << " songs)\n";
    }

    void playNext() {
        if (current == NULL) {
            cout << "[!] Playlist is empty.\n";
            return;
        }

        if (current->next != NULL) {
            current = current->next;
            cout << "[>] Now Playing: " << current->name << endl;
        } else {
            cout << "[!] End of playlist reached.\n";
        }
    }

    void playPrevious() {
        if (current == NULL) {
            cout << "[!] Playlist is empty.\n";
            return;
        }

        if (current->prev != NULL) {
            current = current->prev;
            cout << "[<] Now Playing: " << current->name << endl;
        } else {
            cout << "[!] Start of playlist reached.\n";
        }
    }

    void shufflePlaylist() {
        if (head == NULL || head->next == NULL) {
            cout << "[!] Need at least 2 songs to shuffle.\n";
            return;
        }

        vector<string> songs;      
        Music* temp = head;

        while (temp != NULL) {
            songs.push_back(temp->name);
            temp = temp->next;
        }

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
        cout << "[~] Playlist shuffled successfully!\n";
    }

    void displayPlaylist() {
        if (head == NULL) {
            cout << "[ ] Playlist is empty.\n";
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
                cout << ">> " << temp->name << " (Current)\n";
            else
                cout << "   " << temp->name << endl;

            temp = temp->next;
        }
        cout << "========================================\n";
    }

    void showCurrent() {
        if (current == NULL) {
            cout << "[ ] Playlist is empty.\n";
        } else {
            cout << "[*] Currently Playing: " << current->name << endl;
        }
    }

    void deleteMusic(string name) {
        if (head == NULL) {
            cout << "[X] Playlist is empty.\n";
            return;
        }

        Music* temp = head;

        while (temp != NULL && temp->name != name) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "[X] Music not found.\n";
            return;
        }

        if (head == tail) {
            delete temp;
            head = NULL;
            tail = NULL;
            current = NULL;
        }
        else if (temp == head) {
            head = temp->next;
            head->prev = NULL;
            if (current == temp) {
                current = head;
            }
            delete temp;
        }
        else if (temp == tail) {
            tail = temp->prev;
            tail->next = NULL;
            if (current == temp) {
                current = tail;
            }
            delete temp;
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (current == temp) {
                current = temp->next;
            }
            delete temp;
        }

        songCount--;
        cout << "[-] Music deleted successfully. (" << songCount << " songs remaining)\n";
    }

    void preloadMusic() {
        addMusic("About You by The 1975");
        addMusic("Bags by Clairo");
        addMusic("White Ferrari by Frank Ocean");
        cout << "\n[*] 3 songs preloaded into your playlist!\n";
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
                cout << "\n[!] Exiting Music Player...\n";
                cout << "    Thanks for using our playlist manager!\n\n";
                break;

            default:
                cout << "[X] Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
```

---

## 6. SAMPLE INPUT & OUTPUT

### Test Case 1: Adding Songs

**Input:**
```
Choice: 1
Enter music name: Blinding Lights by The Weeknd
```

**Output:**
```
[+] New music added! (Total: 4 songs)
```

---

### Test Case 2: Display Playlist

**Input:**
```
Choice: 4
```

**Output:**
```
========================================
      YOUR PLAYLIST (4 songs)
========================================
1. >> About You by The 1975 (Current)
2.    Bags by Clairo
3.    White Ferrari by Frank Ocean
4.    Blinding Lights by The Weeknd
========================================
```

---

### Test Case 3: Navigation (Play Next)

**Input:**
```
Choice: 2
Choice: 2
Choice: 5
```

**Output:**
```
[>] Now Playing: Bags by Clairo
[>] Now Playing: White Ferrari by Frank Ocean
[*] Currently Playing: White Ferrari by Frank Ocean
```

---

### Test Case 4: Play Previous

**Input:**
```
Choice: 3
```

**Output:**
```
[<] Now Playing: Bags by Clairo
```

---

### Test Case 5: Shuffle Playlist

**Input:**
```
Choice: 7
Choice: 4
```

**Output:**
```
[~] Playlist shuffled successfully!

========================================
      YOUR PLAYLIST (4 songs)
========================================
1. >> White Ferrari by Frank Ocean (Current)
2.    Blinding Lights by The Weeknd
3.    About You by The 1975
4.    Bags by Clairo
========================================
```

---

### Test Case 6: Delete Song

**Input:**
```
Choice: 6
Enter music to delete: Bags by Clairo
Choice: 4
```

**Output:**
```
[-] Music deleted successfully. (3 songs remaining)

========================================
      YOUR PLAYLIST (3 songs)
========================================
1. >> White Ferrari by Frank Ocean (Current)
2.    Blinding Lights by The Weeknd
3.    About You by The 1975
========================================
```

---

### Test Case 7: Edge Case - Delete Only Song

**Input:**
```
(Assume playlist has only 1 song)
Choice: 6
Enter music to delete: Last Song
Choice: 4
```

**Output:**
```
[-] Music deleted successfully. (0 songs remaining)
[ ] Playlist is empty.
```

---

### Test Case 8: Edge Case - End of Playlist

**Input:**
```
(Current is at last song)
Choice: 2
```

**Output:**
```
[!] End of playlist reached.
```

---

## 7. TIME COMPLEXITY ANALYSIS

| Operation | Time Complexity | Space Complexity | Explanation |
|-----------|----------------|------------------|-------------|
| **Add Music** | O(1) | O(1) | Direct insertion at tail using tail pointer |
| **Play Next** | O(1) | O(1) | Direct pointer traversal to next node |
| **Play Previous** | O(1) | O(1) | Direct pointer traversal to previous node |
| **Display Playlist** | O(n) | O(1) | Must traverse all n nodes to display |
| **Delete Music** | O(n) | O(1) | Linear search to find song, then O(1) deletion |
| **Shuffle** | O(n) | O(n) | O(n) to copy to vector, O(n) to shuffle, O(n) to reassign |
| **Show Current** | O(1) | O(1) | Direct access to current pointer |

### Overall Complexity Summary

**Best Case Scenarios:**
- Adding songs: O(1)
- Navigation: O(1)
- Deletion when current is known: O(1)

**Worst Case Scenarios:**
- Searching for a song: O(n)
- Displaying entire playlist: O(n)
- Shuffling: O(n)

**Space Complexity:**
- Playlist storage: O(n) where n = number of songs
- Shuffle operation: O(n) temporary space for vector
- All other operations: O(1) auxiliary space

---

## 8. FEATURES IMPLEMENTED

### Core Features
✓ Add new songs to playlist  
✓ Delete songs from playlist  
✓ Play next song (forward navigation)  
✓ Play previous song (backward navigation)  
✓ Display entire playlist with current song indicator  
✓ Show currently playing song  
✓ Shuffle playlist using Fisher-Yates algorithm  

### Additional Features
✓ Song counter to track playlist size  
✓ Input validation (empty song names)  
✓ Edge case handling (empty playlist, single song, etc.)  
✓ Memory management with destructor  
✓ Preloaded playlist with sample songs  
✓ User-friendly menu interface  
✓ Clear visual feedback for all operations  

---

## 9. ADVANTAGES & LIMITATIONS

### Advantages

1. **Efficient Bidirectional Navigation**: O(1) time complexity for next/previous operations
2. **Dynamic Memory**: No fixed size limit, grows as needed
3. **Flexible Insertion**: Can easily add songs at any position
4. **Current Song Tracking**: Maintains state without extra overhead
5. **Memory Efficient**: Only allocates memory for actual songs
6. **Real-World Application**: Mirrors actual music player functionality

### Limitations

1. **Linear Search**: Finding a specific song requires O(n) search time
2. **No Random Access**: Cannot jump to song at index i in O(1) time
3. **Shuffle Space Overhead**: Requires O(n) extra space for vector
4. **No Persistence**: Playlist data lost when program exits (no file saving)
5. **Limited Metadata**: Only stores song name, no artist/duration/genre
6. **No Undo Feature**: Cannot revert deletions or shuffles

### Possible Improvements

1. Add hash table for O(1) song lookup by name
2. Implement circular linked list for continuous looping
3. Add file I/O for saving/loading playlists
4. Include song metadata (artist, duration, genre)
5. Implement undo/redo using command pattern with stack
6. Add multiple playlist support
7. Include play history using stack
8. Add queue for "up next" songs

---

## 10. LEARNING OUTCOMES

Through this project, we gained hands-on experience with:

### Technical Skills
- **Doubly Linked List**: Implementation, traversal, insertion, and deletion
- **Pointers**: Understanding and manipulating pointers in C++
- **Dynamic Memory**: Allocation and deallocation with new/delete
- **Algorithm Design**: Fisher-Yates shuffle, linear search
- **Time Complexity**: Analyzing efficiency of operations

### Programming Concepts
- Object-Oriented Programming (classes, encapsulation)
- Memory management and avoiding memory leaks
- Edge case handling and input validation
- User interface design for console applications

### Problem-Solving
- Breaking down real-world problem into algorithmic steps
- Choosing appropriate data structures for requirements
- Debugging pointer-related issues
- Testing various scenarios

---

## 11. CONCLUSION

The Music Playlist Manager successfully demonstrates the practical application of doubly linked lists in a real-world scenario. The project achieves all objectives:

✓ Implements a functional playlist management system  
✓ Demonstrates efficient use of doubly linked list data structure  
✓ Provides bidirectional navigation capability  
✓ Includes random shuffling algorithm  
✓ Handles edge cases and validates input  
✓ Manages memory properly without leaks  

The choice of doubly linked list proved ideal for this application, providing O(1) navigation while maintaining dynamic size flexibility. The implementation successfully balances functionality, efficiency, and code clarity.

This project provided valuable experience in data structure implementation and algorithm design, reinforcing theoretical DSA concepts through practical application.

---

## 12. REFERENCES

1. Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.

2. Malik, D. S. (2017). *Data Structures Using C++* (2nd ed.). Cengage Learning.

3. Fisher-Yates Shuffle Algorithm: https://en.wikipedia.org/wiki/Fisher–Yates_shuffle

4. C++ Documentation: https://cplusplus.com/reference/

5. Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.

---

## APPENDIX A: COMPILATION & EXECUTION

### Compilation
```bash
g++ -std=c++11 playlist.cpp -o playlist
```

### Execution
```bash
./playlist
```

### System Requirements
- C++ compiler (g++, MinGW, MSVC)
- C++11 or higher
- Standard Template Library (STL)

---

**END OF REPORT**
