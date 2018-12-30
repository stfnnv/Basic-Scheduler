#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxdesc 10000
#define maxevent 25
#define maxfilename 50

struct schedule
{
	int hour;
	int minute;
	char desc[maxdesc];
	struct schedule *next;
};

struct schedule *head = NULL;
void sortEvent (struct schedule e[maxevent]);

int index = 0;
struct schedule e[maxevent];

void newEvent () {
	int hourInput, minuteInput;
	char descInput[maxdesc];
	printf ("\n\t\t+======  NEW EVENT  ======+\n");
	
	printf ("\t\t Masukkan jam acara(01 sampai 24): ");
	scanf ("%d", &hourInput);
	if (hourInput > 24 || hourInput < 1)
	{
		inputerror();
		return 0;
	}
	
	printf ("\t\t Masukkan menit acara(00 sampai 59): ");
	scanf ("%d", &minuteInput);
	if (minuteInput > 59 || minuteInput < 0)
	{
		inputerror();
		return 0;
	}
	
	printf ("\n\t\t+====== DESCRIPTION ======+\n");
	printf ("\t\t Masukkan deskripsi acara: ");
	scanf (" %[^\n]s", &descInput);
	
	e[index].hour = hourInput;
	e[index].minute = minuteInput;
	strcpy (e[index].desc, descInput);
	index++;
}

void printList () {
	system("CLS");
	
	int i=0;
	printf ("\n\t\t+====== SCHEDULE ======+\n");
	for (i=1;i<(index+1);i++)
	{
		printf ("\t\t%d : %d %s\n", e[i].hour, e[i].minute, e[i].desc);
	}
}

void printMenu () {
	printf ("\n\t\t+========= MENU ========+\n"
        "\t\t|  1. New Event\t\t|\n"
        "\t\t|  2. Display Schedule\t|\n"
        "\t\t|  3. Help\t\t|\n"
        "\t\t|  4. Save Schedule\t|\n"
        "\t\t|  5. Exit\t\t|\n"
        "\t\t+=======================+\n""");
}

void sortEvent (struct schedule e[maxevent]) {
	int i;
	int j;
	struct schedule temp;
	for (j=0;j<index;j++)
	{
		for (i=0;i<index;i++)
		{
			if (e[i].hour > e[i+1].hour)
			{
				temp = e[i];
				e[i] = e[i+1];
				e[i+1] = temp;
			}
		}
	}
}

void saveEvent(char *filename, struct schedule e[], int size) {
	
	int i=0;
    FILE *f=fopen(filename, "w");
    if (f==NULL)
	{
        return;
    }

    for (i=0; i<size; i++)
	{
        fprintf(f, "%d %d %s\n", e[i].hour, e[i].minute, e[i].desc);
    }

    printf("\n| Jadwal \"%s\" berhasil disimpan.\n\n", filename);
    fclose(f);
}

showhelp () {
	printf ("\n\t\t+======================================== SCHEDULER ========================================+\n"
		"\t\tProgram ini digunakan untuk membuat jadwal harian.\n"
        "\t\t1. New Even		: Opsi ini digunakan untuk memasukkan acara.\n"
        "\t\t2. Display Schedule	: Opsi ini digunakan untuk menampilkan semua acara yang telah terdaftar.\n"
        "\t\t3. Help			: Opsi ini digunakan untuk menampilkan menu bantuan/menu anda saat ini.\n"
        "\t\t4. Save Schedule	: Opsi ini digunakan untuk menyimpan jadwal anda.\n"
        "\t\t5. Exit			: Opsi ini digunakan untuk keluar dari program.\n"
        "\t\t+===========================================================================================+\n""");
}

emptyerror () {
	system("CLS");
	printf("| Tidak ada acara pada jadwal.");
	return main();
}

inputerror () {
	system("CLS");
	printf ("\n\t\t Input salah!");
}

int main () {
	int choice;
	char file[maxfilename];
	printMenu();
	printf ("\t\t| Pilihan: ");
	scanf (" %d", &choice);
		switch (choice) 
		{
			case 1:
				system("CLS");
				newEvent();
				return main();
			case 2:
				if (index == 0)
				{
					emptyerror();
            	}
            	else
				{
					sortEvent(e);
					printList();
				}
				return main();
			case 3:
				system("CLS");
				showhelp();
				return main();
			case 4:
				if (index == 0)
				{
					emptyerror();
            	}
            	else
				{
					printf("%s", "| Mohon masukkan \"filename.txt\": ");
                	scanf (" %[^\n]s", &file);
                	saveEvent(file, e, index);
            	}
				return main();
			case 5:
				printf ("| Goodbye.");
				return 0;
			default:
				inputerror();
				return main();
		}
	return 0;
}
