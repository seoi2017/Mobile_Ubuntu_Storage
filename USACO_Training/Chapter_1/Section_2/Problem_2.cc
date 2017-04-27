//USACO Training Chapter 1,Section 2,Problem 2
//Powered By Inv.
//Accepted at 2017/4/27 15:09
#include<bits/stdc++.h>
using namespace std;
int n;
char c[128][128],s[128][128],t[128][128];
inline void turn90(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=c[n-j+1][i];
        }
    }
}
inline void turn180(){
    int p[128][128];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            p[i][j]=c[n-j+1][i];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=p[n-j+1][i];
        }
    }
}
inline void turn270(){
    int p[128][128];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=c[n-j+1][i];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            p[i][j]=s[n-j+1][i];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=p[n-j+1][i];
        }
    }
}
inline void turnf(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            s[i][j]=c[i][n-j+1];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            c[i][j]=s[i][j];
        }
    }
}
inline bool comp(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(s[i][j]==t[i][j])continue;
            else return false;
        }
    }
    return true;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
           scanf("%c",&c[i][j]);
       }
       scanf("\n");
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
           scanf("%c",&t[i][j]);
       }
       scanf("\n");
    }
    //============================
    if(comp()){
        printf("6\n");
        goto tag;
    }
    turn90();
    if(comp()){
        printf("1\n");
        goto tag;
    }
    turn180();
    if(comp()){
        printf("2\n");
        goto tag;
    }
    turn270();
    if(comp()){
        printf("3\n");
        goto tag;
    }
    turnf();
    if(comp()){
        printf("4\n");
        goto tag;
    }
    turn90();
    if(comp()){
        printf("5\n");
        goto tag;
    }
    turn180();
    if(comp()){
        printf("5\n");
        goto tag;
    }
    turn270();
    if(comp()){
        printf("5\n");
        goto tag;
    }
    printf("7\n");
    tag:;
    fclose(stdin);
    fclose(stdout);
    return 0;
}