#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void caesar_cipher(char string[], int shift)
{
  for(int i = 0; string[i] != '\0'; ++i){
		char ch = string[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + shift;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			string[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + shift;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			string[i] = ch;
		}
	}
}
 
int main()
{
  char password[40]; 
  int ch;
  printf("Enter a Password:\t");
  scanf("%[^\n]s", password);
  printf("\nPassword:\t%s\n",password);
  caesar_cipher(password, 5);
  printf("\nEncrypted Password:\t%s\n", password);
  caesar_cipher(password, -5);
  printf("\nDecrypted Password:\t%s\n", password);
  return 0;
}