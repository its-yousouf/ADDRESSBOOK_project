#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
FILE *fptr = fopen("contacts.csv","w");
int i;
if(fptr == NULL)
  {
    printf("Error: unable to open file for saving\n");
  }
fprintf(fptr,"#%d\n",addressBook->contactCount);
for(i = 0 ; i < addressBook->contactCount ; i++)
{
fprintf(fptr,"%s,%s,%s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
}

fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
FILE *fptr = fopen("contacts.csv","w");
int i;
if(fptr == NULL)
  {
    printf("Error: unable to open file for saving\n");
  }
fscanf(fptr,"#%d\n",&addressBook->contactCount);
for(i = 0 ; i < addressBook->contactCount ; i++)
{
fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
}

fclose(fptr);

}
