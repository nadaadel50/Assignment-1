# Assignment-1
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
int choice;
int degree;
void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
    loadImage();
    doSomethingForImage();
    saveImage();
    return 0;
}

//_________________________________________
void loadImage () {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    cout << "Please, select a filter to apply or 0 to exit " << endl;
    cout << "1- Black & White Filter" << endl;
    cout << "2- Invert Filter" << endl;
    cout << "3- Merge Filter" << endl;
    cout << "4- Flip Filter" << endl;
    cout << "5- Rotate Filter" << endl;
    cout << "6- Darken & Lighten Filter" << endl;
    cout << "0- Exit" << endl;
    cin >> choice;
    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
    if(choice == 3){
        char image2File[100];
        cout << "Enter the source image file name of the second image: ";
        cin >> image2File;
        strcat (image2File, ".bmp");
        readGSBMP(image2File, image2);
    }
}

//_________________________________________
void saveImage () {
    if(choice == 1 || choice == 2|| choice == 4|| choice == 5 && degree == 180 || choice == 6){
        char imageFileName[100];

        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, image);
    }
    else if(choice == 3){
        char image2File[100];
        cout << "Enter the target image file name: " << endl;
        cin >> image2File;
        strcat(image2File, ".bmp");
        writeGSBMP(image2File, image3);
    }
    else if(choice == 5 && degree == 90 || degree == 270 ){
        char image2File[100];
        cout << "Enter the target image file name: ";
        cin >> image2File;
        strcat(image2File, ".bmp");
        writeGSBMP(image2File, image2);
    }
}

//_________________________________________
void doSomethingForImage() {
    if(choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if (image[i][j] > 127)
                    image[i][j] = 255;
                else
                    image[i][j] = 0;
            }
        }
    }
    else if(choice == 2){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                image[i][j] = 255 - image[i][j];
            }
        }
    }
    else if(choice == 3){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                image3[i][j] = (image[i][j] + image2[i][j])/2;
            }
        }
    }
    else if(choice == 4){
        cout << "Please, Enter you want to flip the image Horizontally or Vertically: " << endl;
        cout << "1- H "<< endl;
        cout << "2- V "<< endl;
        char direction; cin >> direction;
        if(direction == 'H'){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE/2+1; j++){
                    int tmp = image[i][j];
                    image[i][j] = image[i][SIZE-1-j];
                    image[i][SIZE-1-j] = tmp;
                }
            }
        }
        else{
            for(int i = 0; i < SIZE/2+1; i++) {
                for (int j = 0; j < SIZE; j++) {
                    int tmp = image[i][j];
                    image[i][j] = image[SIZE-1-i][j];
                    image[SIZE-1-i][j] = tmp;
                }
            }
        }
    }
    else if(choice == 5){
        cout << "Rotate (90), (180) or (270) degrees: ";
        cin >> degree;
        if(degree == 90){
            for(int i = 0; i <SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image2[j][SIZE-1-i] = image[i][j];
                }
            }
        }
        else if(degree == 180){
            for(int i = 0; i < SIZE/2+1; i++) {
                for (int j = 0; j < SIZE; j++) {
                    int tmp = image[i][j];
                    image[i][j] = image[SIZE-1-i][j];
                    image[SIZE-1-i][j] = tmp;
                }
            }
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE/2+1; j++){
                    int tmp = image[i][j];
                    image[i][j] = image[i][SIZE-1-j];
                    image[i][SIZE-1-j] = tmp;
                }
            }
        }
        else if(degree == 270){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image2[SIZE-1-j][i] = image[i][j];
                }
            }
        }
    }
    else if(choice == 6){
        cout << "Do you want to (d)arken or (l)ighten? ";
        char dl; cin >> dl;
        if (dl == 'd'){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image[i][j] /= 2;
                }
            }
        }
        else if(dl == 'l'){
            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    image[i][j] += (255-image[i][j])/2;
                }
            }
        }

    }
}
