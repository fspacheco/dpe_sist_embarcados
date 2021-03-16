#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filter1.h"

#define MAX_SAMPLES 300000

int main(int argc, char **argv) {
    if (argc<3) {
        printf("Uso: filtro arquivo_entrada arquivo_saida\n");
        printf("Opcional: -t executa testes do Micromodeler (Generic C Properties/Generate Test Cases)\n\n");
        printf("Aplica filtro gerado com Micromodeler em um arquivo de áudio e grava arquivo filtrado\n");
        printf("Arquivos de áudio devem estar no formato texto/float\n\n");
        printf("Uso livre para fins educacionais. Fernando S. Pacheco - 2021\n");
        return 0;
    }
    char audio_filename[50];
    char output_filename[50];

    strncpy(audio_filename, argv[1], 50);
    strncpy(output_filename, argv[2], 50);
    
    if (argc==4 && strcmp(argv[3], "-t") == 0) {
        filter1_runTests(); // testes gerados pela ferramenta Micromodeler
    }

    // Leitura do arquivo de entrada
    FILE *fp;
    fp = fopen(audio_filename, "r");
    if (!fp) {
        printf("Erro ao abrir arquivo de audio (entrada).\n");
        exit(-1);
    }
    
    float audio_samples[MAX_SAMPLES]; //alocacao estatica
    int nsamples=0, n;
   
    while(nsamples<MAX_SAMPLES)  {
      n=fscanf(fp, "%f", &audio_samples[nsamples]);
      if (n==EOF)
        break;
      nsamples++;
    }
    fclose(fp);
    printf("Amostras lidas do arquivo %s: %d\n", audio_filename, nsamples);
    
    // Filtragem
    float filtered_audio[MAX_SAMPLES];
    int samplesProcessed;
    filter1Type *filter = filter1_create();	// Create an instance of the filter
    printf( "\n\nInicio da filtragem do audio lido do arquivo\n" );
    filter1_reset(filter);
    samplesProcessed = filter1_filterInChunks(filter, audio_samples, filtered_audio, nsamples);		// Filter the input test signal
    printf( "\n\nFiltragem terminada. Amostras processadas: %d\n", samplesProcessed);

    // Gravacao do arquivo com sinal processado
    fp = fopen(output_filename, "w");
    if (!fp) {
        printf("Erro ao abrir arquivo de audio (saida).\n");
        exit(-1);
    }
    n=0;
    while(n<samplesProcessed)  {
      fprintf(fp, "%f\n", filtered_audio[n]);
      n++;
    }
    fclose(fp);
    printf("Arquivo %s salvo. Amostras gravadas: %d\n", output_filename, n);

    return 0;
}
    
