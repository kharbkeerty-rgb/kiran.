//Title : Inventory Management System
//  Author : Kiran
// Roll NO. : 25EBKCS044
//College : BK Birla Institute Of Engineering And  Technology , Pilani


#include <stdio.h>
#include <stdlib.h>
struct Product
{
    int id;
    char name[50];
    float price;
    int quantity;
};

void addProduct();
void displayProducts();
void searchProduct();
void updateQuantity();
void deleteProduct();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================");
        printf("\n   INVENTORY MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Product");
        printf("\n2. Update Quantity");
        printf("\n3. Search Product");
        printf("\n4. Delete Product");
        printf("\n5. Stock Report");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addProduct();
            break;

        case 2:
            updateQuantity();
            break;

        case 3:
            searchProduct();
            break;

        case 4:
            deleteProduct();
            break;

        case 5:
            displayProducts();
            break;

        case 6:
            printf("\nThank You!\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

void addProduct()
{
    FILE *fp;
    struct Product p;

    fp = fopen("inventory.dat", "ab");

    printf("\nEnter Product ID: ");
    scanf("%d", &p.id);

    printf("Enter Product Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Product Price: ");
    scanf("%f", &p.price);

    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    fwrite(&p, sizeof(p), 1, fp);

    fclose(fp);

    printf("\nProduct Added Successfully.\n");
}

void displayProducts()
{
    FILE *fp;
    struct Product p;

    fp = fopen("inventory.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found.\n");
        return;
    }

    printf("\n-------------------------------------------------------");
    printf("\nID\tName\t\tPrice\tQuantity");
    printf("\n-------------------------------------------------------");

    while (fread(&p, sizeof(p), 1, fp))
    {
        printf("\n%d\t%-15s%.2f\t%d",
               p.id,
               p.name,
               p.price,
               p.quantity);
    }

    fclose(fp);

    printf("\n-------------------------------------------------------\n");
}

void searchProduct()
{
    FILE *fp;
    struct Product p;
    int id, found = 0;

    fp = fopen("inventory.dat", "rb");

    if (fp == NULL)
    {
        printf("\nFile Not Found.\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp))
    {
        if (p.id == id)
        {
            printf("\nProduct Found\n");
            printf("ID : %d", p.id);
            printf("\nName : %s", p.name);
            printf("\nPrice : %.2f", p.price);
            printf("\nQuantity : %d\n", p.quantity);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nProduct Not Found.\n");

    fclose(fp);
}

void updateQuantity()
{
    FILE *fp;
    struct Product p;
    int id, found = 0;

    fp = fopen("inventory.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nFile Not Found.\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp))
    {
        if (p.id == id)
        {
            printf("Current Quantity : %d\n", p.quantity);

            printf("Enter New Quantity : ");
            scanf("%d", &p.quantity);

            fseek(fp, -(long)sizeof(p), SEEK_CUR);

            fwrite(&p, sizeof(p), 1, fp);                                                                                                                                                                                                                                                                                                          

            printf("\nQuantity Updated Successfully.\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nProduct Not Found.\n");

    fclose(fp);
}

void deleteProduct()
{
    FILE *fp, *temp;
    struct Product p;
    int id, found = 0;

    fp = fopen("inventory.dat", "rb");

    if (fp == NULL)
    {
        printf("\nFile Not Found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Product ID to Delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp))
    {
        if (p.id == id)
        {
            found = 1;
            continue;
        }

        fwrite(&p, sizeof(p), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.dat");
    rename("temp.dat", "inventory.dat");

    if (found)
        printf("\nProduct Deleted Successfully.\n");
    else
        printf("\nProduct Not Found.\n");
}