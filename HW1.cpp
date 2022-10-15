// Dev-C++ 5.11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int *IntPtr; // int pointer

void Menu();
void Permute1( int str[], int head, int tail );
void Permute2( int str[], int head, int tail );
int gcount = 1;
void Swap( IntPtr A, IntPtr B );
int Fac( int num );
bool Is_Repeat( int i, int str[], int temp, int len );
void Mission_1( int inp );
void Mission_2( int len );
void Mission_3( int inp );

int main() {
    int num = 2147483647, temp = 2147483647; // case, input
    char ch = '\0';
    
    do {
        if ( ch == '\0' ) {
            // reset
            Menu();
            gcount = 1;
            num = 2147483647;
            temp = 2147483647;
        } // if
        
        scanf( "%d", &num );
        ch = getchar();
        while ( ch != '\n' ) ch = getchar();
        
        // program start
        if ( num == 0 ) break;
        else if ( num == 2147483647 ) {
            ch = '-'; // 隨便設，scanf要int但user直接塞非數字字元
            continue;
        } // else if
        else if ( num < 0 || num > 3 ) {
            printf( "Command does not exist !\n" );
            ch = '\0'; // 要重設，重新印Menu
        } // else if
        else {
            if ( num == 1 || num == 3 ) { // Mission_1 or Mission_3
                printf( "Input a number :\n" );
                do {
                    scanf( "%d", &temp );
                    ch = getchar();
                    while ( ch != '\n' ) ch = getchar();
                } while( ch != '\n' || temp == 2147483647 );
                
                if ( temp == 2147483647 ) continue; // scanf要int但user直接塞非數字字元
                while ( temp < 1 || 9 < temp ) {
                    printf( "### It is NOT in [1,9] ###\n" );
                    scanf( "%d", &temp );
                } // while
                
                if ( num == 1 ) {
                    Mission_1( temp );
                    ch = '\0';
                } // if
                else {
                    Mission_3( temp );
                    ch = '\0';
                } // else
            } // if
            else { // Mission_2
                printf( "Input length :\n" );
                do {
                    scanf( "%d", &temp );
                    ch = getchar();
                    while ( ch != '\n' ) ch = getchar();
                } while( ch != '\n' || temp == 2147483647 );
                
                if ( temp == 2147483647 ) continue; // scanf要int但user直接塞非數字字元
                while ( temp < 2 || 9 < temp ) {
                    printf( "### It is NOT in [2,9] ###\n" );
                    scanf( "%d", &temp );
                } // while
                
                Mission_2( temp );
                ch = '\0';
            } // else
        } // else
    } while ( num != 0 );
    
    return 0;
} // main()

void Menu() {
    printf( "\n" );
    printf( "** Permutation Generator **\n" );
    printf( "* 0. Quit                 *\n" );
    printf( "* 1. N numbers from 1..N  *\n" );
    printf( "* 2. M numbers from input *\n" );
    printf( "* 3. M numbers from 1..9  *\n" );
    printf( "***************************\n" );
    printf( "Input a choice(0, 1, 2, 3):\n" );
    printf( "\n" );
} // Menu()

void Swap( IntPtr A, IntPtr B ) { // call by address
    int temp = *A;
    *A = *B;
    *B = temp;
} // Swap()

int Fac( int num ) { // factorial
    if ( num == 0 ) return 1;
    return num * Fac( num - 1 );
} // Fac()

bool Is_Repeat( int i, int str[], int temp, int len ) { // check is repeated or not
    bool is_repeat = false;
    for ( int j = 0; j < i; j++ ) {
        if ( str[j] == temp ) {
            printf( "### Duplicate! Still need %d numbers! ###\n", len - i );
            is_repeat = true;
            break;
        } // if
    } // for
        
    return is_repeat;
} // Is_Repeat()

void Permute1( int str[], int head, int tail ) {
    if ( head == tail ) {
        printf( "[%d]", gcount );
        for ( int i = 0; i <= tail; i++ ) printf( " %d", str[i] );
        printf( "\n" );
        gcount++;
    } // if
    else {
        for ( int flag = head; flag <= tail; flag++ ) {
            Swap( ( str + head ), ( str + flag ) ); // swap str's index
            Permute1( str, head + 1, tail );
            Swap( ( str + head ), ( str + flag ) ); // recover str's index
        } // for
    } // else
} // Permute1()

void Permute2( int str[], int head, int tail ) {
    if ( head == tail ) {
        for ( int i = 0; i <= tail * 9; i++ ) {
            printf( "[%d]", gcount );
            for ( int j = 0; j <= tail; j++ ) printf( " %d", str[j] );
            printf( "\n" );
            gcount++;
        } // for
    } // if
    else {
        for ( int flag = head; flag <= tail; flag++ ) {
            Swap( ( str + head ), ( str + flag ) );
            Permute2( str, head + 1, tail );
            Swap( ( str + head ), ( str + flag ) );
        } // for
    } // else
} // Permute2()

void Mission_1( int inp ) {
    // generate string
    int str[inp] = {0};
    for ( int i = 0; i < inp; i++ ) str[i] = i + 1;
    // permutation
    Permute1( str, 0, inp - 1 ); // string, start, end
    // others
    int factorial = Fac( inp );
    printf( "Mission 1: %d permutations\nL = %d\n", factorial, inp );
} // Mission_1()

void Mission_2( int len ) {
    // generate string
    int i = 0;
    int temp = 2147483647;
    int str[len] = {0};
    char ch = '\0';
    printf( "Input numbers :\n" );
    do {
        scanf( "%d", &temp );
        ch = getchar();
        while ( ch != '\n' ) ch = getchar();
    } while ( ch != '\n' || temp == 2147483647 );
    
    while ( i < len ) {
        if ( temp == 2147483647 ) ch = '\n'; // Do nothing, 只是為了跳到if ( str[i] == 0 )
        else if ( temp < 1 || 999999 < temp ) printf( "### It is NOT in [1,999999] ###\n" ); // 越界
        else if ( ! Is_Repeat( i, str, temp, len ) ) {
            str[i] = temp; // 沒有重複
            i++;
        } // else if
        
        if ( str[i] == 0 ) {
			if ( temp == str[len - 1] ) break;
            do {
                temp = 2147483647;
                scanf( "%d", &temp );
                ch = getchar();
                while ( ch != '\n' ) ch = getchar();
            } while ( ch != '\n' );
        } // if
    } // while
    
    // timer、permute
    clock_t on, off;
    on = clock();
    Permute1( str, 0, len - 1 ); // string, start, end
    off = clock();
    // others
    int factorial = Fac( len );
    double t = off - on;
    printf( "Mission 2: %d permutations\nT = %.0f ms\n", factorial, t );
} // Mission_2()

void Mission_3( int inp ) {
    // generate string
    int str[inp] = {0};
    for ( int i = 0; i < inp; i++ ) str[i] = i + 1;
    // timer、permute
    clock_t on, off;
    on = clock();
    Permute2( str, 0, inp - 1 );
    off = clock();
    // others
    int factorial = Fac( 9 ) / Fac( 9 - inp );
    double t = off - on;
    printf( "Mission 3: %d permutations\nT = %.0f ms\n", factorial, t );
} // Mission_3()