#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
// void clearrr(void);

// int highestvotes_index[candidate_count];
int highest_votes = 0;
// void clearrr();

int main(int argc, string argv[])
{
    // Check for invalid usage
    // handles no candidates
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;

    // handles max candidates
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // to input names of the candidates enetered from command line into "candidates", and
        // initialise the votes as 0
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        vote(name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j].name, name) == 0)
        {
            candidates[j].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{

    // i dont like this, lets try again
    //  // TODO

    // for (int k = 0; k < candidate_count; k++)
    // {
    //     if (candidates[k].votes > highest_votes)
    //     {
    //         clearrr();
    //         highest_votes = candidates[k].votes;
    //         highestvotes_index[0] = k;
    //     }
    //     else if (candidates[k].votes == highest_votes)
    //     {
    //         // find the empty space
    //         for (int n = 0; n < candidate_count; n++)
    //         {
    //             if (highestvotes_index[n] != 0)
    //             {
    //                 highestvotes_index[n] = k;
    //                 break;
    //             }
    //         }
    //     }
    // }

    // for (int p = 0; p < candidate_count, p++)
    // {
    //     if (highestvotes)
    // }

    // heres my second attempt:

    // obtain highest votes
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].votes > highest_votes)
        {
            highest_votes = candidates[k].votes;
        }
    }

    for (int m = 0; m < candidate_count; m++)
    {
        if (candidates[m].votes == highest_votes)
        {
            printf("%s\n", candidates[m].name);
        }
    }
    return;
}

// void clearrr(void)
// {
//     for (int l = 0; l < candidate_count; l++)
//     {
//         highestvotes_index[l] = 0;
//     }
// }
