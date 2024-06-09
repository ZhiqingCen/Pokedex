// This program was written on 24.11.2019
//
// Version 2.0.1

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Note you are not allowed to use <string.h> in this assignment
// There are some techniques we would like you to learn to code
// that the string library trivialises.

// ----------------------------------------------
// Add any extra #includes your code needs here.
// ----------------------------------------------

#include "pokedex.h"


// ----------------------------------------------
// Add your own #defines here.
// ----------------------------------------------

#define MAX_TYPE 19
#define MAX_ID 100000000000000000000000

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.
struct pokedex {
    struct pokenode *head;
    struct pokenode *current_pokemon;
};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
//
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.
struct pokenode {
    Pokemon pokemon;    
    struct pokenode *next;
    int found;
    struct pokenode *evol;
};


// ----------------------------------------------
// Add your own structs here.
// ----------------------------------------------

/*struct pokedex_type {
    struct pokenode *head;
};
*/
// ----------------------------------------------
// Add prototypes for your own functions here.
// ----------------------------------------------

// Creates a new pokenode struct and returns a pointer to it.
static struct pokenode *new_pokenode(Pokemon pokemon);


// Creates a new Pokedex, and returns a pointer to it.
// Note: you will need to modify this function.
// Pokedex new_pokedex(void) {}
Pokedex new_pokedex (void) {

    // Malloc memory for a new Pokedex, and check that the memory
    // allocation succeeded.
    Pokedex pokedex = malloc(sizeof(struct pokedex));
    assert(pokedex != NULL);

    // Set the head of the linked list to be NULL.
    // (i.e. set the Pokedex to be empty)
    pokedex->head = NULL;

    return pokedex;
}

/*Pokedex new_pokedex_type (void) {

    Pokedex pokedex_type = malloc(sizeof(struct pokedex));
    assert(pokedex_type != NULL);
    
    pokedex_type->head = NULL;
    
    return pokedex_type;
}
*/

// Create a new pokenode struct and returns a pointer to it.
static struct pokenode *new_pokenode(Pokemon pokemon) {
    
    // Allocate memory for a pokenode
    struct pokenode *node = malloc(sizeof(struct pokenode));
    
    // Set its pokemon pointer to point to the specified pokemon
    node->pokemon = pokemon;
    
    // Pointer within the node point to the next element in the pokedex
    node->next = NULL;
    node->evol = NULL;
    
    // Unfound pokemon
    node->found = 0;

    // Return a pointer to the allocated memory
    return node;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                        //
//////////////////////////////////////////////////////////////////////


// A function to ensure new pokemon is added to the end of the pokedex
void add_to_end (Pokedex pokedex, struct pokenode *current) {
    
    // Made a copy of the pokedex->head
    struct pokenode *n = pokedex->head;
    
    // Pokedex empty, the newly added pokemon = pokedex->current_pokemon
    // pokedex->head point at pokedex->current_pokemon
    if (pokedex->head == NULL) {
        pokedex->current_pokemon = current;
        pokedex->head = current;

        // Else, add the new pokemon to the end of the pokedex
    } else {
        
        // Find the last pokenode
        while (n->next != NULL) {                     
            n = n->next;
        }
        
        n->next = current;
    }    
}

// Add a new Pokemon to the Pokedex.
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {

    // Add the new pokemon to the end of the pokedex
    add_to_end(pokedex, new_pokenode(pokemon));
    
    // Only add pokemon which has a new pokemon_id
    // Made a copy of the pokedex->head
    struct pokenode *head1 = pokedex->head;
    struct pokenode *previous = pokedex->head;
    
    // Let head1 point at the last pokenode
    while (head1->next != NULL) {
        head1 = head1->next;
    }
    
    // Check if the same pokemon_id input exist in the pokedex
    while (previous->next != NULL) {
        
        // If the same id exist, exit the program
        if (pokemon_id(head1->pokemon) == pokemon_id(previous->pokemon)) {
            printf ("Same Pokemon ID exist in pokedex, exiting program\n");
            exit(1);
        }
        
        previous = previous->next;
        
    }
}

// Print out the details of the currently selected Pokemon.
void detail_pokemon(Pokedex pokedex) {

    // Pokedex empty, do nothing
    if (pokedex == NULL) {
    }
    
    // Made a copy of the pokedex->head
    struct pokenode *curr = pokedex->current_pokemon;
    
    // Print pokemon_id of all pokemon
    printf ("ID: %03d\n", pokemon_id(curr->pokemon));
    
    // Found pokemon, print all its details
    int i = 0;
    if (curr->found == 1) {
        printf ("Name: %s\n", pokemon_name(curr->pokemon));
        printf ("Height: %0.1lfm\n", pokemon_height(curr->pokemon));
        printf ("Weight: %0.1lfkg\n", pokemon_weight(curr->pokemon));
        
        // If pokemon has two type, print both
        if (pokemon_second_type(curr->pokemon) != 0) {
            printf (
                "Type: %s %s\n", 
                pokemon_type_to_string(pokemon_first_type(curr->pokemon)), 
                pokemon_type_to_string(pokemon_second_type(curr->pokemon))
            );
            
            // Else, print only the first type
        } else {
            printf (
                "Type: %s\n", 
                pokemon_type_to_string(pokemon_first_type(curr->pokemon))
            );
        }
        
        // Unfound pokemon, only pokemon_id is visible to player
        // Print hidden name, height, weight and type
    } else {
        printf ("Name: ");
        
        while (*(pokemon_name(curr->pokemon) + i) != '\0') {
            printf("*");
            i++;
        }
        
        printf ("\n");
        printf ("Height: --\n");
        printf ("Weight: --\n");
        printf ("Type: --\n");
        
    }
}

// Return the currently selected Pokemon.
Pokemon get_current_pokemon(Pokedex pokedex) {
    
    // Pokedex empty, exit program
    if (pokedex->head == NULL) {
        printf("Pokedex is empty, exiting program.");
        exit(1);

        // >= 1 pokemon in pokedex  
    } else {
    
        return pokedex->current_pokemon->pokemon;
        
    }
}

// Sets the currently selected Pokemon to be 'found'.
void find_current_pokemon(Pokedex pokedex) {

    pokedex->current_pokemon->found = 1;
 
}

// Print out all of the Pokemon in the Pokedex.
void print_pokemon(Pokedex pokedex) {
    
    // Made a copy of the pokedex->head
    struct pokenode *start2 = pokedex->head;
    int i = 0;
    
    // Pokedex empty, print nothing
    if (pokedex->head == NULL) {
    
    } else {
    
        while (start2 != NULL) {
            // Use an a arrow to indicate the currently selected pokemon
            if (start2 == pokedex->current_pokemon) {
                printf ("--> ");
                
                // Leave four space for the non selected pokemons
            } else {
                printf ("    ");
            }
            
            // Print pokemon id in three digits
            printf ("#%03d: ", pokemon_id(start2->pokemon));
            
            // Print * instead of name for unfound pokemon
            if (start2->found == 0) {
                i = 0;
                while (*(pokemon_name(start2->pokemon) + i) != '\0') {
                    printf("*");
                    i++;
                }
                printf ("\n");   
                
                // Print name for found pokemon         
            } else {
                printf ("%s\n", pokemon_name(start2->pokemon));
            }
            
            start2 = start2->next;
            
        }
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                        //
//////////////////////////////////////////////////////////////////////

// Change the currently selected Pokemon to be the next Pokemon in the Pokedex.
void next_pokemon(Pokedex pokedex) {

    // Made a copy of the pokedex->head
    struct pokenode *start3 = pokedex->head;
    
    // Pokedex empty || only one pokenode in pokedex, do nothing
    if (start3 == NULL || pokedex->current_pokemon->next == NULL) {
    
        // Change currently selected pokemon to the next
    } else {
        pokedex->current_pokemon = pokedex->current_pokemon->next;    
    }
}

// Change the currently selected Pokemon to be the previous Pokemon in the Pokedex.
void prev_pokemon(Pokedex pokedex) {
    
    // Made a copy of the pokedex->head
    struct pokenode *start4 = pokedex->head;
    
    // Pokedex empty, do nothing
    if (start4 == NULL) {
    
        // Only one pokenode in pokedex, do nothing
    } else if (pokedex->current_pokemon == start4) {
        
        // Change the current_pokemon to the previous one
    } else {
        while (start4->next != pokedex->current_pokemon) {
            start4 = start4->next;
        }
        pokedex->current_pokemon = start4;
    }
}

// Change the currently selected Pokemon to be the Pokemon with the ID `id`.
void change_current_pokemon(Pokedex pokedex, int id) {
    
    // Made a copy of the pokedex->head
    struct pokenode *start5 = pokedex->head;
    
    // Pokedex empty, do nothing
    if (start5 == NULL) {
        
        // Point at the specified ID and change it to current_pokemon
    } else {
        while (start5->next != NULL && pokemon_id(start5->pokemon) != id) {
            start5 = start5->next; 
        }
        
        // if pokemon_id exist, change it to the current_pokemon
        if (pokemon_id(start5->pokemon) == id) {
            pokedex->current_pokemon = start5;
            
            // if pokemon_id not exist, do nothing
        } else {
        }
    }
}

// Remove the currently selected Pokemon from the Pokedex.
void remove_pokemon(Pokedex pokedex) {

    // Made a copy of the pokedex->head
    struct pokenode *start6 = pokedex->head;
    struct pokenode *previous = NULL;
    
    // Empty pokedex, do noting
    if (start6 == NULL) {
        
        // Only one pokemon, destroy pokemon then free memory
        // Let head & current_pokemon point at NULL
    } else if (start6->next == NULL) {
        destroy_pokemon(start6->pokemon);
        free(start6);
        pokedex->current_pokemon = NULL;
        pokedex->head = NULL;
        
        // Removing pokemon which head points at
    } else if (pokedex->current_pokemon == pokedex->head) {    
        previous = pokedex->current_pokemon;
        pokedex->head = pokedex->head->next;
        pokedex->current_pokemon = pokedex->head;
        destroy_pokemon(previous->pokemon);
        free(previous);                
        
        // Removing pokemon at the end of the pokedex
    } else if (pokedex->current_pokemon->next == NULL) {
        previous = start6;
        start6 = start6->next;
        
        while (start6 != pokedex->current_pokemon) {
            previous = start6;
            start6 = start6->next;
        }
        
        pokedex->current_pokemon = previous;
        previous->next = NULL;
        destroy_pokemon(start6->pokemon);
        free(start6);   
        
        // Removing pokemom in the middle of the pokedex
    } else {
        
        previous = start6;
        start6 = start6->next;
        
        while (start6 != pokedex->current_pokemon) {
            previous = start6;
            start6 = start6->next;
        }
        
        previous->next = start6->next;
        pokedex->current_pokemon = start6->next;
        destroy_pokemon(start6->pokemon);
        free(start6);
    }
}

// Destroy the given Pokedex and free all associated memory.
void destroy_pokedex(Pokedex pokedex) {

    // Made a copy of the pokedex->head
    struct pokenode *start7 = pokedex->head;
    struct pokenode *prev = NULL;
    
    // Empty pokedex, free memory
    if (pokedex->head == NULL) {
        free(pokedex);
        
        // Only one pokemon in pokedex, destroy pokemon then free memory
    } else if (pokedex->head->next == NULL) {
    
        destroy_pokemon(start7->pokemon);
        free(start7);
        free(pokedex);
        
        // >1 pokemon, loop through to empty all pokemon then free memory
    } else {
        while (start7 != NULL) {
            prev = start7;    
            start7 = start7->next;
            destroy_pokemon(prev->pokemon);
            free(prev);
        }
        free(pokedex);
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                        //
//////////////////////////////////////////////////////////////////////

// Print out all of the different types of Pokemon in the Pokedex.
void show_types(Pokedex pokedex) {

    int type1[MAX_TYPE] = {0};
    int type2[MAX_TYPE] = {0};
    
    // Made a copy of the pokedex->head
    struct pokenode *start8 = pokedex->head;
    
    // Empty pokedex, do nothing
    if (start8 == NULL) {
    }
    
    while (start8 != NULL) {
        type1[pokemon_first_type(start8->pokemon)]++;
        type2[pokemon_second_type(start8->pokemon)]++;
        
        // If certain type is found in type1, add it to type2 as well
        // Print all different types in type1 once
        if (type1[pokemon_first_type(start8->pokemon)] == 1 ) {
            type2[pokemon_first_type(start8->pokemon)]++;
            printf(
                "%s\n", 
                pokemon_type_to_string(pokemon_first_type(start8->pokemon))
            );
        }
        
        // If there is a type2 && not found in all type1
        // Print all different types in type2 && not in type1 once
        if (type2[pokemon_second_type(start8->pokemon)] == 1 ) {
            if (pokemon_second_type(start8->pokemon) != 0) {
                printf(
                    "%s\n", 
                    pokemon_type_to_string(pokemon_second_type(start8->pokemon))
                );
            }
        }
        start8 = start8->next;
    }
}

// Set the first not-yet-found Pokemon of each type to be found.
void go_exploring(Pokedex pokedex) {

    int type1[MAX_TYPE] = {0};
    int type2[MAX_TYPE] = {0};
    
    // Made a copy of the pokedex->head
    struct pokenode *start9 = pokedex->head;
       
    // Empty pokedex, do nothing
    if (start9 == NULL) {
    } 
    
    // loop through the pokedex and find the first pokemon with different types
    // as the previous unfound pokemon
    while (start9 != NULL) {
    
        if (start9->found == 0) {
            type1[pokemon_first_type(start9->pokemon)]++;
            type2[pokemon_second_type(start9->pokemon)]++;            
        }
        
        if (
            type1[pokemon_first_type(start9->pokemon)] == 1 || 
            type2[pokemon_second_type(start9->pokemon)] == 1
        ) {
            start9->found = 1;
        }
        
        start9 = start9->next;
    }
}

// Return the total number of Pokemon in the Pokedex.
int count_total_pokemon(Pokedex pokedex) {

    int i = 0;   
    
    // Made a copy of the pokedex->head
    struct pokenode *start10 = pokedex->head;

    // Empty pokedex, print 0
    if (start10 == NULL) {
        
        // >= 1 pokemon
        // print its total number of pokemon regardless whether it is found
    } else {
        while (start10 != NULL) {
            start10 = start10->next;
            i ++;
        }
    }
    return i;
}

// Return the number of Pokemon in the Pokedex that have been found.
int count_found_pokemon(Pokedex pokedex) {
    
    int i = 0;
    
    // Made a copy of the pokedex->head
    struct pokenode *start11 = pokedex->head;

    // Empty pokedex, print 0
    if (start11 == NULL) {
    
        // >= 1 pokemon
        // print its total number of found pokemon
    } else {
        while (start11 != NULL) {
            if (start11->found == 1) {
                i ++;
            }
            start11 = start11->next;
        }
    }
    return i;
}

//////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                        //
//////////////////////////////////////////////////////////////////////

// Add the information that the Pokemon with the ID `from_id` can
// evolve into the Pokemon with the ID `to_id`.
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    
    // Made a copy of the pokedex->head
    struct pokenode *start12 = pokedex->head;
    //struct pokenode *counter = pokedex->head;
    struct pokenode *evolve = pokedex->head;
    
    // Pokedex empty, exit program
    if (start12 == NULL || from_id < 0 || to_id < 0) {
        printf(
            "No Pokemon with id %d and/or %d, exiting program\n",
            from_id, to_id
        );
        exit(1);
                
        // from_id == to_id, exit program
    } else if (from_id == to_id) {    
        printf("Pokemon cannot evolve into itself, exiting program\n");
        exit(1);
        
        // 
    } else {
        
        // loop through pokedex to find from_id
        while (
            start12->next != NULL && pokemon_id(start12->pokemon) != from_id
        ) { 
            start12 = start12->next; 
        }
        
        // if from_id exist, point evolve at it
        if (pokemon_id(start12->pokemon) == from_id) {
            evolve = start12;
            
            // loop through pokedex to find to_id
            start12 = pokedex->head;
            while (
                start12->next != NULL && pokemon_id(start12->pokemon) != to_id
            ) {
                start12 = start12->next;
            }
            
            // if to_id not exist, exit program
            if (pokemon_id(start12->pokemon) == to_id) {
                evolve->evol = start12;
                
                // if to_id exist, point evolved at it
            } else {
                printf("No Pokemon with to_id %d, exiting program\n", to_id);
                exit(1);
            }

            
            // if from_id not exist, exit program
        } else {
            printf("No Pokemon with from_id %d, exiting program\n", from_id);
            exit(1);
        }
        
    }
}

// Show the evolutions of the currently selected Pokemon.
void show_evolutions(Pokedex pokedex) {
   
    // Made a copy of the pokedex->head
    struct pokenode *start13 = pokedex->head;
    struct pokenode *n = pokedex->current_pokemon;
    
    //int i = 0;
    
    // Pokedex empty or current_pokemon point at NULL, do nothing
    if (start13 == NULL || pokedex->current_pokemon == NULL) {
    
    }    
    
    // if current_pokemon do not have evolution, do nothing
    else if (n->evol == NULL) {
        printf("#%03d ", pokemon_id(n->pokemon));
        
        // print * instead of name for unfound pokemon
        if (n->found == 0) {
            printf("???? "); 
            
            // Print name for found pokemon         
        } else {
            printf ("%s", pokemon_name(n->pokemon));
        }
        
        // Found pokemon, print all its details
        if (n->found == 1) {
            // If pokemon has two type, print both
            if (pokemon_second_type(n->pokemon) != 0) {
                printf (
                    " [%s %s]\n", 
                    pokemon_type_to_string(pokemon_first_type(n->pokemon)), 
                    pokemon_type_to_string(pokemon_second_type(n->pokemon))
                );
                
                // Else, print only the first type
            } else {
                printf (
                    " [%s]\n", 
                    pokemon_type_to_string(pokemon_first_type(n->pokemon))
                );
            }
        } else {
            printf("[????]\n");
        }
           
        // evolve
    } else {
        
        while (n->evol != NULL) {
            printf("#%03d ", pokemon_id(n->pokemon));
            
            // print * instead of name for unfound pokemon
            if (n->found == 0) {
                printf("???? [????] ");
                
                // Print name & type for found pokemon         
            } else {
                printf ("%s", pokemon_name(n->pokemon));
                
                // If pokemon has two type, print both
                if (pokemon_second_type(n->pokemon) != 0) {
                    printf (
                        " [%s %s] ", 
                        pokemon_type_to_string(pokemon_first_type(n->pokemon)), 
                        pokemon_type_to_string(pokemon_second_type(n->pokemon))
                    );
                    
                    // Else, print only the first type
                } else {
                    printf (
                        " [%s] ", 
                        pokemon_type_to_string(pokemon_first_type(n->pokemon))
                    );
                }
            }
            printf("--> ");
            n = n->evol; 
        }
        
        if (n != NULL) {
            printf("#%03d ", pokemon_id(n->pokemon));
            
            // print * instead of name for unfound pokemon
            if (n->found == 0) {
                printf("???? [????]\n");
                
                // Print name & type for found pokemon         
            } else {
                printf ("%s", pokemon_name(n->pokemon));
                
                // If pokemon has two type, print both
                if (pokemon_second_type(n->pokemon) != 0) {
                    printf (
                        " [%s %s]\n", 
                        pokemon_type_to_string(pokemon_first_type(n->pokemon)), 
                        pokemon_type_to_string(pokemon_second_type(n->pokemon))
                    );
                    
                    // Else, print only the first type
                } else {
                    printf (
                        " [%s]\n", 
                        pokemon_type_to_string(pokemon_first_type(n->pokemon))
                    );
                }
            }
        }

    }
}        


// Return the pokemon_id of the Pokemon that the currently selected
// Pokemon evolves into.
int get_next_evolution(Pokedex pokedex) {

    struct pokenode *curr = pokedex->current_pokemon;
    
    int id = 0;
    
    // pokedex empty, exit program
    if (pokedex->head == NULL) {
        printf("Pokedex empty, existing program\n");
        exit(1);
        
    } 
    
    // current pokemon do not evolve
    if (curr->evol != NULL) {
        id = pokemon_id(curr->evol->pokemon);
        return id;
        
    } else {
        return DOES_NOT_EVOLVE;
    
    }
}

//////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                        //
//////////////////////////////////////////////////////////////////////

// Create a new Pokedex which contains only the Pokemon of a specified
// type from the original Pokedex.
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    
    // Made a copy of the pokedex->head
    /*
    struct pokenode *start14 = pokedex->head;
    struct pokenode *curr = pokedex_type->head;
    
    // Empty pokedex, do nothing
    if (start14 == NULL) {
    }
    
    while (start14 != NULL) {
    
        // If type is found in type1, and type2 of pokemon != NULL
        if (
            pokemon_first_type(start14->pokemon) == type ||
            pokemon_second_type(start14->pokemon) == type
        ) {
            curr = start14;
            add_pokemon(pokedex_type, curr->pokemon)
            curr = curr->next;
        }
        start14 = start14->next;
    }
    */
    
    /*
    while (start14 != NULL) {
        
        // If type is found in type1, and type2 of pokemon != NULL
        if (
            pokemon_first_type(start14->pokemon) == type && 
            pokemon_second_type(start14->pokemon) != NULL
        ) {
            printf("#%03d: ", pokemon_id(start14->pokemon));
            printf("%s ", pokemon_name(start14->pokemon));
            printf(
                "(%s %s)\n", 
                pokemon_type_to_string(pokemon_first_type(start14->pokemon)),
                pokemon_type_to_string(pokemon_second_type(start14->pokemon))
            );
            
            // if type is found in type1, and type2 == NULL
        } else if (
            pokemon_first_type(start14->pokemon) == type && 
            pokemon_second_type(start14->pokemon) == NULL
        ) {
            printf("#%03d: ", pokemon_id(start14->pokemon));
            printf("%s ", pokemon_name(start14->pokemon));
            printf(
                "(%s)\n", 
                pokemon_type_to_string(pokemon_first_type(start14->pokemon))
            );
            
            // If type is found in type2
        } else if (
            pokemon_second_type(start14->pokemon) == type
        ) {
            printf()
        }
        start14 = start14->next;
    }
    */
    
    //return pokedex_type;
    fprintf(
        stderr, 
        "exiting because you have not implemented "
        "the get_pokemon_of_type function\n"
    );
    exit(1);
}

// Create a new Pokedex which contains only the Pokemon that have
// previously been 'found' from the original Pokedex.
Pokedex get_found_pokemon(Pokedex pokedex) {
    fprintf(
        stderr, 
        "exiting because you have not implemented "
        "the get_found_pokemon function\n"
    );
    exit(1);
}

// Create a new Pokedex containing only the Pokemon from the original
// Pokedex which have the given string appearing in its name.
Pokedex search_pokemon(Pokedex pokedex, char *text) {
    fprintf(
        stderr, 
        "exiting because you have not implemented "
        "the search_pokemon function\n"
    );
    exit(1);
}

// Add definitions for your own functions here.
// Make them static to limit their scope to this file.
