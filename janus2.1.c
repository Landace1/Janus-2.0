#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// an "*" denotes changes made that were not included in source code
// also anything between //* and //-* is all original code not from source
// "-*" denotes end of original code
float encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];
//*source code for cesar was defined in int main...
//*Moved source codes for cesar too their own respective void functions (cc),(cce).
void cc();
void cce();
//-*
void decryption();
void encryption();
void getKeyMessage();
void inverse();
//*
void startD();
void startE();
//-*
//decryption formula for cesar sourced from
////www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void cc()
{
	//* changed source code characters to include buffer and buf ch was already in source
	char buf[1024], buffer[1022], ch;
	//-*
	int i, key;
	//*changed from scanf to fgets as flow is better also added buf and buffer
	printf("Enter a message to decrypt: ");
	fgets(buf, 1024, stdin);
	printf("Enter key: ");
	fgets(buffer, 1022, stdin);
	//atoi is so the buffer reads as digit also is why buf and buffer are sepperate
	//as buf is the string and buffer is the digit
	key = atoi(buffer);
	//-*
	for (i = 0; buf[i] != '\0'; ++i) {
		ch = buf[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch - key;
			if (ch < 'a') {
				ch = ch + 'z' - 'a' + 1;
			}
			buf[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ch = ch - key;
			if (ch < 'A') {
				ch = ch + 'Z' - 'A' + 1;
			}
			buf[i] = ch;
		}
	}
	printf("Decrypted message: %s", buf);
	return 0;
}
//encryption formula for cesar sourced from
////www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
void cce()
{
	// will change scanf to fgets later for better flow
	char message[100], ch;
	int i, key;
	printf("Enter a message to encrypt: ");
	gets(message);
	printf("Enter key: ");
	scanf_s("%d", &key);
	for (i = 0; message[i] != '\0'; ++i) {
		ch = message[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch + key;
			if (ch > 'z') {
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ch = ch + key;
			if (ch > 'Z') {
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
	printf("Encrypted message: %s", message);
	return 0;
}
//decryption formula for hill climb sourced from 
//www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
void decryption()
{
	
	int i, j, k;
	inverse();
	for (i = 0; i < 3; i++)
		for (j = 0; j < 1; j++)
			for (k = 0; k < 3; k++)
				decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];
	printf("\nDecrypted string is: ");
	for (i = 0; i < 3; i++)
		printf("%c", (char)(fmod(decrypt[i][0], 26) + 97));
	printf("\n");
}
//encryption formula for hill climb sourced from 
//www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
void encryption()
{
	int i, j, k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 1; j++)
			for (k = 0; k < 3; k++)
				encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];
	printf("\nEncrypted string is: ");
	for (i = 0; i < 3; i++)
		printf("%c", (char)(fmod(encrypt[i][0], 26) + 97));
}
//getKeyMessage formula for hill climb sourced from 
//www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
void getKeyMessage()
{
	int i, j;
	char msg[3];
	printf("Enter 3x3 matrix for key (It should be inversible):\n");
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			scanf_s("%f", &a[i][j]);
			c[i][j] = a[i][j];
		}
	printf("\nEnter a 3 letter string: ");
	scanf_s("%s", msg);
	for (i = 0; i < 3; i++)
		mes[i][0] = msg[i] - 97;
}
//inverse formula for hill climb sourced from 
//www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
void inverse()
{
	int i, j, k;
	float p, q;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++) {
			if (i == j)
				b[i][j] = 1;
			else
				b[i][j] = 0;
		}
	for (k = 0; k < 3; k++) {
		for (i = 0; i < 3; i++) {
			p = c[i][k];
			q = c[k][k];
			for (j = 0; j < 3; j++) {
				if (i != k) {
					c[i][j] = c[i][j] * q - p * c[k][j];
					b[i][j] = b[i][j] * q - p * b[k][j];
				}
			}
		}
	}
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			b[i][j] = b[i][j] / c[i][i];
	printf("\n\nInverse Matrix is:\n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("%d ", b[i][j]);
		printf("\n");
	}
}
//*call to start decryption moved to void
void startD()
{
	
	//*
	int xo;
	char buf[1024];
	printf("\Choose your decryption cipher method (type 1, or 2, etc.)\n");
	printf("#1: Cesar cipher\n");
	printf("#2: Matrix Cipher\n");
	fgets(buf, 1024, stdin);
	xo = atoi(buf);
	switch (xo)

//cesar is case 1
	{
		{case 1:
		{
			//cesar decryption void formula
			cc();
			return 0;
		}

		}
//Hill climb is case 2
					   
		{case 2:
		{
			//hill decryption formula to get message and then decrypt 
			getKeyMessage();
			decryption();
			return 0;
		}


		

		
		}
	}

	//-* 
}
//*call to start encryption moved to void
void startE()
{
	
	//*
	int xo;
	char buf[1024];
	printf("\Choose your encryption cipher method (type 1, or 2, etc.)\n");
	printf("#1: Cesar cipher\n");
	printf("#2: Matrix Cipher\n");
	fgets(buf, 1024, stdin);
	xo = atoi(buf);
	switch (xo)

//cesar is case 1
	{
		{case 1:
		{
			//cesar encryption void formula
			cce();
		}
		return 0;
		}
//Hill climb is case 2
					  
		{case 2:
		{
			//hill encryption formula to get message and then encrypt 
			getKeyMessage();
			encryption();
			return 0;
		}
	//-*
		}
	}
}
//*cleaned up int main to call for void functions (reduce redundancy)
int main()
	{
		
		//*
		int x;
		char buf[1024];
		printf("\Do you want to encrypt or decrypt (type 1, or 2, etc.)\n");
		printf("#1: Encrypt\n");
		printf("#2: Decrypt\n");
		fgets(buf, 1024, stdin);
		x = atoi(buf);
		switch (x)

//case 1 is encryption
		{
			{case 1:
			{
				startE();
			}
			return 0;
			}
//case 2 is decryption
			{case 2:
			{
				startD();
				return 0;
			}
			return 0;
			}
		}
		//*
		
	}

