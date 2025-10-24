#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NUM_PLAY_TYPES 5
int** g_combinations = NULL;
int g_combination_count = 0;
int g_combination_capacity = 0;
const char* SCORING_NAMES[NUM_PLAY_TYPES] = {"TD + 2pt", "TD + FG", "TD", "3pt FG", "Safety"};
void copy_counts(int destination[], int td_8, int td_7, int td, int fg, int sfty) {
    destination[0] = td_8;
    destination[1] = td_7;
    destination[2] = td;
    destination[3] = fg;
    destination[4] = sfty;
}
bool compare_combinations(const int combo1[], const int combo2[]) {
    for (int i = 0; i < NUM_PLAY_TYPES; i++) {
        if (combo1[i] != combo2[i]) {
            return false;
        }
    }
    return true;
}
bool is_combination_unique(const int new_counts[]) {
    for (int i = 0; i < g_combination_count; i++) {
        if (compare_combinations(new_counts, g_combinations[i])) {
            return false; // Found a duplicate
        }
    }
    return true; // Combination is unique
}
void add_unique_combination(const int new_counts[]) {
    if (is_combination_unique(new_counts)) {
        if (g_combination_count >= g_combination_capacity) {
            g_combination_capacity = (g_combination_capacity == 0) ? 10 : g_combination_capacity * 2;
            g_combinations = (int**)realloc(g_combinations, g_combination_capacity * sizeof(int*));
            if (g_combinations == NULL) {
                perror("Failed to reallocate memory for combination pointers");
                exit(EXIT_FAILURE);
            }
        }
        int* new_combo_row = (int*)malloc(NUM_PLAY_TYPES * sizeof(int));
        if (new_combo_row == NULL) {
            perror("Failed to allocate memory for combination row");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < NUM_PLAY_TYPES; i++) {
            new_combo_row[i] = new_counts[i];
        }
        g_combinations[g_combination_count] = new_combo_row;
        g_combination_count++;
    }
}
void cleanup_combinations() {
    if (g_combinations != NULL) {
        for (int i = 0; i < g_combination_count; i++) {
            free(g_combinations[i]);
        }
        free(g_combinations);
        g_combinations = NULL;
    }
    g_combination_count = 0;
    g_combination_capacity = 0;
}
void combination(int score, int fg, int sfty, int td, int td_7, int td_8) {
    if (score == 0) {
        int counts[NUM_PLAY_TYPES];
        copy_counts(counts, td_8, td_7, td, fg, sfty);
        add_unique_combination(counts);
        return;
    }
    if (score < 0) {
        return;
    }
    if (score >= 8) {
        combination(score - 8, fg, sfty, td, td_7, td_8 + 1);
    }
    if (score >= 7) {
        combination(score - 7, fg, sfty, td, td_7 + 1, td_8);
    }
    if (score >= 6) {
        combination(score - 6, fg, sfty, td + 1, td_7, td_8);
    }
    if (score >= 3) {
        combination(score - 3, fg + 1, sfty, td, td_7, td_8);
    }
    if (score >= 2) {
        combination(score - 2, fg, sfty + 1, td, td_7, td_8);
    }
}
int main(void) {
    int score;
    while (1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        if (scanf("%d", &score) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a positive integer score or '1'.\n");
            continue;
        }
        if (score == 1) {
            printf("terminating\n");
            break;
        } 
        if (score < 0) {
            printf("invalid score\n");
            continue;
        }
        cleanup_combinations();
        printf("Possible combinations of scoring plays if a team's score is %d:\n", score);
        if (score<0) {
            printf("invalid score\n");
        } else {
            combination(score, 0, 0, 0, 0, 0);
            if (g_combination_count > 0) {
                printf("Found %d unique combination(s):\n", g_combination_count);
                for (int i = g_combination_count-1; i >=0; i--) {
                    int* counts = g_combinations[i];
                    printf("  %d  %s, %d  %s, %d  %s, %d  %s, %d  %s\n", 
                           counts[0], SCORING_NAMES[0], // TD + 2pt
                           counts[1], SCORING_NAMES[1], // TD + FG
                           counts[2], SCORING_NAMES[2], // TD
                           counts[3], SCORING_NAMES[3], // FG
                           counts[4], SCORING_NAMES[4]  // Safety
                    );
                }
            } else {
                printf("  No combinations found for score %d.\n", score);
            }
        }
        while (getchar() != '\n');
    }
    cleanup_combinations(); 
    return 0;
}