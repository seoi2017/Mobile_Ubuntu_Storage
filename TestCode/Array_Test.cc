#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    static int a[100010]={0};
    a[9]=9;
    printf("%d %d",a[1],a[9]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}