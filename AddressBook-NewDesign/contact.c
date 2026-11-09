#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Sort contacts based on the choosen criteria
    int i, j;
    Contact temp;
    printf("Sort based on :\n1. Name\n2. Phone\n3. Email");
    scanf("%d", &sortCriteria);

    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            int cmp = 0;

            if (sortCriteria == 1)
            {
                cmp = strcmp(addressBook->contacts[j].name,
                             addressBook->contacts[j + 1].name);
            }
            else if (sortCriteria == 2)
            {
                cmp = strcmp(addressBook->contacts[j].phone,
                             addressBook->contacts[j + 1].phone);
            }
            else if (sortCriteria == 3)
            {
                cmp = strcmp(addressBook->contacts[j].email,
                             addressBook->contacts[j + 1].email);
            }
            else
            {
                printf("Invalid sorting criteria\n");
                return;
            }

            if (cmp > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\nNo.\tName\t\tPhone\t\tEmail\n");

    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d\t%s\t\t%s\t%s\n",i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    // saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    int valid1 = 1, res1;
    char str[20];

    while (valid1 == 1)
    {
        printf("Enter Name : ");
        scanf(" %[^\n]", str);

        res1 = validate_name(str);
        if (res1 == 1)
        {
            printf("Invalid name! Enter name with 2 or more letters\n");
        }
        else if (res1 == 0)
        {
            printf("Name accepted!\n");
            break;
        }
    }

    int valid2 = 1, res2;
    char str2[20];
    while (valid2 == 1)
    {
        printf("Enter phone number :\n");
        scanf(" %[^\n]", str2);

        res2 = validate_phone(str2);
        if (res2 == 1)
        {
            printf("Invalid number! Enter again\n");
        }
        else if (res2 == 2)
        {
            printf("Invalid number! Try again");
        }
        else if (res2 == 0)
        {
            printf("Phone number accepted!\n");
            valid2 = 0;
        }
    }

    int valid3 = 1, res3;
    char str3[20];
    while (valid3 == 1){
    printf("Enter Email :\n");
    scanf(" %[^\n]", str3);

    res3 = validate_email(str3);
    if (res3 == 1)
    {
        printf("Error: Invalid email\n");
    }
    else if (res3 == 2)
    {
        printf("Error: Email should not start with @\n");
    }
    else if (res3 == 3)
    {
        printf("Error: Email should end with .com\n");
    }
    else if (res3 == 4)
    {
        printf("Error: Uppercase letters are not allowed\n");
    }
    else if (res3 == 5)
    {
        printf("Error: Email must contain exactly one @\n");
    }
    else if (res3 == 6)
    {
        printf("Error: At least one character is required between @ and .com\n");
    }
    else if (res3 == 0)
    {
        printf("Email accepted\n");
    break;
    }
}
    strcpy(addressBook->contacts[addressBook->contactCount].name, str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);

    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    int x = 1, n, i, found = 0;
    char str[100];

    while (x == 1)
    {
        printf("Search based on:\n1. Name\n2. Phone\n3. Email\n");
        scanf("%d", &n);

        if (n < 1 || n > 3)
        {
            printf("Invalid choice! Enter again\n");
        }
        else if(n == 1){
            printf("Enter the name to search: ");
        }
        else if(n == 2){
            printf("Enter the phone number to search: ");
        }
        else if(n == 3){
            printf("Enter the Email to search: ");
        }
        scanf(" %[^\n]", str);

        found = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if (n == 1 && strcasestr(addressBook->contacts[i].name, str) != NULL)
            {
                found = 1;
            }
            else if (n == 2 && strstr(addressBook->contacts[i].phone, str) != NULL)
            {
                found = 1;
            }
            else if (n == 3 && strcasestr(addressBook->contacts[i].email, str) != NULL)
            {
                found = 1;
            }

            if (found == 1)
            {
                printf("\nContact found!\n");
                printf("\nNo.\tName\t\tPhone\t\tEmail\n");
                printf("%d\t%s\t\t%s\t%s\n",i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                    x = 0;
                break;
            }
        }

        if (found == 0)
        {
            printf("Contact not found!\n");
            x = 0;
        }
    printf("\nSearch again? \n[1= Yes]\n[0 = No]");
    scanf("%d", &x);
    }
}

void editContact(AddressBook *addressBook)
{
    int n, i, found = 0, choice;
    char str[100];
    printf("Edit contact based on:\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &n);

    if (n < 1 || n > 3)
    {
        printf("Invalid choice!\n");
        return;
    }

    printf("Enter the search value: ");
    scanf(" %[^\n]", str);

    // Search for the contact
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (n == 1 && strcasestr(addressBook->contacts[i].name, str) != NULL)
        {
            found = 1;
        }
        else if (n == 2 && strstr(addressBook->contacts[i].phone, str) != NULL)
        {
            found = 1;
        }
        else if (n == 3 && strcasestr(addressBook->contacts[i].email, str) != NULL)
        {
            found = 1;
        }

        if (found == 1)
        {
            break;
        }
    }

    if (found == 0)
    {
        printf("Contact not found!\n");
        return;
    }
    // Display the contact
    printf("\nContact found!\n");
    printf("Name: %s\n", addressBook->contacts[i].name);
    printf("Phone: %s\n", addressBook->contacts[i].phone);
    printf("Email: %s\n", addressBook->contacts[i].email);

    
    printf("\nWhat do you want to edit?\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter new name: ");
        scanf(" %[^\n]", str);

        if (validate_name(str) == 0)
        {
            strcpy(addressBook->contacts[i].name, str);
            printf("Name updated successfully!\n");
        }
        else
        {
            printf("Invalid name!\n");
        }
    }
    else if (choice == 2)
    {
        printf("Enter new phone number: ");
        scanf("%s", str);

        if (validate_phone(str) == 0)
        {
            strcpy(addressBook->contacts[i].phone, str);
            printf("Phone updated successfully!\n");
        }
        else
        {
            printf("Invalid phone number!\n");
        }
    }
    else if (choice == 3)
    {
        printf("Enter new email: ");
        scanf("%s", str);

        if (validate_email(str) == 0)
        {
            strcpy(addressBook->contacts[i].email, str);
            printf("Email updated successfully!\n");
        }
        else
        {
            printf("Invalid email!\n");
        }
    }
else
    {
        printf("Invalid choice!\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    int n, i, j, found = 0;
    char str[100];

    printf("Delete contact based on:\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &n);

    if (n < 1 || n > 3)
    {
        printf("Invalid choice!\n");
        return;
    }

    printf("Enter the search value: ");
    scanf(" %[^\n]", str);

    // Search for the contact
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (n == 1 &&
            strcasestr(addressBook->contacts[i].name, str) != NULL)
        {
            found = 1;
        }
        else if (n == 2 &&
            strstr(addressBook->contacts[i].phone, str) != NULL)
        {
            found = 1;
        }
        else if (n == 3 &&
            strcasestr(addressBook->contacts[i].email, str) != NULL)
        {
            found = 1;
        }

        if (found == 1)
        {
            break;
        }
    }

    if (found == 0)
    {
        printf("Contact not found!\n");
        return;
    }

    // Displaying the contact before deleting
    printf("\nContact to be deleted:\n");
    printf("%s\t%s\t%s\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);

    for (j = i; j < addressBook->contactCount - 1; j++)
    {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}

int validate_name(char *str1)
{
    if (strlen(str1) < 2)
    {
        return 1;
    }
    else
    {
        for (int i = 0; str1[i] != '\0'; i++)
        {
            if ((str1[i] == ' ' || (str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z')))
                return 0;
        }
    }
}

int validate_phone(char *str2)
{
    int i;
    int validate = 1;
    while (validate == 1)
    {
        if (strlen(str2) != 10)
        {
            return 1;
        }
        else
        {
            for (i = 0; str2[i] != '\0'; i++)
            {
                if (!isdigit(str2[i]))
                {
                    return 2;
                }
            }
            return 0;
        }
    }
}

int validate_email(char *str3)
{
    int i, at_count = 0;
    int len = strlen(str3);
    int at_pos = -1;

    if (len < 5)
    {
        return 1;
    }

    if (str3[0] == '@')
    {
        return 2;
    }

    if (strcmp(str3 + len - 4, ".com") != 0)
    {
        return 3;
    }

    for (i = 0; i < len; i++)
    {
        if (str3[i] >= 'A' && str3[i] <= 'Z')
        {
            return 4;
        }

        if (str3[i] == '@')
        {
            at_count++;
            at_pos = i;
        }
    }

    if (at_count != 1)
    {
        return 5;
    }

    if (at_pos >= len - 5)
    {
        return 6;
    }
    return 0;
}