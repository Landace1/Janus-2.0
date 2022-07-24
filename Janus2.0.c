#include <stdio.h>
#include <math.h>
//an "*" in comments denotes code not from source
//hill climb sourced from
//www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
//cesar sourced from
////www.thecrazyprogrammer.com/2016/11/caesar-cipher-c-c-encryption-decryption.html
float encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];
void decryption();
void encryption();
void getKeyMessage();
void inverse();
void cc();
//*void cc1 added to remove redundancy and improve flow for main related to cesar
void cc()
{
	char message[100], ch;
	int i, key;
	printf("Enter a message to decrypt: ");
	gets(message);
	printf("Enter key: ");
	scanf_s("%d", &key);
	for (i = 0; message[i] != '\0'; ++i) {
		ch = message[i];
		if (ch >= 'a' && ch <= 'z') {
			ch = ch - key;
			if (ch < 'a') {
				ch = ch + 'z' - 'a' + 1;
			}
			message[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z') {
			ch = ch - key;
			if (ch < 'A') {
				ch = ch + 'Z' - 'A' + 1;
			}
			message[i] = ch;
		}
	}
	printf("Decrypted message: %s", message);
	return 0;
}
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
void decryption()
{
	//above defines all void functions for hill climb
	//below is the formula for each void function of hill climb
	//sourced from //www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
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
//FORMULA TO GET MESSAGE FOR HILL CLIMB this formula is sourced from www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
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
//FORMULA TO GET INVERSE HILL CLIMB this formula is sourced from www.thecrazyprogrammer.com/2017/02/hill-cipher-c.html
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
int main()
{

	//define int
		//* Funtion to chose what cipher
	int i, x, key;
	printf("\Choose your method\n");
	printf("1 = Ceaser.\n");
	printf("2 = Hill climb.\n");
	scanf_s("%d", &x);
	//*
	//*switch function and divided the source codes appropriatley in brackets to flow
	switch (x)

		//cesar is case 1
	{
		{case 1:
			cc();
		}
			   //Hill climb is case 2
					   //*arranged case two for hill climb to only decrypt
		{case 2:
		{
			getKeyMessage();

			decryption();
			
		}


		// gives output of the decryption

		return 0;
		}
	}

}
