int main() {
    int score;
    while(1) {
        printf("Enter the NFL score (Enter 1 to stop): ");
        scanf('%d', &score);
    if (score<0) {
        printf("invalid score");
    }
    if (score==1) {
        printf('terminating');
    } else{
        printf("Possible combinations of scoring plays if a teams score is %d:", score);
    }
    return 0;
}

}
void combination(int score, int fg, int sfty, int td, int td_7, int td_8) {
    if (score==0) {
        printf("%d TD + 2pt, ", td_8);
        printf("%d TD + FG, ", td_7);
        printf("%d TD, ", td);
        printf("%d 3pt FG, ", fg);
        printf("%d Safety", sfty);
        return;
    }
    if (score>=8) {
        combination(score-8, fg, sfty, td, td_7, td_8+1);
    }
    if (score>=7) {
        combination(score-7, fg, sfty, td, td_7+1, td_8);
    }
    if (score>=6) {
        combination(score-6, fg, sfty, td+1, td_7, td_8);
    }
    if (score>=3) {
        combination(score-3, fg+1, sfty, td, td_7, td_8);
    }
    if (score>=2) {
        combination(score-2, fg, sfty+1, td, td_7, td_8);
    }
}
