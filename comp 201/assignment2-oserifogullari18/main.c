#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

// converts a string to lowercase
char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}
// converts a string to uppercase
char* toUpper(char* s) {
  for(char *p=s; *p; p++) *p=toupper(*p);
  return s;
}
void calculateAve(){
	printf("Type 0 to end the program\nEnter a word: ");
	char entry[50];
	scanf("%s", entry);
	while(entry[0] != '0'){
		int freq = 0;
		int sum = 0;
		FILE *fp;
		fp = fopen("movieReviews.txt","r");
		if(fp == NULL){
			printf("File couldn't open\n");
			break;
		}
		char line[500];
		while(fgets(line,500,fp) != NULL){
			int rate;
			rate = atoi(line);
			char *word = strrchr(line,' '); //splits a review into words
			while(word != NULL){
				if(!strcmp(entry, toLower(word+1))){ //word + 1 since there is a blank at the beginning
					freq++;
					sum += (rate);
				}
				*word = '\0';
				word = strrchr(line,' ');
			}
			
		}
		fclose(fp);
		double ave = (double)sum/ (double)freq;
		printf("%s appears %d times\n",entry,freq);
		printf("The average score of for reviews containing the word %s is %.4f\n", entry, ave);
		printf("Enter a word: ");
		scanf("%s", entry);
	}
}
void findMost(){
	int i = 0;
	int positive[100];
	int negative[100];
	int num_positive;
	int num_negative;
	char *vocab_arr[100];
	FILE *wf;
	wf = fopen("wordList.txt", "r");
	if(wf == NULL){
		printf("Word list file couldn't open\n");
		return;
	}
	char vocabs[500];
	char *vocab;
	fgets(vocabs, 500, wf);
	vocab = strtok(vocabs, "\r");
	while(vocab != NULL){
		vocab_arr[i] = vocab;
		num_positive = 0;
		num_negative = 0;
		FILE *rf;
		rf = fopen("movieReviews.txt", "r");
		if(rf == NULL){
			printf("Movie reviews file couldn't open\n");
			return;
		}
		char line[500];
		while(fgets(line,500,rf) != NULL){
			int rate;
			rate = atoi(line);
			char *word = strrchr(line,' '); //splits a review into words
			while(word != NULL){
				if(!strcmp(vocab, toLower(word+1))){ //word + 1 since there is a blank at the beginning
					if(rate == 3 || rate == 4){
						num_positive++;
					}
					else{
						num_negative++;
					}
				}
				*word = '\0';
				word = strrchr(line,' ');
			}
		}
		fclose(rf);
		vocab = strtok(NULL, "\r");
		positive[i] = num_positive;
		negative[i] = num_negative;
		i++;
	}
	fclose(wf);
	int max_negative = 0;
	int max_positive = 0;
	int index_p = 0;
	int index_n = 0;
	for(int c=0; c<i; c++){
		if(positive[c]> max_positive){
			max_positive = positive[c];
			index_p = c;
		}
		if(negative[c]> max_negative){
			max_negative = negative[c];
			index_n = c;
		}
	}
	printf("\"%s\" occured %d times in positive reviews.\n\"%s\" occured %d times in negative reviews.\n", toUpper(vocab_arr[index_p]), max_positive, toUpper(vocab_arr[index_n]), max_negative);
}

int main(){
	int task;
	printf("Press 1 to calculate the avarage score of a word\nPress 2 to find the most occuring word in positive and negative reviews\nYour entry: ");
	scanf("%d", &task);
	switch (task)
	{
	case 1:
		calculateAve();
		break;
	case 2:
		findMost();
		break;
	default:
		printf("Your entry is invalid\n");
		break;
	}
	printf("End of the program");
}