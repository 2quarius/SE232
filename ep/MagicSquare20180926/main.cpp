//https://tfetimes.com/c-magic-squares-of-odd-order/
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
void inc(int& a,int n)
{
    if(++a==n) a=0;
}
void dec(int& a,int n)
{
    if(--a<0) a=n-1;
}
int main() {
    int n;
    cin >> n;
    if(!(n&1)){cout << "oops!This is an even number!";}
    else {
        int x = n/2,y = 0, c = 0;
        int magicSquare[n*n];
        memset(magicSquare,0,n*n* sizeof(int));
        while(c<n*n)
        {
            if(!magicSquare[x+y*n])
            {
                magicSquare[x+y*n] = c+1;
                inc(x,n);dec(y,n);
                c++;
            }
            else
            {
                dec(x,n);inc(y,n);inc(y,n);
            }
        }
        ostringstream cvr;cvr << n*n;
        int l = cvr.str().size();

        for(int i = 0;i<n;i++)
        {
            int yy = i*n;
            for(int j = 0;j<n;j++)
            {
                cout << setw(l+2) << magicSquare[yy+j];
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    //advance: one solution only
    int A=0,B=0,C=0,D=0,E=0,F=0,G=0,H=0,I=0;
    cin >> A >> B >> C;
    cin >> D >> E >> F;
    cin >> G >> H >> I;

    if(B!=0&&D!=0){
        I = (D+B)/2;
        if(A!=0){
            E = (A+I)/2;
            F = 2*E - D;
            C = 3*E - F -I;
            G = 3*E - A -D;
            H = 3*E - B -E;
        }
        else if(F!=0||H!=0){
            if(H){
                E = (B+H)/2;
                F = 2*E - D;
            }
            else {
                E = (D+F)/2;
                H = 2*E - B;
            }
            A = 2*E - I;
            C = 3*E - F - I;
            G = 2*E - C;
        }
        else if(C!=0||G!=0){
            if(C){
                E = C + I - D;
                G = 2*E -C;
            }
            else{
                E = G + I -B;
                C = 2*E -G;
            }
            A = 2*E - I;
            F = 2*E - D;
            H = 2*E - B;
        }
    }
    else if(B!=0&&F!=0){
        G = (B+F)/2;
        if(C!=0){
            E = (C+G)/2;
            H = 2*E - B;
            I = 3*E - H - G;
            A = 3*E - C -B;
            D = 3*E - F -E;
        }
        else if(H!=0||D!=0){
            if(D){
                E = (F+D)/2;
                H = 2*E - B;
            }
            else {
                E = (B+H)/2;
                D = 2*E - F;
            }
            C = 2*E - G;
            I = 3*E - H - G;
            A = 2*E - I;
        }
        else if(I!=0||A!=0){
            if(I){
                E = I + G - B;
                A = 2*E -I;
            }
            else{
                E = A + G -F;
                I = 2*E -A;
            }
            C = 2*E - G;
            H = 2*E - B;
            D = 2*E - F;
        }
    }
    else if(D!=0&&H!=0){
        C = (D+H)/2;
        if(G!=0){
            E = (G+C)/2;
            B = 2*E - H;
            A = 3*E - B -C;
            I = 3*E - G -H;
            F = 3*E - D -E;
        }
        else if(B!=0||F!=0){
            if(F){
                E = (D+F)/2;
                B = 2*E - H;
            }
            else {
                E = (H+B)/2;
                F = 2*E - D;
            }
            G = 2*E - C;
            I = 3*E - B - C;
            I = 2*E - A;
        }
        else if(A!=0||I!=0){
            if(A){
                E = A + C - H;
                I = 2*E -A;
            }
            else{
                E = I + C -D;
                A = 2*E -I;
            }
            G = 2*E - C;
            B = 2*E - H;
            F = 2*E - D;
        }
    }
    else if(F!=0&&H!=0){
        A = (H+F)/2;
        if(I!=0){
            E = (I+A)/2;
            D = 2*E - F;
            G = 3*E - D -A;
            C = 3*E - I -F;
            B = 3*E - H -E;
        }
        else if(D!=0||B!=0){
            if(B){
                E = (H+B)/2;
                D = 2*E - F;
            }
            else {
                E = (D+F)/2;
                B = 2*E - H;
            }
            I = 2*E - A;
            G = 3*E - D - A;
            C = 2*E - G;
        }
        else if(C!=0||G!=0){
            if(G){
                E = G + A - F;
                C = 2*E -G;
            }
            else{
                E = C + A -H;
                G = 2*E -C;
            }
            I = 2*E - A;
            D = 2*E - F;
            B = 2*E - H;
        }
    }


    if(A!=0&&G!=0){
        if(F!=0){
            E = A+G-F;
            C = 2*E -G;
            //cout << A << G << F << E<<endl;
        }
        else if(C!=0){
            E = (G+C)/2;
            F = A+G-E;
        }
        D = 2*E-F;
        B = 3*E-A-C;
        H = 2*E-B;
        I = 3*E-G-H;
    }
    else if(A!=0&&C!=0){
        if(H!=0){
            E = C+A-H;
            I = 2*E -A;
        }
        else if(I!=0){
            E = (A+I)/2;
            H = C+A-E;
        }
        B = 2*E-H;
        F = 3*E-C-I;
        D = 2*E-F;
        G = 3*E-A-D;
    }
    else if(C!=0&&I!=0){
        if(D!=0){
            E = I+C-D;
            G = 2*E -C;
        }
        else if(G!=0){
            E = (G+C)/2;
            D = I+C-E;
        }
        F = 2*E-D;
        H = 3*E-I-G;
        B = 2*E-H;
        A = 3*E-C-B;
    }
    else if(G!=0&&I!=0){
        if(B!=0){
            E = G+I-B;
            A = 2*E -I;
        }
        else if(A!=0){
            E = (I+A)/2;
            B = G+I-E;
        }
        H = 2*E-B;
        D = 3*E-G-A;
        F = 2*E-D;
        C = 3*E-I-F;
    }

    if(D!=0&&C!=0){
        H = 2*C-D;
        if(G!=0){
            E =(C+G)/2;
            F = 2*E-D;
            I = 3*E-G-H;
            A = 2*E-I;
            B = 2*E-H;
        }
        else if(A!=0){
            E = A+C-H;
            B=2*E-H;
            F=2*E-D;
            G=3*E-A-D;
            I=2*E-A;
        }
        else if(F!=0){
            E = (D+F)/2;
            B = 2*E-H;
            G = 2*E-C;
            A = 3*E-D-G;
            I = 2*E-A;
        }
    }
    if(B!=0&&I!=0){
        D = 2*I-B;
        if(A!=0){
            E =(I+A)/2;
            H = 2*E-B;
            G = 3*E-A-D;
            C = 2*E-G;
            F = 2*E-D;
        }
        else if(C!=0){
            E = C+I-D;
            F=2*E-D;
            H=2*E-B;
            A=3*E-C-B;
            G=2*E-C;
        }
        else if(H!=0){
            E = (B+H)/2;
            F = 2*E-D;
            A = 2*E-I;
            C = 3*E-B-A;
            G = 2*E-C;
        }
    }
    if(F!=0&&G!=0){
        B = 2*G-F;
        if(C!=0){
            E =(C+G)/2;
            D = 2*E-F;
            A = 3*E-C-B;
            I = 2*E-A;
            H = 2*E-B;
        }
        else if(I!=0){
            E = I+G-B;
            H=2*E-B;
            D=2*E-F;
            C=3*E-I-F;
            A=2*E-I;
        }
        else if(D!=0){
            E = (D+F)/2;
            H = 2*E-B;
            C = 2*E-G;
            I = 3*E-F-C;
            A = 2*E-I;
        }
    }
    if(H!=0&&A!=0){
        F = 2*A-H;
        if(I!=0){
            E =(A+I)/2;
            B = 2*E-H;
            C = 3*E-I-F;
            G = 2*E-C;
            D = 2*E-F;
        }
        else if(G!=0){
            E = G+A-F;
            D=2*E-F;
            B=2*E-H;
            I=3*E-G-H;
            C=2*E-G;
        }
        else if(B!=0){
            E = (H+B)/2;
            D = 2*E-F;
            I = 2*E-A;
            G = 3*E-H-I;
            C = 2*E-G;
        }
    }
    cout << A <<" "<< B << " "<<C<<endl;
    cout << D <<" "<< E << " "<<F<<endl;
    cout << G <<" "<< H << " "<<I<<endl;
    return 0;
}