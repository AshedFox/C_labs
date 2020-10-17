#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
	char surname[100];
	char department[20];
	float salary;
};

int main()
{
	struct Employee *employees = malloc(300 * sizeof(struct Employee));
	FILE* f1;

	f1 = fopen("workers.txt", "r");
	int curPos = 0;
	while (!feof(f1)) {
		fscanf(f1, "%s%s%f\n", employees[curPos].surname, employees[curPos].department, &employees[curPos].salary);
		curPos++;
	}
	fclose(f1);
	int size = curPos;
	printf("Opened successfully\n");

	int isExit = 0;
	char input= ' ';
	while (!isExit) {
		printf("\nChoose action:\n1 - Add\n2 - Change\n3 - Delete\n4 - Count total and average\n5 - Show\ns - Save\ne - Exit\n");
		rewind(stdin);
		scanf("%c", &input);
		int isExitInternal = 0;
		switch (input)
		{
		case '1': {
			printf("\nEnter employee surname, department and salary to add: ");
			scanf("%s%s%f",
				   employees[size].surname, employees[size].department, &employees[size].salary);
			size++;
			printf("Added succesfully\n");
			break;
		}
		case '2': {
			printf("\nChoose action:\n1 - Change salary\n2 - Change department\n");
			char input2=' ';
			rewind(stdin);
			scanf("%c", &input2);
			switch (input2)
			{
			case '1': {
				char buffSurname[100], buffDepartment[20];
				float buffSalary;
				printf("\nEnter employee surname and department: ");
				scanf("%s%s", buffSurname, buffDepartment);
				rewind(stdin);
				printf("\nEnter new employee salary: ");
				scanf("%f", &buffSalary);
				int changedPos = -1;
				for (int i = 0; i < size; i++) {
					if (!strcmp(employees[i].surname, buffSurname) && !strcmp(employees[i].department, buffDepartment)) {
						employees[i].salary = buffSalary;
						changedPos = i;
						break;
					}
				}
				if (changedPos != -1) {
					printf("Changed successfully\n");
				}
				else {
					printf("Change failed\n");
				}
				isExitInternal = 1;
				break;
			}
			case '2': {
				char buffSurname[100], buffDepartment[20], newDepartment[20];
				printf("\nEnter employee surname and department: ");
				scanf("%s%s", buffSurname, buffDepartment);
				rewind(stdin);
				printf("\nEnter new department: ");
				scanf("%s", newDepartment);
				int changedPos = -1;
				for (int i = 0; i < size; i++) {
					if (!strcmp(employees[i].surname, buffSurname) && !strcmp(employees[i].department, buffDepartment)) {
						strcpy(employees[i].department, newDepartment);
						changedPos = i;
						break;
					}
				}
				if (changedPos != -1) {
					printf("Changed successfully\n");
				}
				else {
					printf("Change failed\n");
				}
				isExitInternal = 1;
				break;
			}
			case 'b':
				break;
			}
			break;
		}
		case '3': {
			char buffSurname[100], buffDepartment[20];
			printf("\nEnter employee surname and department: ");
			scanf("%s%s", buffSurname, buffDepartment);
			int deletedPos = -1;
			for (int i = 0; i < size; i++) {
				if (!strcmp(employees[i].surname, buffSurname) && !strcmp(employees[i].department, buffDepartment)) {
					deletedPos = i;
					break;
				}
			}
			if (deletedPos != -1) {
				for (int i = deletedPos+1; i < size; i++) {
					employees[i - 1] = employees[i];
				}
				size--;
				printf("Deleted successfully\n");
			}
			else {
				printf("Delete failed\n");
			}
			break;
		}
		case '4': {
			int countOfEmployees = 0;
			float sumOfSalaries = 0;
			for (int i = 0; i < size; i++) {
				if (!strcmp(employees[i].department, "A")) {
					sumOfSalaries += employees[i].salary;
					++countOfEmployees;
				}
			}
			float avgSalary = countOfEmployees == 0 ? 0 : sumOfSalaries / countOfEmployees;
			printf("\nTotal salary of department A: %6.2f\nAverage salary of department A: %6.2f\n", sumOfSalaries, avgSalary);
			break;
		}
		case '5': {
			for (int i = 0; i < size; i++) {
				printf("%s\t\t%s  %6.2f\n", employees[i].surname, employees[i].department, employees[i].salary);
			}
			break;
		}
		case 's': {
			f1 = fopen("workers.txt", "w");
			for (int i = 0; i < size; i++) {
				fprintf(f1, "%s %s %6.2f\n", employees[i].surname, employees[i].department, employees[i].salary);
			}
			fclose(f1);
			printf("Saved successfully\n");
			break;
		}
		case 'e': {
			isExit = 1;
			break;
		}
		}
	}

	return 0;
}
