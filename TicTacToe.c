#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <conio.h>
#define clear_screen() clrscr()
#else
#define clear_screen() printf("\e[1;1H\e[2J")
#endif

typedef struct {
    int row;
    int col; // columns 
} pos; // stands for position 

int best ( char **tic, int x, int y ) {
    int empti = 0;
    for ( int i = 0; i < 3; ++i ) {
        if ( !tic[x][i] )
            empti++;
        if ( !tic[i][y] )
            empti++;
    }
    return empti;
}

pos hard( char **tic, pos move, pos lstmv /* stands for last move */  ) {
    
    if ( move.row < 0 ) {
        srand(time(NULL));
        int mv = rand() % 9;
        move.row = mv / 3;
        move.col = mv % 3;
        return move;
    }

    int po = move.row * 3 + move.col,
        c = 0, r, n = 3, x, y,
        find0[4] = {0},
        empti0[4] = {0},
        x20[4] = {0},
        y20[4] = {0},
        gard[3] = {0},
        gardx1[3] = {0},
        gardy1[3] = {0},
        gard00[3] = {0},
        gardx01[3] = {0},
        gardy01[3] = {0},
        tally[4] = {0},
        save[2];
        
    char *q, name = tic[move.row][move.col];
    
    int find[4] = {0}, empti[4] = {0}, x2[4] = {0}, y2[4] = {0};
    if ( lstmv.row >= 0 ) {
        char e = tic[lstmv.row][lstmv.col];
        for ( int i = 0; i < 3; ++i ) {
            if ( tic[i][lstmv.col] == e )
                find[0]++;
            if ( !tic[i][lstmv.col] ) {
                empti[0]++;
                x2[0] = i;
                y2[0] = lstmv.col;
            }
        }
        if ( (find[0] == 2) && ( empti[0] == 1 ) ){
            move.row = x2[0];
            move.col = y2[0];
            return move;
        }
        
        for ( int i = 0; i < 3; ++i ) {
            if ( tic[lstmv.row][i] == e )
                find[1]++;
            if ( !tic[lstmv.row][i] ) {
                empti[1]++;
                x2[1] = lstmv.row;
                y2[1] = i;
            }
        }
        if ( (find[1] == 2) && ( empti[1] == 1 ) ){
            move.row = x2[1];
            move.col = y2[1];
            return move;
        }
        
        po = lstmv.row * 3 + lstmv.col;
        if ( !(po % 2) ) {
            for ( int i = 0, j = 2; i < 3; j--, i++ ) {
                if ( tic[i][i] == e )
                    find[2]++;
                else if ( !tic[i][i] ) {
                    empti[2]++;
                    x2[2] = i;
                    y2[2] = i;
                    gard[tally[2]++] = i;
                }
                
                if ( tic[i][j] == e )
                    find[3]++;
                else if ( !tic[i][j] ) {
                    empti[3]++;
                    x2[3] = i;
                    y2[3] = j;
                    gardx1[tally[3]] = i;
                    gardy1[tally[3]++] = j;
                }
            }
        }
        if ( (find[2] == 2) && ( empti[2] == 1 ) ){
            move.row = x2[2];
            move.col = y2[2];
            return move;
        }
        if ( (find[3] == 2) && ( empti[3] == 1 ) ){
            move.row = x2[3];
            move.col = y2[3];
            return move;
        }
    }
    
    for ( int i = 0; i < 3; ++i ) {
        if ( tic[i][move.col] == name )
            find0[2]++;
        if ( !tic[i][move.col] ) {
            empti0[2]++;
            x20[2] = i;
            y20[2] = move.col;
        }
    }
    
    if ( (find0[2] == 2) && ( empti0[2] == 1 ) ){
        move.row = x20[2];
        move.col = y20[2];
        return move;
    }
    
        
    for ( int i = 0; i < 3; ++i ) {
        if ( tic[move.row][i] == name )
            find0[3]++;
        if ( !tic[move.row][i] ) {
            empti0[3]++;
            x20[3] = move.row;
            y20[3] = i;
        }
    }
    if ( (find0[3] == 2) && ( empti0[3] == 1 ) ){
        move.row = x20[3];
        move.col = y20[3];
        return move;
    }
    
    
    if ( !(po % 2) ) {
        for ( int i = 0, j = 2; i < 3; j--, i++ ) {
            if ( tic[i][i] == name )
                find0[0]++;
            else if ( !tic[i][i] ) {
                empti0[0]++;
                x20[0] = i;
                y20[0] = i;
                gard00[tally[0]++] = i;
            }
                
            if ( tic[i][j] == name )
                find0[1]++;
            else if ( !tic[i][j] ) {
                empti0[1]++;
                x20[1] = i;
                y20[1] = j;
                gardx01[tally[1]] = i;
                gardy01[tally[1]++] = j;
            }
        }
    }
    
    if ( (find0[0] == 2) && ( empti0[0] == 1 ) ){
        move.row = x20[0];
        move.col = y20[0];
        return move;
    }
    
    if ( (find0[1] == 2) && ( empti0[1] == 1 ) ){
        move.row = x20[1];
        move.col = y20[1];
        return move;
    }
    
    
    if ( empti0[0] > 1 ){
        save[0] = gard00[0];
        for ( int i = 0; i < tally[0] - 1; ++i ) 
            if ( best(tic, save[0], save[0]) < best( tic, gard00[i + 1], gard00[i + 1] ) )
                save[0] = gard00[i + 1];
                
        move.row = save[0];
        move.col = save[0];
        return move;
    }
    
    if ( empti0[1] > 1 ){
        save[0] = gardx01[0];
        save[1] = gardy01[0];
        for ( int i = 0; i < tally[1] - 1; ++i ) 
            if ( best(tic, save[0], save[1]) < best( tic, gardx01[i + 1], gardy01[i + 1] ) ){
                save[0] = gardx01[i + 1];
                save[1] = gardy01[i + 1];
            }
        move.row = save[0];
        move.col = save[1];
        return move;
    }
    
    if ( empti[0] > 1 ) {
        save[0] = gard[0];
        for ( int i = 0; i < tally[2] - 1; ++i ) 
            if ( best(tic, save[0], save[0]) < best( tic, gard[i + 1], gard[i + 1] ) )
                save[0] = gard[i + 1];
                
        move.row = save[0];
        move.col = save[0];
        return move;
    } else if ( empti[1] > 1 ) {
        save[0] = gardx1[0];
        save[1] = gardy1[0];
        for ( int i = 0; i < tally[3] - 1; ++i ) 
            if ( best(tic, save[0], save[1]) < best( tic, gardx1[i + 1], gardy1[i + 1] ) ){
                save[0] = gardx1[i + 1];
                save[1] = gardy1[i + 1];
            }
        move.row = save[0];
        move.col = save[1];
        return move;
    }
    
    if ( empti0[0] ){
        move.row = x20[0];
        move.col = y20[0];
        return move;
    }
    
    if ( empti0[1] ){
        move.row = x20[1];
        move.col = y20[1];
        return move;
    }
    
    if ( empti[0] ) {
        move.row = x2[0];
        move.col = y2[0];
        return move;
    } else if ( empti[1] ) {
        move.row = x2[1];
        move.col = y2[1];
        return move;
    }
    
    
    while ( (n >= 0) && (q = memchr(tic + move.row, '\0', n))) {
        n--;
        r = q  - (*tic + move.row);
        c++;
    }
    if ( c == 1 ) {
        move.col = r;
        return move;
    } else
        c = 0;
    
    for ( int i = 0; i < 3; ++i )
        if ( !tic[i][move.col] ){
            c++;
            r = i;
        }
    
    if ( c == 1 ) {
        move.row = r;
        return move;
    } else
        c = 0;
    n = 0;
    
    
    for ( int i = 0; i < 3; ++i )
        for ( int j = 0; j < 3; ++j )
            if ( !tic[i][j] ) {
                move.row = i;
                move.col = j;
                return move;
            }
    move.row = -1;
    move.col = -1;
    return move;
}

pos easy (void) {
    pos move;
    srand(time(NULL));
    int mv = rand() % 9;
    move.row = mv / 3;
    move.col = mv % 3;
    return move;
}

bool empty ( char **tic ) {
    for ( int i = 0; i < 3; ++i )
        for ( int j = 0; j < 3; ++j )
            if ( !tic[i][j] )
                return false;
    return true;
}
pos think ( char **tic, pos move, int level, char name ) {
    if ( empty( tic ) ) {
        move.row = -1;
        move.col = -1;
        return move;
    }
    static pos lstmv = { -1, -1 };
    
    if ( level ) {
        lstmv = hard( tic, move, lstmv );
        if ( lstmv.row != -1 )
            tic[lstmv.row][lstmv.col] = name;
    } else {
        do {
            lstmv = easy();
        } while (tic[lstmv.row][lstmv.col]);
        tic[lstmv.row][lstmv.col] = name;
    }
    return lstmv;
}

bool check(char **tic, pos move, char name) {
    int error[2] = {0};
    for ( int i = 0; i < 3; ++i ) {
        if ( tic[move.row][i] != name )
            error[0]++;
        
        if ( tic[i][move.col] != name )
            error[1]++;
    }
    if ( !error[0] || !error [1] )
        return false;
    
    int po = move.row * 3 + move.col;
    if ( !(po % 2) ) {
        error[0] = error [1] = 0;
        for ( int i = 0, j = 2; i < 3; j--, i++ ) {
            if ( tic[i][i] != name )
                error[0]++;
                
            if ( tic[i][j] != name )
                error[1]++;
        }
        if ( !error[0] || !error [1] )
            return false;
    }
    
    return true;
}

void draw ( char **tic ) {
    for ( char **tac = tic; tac < tic + 3; tac++ ) {
        for ( char *toe = *tac; toe < *tac + 3; toe++ ) {
            if ( *toe )
                printf(" %c ", *toe);
            else
                printf(" %ld ", (tac - tic) * 3 + (toe - *tac) + 1);
            if ( toe < *tac + 2 )
                printf("|");
        }
        printf("\n");
        if ( tac < tic + 2 )
            for( int i = 0; i < 11; i++ ) {
                if ( i == 3 || i == 7 )
                    printf("+");
                else
                    printf("=");
            }
        printf("\n");
    }
}

int main() {
    
    char *tic[3], player, engine;
    int k = 0, level, move;
    pos enmove = {-1, -1}, plmove = {-1, -1};
    for (int i = 0; i < 3; i++)
        tic[i] = (char *)calloc(3, sizeof(char));

    do {
        printf(" o hey there sunshine X or O: ");
        scanf("%c%*c", &player);
        player = toupper(player);
    } while ( player != 'X' && player != 'O' );
    
    engine = player == 'X' ? 'O' : 'X';
    k = engine == 'X' ? 1 : 0;
    
    do {
        printf(" which level you want\n 1.easy\n 2.f(easy)^-1\n ..: ");
        scanf("%d", &level);
        level--;
    } while ( level > 1 || level < 0 );
    
    if ( k )
        enmove = think(tic, plmove, level, engine);
    
    for ( int i = 0; i < 9; ++i){
        
        clear_screen();
        draw( tic );
        pos crntmv; // stands for current move
        do {
            printf("\n your move: ");
            scanf("%d", &move);
            move--;
            crntmv.row = move / 3;
            crntmv.col = move % 3;
        } while ( ( move < 9 ) && ( move > -1 ) && tic[crntmv.row][crntmv.col] );
        tic[crntmv.row][crntmv.col] = player;
        if ( !check( tic, crntmv, player ) ) {
            clear_screen();
            draw( tic );
            printf("\n the winner is you pumpkin-pie");
            return 0;
        }
        clear_screen();
        draw( tic );
        printf("\n thinking...\n");
        enmove = think(tic, crntmv, level, engine);
        if ( enmove.row != -1 )
            if ( !check( tic, enmove, engine ) ) {
                clear_screen();
                draw( tic );
                printf("\n I won you dumdum\n");
                return 0;
            }
            
        if ( enmove.row == -1 || empty(tic))
            break;
        
    }
    clear_screen();
    draw( tic );
    printf("\n we're both winners cupcake\n");
    
    for (int i = 0; i < 3; i++)
        free(tic[i]);
    return 0;
}