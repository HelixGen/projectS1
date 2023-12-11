#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 200 


typedef struct {
    char symptom[100];
    char disease[100];
    char doctor[100];
} Record;


Record* hashTable[TABLE_SIZE];


 int hash(char *symptom) {
 int hashValue = 0;
    int i = 0;
    while (symptom[i] != '\0') {
        hashValue += symptom[i];
        i++;
    }
    return hashValue % TABLE_SIZE;
}


void initHashTable() {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}


void insert(char *symptom, char *disease, char *doctor) {
    Record *newRecord = (Record *) malloc(sizeof(Record));
    strcpy(newRecord->symptom, symptom);
    strcpy(newRecord->disease, disease);
    strcpy(newRecord->doctor, doctor);

    int index = hash(symptom);
    while (hashTable[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable[index] = newRecord;
}


Record* findDisease(char *symptom) {
    int index = hash(symptom);
    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index]->symptom, symptom) == 0) {
            return hashTable[index];
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return NULL;
}





void displayRecords() {
printf("All records:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
    if (hashTable[i] != NULL) {
      printf("Symptom: %s, Disease: %s, Doctor: %s\n", hashTable[i]->symptom, hashTable[i]->disease, hashTable[i]->doctor);
     }
 }
}

int main() {
    initHashTable();
    char *illnesses[] = {
        "Common Cold", "Influenza", "Stomach Flu", "Migraine", "Bronchitis",
        "Allergies", "Pneumonia", "Gastroenteritis", "Hypertension", "Diabetes",
        "Arthritis", "Asthma", "Urinary Tract Infection", "Depression", "Anxiety"
    };

     char *symptoms[] = {
       "sneezing", "coughing","Nausea","headache","pale","chest pain",
       "diarrhoea","aching body","vomiting","dizziness", "dry skin",
       "tenderness","wheezing","burning sensation","tearfulness"
    };

     char *doctors[] = {
        "Dr. Smith", "Dr. Johnson", "Dr. Davis", "Dr. Brown", "Dr. Taylor",
        "Dr. White", "Dr. Miller", "Dr. Wilson", "Dr. Anderson", "Dr. Martinez",
        "Dr. Garcia", "Dr. Lee", "Dr. Turner", "Dr. Robinson", "Dr. Clark"
    };

      for (int i = 0; i < 15; i++) {
        insert(symptoms[i],illnesses[i],doctors[i]);

      }

      

    
    
    

    
    char symptom[100];
    printf("Enter your symptom: ");
    scanf("%s", symptom);

    Record *found = findDisease(symptom);
    if (found != NULL) {
        printf("Possible disease: %s\nRecommended doctor: %s\n", found->disease, found->doctor);
    } else {
        printf("No information available for this symptom.\n");
    }

    return 0;
}