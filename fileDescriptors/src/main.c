// Question

/** REQUIRED HEADER FILES **/

#include<stdio.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

int main(int argc, char* argv[]){
	int num;
	printf("Enter the number of the exercise you want to execute: ");
	scanf("%d", &num);
	switch(num){
		case 1:
			task_1();
			break;
		case 2:
			task_2(argc,argv);
			break;
		case 3:
			task_3(argc,argv);
			break;
		case 4:
			task_4();
			break;
		case 5:
			task_5();
			break;
		case 6:
			task_6();
			break;
		default:
			printf("Enter the valid number.\n");
			break;
	}
	return 0;
}
