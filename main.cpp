#include <iostream>
#include<cstring>
#include<cmath>
#define MAXN 10
using namespace std;
typedef struct {
    int row,col;
    int ma[MAXN][MAXN];
}Matrix;

Matrix get_matrix();
Matrix add(Matrix m1,Matrix m2);
Matrix sub(Matrix m1,Matrix m2);
Matrix mul(Matrix m1,Matrix m2);
Matrix get_Cofactor(Matrix m,int p,int q); //求余子式
Matrix get_Inverse(Matrix m);  //求逆矩阵
int get_determinant(Matrix m); //求行列式
void print_matrix(Matrix m);
void print_menu(); //打印菜单

int main()
{
    cout << "\t  Matrix calculator\n";
    cout << "\t\t\t by jokersio\n";

    while(1)
    {
        print_menu();
        char com;
        cin>>com;

        Matrix a,b,ans;

        switch (com)
        {
            case '1':
            {
                a=get_matrix();
                b=get_matrix();
                if(a.row==b.row&&a.col==b.col)
                {
                    ans=add(a,b);
                    print_matrix(ans);
                }
                else
                {
                    cout<<"Your input is illegal!\n";
                    cout<<"These two matrices have different sizes.\n";
                    cout<<"Please try again!\n";
                }
                break;
            }
            case '2':
            {
                a=get_matrix();
                b=get_matrix();
                if(a.row==b.row&&a.col==b.col)
                {
                    ans=sub(a,b);
                    print_matrix(ans);
                }
                else
                {
                    cout<<"Your input is illegal!\n";
                    cout<<"These two matrices have different sizes.\n";
                    cout<<"Please try again!\n";
                }
        }
            case '3':
            {
                a=get_matrix();
                b=get_matrix();
                if(a.col==b.row)
                {
                    ans=mul(a,b);
                    print_matrix(ans);
                }
                else
                {
                    cout<<"Your input is illegal!\n";
                    cout<<"These two matrices cannot be multiplied.\n";
                    cout<<"Please try again!\n";
                }
                break;
            }
            case '4':
            {
                a=get_matrix();
                if(a.col==a.row)
                {
                    cout<<"The determinant is:\n";
                    cout<<get_determinant(a)<<endl;
                }
                else
                {
                    cout<<"Your input is illegal!\n";
                    cout<<"This matrix is not a square matrix.\n";
                    cout<<"Please try again!\n";
                }
                break;
            }
            case '5':
            {
                a=get_matrix();
                if(a.col==a.row)
                {
                    if(get_determinant(a)==0)
                        cout<<"This matrix is not invertible\n";
                    else
                        print_matrix(get_Inverse(a));
                }
                else
                {
                    cout<<"Your input is illegal!\n";
                    cout<<"This matrix is not a square matrix.\n";
                    cout<<"Please try again!\n";
                }
                break;
            }
            case '6':
                return 0;
        }

    }
    return 0;
}

void print_menu()
{
    cout<<"\t\tMenu\n";
    cout<<"\t1.Matrix addition\n";
    cout<<"\t2.Matrix subtraction\n";
    cout<<"\t3.Matrix multiplication\n";
    cout<<"\t4.Matrix determinant\n";
    cout<<"\t5.Inverse matrix\n";
    cout<<"\t6.Quit\n";
}

Matrix get_matrix()
{
    Matrix m;
    cout<<"Please input the rows and columns of your matrix\n";
    cin>>m.row>>m.col;
    cout<<"Please input your matrix\n";
    for(int i=1;i<=m.row;i++)
        for(int j=1;j<=m.col;j++)
            cin>>m.ma[i][j];
    return m;
}

Matrix add(Matrix m1,Matrix m2)
{
    Matrix m;
    m.row=m1.row,m.col=m1.col;
    for(int i=1;i<=m.row;i++)
        for(int j=1;j<=m.col;j++)
            m.ma[i][j]=m1.ma[i][j]+m2.ma[i][j];
   return m;
}

Matrix sub(Matrix m1,Matrix m2)
{
    Matrix m;
    m.row=m1.row,m.col=m1.col;
    for(int i=1;i<=m.row;i++)
        for(int j=1;j<=m.col;j++)
            m.ma[i][j]=m1.ma[i][j]-m2.ma[i][j];
   return m;
}

Matrix mul(Matrix m1,Matrix m2)
{
    Matrix m;
    m.row=m1.row,m.col=m2.col;
    memset(m.ma,0,sizeof(m.ma));
    for(int i=1;i<=m.row;i++)
        for(int j=1;j<=m.col;j++)
            for(int k=1;k<=m1.col;k++)
                m.ma[i][j]+=m1.ma[i][k]*m2.ma[k][j];
   return m;
}

Matrix get_Cofactor(Matrix m,int p,int q)
{
    Matrix ans;
    int Row=1,Col=1,n=m.col;//n是原矩阵的阶数
    ans.col=ans.row=n-1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i!=p&&j!=q)
            {
                ans.ma[Row][Col]=m.ma[i][j];
                Col++;
                if(Col==n)
                    Col=1,Row++;
            }
        }
    return ans;
}

int get_determinant(Matrix m)
{
    int D=0,k=1,n=m.col;

    if(n==1)
        return m.ma[1][1];

    for(int i=1;i<=n;i++)
    {
        D+=k*m.ma[1][i]*get_determinant(get_Cofactor(m,1,i));
        k*=-1;
    }
    return D;
}

void print_matrix(Matrix m)
{
    cout<<"The answer is:\n";
    for(int i=1;i<=m.row;i++)
    {
        for(int j=1;j<=m.col;j++)
            cout<<m.ma[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

Matrix get_Inverse(Matrix m)
{
    Matrix ans;
    int n=m.col;//n是原矩阵的阶数
    ans.col=ans.row=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            ans.ma[i][j]=(int)pow(-1,i+j)*get_determinant(get_Cofactor(m,i,j));
        }
    return ans;
}
