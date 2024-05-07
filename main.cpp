#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

int codeClient = 0;
int codeVehicle = 0;
int codeLocation = 0;


struct Clients {
    char clientName[50];
    char cpf[12];
    char gender;
    int birth;
} client[9];

struct Vehicles {
	
	char plate[8];
	char type[15];
	char model[20];
	int year;
	char color[15];
	
}vehicle[9];

struct Location {
    
    Clients* client;
    Vehicles* vehicle;
    int code;

}location[9];


void clientRegister(struct Clients client[9]);
void vehicleRegister(struct Vehicles vehicle[9]);
void locationRegister(struct Location location[9], struct Clients client[9], struct Vehicles vehicle[9]);
void process(int choice, struct Clients client[9], struct Vehicles vehicle[9], struct Location location[9]);
void searchClientName(struct Location location[9], struct Clients client[9]);
void searchVehicleName(struct Location location[9], struct Vehicles vehicle[9]);
void list(struct Location location[9], struct Clients client[9], struct Vehicles vehicle[9]);
int menu();




int main() {
    
    setlocale(LC_ALL, "portuguese");
    
    int choice;

    do {
        
        choice = menu();

        process(choice, client, vehicle, location);
        
    } while (choice != 0);

    return 0;
}






void process (int choice,struct Clients client[9], struct Vehicles vehicle[9], struct Location location[9]){
    
    switch (choice) {
        case 1:
            clientRegister(client);
            break;
        case 2:
            vehicleRegister(vehicle);
            break;
        case 3:
            locationRegister(location, client, vehicle);
            break;
        case 4:
            searchClientName(location, client);
            break;
        case 5:
            searchVehicleName(location, vehicle);
            break;
        case 6:
            list(location, client, vehicle);
            break;
        case 0:
            printf("Encerrando o programa...\n");
            exit(1);
            break;
        default:
            printf("\033[37m\033[41mOpção inválida. Por favor, tente novamente.\033[0m\n");
            break;
    }

}

int menu (){
    
    int choice;

	printf("+-----------------------+");
	printf("\n|         MENU          |");
	printf("\n+-----------------------+");
	printf("\n|                       |");
	printf("\n|[1] Cadastrar Cliente  |");
	printf("\n|[2] Cadastrar Veículo  |");
    printf("\n|[3] Fazer Locação      |");
	printf("\n|[4] Buscar Cliente     |");
	printf("\n|[5] Buscar Veículo     |");
	printf("\n|[6] Listar Locação     |");
	printf("\n|[0] Sair               |");
	printf("\n|                       |");
	printf("\n+=======================+");

    printf("\n\n - Digite a opção desejada: ");
    scanf("%d", &choice);
    fflush(stdin);
    
    system("cls");

    return choice;
    
}


void clientRegister(struct Clients client[9]) {
	
	char opt;
	
	
	do {
		
		printf("__________________________________\n");
		printf("\033[33m_____REGISTRANDO NOVO CLIENTE_____\033[0m\n");
		printf("__________________________________\n¦");
		printf("\n");
		fflush(stdin);
		printf("| \033[30m\033[47mNome Completo:\033[0m ");
		gets(client[codeClient].clientName);
		printf("| \033[30m\033[47mCPF:\033[0m ");
		scanf(" %s", &client[codeClient].cpf);
		printf("| \033[30m\033[47mGênero (M/F):\033[0m ");
		scanf(" %c", &client[codeClient].gender);
		printf("| \033[30m\033[47mData de Nascimento (DDMMAAAA):\033[0m ");
		scanf(" %d", &client[codeClient].birth);
		printf("| \033[30m\033[47mCódigo do Cliente:\033[0m %d\n¦\n", codeClient);
        codeClient++;
		printf("|\033[30m\033[43mDeseja Cadastrar Novo Cliente? (S/N)\033[0m -> ");
		scanf(" %c", &opt);
		printf("|__________________________________\n\n");
	    
	    system("pause");
	    system("cls");
		
	} while (toupper(opt) == 'S');
	
	FILE* file = fopen("database/client.json", "a");
    if (file != NULL) {
        if (codeClient == 1) {
            fprintf(file, "[\n");
        } else {
            fprintf(file, ",\n");
        }

        for (int i = 0; i < codeClient; i++) {
            fprintf(file, "  {\n");
            fprintf(file, "    \"Nome\": \"%s\",\n", client[i].clientName);
            fprintf(file, "    \"CPF\": %s,\n", client[i].cpf);
            fprintf(file, "    \"Gênero\": \"%c\",\n", toupper(client[i].gender));
            fprintf(file, "    \"Data de Nascimento\": %d\n", client[i].birth);
            fprintf(file, "  }\n");
        }

        fprintf(file, "]\n");
        fclose(file);
        
    }
	
	
    
}

void vehicleRegister(struct Vehicles vehicle[9]) {
    
    
	char opt;
	
	do {
		
		printf("__________________________________\n");
		printf("\033[33m_____REGISTRANDO NOVO VEÍCULO_____\033[0m\n");
		printf("__________________________________\n¦");
		printf("\n");
		fflush(stdin);
		printf("| \033[30m\033[47mPlaca do Veículo (Ex: PJF3473):\033[0m ");
		gets(vehicle[codeVehicle].plate);
		printf("| \033[30m\033[47mTipo (EX: Carro, Moto):\033[0m ");
		scanf(" %s", &vehicle[codeVehicle].type);
		printf("| \033[30m\033[47mModelo:\033[0m ");
		scanf(" %s", &vehicle[codeVehicle].model);
		printf("| \033[30m\033[47mAno:\033[0m ");
		scanf(" %d", &vehicle[codeVehicle].year);
		printf("| \033[30m\033[47mCor:\033[0m ");
		scanf(" %s", &vehicle[codeVehicle].color);
		printf("| \033[30m\033[47mCódigo do Veículo:\033[0m %d\n¦\n", codeVehicle);
        codeVehicle++;
		printf("|\033[30m\033[43mDeseja Cadastrar Novo Veículo? (S/N)\033[0m -> ");
		scanf(" %c", &opt);
		printf("|__________________________________\n\n");
	    
	    system("pause");
	    system("cls");
		
	} while (toupper(opt) == 'S');
	
	FILE* file = fopen("database/vehicles.json", "a");
    if (file != NULL) {
        if (codeVehicle == 1) {
            fprintf(file, "[\n");
        } else {
            fprintf(file, ",\n");
        }

        for (int i = 0; i < codeVehicle; i++) {
            fprintf(file, "  {\n");
            fprintf(file, "    \"Placa\": \"%s\",\n", vehicle[i].plate);
            fprintf(file, "    \"Tipo\": %s,\n", vehicle[i].type);
            fprintf(file, "    \"Modelo\": \"%s\",\n", vehicle[i].model);
            fprintf(file, "    \"Ano\": %d\n", vehicle[i].year);
            fprintf(file, "    \"Cor\": %s\n", vehicle[i].color);
            fprintf(file, "  }\n");
        }

        fprintf(file, "]\n");
        fclose(file);
        
    }
	
	
	
}


void locationRegister(struct Location location[9], struct Clients client[9], struct Vehicles vehicle[9]){

    char opt;
	
	
	do {
		
		printf("__________________________________\n");
		printf("\033[33m_____REGISTRANDO NOVA LOCAÇÃO_____\033[0m\n");
		printf("__________________________________\n¦");
		printf("\n");
		fflush(stdin);
		
        printf("| \033[30m\033[47mCódigo do cliente:\033[0m ");
        int clientCode;
        scanf("%d", &clientCode);
        
        if (clientCode < 0 || clientCode > codeClient) {
            printf("¦ \033[37m\033[41mCódigo do Cliente inválido!\033[0m\n");
            printf("==================================\n\n");
            system("pause");
            system("cls");
            menu();
        }
		
        printf("| \033[30m\033[47mCódigo do veículo:\033[0m ");
		int vehicleCode;
        scanf("%d", &vehicleCode);

        if (vehicleCode < 0 || vehicleCode > codeVehicle) {
            printf("¦ \033[37m\033[41mCódigo do Veículo inválido!\033[0m\n");
            printf("==================================\n\n");
            system("pause");
            system("cls");
            menu();
        }

        location[codeLocation].client = &client[clientCode];
        location[codeLocation].vehicle = &vehicle[vehicleCode];
        location[codeLocation].code = codeLocation;
		
		
		printf("\n| \033[37m\033[42mLocação registrada com sucesso!\033[0m\n¦\n");
        printf("| Código da Locação: %d\n", codeLocation);

        codeLocation++;

		printf("|\033[30m\033[43mDeseja Cadastrar Nova Locação? (S/N)\033[0m -> ");
		scanf(" %c", &opt);
		printf("|__________________________________\n\n");
	    
	    system("pause");
	    system("cls");
		
	} while (toupper(opt) == 'S');
	
	FILE* file = fopen("database/location.json", "a");
    if (file != NULL) {
        if (codeLocation == 1) {
            fprintf(file, "[\n");
        } else {
            fprintf(file, ",\n");
        }

        for (int i = 0; i < codeLocation; i++) {
            fprintf(file, "  {\n");
            fprintf(file, "    \"Nome\": \"%s\",\n", location->client->clientName);
            fprintf(file, "    \"Modelo\": %s\n", location->vehicle->model);
             fprintf(file, "    \"Placa\": %s\n", location->vehicle->plate);
            fprintf(file, "  }\n");
        }

        fprintf(file, "]\n");
        fclose(file);
        
    }
	
	

}

void searchClientName(struct Location location[9], struct Clients client[9]) {
	
	printf("\033[33m+-------------------------------------+\033[0m\n");
	printf("\033[33m|      BUSCAR LOCAÇÃO DO CLIENTE      |\033[0m\n");
	printf("\033[33m+-------------------------------------+\033[0m\n");
	printf("\033[33m¦\033[0m\n");
	fflush(stdin);
	
	char searchName[50];
	
	printf("\033[33m|\033[0m \033[30m\033[47mDigite o nome do cliente:\033[0m ");
	scanf(" %s", &searchName);
	
	int found = 0;
	
	for (int i = 0; i < codeLocation; i++) {
        if (strcmp(client[i].clientName, searchName) == 0) {
        	
        	printf("\033[33m|\033[0m\n");
            printf("\033[33m|\033[0m Cliente: %s\n", location[i].client->clientName);
            printf("\033[33m|\033[0m Veículo: %s\n", location[i].vehicle->model);
            printf("\033[33m|\033[0m Código de locação: %d\n", location[i].code);
            printf("\033[33m+======================================\033[0m\n");
            found = 1;
        }
    }
    
    if (!found) {
    	printf("\n\033[37m\033[41m| Nenhuma locação encontrada para o cliente '%s'. \033[0m \n\n", searchName);
    }

    system("pause");
    system("cls");
}

void searchVehicleName(struct Location location[9], struct Vehicles vehicle[9]) {
		
	printf("\033[33m+-------------------------------------+\033[0m\n");
	printf("\033[33m|      BUSCAR LOCAÇÃO DE VEÍCULO      |\033[0m\n");
	printf("\033[33m+-------------------------------------+\033[0m\n");
	printf("\033[33m¦\033[0m\n");
	fflush(stdin);
		
	char searchVehicle[50];
	
	printf("\033[33m|\033[0m \033[30m\033[47mDigite a placa do veículo:\033[0m ");
	scanf(" %s", &searchVehicle);
	
	int found = 0;
	
	for (int i = 0; i < codeLocation; i++) {
        if (strcmp(vehicle[i].plate, searchVehicle) == 0) {
        	
        	printf("\033[33m|\033[0m\n");
        	printf("\033[33m|\033[0m Veículo: %s\n", location[i].vehicle->model);
            printf("\033[33m|\033[0m Cliente: %s\n", location[i].client->clientName);
            printf("\033[33m|\033[0m Código de locação: %d\n", location[i].code);
            printf("\033[33m+======================================\033[0m\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("\n\033[37m\033[41m| A placa '%s' não foi locada ou não existe. \033[0m \n\n", searchVehicle);
    }

    system("pause");
    system("cls");
}

    

void list(struct Location location[9], struct Clients client[9], struct Vehicles vehicle[9]) {
    printf("Lista: \n");
    
    FILE* file = fopen("database/location.json", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    char buffer[100];
    int jumpLine = 0;
    
    while (fscanf(file, "%s", buffer) == 1) {
        
        printf("%s ", buffer);
        jumpLine++;

        if(jumpLine == 10){
            printf("\n");
            jumpLine = 0;
        }
        

    }

    buffer[0] = '\0';
    fclose(file);
    
    system("pause");
	system("cls");
    
    
}
