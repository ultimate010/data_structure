//邻接矩阵
#include <iostream>
#include<limits.h>

using namespace std;
#define maxValue INT_MAX
#define maxEdges 30
#define maxVertices 10

typedef char VType; //数据类型
typedef int WType;  //权值类型
typedef struct
{
  VType VerticesList[maxVertices];
  int Edge[maxVertices][maxVertices];
  int numVertices, numEdges;

}MGraph;
//邻接表


typedef struct node  //链入结点
{
  int dest;   //目标顶点下标
  //	WType cost;  //边权值
  struct node*link;  //下一个链入指针
}EdgeNode;

typedef struct VertexNode //顶点结点
{
  VType data;
  EdgeNode*first;
}VertexNode;

typedef struct ALGraph
{
  VertexNode VerticesList[maxVertices];
  int numVertices, numEdges;
}ALGraph;


typedef char TElemType;
typedef struct Node{
  TElemType data;
  struct Node*fchild, *nsibling;
}CSNode, *CSTree;


void convert(MGraph& G1, ALGraph& G2)  //将邻接矩阵转化为邻接表，用的邻接表是队列，只有first表头，从后往前插法，老师的答案中是循环队列
{
  int i,j;
  /*bug why you new EdgeNode in here*/
  //EdgeNode *p = new EdgeNode;
  EdgeNode *p = NULL;
  for (i = 0; i < G1.numVertices; i++)
  G2.VerticesList[i].data = G1.VerticesList[i];
  G2.numVertices = G1.numVertices;
  G2.numEdges = G1.numEdges; //初始化，复制数据
  for (i = 0; i < G1.numVertices; i++)
  {
    G2.VerticesList[i].first = NULL;
    //		G2.VerticesList[i].first->link = NULL;
    for(j = 0; j < G1.numVertices; j++)
    {
      if ( i != j &&G1.Edge[i][j] != 0)
      {
	p = new EdgeNode;
	p->dest = j;

	//	p->cost = GetWeight(G1, i, j);
	/* bug 这儿就是前插法建立单链表没啥特别的你好好看看链表 */
	p->link = G2.VerticesList[i].first;     //从后往前插
	G2.VerticesList[i].first = p;
      }
    }
  }
}

void Construct(MGraph &G)  //初始化邻接矩阵
{
  int i,j;
  cout << "请输出顶点个数：";
  cin >> G.numVertices;
  cout << "请输入边的个数：";
  cin >> G.numEdges;
  cout << "请输入顶点信息" <<endl;
  for (i = 0; i < G.numVertices; i++)
  {
    cin >> G.VerticesList[i];
  }

  cout << "请输入边的信息:"<<endl;

  for (i = 0; i < G.numVertices; i++)
  for(j = 0; j < G.numVertices;j++)
  {
    if (i != j)
    {

      cout << "<" << i << " " << j << ">";
      cin >> G.Edge[i][j];
    }
    else
    G.Edge[i][j] = 0;
  }
}


/* bug 区分用引用和不用的区别,还有const的使用 */
//void outputGraph(ALGraph G)  //输出邻接表
void outputGraph(const ALGraph & G)//输出邻接表
{
  int i = 0;
  /* bug 记住初始化为NULL这个习惯很重要 */
  //EdgeNode *p;
  EdgeNode * p = NULL;
  for( i = 0; i < G.numVertices; i++)
  {
    cout << G.VerticesList[i].data ;
    p = G.VerticesList[i].first;
    while(p  != NULL)
    {
      cout << "->" << G.VerticesList[p->dest].data ;
      p = p->link;
    }
    cout << endl;
  }
}

int FirstNeighbor(MGraph& G, int v)  //邻接矩阵中找顶点的第一个邻接结点，将邻接矩阵转换成树的时候要用
{
  if (v != -1)
  {
    for(int col= 0; col < G.numVertices;col++)
    {
      if (G.Edge[v][col] == 1)
      {
	return col;
      }
    }
  }
  return -1;
}


int NextNeighbor(MGraph & G, int v, int w)  //找邻接矩阵在v邻接结点后的下个邻接结点，将邻接矩阵转换成树的时候要用
{
  int col;
  if (v != -1 && w != -1)
  {
    for(col = w+1; col < G.numVertices;col++)
    {
      if (G.Edge[v][col] == 1)
      {

	return col;
      }

    }
  }
  return -1;
}

CSTree DFS(MGraph& G, int v, int visited[], int j) //一次深度优先遍历生成一棵树，包括树的根结点
{
  visited[v] = 1;
  CSTree p = new CSNode;
  p->data = G.VerticesList[v];
  p->fchild = p->nsibling = NULL;
  int w = FirstNeighbor(G, v);
  CSTree next = NULL;
  while(w != -1)
  {
    if (!visited[w])
    {
      if (j == 0)
      {
	j++;
	p->fchild = DFS(G, w, visited, j);
	next = p->fchild;
      }else{
	j++;
	/*  bug 建立子女兄弟树方法错误*/
	next->nsibling =  DFS(G, w, visited, j);
	next = next->nsibling;
      }
    }
    w = NextNeighbor(G,v,w);
  }
  return p;
}

void G_To_F(MGraph& G, CSTree& T)  //将每次生成的树连成森林
{
  int *visited = new int[G.numVertices];
  int i = 0,j = 0;
  CSTree p = T;
  for (i = 0; i < G.numVertices; i++)
  {
    visited[i] = 0;
  }
  for (i = 0; i < G.numVertices; i++)
  {
    if (!visited[i])
    {
      if (j == 0)
      {
	T = DFS(G,i,visited,0);
	p = T;
	j++;
      }
      else
      {
	p->nsibling = DFS(G, i, visited,0);
	p = p->nsibling;
      }
    }
  }
  /* bug Don't forget delete */
  delete [] visited;
}

void outputT(const CSTree& T, int k) //输出子女兄弟森林，上次作业中的算法
{
  if (T != NULL)
  {
    for (int i= 0; i < k; i++){
      //根据层次打印
      cout << "\t";
    }
    /* bug 算法,先输出本身,再第一个儿子,再兄弟 */
    cout << T->data << endl;
    CSTree p = T->fchild;
    while(p){
      outputT(p,k + 1);
      p = p->nsibling;
    }
  }
}


void clearGraph(ALGraph& G) //将动态创建的邻接表释放
{
  int i = 0;
  EdgeNode *p;
  for(i = 0; i < G.numVertices; i++)
  {
    while (G.VerticesList[i].first != NULL)
    {
      p = G.VerticesList[i].first;
      G.VerticesList[i].first= p->link;
      delete p;
    }
  }
}



void clearForest(CSTree& T)  //将动态创建的森林释放
{
  if (T != NULL)
  {
    clearForest(T->fchild);
    clearForest(T->nsibling);
    delete T;
    T = NULL;

  }
}

/* for test */
void testConstruct(MGraph &G){
  G.numVertices = 5;
  G.numEdges = 6;
  int i = 0,j = 0;
  for (i = 0; i < G.numVertices; i++)
  {
    G.VerticesList[i] = 'a' + i;
  }

  for (i = 0; i < G.numVertices; i++){
    for(j = 0; j < G.numVertices;j++)
    {
      G.Edge[i][j] = 0;
    }
  }
  G.Edge[2][1] = 1;
  G.Edge[3][1] = 1;
  G.Edge[4][1] = 1;
  G.Edge[1][2] = 1;
  G.Edge[1][3] = 1;
  G.Edge[1][4] = 1;
}

void outputForest(const CSTree & T){
  if(T == NULL){
    return ;
  }
  outputT(T,0);
  //输出每一个子树
  CSTree p = T->nsibling;
  while(p){
    outputT(p,0);
    p = p->nsibling;
  }
}
void outputForest0(const CSTree & T,int level){
  if(T == NULL){
    return ;
  }
  for(int i = 0;i < level;i++){ cout <<"\t"; }
  cout <<T->data <<endl;
  outputForest0(T->fchild,level + 1);
  outputForest0(T->nsibling,level);
}

int main()
{
  MGraph m;  //一个邻接矩阵
  ALGraph a;   //邻接表
  CSTree T = NULL;  //子女兄弟树
  //  Construct(m);   //初始化邻接矩阵
  testConstruct(m);
  convert(m, a);  //将矩阵转化为表
  cout <<"The table is " <<endl;
  outputGraph(a);      //输出表
  G_To_F(m,T);    //矩阵转化成森林
  cout <<"The trees is " <<endl;
  outputForest(T);    //输出子女兄弟森林
  outputForest0(T,0); //新的输出方式,更简单
  clearForest(T);
  clearGraph(a);
  return 0;
}
