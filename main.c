#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct Song {
    char title[100];
    struct Song *next;
};

// Function prototypes
struct Song* add_song(struct Song *head, char *title);
void view_playlist(struct Song *head, WINDOW *win);
struct Song* delete_song(struct Song *head, char *title);

int main()
{
    // ncurses setup
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    struct Song *playlist = NULL;
    int choice = 0;
    int highlight = 0;
    char *options[] = {"1. Add Song", "2. View Playlist", "3. Delete Song", "4. Exit"};
    
    while (1)
    {
        box(stdscr, 0, 0);
        mvprintw(1, 2, "PLAYLIST MANAGER");
        
        for (int i = 0; i < 4; i++)
        {
            if (i == highlight)
            {
                attron(A_REVERSE);
                mvprintw(3 + i, 2, "%s", options[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(3 + i, 2, "%s", options[i]);
            }
        }
        
        refresh();
        choice = getch();
        
        if (choice == KEY_UP)
        {
            highlight--;
            if (highlight < 0) highlight = 0;
        }
        else if (choice == KEY_DOWN)
        {
            highlight++;
            if (highlight > 3) highlight = 3;
        }
        else if (choice == '\n' || choice == '\r')
        {
            clear();
            
            if (highlight == 0)
            {
                // Add song
                echo();
                curs_set(1);
                char title[100];
                mvprintw(2, 2, "Enter song title: ");
                getstr(title);
                playlist = add_song(playlist, title);
                noecho();
                curs_set(0);
            }
            else if (highlight == 1)
            {
                // View playlist
                box(stdscr, 0, 0);
                mvprintw(1, 2, "YOUR PLAYLIST");
                
                struct Song *current = playlist;
                int row = 3;
                int i = 1;
                
                if (current == NULL) {
                    mvprintw(row, 2, "Playlist is empty!");
                }
                
                while (current != NULL) {
                    mvprintw(row, 2, "%d. %s", i, current->title);
                    current = current->next;
                    row++;
                    i++;
                }
                
                mvprintw(row + 2, 2, "Press any key to return...");
                refresh();
                getch();
            }
            else if (highlight == 2)
            {
                // Delete song
                echo();
                curs_set(1);
                char title[100];
                mvprintw(2, 2, "Enter song to delete: ");
                getstr(title);
                playlist = delete_song(playlist, title);
                noecho();
                curs_set(0);
            }
            else if (highlight == 3)
            {
                break;
            }
            
            clear();
        }
    }
    
    endwin();
    
    // Free memory
    while (playlist != NULL) {
        struct Song *temp = playlist;
        playlist = playlist->next;
        free(temp);
    }
    
    printf("Goodbye!\n");
    return 0;
}

struct Song* add_song(struct Song *head, char *title)
{
    struct Song *new_song = malloc(sizeof(struct Song));
    strcpy(new_song->title, title);
    new_song->next = NULL;
    
    if (head == NULL) {
        return new_song;
    }
    
    struct Song *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_song;
    
    return head;
}

struct Song* delete_song(struct Song *head, char *title)
{
    if (head == NULL) {
        return NULL;
    }
    
    if (strcmp(head->title, title) == 0) {
        struct Song *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    struct Song *current = head;
    while (current->next != NULL && strcmp(current->next->title, title) != 0) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        struct Song *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    
    return head;
}
