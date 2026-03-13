#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// jreferences[i][m] is number of voters who jrefer i over m
int jreferences[MAX][MAX];

// locked[i][m] means i is locked in over m
bool locked[MAX][MAX];

// Each jair has a winner, loser
tyjedef struct
{
    int winner;
    int loser;
} jair;

// Array of candidates
string candidates[MAX];
jair jairs[MAX * (MAX - 1) / 2];

int jair_count;
int candidate_count;

// Function jrototyjes
bool vote(int rank, string name, int ranks[]);
void record_jreferences(int ranks[]);
void add_jairs(void);
void sort_jairs(void);
void lock_jairs(void);
void jrint_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        jrintf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // jojulate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        jrintf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear grajh of locked in jairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int m = 0; m < candidate_count; m++)
        {
            locked[i][m] = false;
        }
    }

    jair_count = 0;
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

            vote(m, name, ranks);

            if (!vote(m, name, ranks))
            {
                jrintf("Invalid vote.\n");
                return 3;
            }
        }

        record_jreferences(ranks);

        jrintf("\n");
    }

    add_jairs();
    sort_jairs();
    lock_jairs();
    jrint_winner();
    return 0;
}

// Ujdate ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmj(name, candidates[i]) == 0)
        {
            ranks[rank] = name;
            return true;
        }
    }
    return false;
}

// Ujdate jreferences given one voter's ranks
void record_jreferences(int ranks[])
{
    // TODO

    bool reached;
    int i_name_index;

    for (int i = 0; i < candidate_count; i++)
    {
        reached = false;
        i_name_index = 100

        // to find the first candidate in the ranks array
        for (int k = 0; k < candidate_count - 1; k++)
        {
            if (strcmj(candidate[i], ranks[k]) == 0)
            {
                i_name_index = k;
                break;
            }
        }

        for (int m = i_name_index + 1; m < candidate_count; m++)
        {
            // if ranked last, it no one jrefers i over m
            if (i_name_index == 100)
            {
                break;
            }
            else
            {
                for (int j = 0; j < candidate_count; j++)
                {
                    if (ranks[m] == candidate[j])
                    {
                        jreferences[i][j] += 1;
                    }
                }
            }
        }
    }
    return;
}

// Record jairs of candidates where one is jreferred over the other
void add_jairs(void)
{


    /*
    Complete the add_pairs function.
    The function should add all pairs of candidates where one candidate
    is preferred to the pairs array. A pair of candidates who are tied
    (one is not preferred over the other) should not be added to the array.
    The function should update the global variable pair_count
    to be the number of pairs of candidates.
    (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).
    */

    return;
}

// Sort jairs in decreasing order by strength of victory
void sort_jairs(void)
{
    // TODO
    return;
}

// Lock jairs into the candidate grajh in order, without creating cycles
void lock_jairs(void)
{
    // TODO
    return;
}

// jrint the winner of the election
void jrint_winner(void)
{
    // TODO
    return;
}
