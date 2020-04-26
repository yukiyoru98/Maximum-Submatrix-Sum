#include <iostream>
#include <limits>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

//function prototype
bool notInteger(int);


int main(){
    
    srand(unsigned(time(NULL)));//random seed
    
    int row=0;//num of rows
    int column=0;//num of columns
    
    //prompt for matrix's size
    cout << "Please enter number of rows(vertical direction) of matrix:\n";
    do{//avoid input that is not integer
        cin >> row;
    }while(notInteger(row)==true);
    
    cout << "Please enter number of columns(horizontal direction) of matrix:\n";
    do{//avoid input that is not integer
        cin >> column;
    }while(notInteger(column)==true);
    
    //matrix declaration
    int **matrix = new int*[row];//matrix is "an arrays of pointers to array"
    //let each of the pointers in "the array of pointers to array" point to the first position in each row in the matrix
    for(int m=0; m<row; m++){
        matrix[m] = new int[column];
    }
    
    
    //the user chooses to input numbers or randomly pick by cpu
    cout << "Enter(1)to input your own numbers \n(2)to randomly pick numbers(which will be limited between -100 ~ 100) by the computer\n";
    int choice=0;
    do{//avoid invalid input
        cin >> choice;
        if(notInteger(choice)==false);
        else{//choice is neither 1 or 2
            cout << "Invalid input! Please try again:";
        }
    }while((notInteger(choice)==true)||((choice!=1)&&(choice!=2)));
    
    if(choice==1){//the user wants to input his own numbers
        int input;
        //input numbers
        for(int m=0; m<row; m++){
            for(int n=0; n<column; n++){
                do{
                    cout << "Please enter the number for Row" << m+1 << "Column" << n+1 << endl;
                    cin >> input;
                }while(notInteger(input)==true);//avoid non-integer
                matrix[m][n] = input;
            }
        }
        //display matrix
        cout << "*Original Matrix*" << endl;
        for(int m=0; m<row; m++){
            cout << '|' ;
            for(int n=0; n<column; n++){
                cout  << setw(5)  << matrix[m][n] << " |";
            }
            cout << endl;
        }
    }
    else{//random pick numbers between -100~100 for matrix and display matrix
        
        cout << "*Original Matrix*\n\n";
        for(int m=0; m<row; m++){
            cout << '|' ;
            for(int n=0; n<column; n++){
                int sign = rand() % 2;//sign=0 means negative, =1 means positive
                matrix[m][n] = (pow(-1,sign)) * (rand() % 100);//give number to matrix[m][n]
                cout  << setw(5)  << matrix[m][n] << " |";
            }
            cout << endl;
        }
        
    }
    
    
    //search for maximum sum of sub-matrix
    
    //variables for saving the position of maxSum sub-matrix
    int maxStartx=0;
    int maxStarty=0;
    int maxEndx=0;
    int maxEndy=0;
    
    //maxSum saves the maximum sum(initially assume matrix[0][0] is the largest)
    int maxSum=matrix[0][0];
    
    //sum is to save the sum of every submatrix temporarily
    int sum=0;
    
    //search for every submatrix
    for(int starty=0; starty<row; starty++){
        for(int startx=0; startx<column; startx++){
            //start from matrix[startx][starty] in the beginning of each for-loop operation
            
            int xflag=startx, yflag=starty;//the x,yflags point to the next element to sum
            
            for(int stopy=starty; stopy<row; stopy++){
                for(int stopx=startx; stopx<column; stopx++){
                    
                    //summarize submatrix
                    for(yflag=starty; yflag<=stopy; yflag++){
                        for(xflag=startx; xflag<=stopx; xflag++){
                            sum += matrix[yflag][xflag];
                        }
                    }//end of summarization
                    
                    //compare with current maximum sum
                    if(sum>maxSum){//if bigger, record the position of the submatrix
                        maxSum=sum;
                        maxStartx=startx;
                        maxStarty=starty;
                        maxEndx=stopx;
                        maxEndy=stopy;
                    }
                    
                    sum=0;//reset sum for next submatrix summarization
                    //xflag=startx;
                }//search for the next submatrix
            }
        }
    }
    
    //show maximum sum and submatrix
    cout << "The submatrix with the maximum sum *" << maxSum << "* is" << endl;
    for(int m=maxStarty; m<=maxEndy; m++){
        cout << '|' ;
        for(int n=maxStartx; n<=maxEndx; n++){
            cout  << setw(5)  << matrix[m][n] << " |";
        }
        cout << endl;
    }
    
    //delete matrix after using "new"
    for(int m=0; m<row; m++){
        delete []matrix[m];
    }
    delete []matrix;
    
    system("pause");
    return 0;
}

//functions
bool notInteger(int input){//avoid non-integer input
    
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid input! Please try again:\n";
        return true;
    }
    else return false;
}
