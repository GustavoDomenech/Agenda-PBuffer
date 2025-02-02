#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void *pBuffer = NULL;

void clearScreen () {
    system( CLEAR );
}

void printMenu () {
    

printf( "--------------------------\n"
    "|         *MENU*         |\n"
    "|  1- Adicionar Pessoa   |\n"
    "|  2- Remover Pessoa     |\n"
    "|  3- Buscar Pessoa      |\n"
    "|  4- Listar todos       |\n"
    "|  5- Sair               |\n"
    "--------------------------\n"
    "O que deseja fazer? " );
}

void addPerson () {
    printf ( "Nome: " );
    fgets ( ( char * ) pBuffer + 1000, 100, stdin );
    ( ( char * ) pBuffer + 1000 ) [ strcspn ( ( char * ) pBuffer + 1000, "\n" ) ] = 0;

    printf ( "Idade: " );
    fgets ( ( char * ) pBuffer + 1100, 100, stdin );
    *( int * ) ( ( char * ) pBuffer + 1100 ) = atoi ( ( char * )pBuffer + 1100 );


    printf ( "Email: " );
    fgets ( ( char * ) pBuffer + 1200, 100, stdin );
    ( ( char * ) pBuffer + 1200 ) [strcspn ( ( char * ) pBuffer + 1200, "\n" ) ] = 0;

    *( size_t * ) ( ( char * ) pBuffer + 1300 ) = strlen( ( char * ) pBuffer + 1000 ) + 1;
    *( size_t * ) ( ( char * ) pBuffer + 1400 ) = strlen ( ( char * ) pBuffer + 1200 ) + 1;
    *( size_t * ) ( ( char * ) pBuffer + 1500 ) = *( size_t * ) ( ( char * ) pBuffer + 1300 ) + sizeof( int ) + *( size_t * ) ( ( char * ) pBuffer + 1400 );

    pBuffer = realloc ( pBuffer, *( size_t * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1500 ) + sizeof ( size_t ) );
    if ( !pBuffer ) {
        perror ( "Falha ao realocar memoria" );
        exit (EXIT_FAILURE);
    }

    // Copia os dados para o final do buffer
    memcpy ( ( char * ) pBuffer + sizeof ( size_t ) + *( size_t * ) pBuffer, ( char * ) pBuffer + 1000, *( size_t * ) ( ( char * ) pBuffer + 1300 ) );
    memcpy ( ( char * ) pBuffer + sizeof ( size_t ) + *( size_t * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1300 ), ( char * ) pBuffer + 1100, sizeof ( int ) );
    memcpy ( ( char * ) pBuffer + sizeof ( size_t ) + *( size_t * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1300 ) + sizeof ( int ), ( char * ) pBuffer + 1200, *( size_t * ) ( ( char * ) pBuffer + 1400 ) );

    // Atualiza o tamanho total do buffer
    *( size_t * ) pBuffer += *( size_t * ) ( ( char * ) pBuffer + 1500 );

    printf ( "Pessoa adicionada com sucesso!\n\nPressione Enter para continuar..." );
    getchar ();
    clearScreen ();
}

void searchPerson() {
    if ( !pBuffer || *( size_t * ) pBuffer == 0 ) {
        printf ( "Agenda vazia!\n\nPressione Enter para continuar..." );
        getchar ();
        clearScreen ();
        return;
    }
   
    printf ( "Nome da pessoa a ser buscada: ");
    fgets ( ( char * ) pBuffer + 1000, 100, stdin );
    ( ( char * ) pBuffer + 1000 ) [ strcspn ( ( char * ) pBuffer + 1000, "\n" ) ] = 0;

    *( int * ) ( ( char * ) pBuffer + 1700 ) = 0;

    *( size_t * ) ( ( char * ) pBuffer + 1600 ) = sizeof ( size_t );
    while (* ( size_t * ) ( ( char * ) pBuffer + 1600 ) < *( size_t * ) pBuffer + sizeof ( size_t ) ) {
        if ( strcmp ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ), ( char * ) pBuffer + 1000 ) == 0 ) {

            printf ( "Pessoa encontrada:\n" );
            printf ( "Nome: %s\n", ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) );
            printf ( "Idade: %d\n", *( int * ) ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 ) );
            printf ( "Email: %s\n", ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) + strlen ( ( char * ) pBuffer + * ( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof ( int ) );
            printf ( "\nPressione Enter para continuar..." );
            getchar ();
            clearScreen ();

            *(int *) ( ( char * ) pBuffer + 1700 ) = 1;
            break;
        }

        *( size_t * ) ( ( char * ) pBuffer + 1600 ) += strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1; // Nome
        *( size_t * ) ( ( char * ) pBuffer + 1600 ) += sizeof ( int ); // Idade
        *( size_t * ) ( ( char * )pBuffer + 1600 ) += strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1; // Email
    }

    if ( *( int * ) ( ( char * ) pBuffer + 1700 ) == 0 ) {
        printf ( "Pessoa nao encontrada! Pressione Enter para continuar..." );
        getchar ();
        clearScreen ();
    }
}

void removePerson () {
    if ( !pBuffer || *(size_t *)pBuffer == 0 ) {
        printf ( "Agenda vazia\n\nPressione Enter para continuar..." );
        getchar ();
        clearScreen ();
        return;
    }

    printf ( "Nome da pessoa a ser removida: " );
    fgets ( ( char * ) pBuffer + 1000, 100, stdin );
    ( ( char * ) pBuffer + 1000 ) [ strcspn ( ( char * ) pBuffer + 1000, "\n" ) ] = 0;

    *( size_t * ) ( ( char * ) pBuffer + 1600 ) = sizeof ( size_t );
    while ( *( size_t * ) ( ( char * ) pBuffer + 1600 ) < * ( size_t * ) pBuffer + sizeof ( size_t ) ) {
        if ( strcmp ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ), ( char * ) pBuffer + 1000 ) == 0 ) {

            *( size_t * ) ( ( char * ) pBuffer + 1700 ) = strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1;
            *( size_t * ) ( ( char * ) pBuffer + 1800 ) = strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) + *( size_t * ) ( ( char * ) pBuffer + 1700 ) + sizeof ( int ) ) + 1;
            *( size_t * ) ( ( char * ) pBuffer + 1900 ) = *( size_t * ) ( ( char * ) pBuffer + 1700 ) + sizeof ( int ) + * ( size_t * ) ( ( char * ) pBuffer + 1800 );

            memmove( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ), ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) + *( size_t * ) ( ( char * ) pBuffer + 1900 ), 
            *( size_t * ) pBuffer + sizeof ( size_t ) - * ( size_t * ) ( ( char * ) pBuffer + 1600 ) - *( size_t * ) ( ( char * )pBuffer + 1900 ) );
            *( size_t * ) pBuffer -= *( size_t * ) ( ( char * ) pBuffer + 1900 );
            pBuffer = realloc ( pBuffer, *( size_t * ) pBuffer + sizeof ( size_t ) );
            if ( !pBuffer && *( size_t * ) pBuffer > 0 ) {
                perror ( "Falha ao realocar memória" );
                exit(EXIT_FAILURE);
            }
            printf ( "Pessoa removida com sucesso!\n\nPressione Enter para continuar..." );
            getchar ();
            clearScreen ();
            return;
        }
        * ( size_t * ) ( ( char * ) pBuffer + 1600 ) += strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof ( int ) + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 )
        + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof( int ) ) + 1;
    }

    printf( "Pessoa nao encontrada!\n\nPressione Enter para continuar..." );
    getchar ();
    clearScreen ();
}

void listAll () {
    if ( !pBuffer || *( size_t * ) pBuffer == 0 ) {
        printf( "Agenda vazia!\n\nPressione Enter para continuar..." );
        getchar ();
        clearScreen ();
        return;
    }

    *( size_t * ) ( ( char * ) pBuffer + 1600 ) = sizeof ( size_t );
    while ( *( size_t * ) ( ( char * ) pBuffer + 1600 ) < *( size_t * ) pBuffer + sizeof ( size_t ) ) {
        printf( "***************************************\n" );
        printf( "Nome: %s\n", ( char * ) pBuffer + * ( size_t * ) ( ( char * ) pBuffer + 1600 ) );
        printf( "Idade: %d\n", *( int * ) ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 ) );
        printf( "Email: %s\n", ( char * ) pBuffer + * ( size_t * ) ( ( char * ) pBuffer + 1600 ) + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof ( int ) );
        *( size_t * ) ( ( char * ) pBuffer + 1600 ) += strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof ( int ) + strlen ( ( char * ) pBuffer + *( size_t * ) ( ( char * ) pBuffer + 1600 ) 
        + strlen ( ( char * ) pBuffer + * ( size_t * ) ( ( char * ) pBuffer + 1600 ) ) + 1 + sizeof ( int ) ) + 1;
        printf( "***************************************\n" );
    }

    printf( "\nPressione Enter para continuar..." );
    getchar ();
    clearScreen ();
}

int main () {
    pBuffer = malloc (sizeof ( size_t ) + 4000 );
    if ( !pBuffer ) {
        perror( "Falha ao alocar memoria" );
        return EXIT_FAILURE;
    }

    *( size_t * ) pBuffer = 0;

    while ( 1 ) {
        printMenu ();

        fgets ( ( char * ) pBuffer + 2000, 100, stdin );
        *( int * ) ( ( char * ) pBuffer + 2100 ) = atoi ( ( char * ) pBuffer + 2000 );

        switch ( *( int * ) ( ( char * ) pBuffer + 2100 ) ) {
            case 1:
                addPerson ();
                break;
            case 2:
                removePerson ();
                break;
            case 3:
                searchPerson ();
                break;
            case 4:
                listAll ();
                break;
            case 5:
                printf( "Saindo...\n" );
                free( pBuffer );
                return 0;
            default:
                printf( "Escolha invalida!\n\nPressione Enter para continuar..." );
                getchar();
                clearScreen();
        }
    }
}