#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
            }
        }
    }

    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair pair;
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair.winner = i;
                pair.loser = j;
                pairs[pair_count] = pair;
                pair_count = pair_count + 1;
            }
        }
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int list[pair_count];
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                list[count] = preferences[i][j] - preferences[j][i];
                count = count + 1;
            }
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (list[i] < list[j])
            {
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        bool Winner_exist = false;
        bool loop_break = false;
        int cycle = -1;
        int x = pairs[i].winner;
        int loop_count = 0;
        int winner_count = 0;
        int list[pair_count];
        while (!loop_break)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                Winner_exist = false;
                if (locked[j][x])
                {
                    if (j == pairs[i].loser)
                    {
                        cycle = j;
                        Winner_exist = true;
                        loop_break = true; // break when cycle exists
                        break;
                    }
                    else
                    {
                        list[loop_count] = j;
                        loop_count = loop_count + 1;
                        Winner_exist = true;
                        break;
                    }
                }
            }
            if (Winner_exist == false)
            {
                loop_break = true; // breaks when no parent node exist (winner)
                continue;
            }
            if (cycle == pairs[i].loser)
            {
                continue;
            }
            x = list[winner_count];
            winner_count = winner_count + 1;
        }
        if (cycle == pairs[i].loser) // for every ith iteration, if cycle exists, skip locking pair.
        {
            continue;
        }

        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int W;
    for (int i = 0; i < candidate_count; i++)
    {
        W = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            W = W + locked[j][i];
        }
        if (W == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    // TODO
    return;
}
