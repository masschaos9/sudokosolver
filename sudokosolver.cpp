//
//  sudokosolver.cpp
//  helloworld
//
//  Created by Siddhi Vora on 13/07/24.
//


#include <iostream>
#include<vector>
#include<map>
using namespace std;

int checkrows(const vector<vector<char>> &A)
{
    
    for(int i=0;i<9;i++)
    {
        map<char,int> hash;
        for(int j=0;j<9;j++)
        {
            if(A[i][j]!='.'&&hash.find(A[i][j])!=hash.end())
            return 0;
            hash[A[i][j]]++;
        }
        hash.clear();
    }
    return 1;
}

int checkcolumns(const vector<vector<char>> &A)
{
    
    for(int i=0;i<9;i++)
    {
        map<char,int> hash;
        for(int j=0;j<9;j++)
        {
            if(A[j][i]!='.'&&hash.find(A[j][i])!=hash.end())
            return 0;
            hash[A[j][i]]++;
        }
        hash.clear();
    }
    return 1;
}

int checkboxes(const vector<vector<char>> &A)
{
    
    for(int row=0;row<9;row+=3)
    {
        for(int col=0;col<9;col+=3)
        {
            map<char,int> hash;
            for(int i=0;i<9;i++)
            {
                char t=A[3*(row/3)+i/3][3*(col/3)+i%3];
                if(t!='.'&&hash.find(t)!=hash.end())
                return 0;
                hash[t]++;
            }
            hash.clear();
        }
    }
    return 1;
}


bool isValidMove(vector<vector<char>> &board,int row,int col,int dig)
{
    for(int i=0;i<9;i++)
    {
        if(board[i][col]-'0'==dig)
        return false;
        if(board[row][i]-'0'==dig)
        return false;
        if(board[3*(row/3)+i/3][3*(col/3)+i%3]-'0'==dig)
        return false;
    }
    return true;
}

bool solver(vector<vector<char>> &board)
{
    for(int i=0;i<board.size();i++)
    {
        for(int j=0;j<board[0].size();j++)
        {
            if(board[i][j]=='.')
            {
                for(int k=1;k<=9;k++)
                {
                    
                    if(isValidMove(board,i,j,k))
                    {
                        board[i][j]=(char)(k+'0');
                        bool cansolvefurther=solver(board);
                        
                        if(cansolvefurther)//If u can solve further u keep the value as it is and go ahead
                        return true;
                        else
                        board[i][j]='.';
                        
                    }
                    
                }
                if(board[i][j]=='.')//No move was found valid for i,j
                return false;
            }
            
        }
    }
    return true;
    
    
}
void solveSudoku(vector<vector<char>> &A) {
    if(solver(A))
    {
        for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    }
    else
    cout<<"No solution";
    
}

int main()
{
    // 0 means unassigned cells
    // Enter your board here
    int grid[9][9] = { { 3, 0, 6, 5, 0, 8, 0, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 0, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 0, 2, 0, 6, 3, 0, 0 } };
                       
    vector<vector<char>> characterGrid(9,vector<char>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                characterGrid[i][j] = '.';
            } else {
                characterGrid[i][j] = '0' + grid[i][j];
            }
        }
    }
    int r=checkrows(characterGrid);
    int c=checkcolumns(characterGrid);
    int b=checkboxes(characterGrid);
    if(r&b&c)
    solveSudoku(characterGrid);
    else
    cout<<"InValid Grid";
 
    return 0;
}
