/*
	Live Server on port 7465
*/
#include<io.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	int continuer = 1;
	char *message, mc;

	printf("Avant de commencer, ce jeu utilise le terminal Microsoft Telnet pour fonctionner, pour pouvoir jouer veuillez activer le terminal dans le panneau de configuration et le lancer\n Pour commencer appuyez sur ENTREE");
	getchar();
	system("cls");

    printf("5 fevrier 2020, Vous etes detective et vous enquetez sur un nouveau cas de meurtre");
    getchar();
    printf("Le rapport montre le profil d'une femme de 26 ans, enceinte de 3 mois. Elle etait chanteuse independante et chantais dans quelques bars du quartier");
    getchar();
    printf("Pas de piste pour le moment il faut donc chercher parmi les temoignages, heureusement ces derniers sont enregistres dans une base de donnees mais il nous faut un port de connexion");
    getchar();
    printf("Mais pas de panique, en cas de perte l'administrateur a laisse une note permettant de retrouver le port");
    getchar();
    printf("\"note de l'admin : \n Si quelqu'un oublie le port, deja felicitation (sarcasme) puis voici l'enigme, (Bananes, Kiwi, Fraise, Pomme) sur ce bonne salade de fruits. \n PS : Essayer de ne pas oublier le port cette fois ci\"");
    getchar();


	printf("\nInitialisation de la connection...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Connection initialisee.\n");
	printf("Sur le terminal Telnet veuillez entrer la commande de connexion (o localhost <port>)\n");

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	//printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 7465 );

	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//puts("Bind done");

	//Listen to incoming connections
	listen(s , 3);

	//Accept and incoming connection
	puts("En attente de la connection.. ");

	c = sizeof(struct sockaddr_in);

	while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
	    system("cls");
		puts("Connection etablie\n");

		//Reply to the client

		message = "Bienvenue sur la base de donnees des temoignages\r\n\n";
		send(new_socket , message , strlen(message) , 0);
        fflush(stdin);
		printf("Ok, La connexion est etablie, pour acceder a un temoignage entrez un mot-cle pour trouver des correspondances\r\n les verbe doivent etre mis a l'infinitif, pour porter une accusation tapez \"guess\"\n");
		message = ("1er profil :\r\n Conjoint de la victime 30 ans \r\n gerant d’un rayon fruits et legumes de supermarche \r\n\r\n  La derniere fois que je l ai vu c etait a l appartement. On revenait de l echographie des trois mois, on etait si heureux ou en tout cas moi je l etais. Elle semblait un peu triste. Je pensais que c etait parce qu elle avait rate son entrevu avec un producteur.\r\n\r\n\r\n");
        send(new_socket , message , strlen(message) , 0);
        message = ("2eme profil :\r\n Meilleur ami de la victime 25 ans \r\n Etudiant \r\n\r\n  Le soir de sa mort, j etais chez moi. Je ne faisais que regarder la tele.\r\n\r\n\r\n");
        send(new_socket , message , strlen(message) , 0);
        message = ("3eme profil :\r\n Femme 23 ans \r\n Chanteuse/Musicienne Independante \r\n\r\n  Oui j etais au bar, j ai chante juste apres elle. Je la connais a peine, je ne savais m eme pas qu elle attendait un bebe. \r\n\r\n\r\n");
        send(new_socket , message , strlen(message) , 0);
        while(continuer == 1)
        {
            while(strcmp(&mc,"guess") != 0)
            {
                printf("Mot-cle : ");
                scanf("%s",&mc);
                fflush(stdin);

                if(strcmp(&mc,"triste") == 0)
                {

                                message = "Meilleur Ami : \r\n\r\n Oui ces temps-ci, elle etait triste. En tout cas elle semblait tres triste. Elle ne sortait plus beaucoup de chez elle. Pour moi c est son conjoint qui la retenait chez eux. Il etait tres colerique. \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }

                if((strcmp(&mc,"bar") == 0)||(strcmp(&mc,"soiree") == 0))
                {

                                message = "Conjoint : \r\n\r\n Normalement, ce soir-la au bar, un chercheur de talent devait  etre present. Elle etait stressee avant de partir car une autre femme la menaçait et l intimidait en lui disant qu elle n avait aucun talent et qu elle ne decrocherait pas l offre du chercheur de talent. \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"bebe") == 0)||(strcmp(&mc,"enfant") == 0))
                {

                                message = "Conjoint : \r\n\r\n OUI ! J etais au courant que l enfant n etait pas de moi. Je ne l ai pas specifie car on avait decide de faire abstraction de ce detail.  \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"colere") == 0)||(strcmp(&mc,"tromperie") == 0)||(strcmp(&mc,"tromper") == 0))
                {

                                message = "Conjoint : \r\n\r\n Bien sûr que j etais en colere et que j aurais toujours ete en colere contre elle de m avoir trahi mais je l aimais et j aimais cet enfant.  \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"violent") == 0)||(strcmp(&mc,"pere") == 0))
                {

                                message = "Meilleur Ami : \r\n\r\n Il nous en voulait. Quand il a appris que j etais le pere il a commence a  etre violent envers moi et envers elle. Il ne faisait que de dire qu il l aimait mais il montrait le contraire.  \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"tromperie") == 0)||(strcmp(&mc,"tromper") == 0||(strcmp(&mc,"distance") == 0)))
                {

                                message = "Meilleur Ami : \r\n\r\n Elle ne me parlait plus depuis quelque semaine. Elle me rejetait et m en voulait. C est vrai que c est un peu ma faute qu on ait couchee ensemble, c est d ailleurs pour ça que je n etais pas au bar avec elle. Elle ne voulait plus de moi dans sa vie.  \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"mur") == 0)||(strcmp(&mc,"verre") == 0))
                {

                                message = "Meilleur Ami : \r\n\r\n Bien sur que quand elle m a dit qu elle ne voulait plus de moi dans sa vie ça m a mis en rogne. Cet enfant etait le mien et je voulais  etre la pour lui ! Je ne l ai jamais blesse au bar, je visais les murs et non elle ! J etais juste tres en colere mais jamais je ne lui aurais fait du mal.   \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"menacer") == 0)||(strcmp(&mc,"intimider") == 0))
                {

                                message = "Chanteuse : \r\n\r\n Je ne la menaçais pas. J essayais de la destabiliser. Elle etait douee, elle avait une magnifique voix. J etais juste jalouse d elle, mais jamais je lui aurais fait du mal. Demandez au barman, je ne l ai jamais touche ni violente   \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if((strcmp(&mc,"bar") == 0)||(strcmp(&mc,"harceler") == 0))
                {

                                message = "Chanteuse : \r\n\r\n La semaine derniere, un homme completement bourrer est venu la harceler. Il n arr etait pas de crier qu il etait le vrai pere, qu il meritait d  etre present pour l enfant. Il a balance plein de verre contre les murs, c etait SUPER dangereux.   \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }
                if(strcmp(&mc,"barman") == 0)
                {

                                message = "Barman : \r\n\r\n Effectivement elles ne se sont pas violentees ce soir la cependant elle avait l air triste ce soir-la aussi. Elle est rentree un peu plus longtemps que d habitude. Elle s est pris quelques shoots et deux ou trois bieres.   \r\n\r\n\r\n";
                                send(new_socket , message , strlen(message) , 0);

                }

            }
            printf("Indiquez le nom de la personne que vous croyez etre le/la coupable : \n");
            scanf("%s", &mc);
            fflush(stdin);

            if(strcmp(&mc, "victime") == 0)
            {
                printf("Felicitation vous avez vu juste,");
            }
            else
            {
                printf("Malheureusement ce n'est pas la bonne reponse, voullez vous connaitre la verite ou continuer a chercher ? Oui(1) Non(2) : ");
                scanf("%d",&continuer);
            }

        }
        printf("la victime s'est suicidee. Apres les violences de son conjoint, la proximite excessive de son meilleur ami et les intimidations de l autre chanteuse, la victime est tombee dans une profonde depression. Apres les quelques verres bu au bar, la victime est sortie dans la rue et est montee sur des echafaudages. Apres quelques larmes coulees,  elle a saute et s est fracassee le crane contre un parpaing.");

	}

	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
		return 1;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
