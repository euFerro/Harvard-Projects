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
}
pair;

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
        //PRINTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
        printf("candidates[%i] = {%s}\n", i, candidates[i]);
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    //initialize preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
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

            if (vote(j, name, ranks) == false)
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
    bool isIn = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            isIn = true;
        }
        printf("RANKS[%i]: %i\n", i, ranks[i]);
    }
    return isIn;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if(i == j)
            {
                preferences[ranks[i]][ranks[j]] = 0;
            }
            else if (i != j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    printf("\npreferences\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i over %i ( %i ) ", i, j, preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int position = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
                {
                    pairs[position].winner = i;
                    pairs[position].loser = j;
                    position++;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[position].winner = j;
                    pairs[position].loser = i;
                    position++;
                    pair_count++;
                }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
            printf("pairs[%i].winner --> %i\n", i, pairs[i].winner);
            printf("pairs[%i].loser --> %i\n", i, pairs[i].loser);
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
            int strength1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int strength2 = preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner];

            if (strength1 < strength2)
            {
                int aux = pairs[i].winner;
                pairs[i].winner = pairs[i+1].winner;
                pairs[i+1].winner = aux;

                int aux2 = pairs[i].loser;
                pairs[i].loser = pairs[i+1].loser;
                pairs[i+1].loser = aux2;
            }
    }
     for (int i = 0; i < candidate_count; i++)
    {
            printf("Sorted Pairs Array\n");
            printf("pairs[%i].winner --> %i\n", i, pairs[i].winner);
            printf("pairs[%i].loser --> %i\n", i, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
            if (pairs[i].loser != pairs[candidate_count-1].winner)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
    }


    printf("\nlocked\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i over %i ( %i ) ", i, j, locked[i][j]);
        }
        printf("\n");
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int won;
    int count;

    for (int i = 0; i < candidate_count; i++)
    {
        count = 0;
        for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][i] == false)
                {
                    count++;
                }
                if (count == 3)
                {
                    won = i;
                    break;
                }
            }
    }
    string finalWinner = candidates[won];
    printf("%s\n", finalWinner);
    return;
}

