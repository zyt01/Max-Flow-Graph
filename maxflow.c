//
//  maxflow.c
//  Max Flow Graph -- Ford-Fulkerson
//
//  Created by 张宇彤 on 15/9/23.
//  Copyright (c) 2015年 张宇彤. All rights reserved.
//
#include <stdio.h>

////////////////////////////////  Basic Definitions  /////////////
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define MAXLINE 1000
#define oo 1000000000

////////////////////////////////  Declarations  //////////////////
int n;  // number of nodes
int e;  // number of edges
int capacity[MAX_NODES][MAX_NODES]; // capacity matrix
int flow[MAX_NODES][MAX_NODES];     // flow matrix
int color[MAX_NODES]; // needed for breadth-first search
int pred[MAX_NODES];  // array to store augmenting path
char temps[30],temps2[30],fbuf[30];//tempname
int names[MAX_NODES];//name

int min (int x, int y) {
    return x<y ? x : y;  // returns minimum of x and y
}

///////////////  A Queue for Breadth-First Search  /////////////////////////
int head,tail;
int q[MAX_NODES+2];

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

/////////////////  Breadth-First Search for an augmenting path  ///////////////////
int bfs (int start, int target) {
    int u,v;
    for (u=0; u<=n-1; u++) {
        color[names[u]] = WHITE;
    }
    head = tail = 0;
    enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
        u = dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
        for (v=0; v<=n-1; v++) {
            if (color[names[v]]==WHITE && capacity[u][names[v]]-flow[u][names[v]]>0) {
                enqueue(names[v]);
                pred[names[v]] = u;
            }
        }
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

////////////////////  Ford-Fulkerson Algorithm   ////////////////////////
int max_flow (int source, int sink) {
    int i,j,u;
    // Initialize empty flow.
    int max_flow = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            flow[names[i]][names[j]] = 0;
        }
    }
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
        // Determine the amount by which we can increment the flow.
        int increment = oo;
        for (u=sink; pred[u]>=0; u=pred[u]) {
            increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
        }
        // Now increment the flow.
        for (u=sink; pred[u]>=0; u=pred[u]) {
            flow[pred[u]][u] += increment;
            flow[u][pred[u]] -= increment;
        }
        max_flow += increment;
    }
    // No augmenting path anymore. We are done.
    return max_flow;
}

/////////  Reading the input file and the main program   ////////////
void read_input_file() {
    int a,b,c,i,j,f,k;
    FILE* input = fopen("test.net","r");
    // read number of nodes and edges
    fscanf(input,"%s      %d",&temps[0],&n);
    // initialize empty capacity matrix
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            capacity[names[i]][names[j]] = 0;
        }
    }
    // read nodes names
    for (i=0; i<n; i++) {
        fscanf(input,"%d %d",&f,&k);
        names[f] = k;
    }
    // read number of nodes and edges
    fscanf(input,"%s      %d",&temps2[0],&e);
    // read edge capacities
    for (i=0;i<e;i++) {
        fscanf(input,"%d %d  %d",&a,&b,&c);
        capacity[a][b] = c;
    }
    /*************************************
     while(fgets(fbuf,sizeof(fbuf),input)){
     sscanf(fbuf,"%d %d  %d",&a,&b,&c);
     capacity[a][b] = c;
     }
     *************************************/
    fclose(input);
}
/////////////////////    print    ////////////////////
void print(){
    int i=0,j,t;
    for(i=0;i<n;i++){
        printf("\t%d",names[i]);
    }
    printf("\n");
    for(i=0;i<n-1;i++){
        printf("%d",names[i]);
        for(t=0;t<=i;t++)printf(" \t");
        for(j=i+1;j<n;j++){
            printf("\t%d",max_flow(names[i],names[j]));
        }
        printf("\n");
    }
}

////////////////////////// inputf ///////////////////
void inputf(){
    FILE *fp;
    int i=0,j,t;
    char fname[MAXLINE],stream[MAXLINE];
    sprintf(fname,"%s%s", "result", ".txt");
    if((fp=fopen(fname,"w+"))==NULL)
    {
        printf("Can not open %s file!\n", fname);
        return;
    }
    /////////////    print    //////////
    
    for(i=0;i<n;i++){
        fprintf(fp,"\t%d",names[i]);
    }
    fprintf(fp,"\n");
    for(i=0;i<n-1;i++){
        fprintf(fp,"%d",names[i]);
        for(t=0;t<=i;t++)fprintf(fp," \t");
        for(j=i+1;j<n;j++){
            fprintf(fp,"\t%d",max_flow(names[i],names[j]));
        }
        fprintf(fp,"\n");
    }
    ////////////////////////////////////
    
    fclose(fp);
}//end inputf

/////////////////////    test     ////////////////////
int main () {
    
    read_input_file();
    
    print();
    
    inputf();
    
    return 0;
}