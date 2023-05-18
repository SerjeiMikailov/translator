#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 100

typedef struct {
    char pt[MAX_WORD_LENGTH];
    char en[MAX_WORD_LENGTH];
} Word;

int main()
{
    FILE *fileOrigin, *fileDestiny;
    char line[MAX_LINE_LENGTH];

    fileOrigin = fopen("/home/serjei/projects/Conversor/input.txt", "r");
    if (fileOrigin == NULL)
    {
        printf("Erro ao abrir o arquivo de origem.\n");
        return 1;
    }

    fileDestiny = fopen("/home/serjei/projects/Conversor/output.txt", "w");
    if (fileDestiny == NULL)
    {
        printf("Erro ao abrir o arquivo de destino.\n");
        fclose(fileOrigin);
        return 1;
    }

    FILE *fileCSV = fopen("/home/serjei/projects/Conversor/words.csv", "r");
    if (fileCSV == NULL)
    {
        printf("Erro ao abrir o arquivo de palavras.\n");
        fclose(fileOrigin);
        fclose(fileDestiny);
        return 1;
    }

    Word words[1000];
    int numWords = 0;

    char wordLine[MAX_LINE_LENGTH];
    while (fgets(wordLine, MAX_LINE_LENGTH, fileCSV) != NULL)
{
    char *ptWord = strtok(wordLine, ",");
    char *enWord = strtok(NULL, ",");
    if (ptWord != NULL && enWord != NULL)
    {
        ptWord[strcspn(ptWord, "\r\n")] = '\0';
        enWord[strcspn(enWord, "\r\n")] = '\0';

        strcpy(words[numWords].pt, ptWord);
        strcpy(words[numWords].en, enWord);
        numWords++;
    }
}

    while (fgets(line, MAX_LINE_LENGTH, fileOrigin) != NULL)
    {
        char *token = strtok(line, " \n");
        while (token != NULL)
        {
            int translated = 0;
            for (int i = 0; i < numWords; i++)
            {
                token[strcspn(token, "\r\n")] = '\0';

                if (strcmp(token, words[i].pt) == 0)
                {
                    fprintf(fileDestiny, "%s ", words[i].en);
                    translated = 1;
                    break;
                }
            }
            if (!translated)
            {
                fprintf(fileDestiny, "%s ", token);
            }
            token = strtok(NULL, " \n");
        }

        fprintf(fileDestiny, "\n"); 
    }

    fclose(fileOrigin);
    fclose(fileDestiny);
    fclose(fileCSV);

    printf("Tradução concluída com sucesso!\n");

    return 0;
}
