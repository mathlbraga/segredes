#include <stdlib.h>	 // exit()
#include <errno.h>
#include <stdio.h>        // printf(), perror()
#include <sys/types.h>    // AF_INET, SOCK_STREAM
#include <sys/socket.h>   // socket(), connect()
#include <netinet/in.h>   // struct sockaddr_in
#include <arpa/inet.h>    // htons(), inet_addr()
#include <unistd.h>       // close()

#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
#include <netdb.h>


/* início do programa */

int main(int argc, char **argv[])
{
    int incremento;
    int sock;
    int conexao;
    int inicio = 0;
    int final = 65000;
    int portas = 0;

    char * endereco;

    struct sockaddr_in addr_destino;

    if (argc > 1)
    {
        endereco = argv[1];
    }

    if (argc == 1)
    {
        printf("__________________________________________\n");
	    printf("..........................................\n");
        printf("...... PortScanner TCP Connect v1.0 ......\n");
        printf("..........................................\n");
        printf("...... CST em Redes de Computadores ......\n");
        printf("..... Segurança de Redes e Sistemas ......\n");
        printf("..........................................\n");
        printf("..... Prof. Matheus Lorenzato Braga ......\n");
        printf("..........................................\n");
        printf("__________________________________________\n");
    	printf("..........................................\n");
        printf(".......... Uso: postscan <host> ..........\n");
        printf("..........................................\n");
        exit(0);
    }

    printf("Verificando %s. Porta inicial: %d Porta final: %d\n", endereco, inicio, final);
    for (incremento = inicio; incremento < final; incremento++)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        addr_destino.sin_family = AF_INET;
        addr_destino.sin_port = htons(incremento);
        addr_destino.sin_addr.s_addr = inet_addr(endereco);
        bzero(&(addr_destino.sin_zero), 8);

        conexao = connect(sock, (struct sockaddr *)&addr_destino, sizeof(addr_destino));

        if (conexao < 0)
        {
            close(conexao);
            close(sock);
        }
        else
        {
	    portas = portas + 1;
            printf("Porta: %d - STATUS [ABERTA] \n", incremento);
            close(conexao);
            close(sock);
        }
    }
    printf(".....Total de portas encontradas: %d .......\n", portas);
    return 0;
}