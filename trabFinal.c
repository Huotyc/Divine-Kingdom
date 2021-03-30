/**
Jorge Gabriel de Oliveira Medeiros 
Pedro Henrique Resende Marques     
Savio moreira garcia da silva     
Taynara Diniz Moreira de Souza     
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define HP_MAX 35;

int tipoInimigo[10]; //cada tipo de inimigo que foi morto
int contadorGlobal = 0;  //variavel usada pra alocar de forma correta cada tipo de inimigo morto
int contadorFraco = 0;   //variavel usada pra lutar contra oponentes mais fortes
int jPO = 50; //Jogador Peças de Ouro inicial
int jPop = 0;     //popções que o jogador tem
static char item[5][50] = {" " , " " , " " , " "}; // Inventario inicial do jogador
int compInventario[4]; //vai armazenar o valor da comparação do inventario, para ver se o item é utilizavel ou não
int compInventarioQuebrado[4];
int cidade;  //Cidade em que o jogador está
int cidadeIs; //Jogador está ou não em uma cidade? 1== true 0 == falso


struct infoJ //info Jogador
{
    int atk;
    int def;
    int vel;
    int hp;
    float carry;//limite de carga 10.50
};

struct infoJ JogadorDados;//informações do jogador

struct infoO //informação Oponente
{
    char    nome[100];
    int     atk;
    int     hp;
    int     vel;
    int     gold;//PO dropado pela morte do oponente
};

struct local // Informações do lugar em que o jogador está 
{
    int loja;   //chama outra fun
    int taverna; //chama outra fun
    char nome[20];

};

struct local lugar[5];

struct infoO inimigo[10];

int rnJesusEsc ()//retorna um numero aleatorio que define a escolha do oponente
{
    int sort;
    srand (time(NULL));
    sort = rand() % 11;
    return sort;
}


int rnJesusOpo (int n) //retorna um número aleatório até 3, que é usado na função de batalha, para decidir qual oponente o jogador vai enfrentar, indo de 1 - 4
{
    int sort;
    srand(time(NULL));
    sort = rand() % n;
    return sort;
} 

int rnJesusCrit () //retorna um número que diz se o ataque é crítico ou não
{
    srand(time(NULL));
    return rand() % 6;
}

void inimigoInfo () //setagem das informações do inimigo
{

    strcpy(inimigo[0].nome , "Lobo");
    inimigo[0].atk =    3;
    inimigo[0].hp =     5;
    inimigo[0].vel =    3;
    inimigo[0].gold =   15;

    strcpy(inimigo[1].nome , "Bandido");
    inimigo[1].atk =    4;
    inimigo[1].hp =     10;
    inimigo[1].vel =    2;
    inimigo[1].gold =   35;

    strcpy(inimigo[2].nome , "Slime");
    inimigo[2].atk =    1;
    inimigo[2].hp =     5;
    inimigo[2].vel =    0;
    inimigo[2].gold =   5;

    strcpy (inimigo[3].nome,"Gigante");
    inimigo[3].atk =    8;
    inimigo[3].hp =     20;
    inimigo[3].vel =    2;
    inimigo[3].gold =   100;

    strcpy (inimigo[4].nome,"Elfo");
    inimigo[4].atk =    4;
    inimigo[4].hp =     14;
    inimigo[4].vel =    6;
    inimigo[4].gold =   45;

    strcpy (inimigo[5].nome,"Goblin");
    inimigo[5].atk =    3;
    inimigo[5].hp =     17;
    inimigo[5].vel =    5;
    inimigo[5].gold =   30;

    strcpy (inimigo[6].nome,"Gnomo");
    inimigo[6].atk =    5;
    inimigo[6].hp =     13;
    inimigo[6].vel =    2;
    inimigo[6].gold =   20;

    strcpy (inimigo[7].nome,"Dragão");
    inimigo[7].atk =    9;
    inimigo[7].hp =     30;
    inimigo[7].vel =    6;
    inimigo[7].gold =   150;

    strcpy (inimigo[8].nome,"Mago");
    inimigo[8].atk =    5;
    inimigo[8].hp =     13;
    inimigo[8].hp =     2;
    inimigo[8].gold =   35;

    strcpy (inimigo[9].nome,"Izanagi - O rei Phoenix");
    inimigo[9].atk =    10;
    inimigo[9].hp =     200;
    inimigo[9].vel =    20;
    inimigo[9].gold =   1000;
}

void boasVindas(){
    char nome[50];
    int i;

    printf("Insira seu nome:\n");
    scanf(" %[^\n]s", nome);
    puts("\n\n");
    puts("******************************");
    puts("*        BEM-VINDO AO        *");
    puts("*       DIVINE KINGDOM       *");
    puts("******************************");
    puts("\n\n");
    usleep(500000);

    printf("%s aprecie o jogo!!!\n", nome);
    for(i = 0; i < 30; i++){
        printf(".");
        fflush(stdout);
        usleep(59990);
    }
    printf("\n");
    puts("Voce acorda na porta de uma caverna, com suas roupas meio queimadas e cansado."
    	"\nVoce ouve barulhos estranhos vindos da caverna e vai para a cidade...");
}

void izanagi ()
{
    inimigoInfo();
    int i;
    int opt;//1 = atk, 2 = def, 3 = fugir, 4 usar itens
    int rand;
    int enemyDef; //1 == inimigo está se defendendo, 0 == inimigo não está se defendendo
    int jDef;     //1 == jogador está se defendendo, 0 == jogador não está se defendendo
    int jCrit;    //3 == dano crítico               , qualquer outro número, dano normal
    int enemyCrit;//3 == dano crítico               , qualquer outro número, dano normal
    int fimDaLuta;//1 == 


    puts ("Finalmente voce veio ate mim...");

    do {

        puts ("\nO que vai fazer?\n\n1 - Atacar o oponente\n2 - Defender-se\n4 - Usar um item\n5- Usar uma popcao de cura");
        scanf ("%d",&opt);
    switch (opt)
    {
        case 1://ataque
        {
            jCrit = rnJesusCrit();

            if (enemyDef == 0 && jCrit != 3)//inimigo não defendeu, ataque não foi crítico 
            {
                printf ("E ISSO QUE VOCES MORTAIS DIZEM QUE E MACHUCAR ALGUEM? PATETICO!\n",JogadorDados.atk);
                inimigo[9].hp -= JogadorDados.atk;
            } else if (enemyDef == 1 && jCrit != 3)//inimigo defendeu, ataque não crítico
            {
                printf ("EU JA SEI CADA PASSO QUE VOCE VAI DAR, MORTAL, VOCE NAO CONSEGUIRA ME DERROTAR!\n");
                inimigo[9].hp = inimigo[9].hp -= JogadorDados.atk / 2;

            }else if (enemyDef == 1 && jCrit == 3)//inimigo defendeu, ataque crítico
            {
                printf ("VOCE NAO CONSEGUIRA ME MACHUCA- M-MAS O QUE E ISSO?!",JogadorDados.atk * 2);
                inimigo[9].hp -= JogadorDados.atk * 2;
            
            }else if (enemyDef == 0 && jCrit == 3) 
            {
                printf ("AAAAAAAAAAAAAAAAAAAAA!\n",JogadorDados.atk * 2);
                inimigo[9].hp -= JogadorDados.atk * 2;
            }
            jDef = 0;
            enemyDef = 0;
        }
        break;
        case 2://defesa
        {
            printf ("Você assume uma posição defensiva, recebendo menos dano próxima rodada!\n");
            jDef = 1;
        }

        break;
        case 3://fuga
        {
            printf ("Você tenta fugir!\n");
        
            puts ("*Izanagi bafora*, VOCE QUER MESMO FUGIR DE MIM? O DEUS DO FOGO? HAH, PATETICO..");
        }
        break;
        case 4://usar item
        {
            int usar_item;  
            printf("Escolha o item que deseja usar: \n1-%s\n2-%s\n3-%s\n4-%s\n ", item[0],item[1],item[2],item[3]);
            scanf("%d", &usar_item);
            
            // item 1
            if(usar_item == 1)
            {
                compInventario[0] = strcmp (item[0]," ");
                compInventarioQuebrado[0] = strcmp (item[0],"Item quebrado");

                if (compInventario[0]== 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[0] == 0 ) printf ("Voce nao pode usar um item quebrado!\n");
                else 
                {
                    printf("Voce usou o item %s\n", item[0]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+2);
                    inimigo[9].hp -= (JogadorDados.atk+2);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 2 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[0], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    
                    }
                }
            }
            // item 2
            else if(usar_item == 2)
            {
                compInventario[1] = strcmp (item[1]," ");
                compInventarioQuebrado[1] = strcmp (item[1],"Item quebrado");
                if (compInventario[1]== 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[1] == 0)printf ("Voce nao pode usar um item quebrado");
                else 
                { 
                    printf("Voce usou o item %s\n", item[1]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+4);
                    inimigo[9].hp -= (JogadorDados.atk+4);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 4 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[1], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    break;
                    
                    }
                }
            } 
            // item 3
            else if(usar_item == 3)
            {
                compInventario[2] = strcmp (item[2]," ");
                compInventarioQuebrado[2] = strcmp (item[2],"Item quebrado");

            if (compInventario[2] == 0 ) printf ("Slot vazio!\n");
            else if (compInventarioQuebrado[2] == 0) printf ("Voce nao pode usar um item quebrado!");
            else 
                {
                    printf("Voce usou o item %s\n", item[2]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+20);
                    inimigo[9].hp -= (JogadorDados.atk+20);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 20 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[2], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    
                    }
                }
            }
            // item 4
            else if(usar_item == 4)
            {
                compInventario[3] = strcmp(item[3]," ");
                compInventarioQuebrado[3] = strcmp(item[3],"Item quebrado");

                if (compInventario[3] == 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[3] == 0) printf ("Voce nao pode usar um item quebrado") ;
                else 
                {

                
                    printf("Voce usou o item %s\n", item[3]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+75);
                    inimigo[9].hp -= (JogadorDados.atk+75);
        
                }
        break;
        }


    }
        case 5: //uso da popção
        if (jPop > 0)
        {
            if (JogadorDados.hp < 35 && JogadorDados.hp >= 30)
            {
                JogadorDados.hp = 35;
            } 
            else if (JogadorDados.hp <= 30)
            {
                jPop--;
                JogadorDados.hp += 5;
                printf ("Voce agora esta com %d e com %d popcoes.\n",JogadorDados.hp,jPop);
            }
            else puts ("Crianca estupida, voce esta saudavel demais ao meu ver para sequer usar uma popcao..\n");
        }else puts ("Eu nao tenho mais popcoes!!!");
        break;
    }
    //fim das ações do Jogador
    if (JogadorDados.hp <=0 || inimigo[9].hp <=0)
    {
       printf ("\nO combate acabou e ");
       if (JogadorDados.hp <=0) 
        {
            printf ("%s saiu vitorioso!",inimigo[9].nome);
            fimDaLuta = 1;
            printf ("*Voce morre agonizando no chao, enquanto Izanagi ve voce de longe e ri.*\n");
            return 1;
            break;
        }
        else                     
        {
        
        printf ("Você saiu vitorioso!\n");
        printf ("*coff* *coff* Parabens crianca, voce chegou longe, nao passou pela minha cabeca que voce conseguiria um dia me matar, voce ganhou sua liberdade... *Izanagi se desintegra, deixando nada para tras*\n*E voce cai duro no chao, morto.*");
            fimDaLuta == 1;
        break;
        }     
     }

    if (fimDaLuta == 1) //fim da luta!
    {
        break;
    }

    rand = rnJesusEsc();//função responsável pelo oq o oponente vai fazer, com rand sendo par ele ataca, 
    enemyCrit = rnJesusCrit();

    if (fimDaLuta == 1) break;

    if (rand % 2 == 0 && jDef == 1) 
    {
        printf ("O oponente lhe atacou, mas você já esperava por isso!\n");

        if (JogadorDados.def * 2 >= inimigo[9].atk) printf (" E voce toma nada de dano, nada mal para uma criança!");
        else 
        {
            JogadorDados.hp -= JogadorDados.def * 2 - inimigo[9].atk;   
        }
    }

    else if (rand % 2 == 0 && enemyCrit == 3) 
    {
        printf ("Izanagi some, e alguns instantes depois, voce consegue ver ele descendo como uma aguia para atingi-lo, sem reacao, voce toma %d pontos de dano!\n",inimigo[9].atk * 2);
        JogadorDados.hp -= inimigo[9].atk * 2;
         
    }
    else if (rand % 2 == 0) 
    {
        printf ("Izanagi cospe uma labareda de chamas em voce, por pouco voce consegue escapar!\n",inimigo[9].atk);
        JogadorDados.hp -= inimigo[9].atk;
    }
    
    else 
    {
        printf ("Izanagi se cobre usando suas imensas asas, e apos alguns instantes, uma luz estonteante aparece!!\n");
        inimigo[9].hp += 3;
        enemyDef = 1;
    }

    if (JogadorDados.hp <=0 || inimigo[9].hp <=0)
    {
       printf ("\nO combate acabou e ");
       if (JogadorDados.hp <=0) 
        {
            printf ("%s saiu vitorioso!",inimigo[9].nome);
            fimDaLuta = 1;
            break;
        }
        else                     
        {
        
         printf ("Você saiu vitorioso!\n");
        printf ("*coff* *coff* Parabens crianca, voce chegou longe, nao passou pela minha cabeca que voce conseguiria um dia me matar, voce ganhou sua liberdade... *Izanagi se desintegra, deixando nada para tras*\n*E voce cai duro no chao, morto.*");
            fimDaLuta == 1;
        break;
        break;
        }     
     }
    if (fimDaLuta == 1) break;
    printf ("\nSeu Hp é de: %d\nO do seu oponente é: %d\n",JogadorDados.hp,inimigo[9].hp);
        printf ("Fim de jogo.\n");
        return 1;
    }while (1);

}

void batalha(int idInimigo) 
{
    inimigoInfo();
    int i;
    int opt;//1 = atk, 2 = def, 3 = fugir, 4 usar itens
    int rand;
    int enemyDef; //1 == inimigo está se defendendo, 0 == inimigo não está se defendendo
    int jDef;     //1 == jogador está se defendendo, 0 == jogador não está se defendendo
    int jCrit;    //3 == dano crítico               , qualquer outro número, dano normal
    int enemyCrit;//3 == dano crítico               , qualquer outro número, dano normal
    int fimDaLuta;//1 == 

    if (contadorGlobal > 30) 
    {
        puts ("Voce sente algo lhe chamando, e vai atras para tentar descobrir o que e..."
        	"\nVoce ve uma luz e começa a sentir calor cada vez mais que se aproxima dessa voz,"
        	"\nao chegar perto o suficiente voce ve a figura de uma fenix...");

        izanagi();
        
    }

    printf ("Você se depara com um %s!\n",inimigo[idInimigo].nome);

    do {

        puts ("\nO que vai fazer?\n\n1 - Atacar o oponente\n2 - Defender-se\n3 - Tentar fugir\n4 - Usar um item\n5- Usar uma popcao de cura");
        scanf ("%d",&opt);

    switch (opt)
    {
        case 1://ataque
        {
            jCrit = rnJesusCrit();

            if (enemyDef == 0 && jCrit != 3)//inimigo não defendeu, ataque não foi crítico 
            {
                printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk);
                inimigo[idInimigo].hp -= JogadorDados.atk;
            } else if (enemyDef == 1 && jCrit != 3)//inimigo defendeu, ataque não crítico
            {
                printf ("O oponente já esperava seu ataque, tomando dano reduzido!\n");
                inimigo[idInimigo].hp = inimigo[idInimigo].hp -= JogadorDados.atk / 2;

            }else if (enemyDef == 1 && jCrit == 3)//inimigo defendeu, ataque crítico
            {
                printf ("O oponente esperava seu ataque, mas não um acerto crítico! Você causa %d pontos de dano completamente negando a defesa do oponente!",JogadorDados.atk * 2);
                inimigo[idInimigo].hp -= JogadorDados.atk * 2;
            
            }else if (enemyDef == 0 && jCrit == 3) 
            {
                printf ("Você ataca, causando um dano crítico inesperado no seu oponente, por um total de %d pontos de dano!\n",JogadorDados.atk * 2);
                inimigo[idInimigo].hp -= JogadorDados.atk * 2;
            }
            jDef = 0;
            enemyDef = 0;
        }
        break;
        case 2://defesa
        {
            printf ("Você assume uma posição defensiva, recebendo menos dano próxima rodada!\n");
            jDef = 1;
        }

        break;
        case 3://fuga
        {
            printf ("Você tenta fugir!\n");
            if (JogadorDados.vel > inimigo[idInimigo].vel) 
            {
                printf ("E consegue!\n");
                fimDaLuta = 1;
                break;
            }
            else 
            {
                printf ("E falha, tomando %d pontos de dano!\n",inimigo[idInimigo].atk);
                JogadorDados.hp -= inimigo[idInimigo].atk;
            }
        }
        break;
        case 4://usar item
        {
            int usar_item;  
            printf("Escolha o item que deseja usar: \n1-%s\n2-%s\n3-%s\n4-%s\n ", item[0],item[1],item[2],item[3]);
            scanf("%d", &usar_item);
            
            // item 1
            if(usar_item == 1)
            {
                compInventario[0] = strcmp (item[0]," ");
                compInventarioQuebrado[0] = strcmp (item[0],"Item quebrado");

                if (compInventario[0]== 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[0] == 0 ) printf ("Voce nao pode usar um item quebrado!\n");
                else 
                {
                    printf("Voce usou o item %s\n", item[0]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+2);
                    inimigo[idInimigo].hp -= (JogadorDados.atk+2);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 2 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[0], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    
                    }
                }
            }
            // item 2
            else if(usar_item == 2)
            {
                compInventario[1] = strcmp (item[1]," ");
                compInventarioQuebrado[1] = strcmp (item[1],"Item quebrado");
                if (compInventario[1]== 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[1] == 0)printf ("Voce nao pode usar um item quebrado");
                else 
                { 
                    printf("Voce usou o item %s\n", item[1]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+4);
                    inimigo[idInimigo].hp -= (JogadorDados.atk+4);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 4 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[1], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    break;
                    
                    }
                }
            } 
            // item 3
            else if(usar_item == 3)
            {
                compInventario[2] = strcmp (item[2]," ");
                compInventarioQuebrado[2] = strcmp (item[2],"Item quebrado");

            if (compInventario[2] == 0 ) printf ("Slot vazio!\n");
            else if (compInventarioQuebrado[2] == 0) printf ("Voce nao pode usar um item quebrado!");
            else 
                {
                    printf("Voce usou o item %s\n", item[2]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+20);
                    inimigo[idInimigo].hp -= (JogadorDados.atk+20);
                    
                    //Probabilidade do item se quebrar durante a batalha
                    if(rand % 20 == 0)
                    {
                        printf("O item se quebrou\n");
                        strcpy(item[2], "Item quebrado");
                        
                    }
                    if(usar_item == 1){
                    printf ("Você nao pode mais usar esse item\n");
                    
                    }
                }
            }
            // item 4
            else if(usar_item == 4)
            {
                compInventario[3] = strcmp(item[3]," ");
                compInventarioQuebrado[3] = strcmp(item[3],"Item quebrado");

                if (compInventario[3] == 0) printf ("Slot vazio!\n");
                else if (compInventarioQuebrado[3] == 0) printf ("Voce nao pode usar um item quebrado") ;
                else 
                {

                
                    printf("Voce usou o item %s\n", item[3]);
                    printf ("Você ataca, causando %d pontos de dano no inimigo!\n",JogadorDados.atk+75);
                    inimigo[idInimigo].hp -= (JogadorDados.atk+75);
        
                }
        break;
        }


    }
        case 5: //uso da popção
        if (jPop > 0)
        {
            if (JogadorDados.hp < 35 && JogadorDados.hp >= 30)
            {
                JogadorDados.hp = 35;
            } 
            else if (JogadorDados.hp <= 30)
            {
                jPop--;
                JogadorDados.hp += 5;
                printf ("Voce agora esta com %d e com %d popcoes.\n",JogadorDados.hp,jPop);
            }
            else puts ("Crianca estupida, voce esta saudavel demais ao meu ver para sequer usar uma popcao..\n");
        }else puts ("Eu nao tenho mais popcoes!!!");
        break;
    }
    //fim das ações do Jogador 
    if (JogadorDados.hp <=0 || inimigo[idInimigo].hp <=0)
    {
       printf ("\nO combate acabou e ");
       if (JogadorDados.hp <=0) 
        {
            printf ("%s saiu vitorioso!",inimigo[idInimigo].nome);
            fimDaLuta = 1;
            printf ("*Voce morre agonizando no chao, em seu ultimo suspiro de vida, voce ve uma raposa flamejante*\n");
            return 1;
            break;
        }
        else                     
        {
        
        printf ("você saiu vitorioso!\n");
        printf ("Ganhando %d PO",inimigo[idInimigo].gold);
            fimDaLuta == 1;
            jPO += inimigo[idInimigo].gold;
            
            contadorFraco++;
            contadorGlobal++;
        break;
        }     
     }

    if (fimDaLuta == 1) //fim da luta!
    {
        break;
    }

    rand = rnJesusEsc();//função responsável pelo oq o oponente vai fazer, com rand sendo par ele ataca, 
    enemyCrit = rnJesusCrit();

    if (rand % 2 == 0 && rand == 10) 
    {
        printf ("O oponente tenta fugir...\n");

        if (inimigo[idInimigo].vel > JogadorDados.vel) 
        {
            puts ("E consegue!");
            fimDaLuta == 1;
            break;
        }else 
        {
            printf ("E falha, tomando %d pontos de dano de você por tentar fugir do conflito, isso não é educado >:(\n",JogadorDados.atk);
            inimigo[idInimigo].hp -= JogadorDados.atk;
        }
    }

    if (fimDaLuta == 1) break;

    else if (rand % 2 == 0 && jDef == 1) 
    {
        printf ("O oponente lhe atacou, mas você já esperava por isso!\n");

        if (JogadorDados.def * 2 >= inimigo[idInimigo].atk) printf (" E voce toma nada de dano :D, boa defesa criança!");
        else 
        {
            JogadorDados.hp -= JogadorDados.def * 2 - inimigo[idInimigo].atk;   
        }
    }

    else if (rand % 2 == 0 && enemyCrit == 3) 
    {
        printf ("O oponente lhe ataca de forma inesperada, , causando um dano crítico de: %d!\n",inimigo[idInimigo].atk * 2);
        JogadorDados.hp -= inimigo[idInimigo].atk * 2;
         
    }
    else if (rand % 2 == 0) 
    {
        printf ("O oponente lhe ataca, causando %d pontos de dano!\n",inimigo[idInimigo].atk);
        JogadorDados.hp -= inimigo[idInimigo].atk;
    }
    
    else 
    {
        printf ("O oponente assume posição defensiva, se preparando para seu próximo ataque que terá dano reduzido!\n");
        enemyDef = 1;
    }

    if (JogadorDados.hp <=0 || inimigo[idInimigo].hp <=0)
    {
       printf ("\nO combate acabou e ");
       if (JogadorDados.hp <=0) 
        {
            printf ("%s saiu vitorioso!",inimigo[idInimigo].nome);
            fimDaLuta = 1;
            break;
        }
        else                     
        {
        
        printf ("você saiu vitorioso!\n");
        printf ("Ganhando %d PO",inimigo[idInimigo].gold);
            
            jPO += inimigo[idInimigo].gold;
            fimDaLuta = 1;
            contadorFraco++;
            contadorGlobal++;
        break;
        }     
     }
    if (fimDaLuta == 1) break;
    printf ("\nSeu Hp é de: %d\nO do seu oponente é: %d\n",JogadorDados.hp,inimigo[idInimigo].hp);

    }while (1);

}

struct arma //informações da arma! 
{
    char nome[20];
    int tipo; //tipo 1= espada, 2= arco, 3= lança, 4= claymore 
    float peso;
    int dano;
    int price;
};

struct arma armas;

struct itensLoja //Armas na loja, e se a loja vende poções ou não
{
    struct arma armas[10];

    int hpp;//health poption
    int hppPrice;
};

void inventario(){
    
    int i;

    printf("\nInventario: \n");
    for(i=0; i<4; i++){    
    printf("\n\t %s", item[i]);
    
    }

    printf("\n");
}

void loja () //loja do jogo
{
    void inventario();
    
    struct itensLoja itens;
    itens.hpp       = 3;//quantidade de popções
    itens.hppPrice  = 5;//preço das popções
    
    int i;
    char escolha,confirm,opt;
    int poptionsQtd;    //quantidade de popções que o Player leva

    strcpy (itens.armas[0].nome , "Espada Curta");
    itens.armas[0].dano =   2;
    itens.armas[0].peso =   3.5;
    itens.armas[0].price =  10;
    itens.armas[0].tipo =   1;
    
    strcpy (itens.armas[1].nome, "Arco de Caca");
    itens.armas[1].dano =   4;
    itens.armas[1].peso =   2.5;
    itens.armas[1].price =  25;
    itens.armas[1].tipo =   2;

    strcpy (itens.armas[2].nome, "Lança do Deus Raijin");
    itens.armas[2].dano =   20;
    itens.armas[2].peso =   3.75;
    itens.armas[2].price =  250;
    itens.armas[2].tipo =   3;

    strcpy (itens.armas[3].nome, "Zangetsu, A rasga ceus");
    itens.armas[3].dano =   75;
    itens.armas[3].peso =   6;
    itens.armas[3].price =  750;
    itens.armas[3].tipo =   4;

    puts ("*Para sair da loja sem comprar nada, negue todas as ofertas de arma, e nao compre nenhuma popcao*");
    puts ("\nBem vindo a minha loja, o que deseja comprar?");

    puts ("\n");
    
    for ( i = 0; i < 2; i++) 
        {
        
            if (itens.armas[i].tipo == 1) printf ("Temos esse item: Um(a) %s bem versatil e afiada, pode lhe ser util, e como ela e bem afiada, causara %d pontos de dano, também e bem leve, pesando apenas %.1f e pela bagatela de: %d\n",itens.armas[i].nome,itens.armas[i].dano, itens.armas[i].peso, itens.armas[i].price);
            else if (itens.armas[i].tipo == 2) printf ("Temos esse %s: que pode ser bem util se voce não gosta de entrar em combate direto com seus oponentes, e bom, é um arco, ele machuca, logo, causara %d pontos de dano, pesando miseros %.1f, e pela bagatela de: %d\n",itens.armas[i].nome, itens.armas[i].dano, itens.armas[i].peso, itens.armas[i].price);
            
         if (contadorGlobal >= 15) printf ("Ahh essa lança, dizem as lendas que ela foi produzida ao som dos Taikos de Raijin, mas não tenho muita certeza, sei que ela parece bem dura e que causara a enorme quantia  de %d pontos de dano nos seus oponentes, e bom, aparenta ser uma lanca bem leve, acho que pesa uns %1.f, e so por causa da lenda, ela sai por %d\n",itens.armas[i].dano,itens.armas[i].peso,itens.armas[i].price);
            
         if (contadorGlobal >= 25) 
         {
            printf ("Ahh, essa claymore, eu gastei minha vida inteira nela, é meu motivo de viver, e seu nome é... %s, e um bom nome? Haha! Logico que e! Bom, te vendo ela por %d PO, sem mais nem menos. E toma cuidado se for levar ela em? Ela e bem pesada %1.f! Boa sorte crianca!\n",itens.armas[i].nome,itens.armas[i].price,itens.armas[i].peso);
            itens.armas[4].tipo = 4;
         }
        puts ("Vai levar? Y/N\n");
        scanf (" %c",&escolha);

        if (escolha == 'Y' || escolha == 'y') 
        {
            if (jPO >= itens.armas[i].price) //e ter slot vazio no inventario
            {

            jPO -= itens.armas[i].price;
            //infoJ
            printf ("Você adquiriu %s, seu saldo restante é de: %d PO\n",itens.armas[i].nome,jPO);
            
            //atualização do inventário começa aqui
            

            if(itens.armas[i].nome == itens.armas[0].nome){
              strcpy(item[0] , itens.armas[0].nome);
            } 
            else if(itens.armas[i].nome == itens.armas[1].nome){
                strcpy(item[1] , itens.armas[1].nome);
                    
            }else if(itens.armas[i].nome == itens.armas[2].nome){
                strcpy(item[1] , itens.armas[1].nome);
            }
            else if(itens.armas[i].nome == itens.armas[3].nome){
                strcpy(item[1] , itens.armas[3].nome);
            }
            else{
              strcpy(item[0] , itens.armas[0].nome);
              strcpy(item[1] , itens.armas[1].nome);
              strcpy(item[2] , itens.armas[2].nome);
              strcpy(item[3] , itens.armas[3].nome);
            }
            
          
            inventario();
            //e termina aqui

            if (itens.armas[i].tipo == 4) puts ("*Ao sair da loja voce da uma ultima olhada para tras, mas voce nao ve mais o velho, sem se preocupar muito, voce continua seu rumo com a Rompe-Ceus em maos..*");
            }else puts ("Voce parece que esta com a mochila cheia crianca, desculpe, mas e tolice vender isso para voce.\n");
        }
        else puts ("\nNão sabe o que está perdendo criança...\n");

    }
    
    i = 0;

    do 
    {
        if (i == 0)
        {
            printf ("\nE também tenho %d popções de cura, quantas vai levar? Cada uma por %d\n",itens.hpp,itens.hppPrice);
            printf("Coloque o valor desejado ou 0 para sair da loja\n");
            scanf ("%d",&poptionsQtd);
            if (poptionsQtd <= 0 ) break;
        }else 
        {
            printf ("\nTenho somente %d popções de cura, quantas vai levar? Cada uma por %d\n",itens.hpp,itens.hppPrice);
            printf("Coloque o valor desejado ou 0 para sair da loja\n");
            scanf ("%d",&poptionsQtd);
            if (poptionsQtd <= 0 ) break;
        }

    if (poptionsQtd >= 1 && poptionsQtd <= 3) 
    {
        if (poptionsQtd > itens.hpp )  
        {
            puts ("Isso é mais do que eu tenho no estoque");
            break;
        }

        printf ("Ok, isso vai dar %d PO\n", itens.hppPrice * poptionsQtd);
        
        if (jPO >= itens.hppPrice * poptionsQtd)
        {
            puts ("Tem certeza que quer comprar? (Y/N)\n");
            scanf (" %c",&confirm);
        
            if (confirm == 'Y' || confirm == 'y')
            {
        
                jPO -= itens.hppPrice * poptionsQtd;
                printf ("Você adquiriu %d popções, seu saldo restante é de: %d PO\n",poptionsQtd,jPO);
                itens.hpp -= poptionsQtd;
                jPop += poptionsQtd;

                if (itens.hpp <= 0) 
                {
                    printf ("Desculpa criança, não tenho mais popções, talvez meu fornecedor venha deixar mais depois..\n");
                    break;
                }
                
            }else        puts ("Boa sorte lá fora então criança!");    
        
        }else printf ("Você não tem dinheiro suficiente criança, eu sou dono de loja, não de centro de caridade! Você precisa de mais %d\n",itens.hppPrice * poptionsQtd);
        
    if (itens.hpp <= 0) printf ("Desculpa criança, não tenho mais popções, talvez meu fornecedor venha deixar mais depois..\n");
        
    }
    i++;
    }while(1);
    
}


void taverna ()         //Lugar onde o Jogador pode descansar e encher seu HP de graça
{
    puts ("\nVocê descansa e se sente restaurado!");
    JogadorDados.hp = HP_MAX;
    puts("*Já descansado, você sai da taverna e sente o sol brilhando em seu rosto o que lhe enche de determinação!*\n");
}

void citySaida () 
{
    puts ("Você sai da cidade! E vai rumo a caverna, que você sabe que existe na redondeza.\n");
    cidadeIs = 0;
    puts ("Ao entrar na caverna você não consegue enxergar praticamente nada!");
    if (contadorFraco < 11) {
        batalha(rnJesusOpo(2));//essa função de batalha chama a função rnJesus pra saber qual oponente o jogador vai enfrentar pelo numero semi aleatório
        
    }else if (contadorFraco >= 11)
    {
        batalha(rnJesusOpo(8));
    }else
    {
        batalha(rnJesusOpo(9));
    }
}

void menuCidade () 
{
    char opt;
        do {
        puts ("\nO que deseja fazer?\nIr a loja - P\nIr a taverna - T\nSair da Cidade - M");
        scanf (" %c",&opt);
        
        if (opt == 'P' || opt == 'p')     
        {
             loja();
            setbuf (stdin, NULL);
        }
        else if (opt == 'T' || opt == 't') 
        { 
            taverna();
            setbuf (stdin, NULL);
        }
        else if (opt == 'M' || opt == 'm')  
        {
            citySaida();

            continue;
        }
        else    printf ("Opção não válida!\n");
        }while (1);
}

void jogadorInfo () //rodar antes de combate, para atualizar as informações do jogador, atk, def, vel limite carry
{
    JogadorDados.atk    = 2;
    JogadorDados.vel    = 3;
    JogadorDados.hp     = 35;

}
    
int main () 
{
    lugar[5];
    char opt;
    cidade = 1;
    cidadeIs = 1;
    boasVindas();
    while (cidadeIs == 1) {
        
        jogadorInfo();
        menuCidade();
    }
    printf ("\nJogador não se encontra numa cidade, funções além das atuais estão por vir!\n");

}