#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
const int N=1010,K=30;
struct str_t{
    int t;
    bool vis;
    char str[K];
    str_t(){
        this->vis=false;
    }
    bool operator <(const str_t &x)const{
        return strcmp(this->str,x.str)<0;
    }
};
vector<str_t> e[K];
int cases,n,in[K],out[K],fa[K];
bool used[K];
stack<char*> stk; 
inline int findfa(int x){
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
inline void bing(int x,int y){
    int a=findfa(x),b=findfa(y);
    if(a==b)return;
    fa[b]=a;
}
bool have_euler_path(int &x){
    int indeg=0,outdeg=0;
    x=-1;
    for(int i=1;i<K;i++){
        if(used[i]){
            if(in[i]==out[i])continue;
            else if(in[i]-out[i]==1)indeg++;
            else if(out[i]-in[i]==1)outdeg++,x=i;
            else return false;
        }
    }
    if(!indeg && !outdeg)return true;
    else if(indeg==1 && outdeg==1)return true;
    else return false;
}
bool is_only_circle(){
    int cnt=0;
    for(int i=1;i<K;i++){
        if(used[i] && fa[i]==i)cnt++;
    }
    return cnt==1;
}
void find_euler_path(int x){
    int size=e[x].size();
    for(int i=0;i<size;i++){
        if(!e[x][i].vis){
            e[x][i].vis=true;
            find_euler_path(e[x][i].t);
            stk.push(e[x][i].str);
        }
    }
}
void print_euler_path(){
    printf("%s",stk.top());
    stk.pop();
    while(!stk.empty()){
        printf(".%s",stk.top());
        stk.pop();
    }
    printf("\n");
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d",&cases);
    while(cases--){
        scanf("%d",&n);
        for(int i=1;i<K;i++){
            fa[i]=i;
            e[i].clear();
        }
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        memset(used,false,sizeof(used));
        for(int i=1;i<=n;i++){
            char temp[K];
            scanf("%s",temp);
            str_t now;
            int st=temp[0]-'a'+1;
            int et=temp[strlen(temp)-1]-'a'+1;
            now.t=et;
            now.vis=false;
            memcpy(now.str,temp,sizeof(now.str));
            e[st].push_back(now);
            used[st]=used[et]=true;
            in[et]++,out[st]++;
            bing(st,et);
        }
        int temp=1;
        if(have_euler_path(temp) && is_only_circle()){
            for(int i=1;i<K;i++){
                if(used[i])sort(e[i].begin(),e[i].end());
            }
            if(temp==-1){
                for(int i=1;i<K;i++){
                    if(used[i]){
                        find_euler_path(i);
                        break;
                    }
                }
            }
            else find_euler_path(temp);
            print_euler_path();
        }
        else printf("***\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}