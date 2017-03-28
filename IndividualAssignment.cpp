#define X 2
#define Y 2
#define Z 2

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

int A[X][Y];
int B[Y][Z];
int C[X][Z];

struct x {
	int row;
};


//multiply the matrix through different threads//
void *multiply(void *arg)
{
	struct x *num = (struct x *)arg;
	int row, col, inner;
	row = num->row;

		for(col = 0; col < Z; col++) {
			for(inner = 0; inner < Y; inner++) {
				C[row][col] += A[row][inner] * B[inner][col];

			}
		}

pthread_exit(0);
}

int main() {

	cout << "Enter the rows and columns for the first matrix to be multiplied:" << endl;
	for(int index_x = 0; index_x < X; index_x++){
        	for(int index_y = 0; index_y < Y; index_y++){
		cout << "Enter a value for Row " << index_x << " Col " <<  index_y << endl;
            	   cin >> A[index_x][index_y];
	}
    }


	cout << "Enter the rows and columns for the second matrix to be multiplied:" << endl;
	for(int index_y2 = 0; index_y2 < Y; index_y2++){
        	for(int index_x2 = 0; index_x2 < X; index_x2++){
		cout << "Enter a value for Row " << index_y2 << " Col " <<  index_x2 << endl;
           	    cin >> B[index_y2][index_x2];
	}
    }

pthread_t multiplyT[X];
pthread_attr_t attr;
void * status;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


for(int i = 0; i < X; i++)
{
	struct x *num = (struct x *) malloc(sizeof(struct x));
	num->row = i;

	int rc = pthread_create(&multiplyT[i], NULL,multiply,(void*)num);
	if(rc)
{
	cout<<"Unable to create Thread"<<endl;
exit(-1);
}


}

pthread_attr_destroy(&attr);
for(int i=0;i<X;i++)
{
int rc = pthread_join(multiplyT[i], &status);
if(rc){
cout<<"Unable to join"<<endl;
exit(-1);
}
cout<<"Thread is finished"<<endl;

}

cout << endl;
cout << "The multiplied matrix is " << endl;

//print the multiplied matrix//
	for(int index_x = 0; index_x < X; index_x++){
        	for(int index_z = 0; index_z < Z; index_z++){
            	    cout <<""<< C[index_x][index_z]<<" ";
	}
	cout<<endl;
}
 pthread_exit(NULL);
}
