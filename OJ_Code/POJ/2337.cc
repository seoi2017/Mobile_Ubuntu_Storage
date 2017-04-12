#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define N 1010
#define LEN 30
using namespace std;
struct stack_t{
    int top,s[N];
    void init(){
        top=0;
        memset(s,0,sizeof(s));
    }
    void push(int x){
        s[++top]=x;
    }
}stack;
int n,top,in[LEN],out[LEN],map[LEN][LEN],vis[N]={0};
int st=0,et=0,tot=1;
string s[N];
void dfs(int x,int &cnt){
    stack.push(x);
    for(int i=1;i<LEN;i++){
        if(map[x][i]){
            map[x][i]--;
            cnt++;
            dfs(i,cnt); 
            break;
        }
    }
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false);
    int cases;
    cin>>cases;
    while(cases--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>s[i];
        sort(s+1,s+1+n);
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        st=et=0;
        tot=1;
        for(int i=1;i<=n;i++){
            int st=s[i][0]-'a'+1;
            int et=s[i][s[i].length()-1]-'a'+1;
            in[et]++;
            out[st]++;
            map[st][et]++;
        }
        for(int i=1;i<LEN;i++){
            if(out[i]-in[i]==1 && !st)st=i;
            if(in[i]-out[i]==1 && !et)et=i;
            if(abs(out[i]-in[i])==1 && et && st){
                cout<<"***"<<endl;
                goto ended;
            }
        }
        if(!st && !et){
            cout<<"***"<<endl;
            goto ended;
        }
        dfs(st,tot);
        if(tot!=n){
            cout<<"***"<<endl;
        }
        else{
            for(int i=1;i<stack.top;i++){
                for(int j=1;j<=n;j++){
                    if(!vis[j] && s[j][0]==stack.s[i]){
                        vis[j]=1;
                        cout<<s[j]<<".";
                        break;
                    }
                }
            }
        }
        ended:;
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}