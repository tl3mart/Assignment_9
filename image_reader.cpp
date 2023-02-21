// Assignment #9
//Thomas Martinez SYDE 121
\

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;

void readimage(string& file_name, ifstream& infile,  int& width, int& length, int& grey_max, string& format, string& line)
{
    getline(infile, format);
    getline (infile, line);
    infile >> width;
    infile >> length;
    infile >> grey_max;
}
int** getting_w_l(int w,int l, ifstream& infile, string file_name)
{

int** pixels = new int*[l];
for (int i = 0; i < l; i++) {
  pixels[i] = new int[w];
  cout << "\n";
 
  for (int j = 0; j < w; j++) {
    infile >> pixels[i][j];
    
  }
}

  
return (pixels);
}

void invert(int l,  int w, string line, string format, int grey_max, int** pixels )
{
  ofstream openfile;
  
  int inverted;
  openfile.open("img_invert.ppm");
  
  openfile << format <<"\n";
  openfile << line << "\n";
  openfile << w << " " << l <<"\n";
  openfile << grey_max;

  for (int i = 0; i < l; i++) {
  
 
  openfile << "\n";
  for (int j = 0; j < w; j++) {
    

    pixels[i][j] = abs(255 - pixels[i][j]);
    openfile << pixels[i][j];
    openfile << " ";
  }
}


openfile.close();

}

void avr_row(int w, int l, int** pixels)
{
  
ofstream outdata;

int data[w];

outdata.open("OutData.txt");

for (int i = 0; i < l; i++ ){
  double sum = 0;
for (int j =0; j < w; j++)
{
   data[i] =  pixels[i][j];
   sum =  data[i] + sum; 
   
}
outdata << "Average for row " << i << " is: " << sum/l;
outdata << "\n";

}

outdata.close();

}
void avr_col(int w, int l, int** pixels)
{
double sum_1;
ofstream openfile;
openfile.open("OutData.txt", ios::app);
  for (int j =0 ; j < w; j++)
  {
  sum_1 = 0;
    for ( int i = 0; i< l; i++){
    sum_1 = pixels[i][j] + sum_1;
  }
openfile << "The average for " << j <<  " column is "  << sum_1/w << "\n";
}
openfile.close();
}

double avrg_image( int l, int w, int** pixels)
{
  double sum = 0;
  ofstream openfile;
  openfile.open("OutData.txt", ios::app);
for (int i =0 ; i < l; i++)
  {

    for ( int j = 0; j< w; j++){
    sum = pixels[i][j] + sum;
  }

}
double average = sum/(l*w);
openfile << "The average pixel number is " << average << "\n";
openfile.close();
return(average);

}

double std_image (double average, int l, int w, int** pixels)
{
ofstream openfile;
openfile.open("OutData.txt", ios::app);
  double sum, STD;
for (int i = 0; i < l; i++)
        for (int j = 0; j < w; j++) 
            sum = pow(pixels[i][j]-average,2) + sum;
    
    

    openfile << "The standard deviation is " << STD;
return (sqrt(sum/((w*l)-1)));
}

void distribution(double average, double STD)
{
ofstream openfile;
openfile.open("OutData.txt", ios::app);

for (int i = 1; i <=3; i++)
{
  

 openfile << "\n" << "Average + " <<  i <<"STD: " << (average + (i * STD)) << "\n";
 openfile << "Average - " << i <<"STD: " << (average - (i * STD));

}

openfile.close();

}

int main()
{
string file_name, format, line;
ifstream infile;
cout << "What is the name of your file ?\n";
cin >> file_name;
int width, length, grey_max;
double average, STD;

infile.open(file_name);

readimage(file_name, infile, width, length, grey_max, format, line);
int** pixels = getting_w_l(width, length, infile, file_name);
avr_row (width, length, pixels);
avr_col (width, length, pixels);
average = avrg_image(length, width,pixels);
STD = std_image (average, length, width, pixels);
distribution(average, STD);
invert (length, width, line, format, grey_max, pixels);

infile.close( );

delete pixels;

return 0;
}