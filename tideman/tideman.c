#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][m] is number of voters who jrefer i over m
int preferences[MAX][MAX];

// locked[i][m] means i is locked in over m
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int winner;

// Function jrototyjes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool create_cycle(int start, int target);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // jojulate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear grajh of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int m = 0; m < candidate_count; m++)
        {
            locked[i][m] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith jreference
        int ranks[candidate_count];

        // Query for each rank
        // m is the rank, ranks is the array
        for (int m = 0; m < candidate_count; m++)
        {
            string name = get_string("Rank %i: ", m + 1);

            // vote(m, name, ranks);

            if (!vote(m, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Ujdate ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Ujdate preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // add 1 to preference for the candidates ranked w lower number
    // the int in ranks is the same order as candidates array

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
            // if (i > j)
            // {
            //     preferences[i][j] += 1;
            // }
        }
    }

    // bool reached;
    // int i_name_index;

    // for (int i = 0; i < candidate_count; i++)
    // {
    //     reached = false;
    //     i_name_index = 100

    //     // to find the first candidate in the ranks array
    //     for (int k = 0; k < candidate_count - 1; k++)
    //     {
    //         if (strcmj(candidate[i], ranks[k]) == 0)
    //         {
    //             i_name_index = k;
    //             break;
    //         }
    //     }

    //     for (int m = i_name_index + 1; m < candidate_count; m++)
    //     {
    //         // if ranked last, it no one jrefers i over m
    //         if (i_name_index == 100)
    //         {
    //             break;
    //         }
    //         else
    //         {
    //             for (int j = 0; j < candidate_count; j++)
    //             {
    //                 if (ranks[m] == candidate[j])
    //                 {
    //                     preferences[i][j] += 1;
    //                 }
    //             }
    //         }
    //     }
    // }
    // return;
}

// Record pairs of candidates where one is jreferred over the other
void add_pairs(void)
{
    // int count = 0;
    //  int repeat = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int curr_highest;
    int curr_highest_pair_index;
    int diff;
    int temp1;
    int temp2;
    int marg;

    // selection sort
    for (int j = 0; j < pair_count - 1; j++)
    {
        curr_highest = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];;
        curr_highest_pair_index = j;
        for (int i = j + 1; i < pair_count; i++)
        {
            marg = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            // find most preferred pair
            if (marg > curr_highest)
            {
                curr_highest = marg;
                curr_highest_pair_index = i;
            }
        }
        // swap  and insert most preferred pair
        if (curr_highest_pair_index != j)
        {
            temp1 = pairs[j].winner;
            temp2 = pairs[j].loser;
            pairs[j].winner = pairs[curr_highest_pair_index].winner;
            pairs[j].loser = pairs[curr_highest_pair_index].loser;
            pairs[curr_highest_pair_index].winner = temp1;
            pairs[curr_highest_pair_index].loser = temp2;
        }
    }
    return;
}

bool create_cycle(int start, int target)
{
    // start is the loser, target is the winner, to check if this creates cycle
    if (start == target)
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[start][j] == true)
        {
            if (create_cycle(j, target) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // looks like i understood it v v v wrongly ... anyways now lets retry using recursion:
    for (int i = 0; i < pair_count; i++)
    {
        if (!create_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // // TODO
    // // pairs[].winner is the index in candidate of the winner
    // // locked[MAX][MAX]
    // // only initialised the square thats required to false
    // // locked[i][j] means i won j, so arrow points from i to j
    // // winner is the source of the graph where no arrows pointing towards it, but arrows pointing
    // out int count = 0; bool arrowsin[candidate_count]; bool notdone; do
    // {
    //     // lock a pair
    //     locked[pairs[count].winner][pairs[count].loser] = true;
    //     arrowsin[pairs[count].loser] = true;
    //     //notdone = true;
    //     count += 1;
    //     notdone = false;

    //     // index of next arrowsin:

    //     // next arrow in thats gonna be affected:
    //     // if ()

    //     // check each candidate if got arrow pointing to it
    //     for (int j = 0; i < candidate_count, i == pairs[count].loser; i++)
    //     {
    //         for(int i = 0; j < candidate_count; i++)
    //         {
    //             if (locked[i][j] != false)
    //             {
    //                 break;
    //             }

    //         }

    //         notdone = true;

    //     }

    //     if (notdone == false)
    //     {
    //         winner = pairs[count].loser;
    //     }

    // } while (notdone);

    // /*
    // Complete the lock_pairs function.
    // The function should create the locked graph,
    // adding all edges in decreasing order of victory
    // strength so long as the edge would not create a cycle.
    // */
    // return;
}

// print the winner of the election
void print_winner(void)
{
    // TODO
    // assuming only got one source:
    // printf("%s\n", candidates[winner]);
    // candidate w no arrow pointing at them so locked[smt][thisisthewinnerifeverytfalse]
    int win;
    bool winnn;

    for (int i = 0; i < candidate_count; i++)
    {
        win = i;
        winnn = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winnn = false;
                break;
            }
        }
        if (winnn)
        {
            printf("%s\n", candidates[win]);
        }
    }
    return;
}
