#include <bits/stdc++.h>

using namespace std;

typedef struct process{
	int pid;
	int mem;
	int min_flt;
	int maj_flt;
	int swap;
} Process;

//Retorna uma lista com todos os processos abertos no sistema
list<Process> getProcessosAbertos(){

	//Inicializa��o das vari�veis
	FILE *fp;
	char path[1035];
	char *aux;
	list<Process> processosAbertos;

	//Comando que pega todos os pid, e page falts do sistema
	string comando = "ps -eo pid,min_flt,maj_flt --no-header | head --lines=-2";

	//O comando � executado no terminal e a sa�da � armazenada em um arquivo
	fp = popen(comando.c_str(), "r");

	//Verifica se o comando foi executado
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	//L� a sa�da linha por linha
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		aux = strtok(path," ");
		Process p;
		p.pid = atoi(aux);
		aux = strtok(NULL," ");
		p.min_flt = atoi(aux);
		aux = strtok(NULL," ");
		p.maj_flt = atoi(aux);

		FILE *f;
		char path2[1035];

		//Comando que pega o arquivo status do pid passado
		string comando = "cat /proc/" + to_string(p.pid) + "/status | head -18 | tail -1 | awk '{print $2}'";

		//O comando � executado no terminal e a sa�da � armazenada em um arquivo
		f = popen(comando.c_str(), "r");

		//Verifica se o comando foi executado
		if (f == NULL) {
			printf("Failed to run command\n" );
			exit(1);
		}

		//L� a sa�da linha por linha
		while (fgets(path2, sizeof(path2)-1, f) != NULL)
			p.mem = atoi(path2);
		
		pclose(f);

		//Comando que pega o arquivo status do pid passado
		comando = "cat /proc/" + to_string(p.pid) + "/status | head -32 | tail -1 | awk '{print $2}'";

		//O comando � executado no terminal e a sa�da � armazenada em um arquivo
		f = popen(comando.c_str(), "r");

		//Verifica se o comando foi executado
		if (f == NULL) {
			printf("Failed to run command\n" );
			exit(1);
		}

		//L� a sa�da linha por linha
		while (fgets(path2, sizeof(path2)-1, f) != NULL)
			p.swap = atoi(path2);
		
		pclose(f);
		
		//Adiciona o processo em uma lista de processos abertos
		processosAbertos.push_back(p);
	}

	//Fecha o arquivo
	pclose(fp);

	return processosAbertos;
}

void readProcess(list<Process> process){
	for(list<Process>::iterator it = process.begin(); it != process.end(); it++){
		printf("pid: %d\n\tmin_flt: %d\n\tmaj_flt: %d\n\tmem: %d\n\tswap: %d\n", it->pid, it->min_flt, it->maj_flt, it->mem, it->swap);
	}
}

int main(int argc, char *argv[]){
	printf("A quantidade total da mem�ria principal � de: ");
	fflush(stdout);
	system("cat /proc/meminfo | head -1 | awk '{print $2}'");
	printf("A quantidade total da mem�ria cache � de: ");
	fflush(stdout);
	system("cat /proc/meminfo | head -5 | tail -1 | awk '{print $2}'");
	printf("A quantidade total de swapping � de: ");
	fflush(stdout);
	system("cat /proc/meminfo | head -15 | tail -1 | awk '{print $2}'");
	printf("As informa��es por processo est�o detalhadas abaixo:\n");
	list<Process> processos = getProcessosAbertos();
	readProcess(processos);
}
