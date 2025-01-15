#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataType int
typedef long long ll;
const ll INF = 0x3f3f3f3f; //一个足够大的整数

// 顺序栈操作定义
#define STACKSIZE 1010
typedef struct
{
    DataType data[STACKSIZE];
    int top;
} SeqStack;

// 初始化为空栈
void InitStack(SeqStack* s)
{
    s->top = -1; // 置空栈
}

// 判断栈s是否为空，为空返回1，否则返回0
int StackEmpty(SeqStack* s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// 将元素x压入栈s中，正常入栈返回1，否则返回0
int Push(SeqStack* s, DataType x)
{
    if (s->top == STACKSIZE - 1) // 栈满，不能入栈
    {
        printf("栈已满！\n");
        return 0; // 入栈失败
    }
    else
    {
        s->top++; // 栈顶位置加1
        s->data[s->top] = x; // x入栈
        return 1; // 入栈成功
    }
}

// 将栈s的栈顶出栈，并通过指针变量x将顶栈元素返回，正常出栈返回1，否则返回0

int Pop(SeqStack* s, DataType* x)
{
    if (s->top == -1)
    {
        printf("栈已空！\n");
        return 0; // 栈空，不能出栈
    }
    else
    {
        *x = s->data[s->top]; // 栈顶元素保存在*x中
        s->top--; // 栈顶位置减1
        return 1; // 出栈成功
    }
}

// 读取栈顶元素，并通过参数x返回其值
int GetTop(SeqStack* s, DataType* x)
{
    if (s->top == -1)
    {
        printf("栈已空！\n");
        return 0; // 栈空，读取失败
    }
    else
    {
        *x = s->data[s->top]; // 栈顶元素保存在*x中，此时栈顶并不出栈
        return 1; // 读取成功
    }
}

// 队列定义
#define QUEUESIZE 1010
typedef struct
{
    DataType data[QUEUESIZE];
    int front, rear;
} SeqQueue;

void InitQueue(SeqQueue* q) // 初始化队列
{
    q->front = -1;
    q->rear = -1;
}

int EmptyQueue(SeqQueue* q)
{
    if (q->front == q->rear) return 1;
    else return 0;
}

int DeleteQueue(SeqQueue* q, DataType* x) // 出队
{
    if (q->front == q->rear)
    {
        printf(" 队列已为空，无元素可取\n");
        return 0;
    }
    else
    {
        q->front++;
        *x = q->data[q->front];
        return 1;
    }
}

int EnterQueue(SeqQueue* q, DataType x) // 进队
{
    if (q->rear == QUEUESIZE)
    {
        printf("队已满，不能插入元素\n");
        return 0;
    }
    else
    {
        q->rear++;
        q->data[q->rear] = x;
        return 1;
    }
}

int GetFront(SeqQueue* q, DataType* x) // 取队首元素
{
    if (q->front == q->rear)
    {
        printf(" 队列已为空，无元素可取\n");
        return 0;
    }
    else
    {
        *x = q->data[q->front + 1];
        return 1;
    }
}

#define MAXNUM 100+2 //最大景点数目
int NodeNum,PathNum; // 结点（景点）数
int p[MAXNUM][MAXNUM]; // 邻接矩阵储存图结构

// 最短路径算法定义
int px[MAXNUM]; // 储存最短路径
int v[MAXNUM]; // 判断是否经过
int lastv[MAXNUM]; // 储存上一个结点
char name[MAXNUM][100]; // 储存景点名
char Introductions[MAXNUM][999]; // 储存景点介绍
int None_exist[MAXNUM]; // 用于跳过被删除的景点

void Dijkstra(int pp[], int st, SeqQueue* qq)
{
    if (None_exist[st])
    {
        printf("该结点不存在！\n");
        return;
    }
    memset(v, 0, sizeof(v));
    memset(lastv, 0, sizeof(lastv));
    InitQueue(qq);
    // A到各点最短路径
    pp[st] = 0;
    v[st] = 1;
    EnterQueue(qq, st);
    int x;
    while (!(EmptyQueue(qq)))
    {
        DeleteQueue(qq, &x);

        for (int i = 1; i <= PathNum; i++)
        {
            if (p[x][i] > 0)
            {
                if (pp[i] > pp[x] + p[x][i])
                {
                    pp[i] = pp[x] + p[x][i];
                    lastv[i] = x;
                }
                if (v[i] == 0)
                    EnterQueue(qq, i);
                v[i] = 1;
            }
        }
    }
    for (int i = 1; i <= NodeNum; i++)
    {
        if (None_exist[i]) continue;
        // cout << "从结点" << st << "到结点" << i << "的最短路径：";
        /*printf("从结点%d到结点%d的最短路径：", st, i);*/
        printf("从 %s 到 %s 的最短路径：", name[st], name[i]);
        if (pp[i] == INF)
        {
            //cout << "INF ";
            printf("无法到达 \n");
            continue;
        }
        printf("%3d  ", pp[i]);
        int  v = i;
        // cout << v;
        /*printf("%d", v);*/

        SeqStack* stk = (SeqStack*)malloc(sizeof(SeqStack));
        InitStack(stk);
        Push(stk, v);
        while (lastv[v] != 0)
        {
            if (lastv[v] > PathNum) break;
            Push(stk, lastv[v]);
            v = lastv[v];
        }
        
        int* ToPrint=&v; //随便进行初始化
        Pop(stk, ToPrint);
        //printf("%d", *ToPrint);
        printf("%s", name[*ToPrint]);
        while (!StackEmpty(stk))
        {
            Pop(stk, ToPrint);
            //printf(" -> %d", *ToPrint);
            printf(" -> %s", name[*ToPrint]);
        }
        printf("\n");

    }
}

void DijkstraSingle(int pp[], int st,int ed, SeqQueue* qq)
{
    if (None_exist[st]|| None_exist[ed])
    {
        printf("结点不存在！\n");
        return;
    }
    memset(v, 0, sizeof(v));
    memset(lastv, 0, sizeof(lastv));
    InitQueue(qq);
    // A到各点最短路径
    pp[st] = 0;
    v[st] = 1;
    EnterQueue(qq, st);
    int x;
    while (!(EmptyQueue(qq)))
    {
        DeleteQueue(qq, &x);

        for (int i = 1; i <= PathNum; i++)
        {
            if (p[x][i] > 0)
            {
                if (pp[i] > pp[x] + p[x][i])
                {
                    pp[i] = pp[x] + p[x][i];
                    lastv[i] = x;
                }
                if (v[i] == 0)
                    EnterQueue(qq, i);
                v[i] = 1;
            }
        }
    }
    int i = ed;
    {
        if (None_exist[i]) return;
            printf("从 %s 到 %s 的最短路径：", name[st], name[i]);
        if (pp[i] == INF)
        {
            printf("无法到达 \n");
            return;
        }
        printf("%3d  ", pp[i]);
        int  v = i;

        SeqStack* stk = (SeqStack*)malloc(sizeof(SeqStack));
        InitStack(stk);
        Push(stk, v);
        while (lastv[v] != 0)
        {
            if (lastv[v] > PathNum) break;
            Push(stk, lastv[v]);
            v = lastv[v];
        }

        int* ToPrint = &v;
        Pop(stk, ToPrint);
        printf("%s", name[*ToPrint]);
        while (!StackEmpty(stk))
        {
            Pop(stk, ToPrint);
            printf(" -> %s", name[*ToPrint]);
        }
        printf("\n");
    }
}

// 模糊匹配
int vague(char* str, char* target)
{
    int i, j, tag = 0;
    for (i = 0; i < strlen(str); i += 2) //中文占两位，每次匹配+=2
    {
        for (j = 0; j < strlen(target); j += 2)
        {
            if (str[i] == target[j] && str[i + 1] == target[j + 1])
                tag++;
        }
    }
    return tag == strlen(str) / 2 ? 1 : 0;
}

//模糊查询
void SearchVague(char str[20])
{
    for (int i = 1; i <= NodeNum; i++)
    {
        if (vague(str, name[i]))
        {
            printf("%d ： %s\n    %s\n", i, name[i], Introductions[i]);
        }
    }
}

// Prim算法构造最小生成树
void Prim()
{
    int i, j, k;
    int MinCost;
    int PathSum = 0;
    int LowCost[MAXNUM] = { INF };
    int LowCost_Final[MAXNUM] = { INF };
    int CloseVertex[MAXNUM] = { INF };

    // 初始化LowCost和CloseVertex数组
    for (i = 1; i <= NodeNum; i++)
    {
        if (i == 1)
            LowCost[i] = 0; // 起始顶点的LowCost设为0
        else if (PathNum == 0)
        {
            LowCost[i] = INF;
        }
        else
            LowCost[i] = p[1][i]; // 其他顶点的LowCost设为与起始顶点的边权

        CloseVertex[i] = 1; // 初始时所有顶点的前驱都是起始顶点
    }

    for (i = 1; i < NodeNum; i++)
    {
        MinCost = INF;
        k = 1;
        for (j = 2; j <= NodeNum; j++)
        {
            if (LowCost[j] != 0 && LowCost[j] < MinCost)
            {
                MinCost = LowCost[j];
                k = j;
            }
        }

        if (MinCost == INF)
        {
            printf("非连通图，无生成树！架设铁轨方案不存在！\n");
            return;
        }

        // 输出当前选中的边
        // printf("所选路径(%d,%d) %d\n", CloseVertex[k], k, LowCost[k]);
        printf("所选路径< %s 》 %s > %d\n", name[CloseVertex[k]], name[k], LowCost[k]);
        PathSum += LowCost[k];


        // 更新LowCost和CloseVertex
        LowCost_Final[k] = LowCost[k];
        LowCost[k] = 0; // 当前顶点已经加入生成树
        for (j = 1; j <= NodeNum; j++)
        {
            if (p[k][j] < LowCost[j])
            {
                CloseVertex[j] = k;
                LowCost[j] = p[k][j];
            }
        }
    }
}

// 查找汉密尔顿路径的函数，start为起始顶点，path用于记录路径，visited记录顶点是否被访问过
int HamiltonPath(int start, int path[], int visited[]) {
    int i;

    // 将起始顶点加入路径并标记为已访问
    path[0] = start;
    visited[start] = 1;

    // 如果路径中已经包含了所有顶点，说明找到了汉密尔顿路径
    if (path[0] == NodeNum) 
    {
        return 1;
    }

    // 尝试将未访问过的相邻顶点加入路径
    for (i = 1; i <= NodeNum; i++) 
    {
        if (p[start][i] > 0 && visited[i] == 0) 
        {  // 如果顶点i与当前顶点有边相连且未被访问
            path[path[0] + 1] = i;
            visited[i] = 1;
            if (HamiltonPath(i, path, visited)) 
            {  // 递归查找下一层
                return 1;
            }
            visited[i] = 0;  // 回溯，取消该顶点的访问标记
        }
    }

    return 0;  // 未找到汉密尔顿路径
}

// 辅助函数，用于输出找到的汉密尔顿路径
void PrintHamiltonPath(int path[]) 
{
    int i;
    for (i = 1; i <= PathNum; i++) 
    {
        if (path[i] != 0) 
        {
            printf("-> %s ", name[path[i]]);
        }
    }
    printf("\n");
}

// 添加景点
void AddAttraction()
{
    NodeNum++;
    int cnt=0;
    printf("景点名称>>");
    scanf("%s", name[NodeNum]);
    printf("景点简介>>");
    scanf("%s", Introductions[NodeNum]);
    printf("与景点关联路径数>>");
    scanf("%d", &cnt);
    if(cnt!=0)
    for (int i = 1; i <= NodeNum - 1; i++)
    {
        if (None_exist[i]) continue;
        printf("%d ： %s\n", i, name[i]);
    }
    int tmp_node, tmp_path;
    while (cnt--)
    {
        printf("请输入所连接结点>>");
        scanf("%d", &tmp_node);
        printf("请输入路径长度>>");
        scanf("%d", &tmp_path);
        p[NodeNum][tmp_node] = tmp_path;
        p[tmp_node][NodeNum] = tmp_path;
    }
    printf("添加景点成功！\n");
}

// 删除景点
void DeleteAttraction()
{
    for (int i = 1; i <= NodeNum; i++)
    {
        printf("%d ： %s\n", i, name[i]);
    }
    int tmp_num;
    printf("请输入待删除景点编号>>");
    scanf("%d", &tmp_num);
    None_exist[tmp_num] = 1;
    for (int i = 1; i <= NodeNum; i++)
    {
        p[i][tmp_num] = INF;
        p[tmp_num][i] = INF;
    }
    printf("删除景点成功！\n");
}

void Menu()
{
    printf("================================================================\n");
    printf("****                                                        ****\n");
    printf("****               Touring Navigator                        ****\n");
    printf("****               城市交通导游图                           ****\n");
    printf("****                                                        ****\n");
    printf("****                1.查找最短路径                          ****\n");
    printf("****                2.展示邻接矩阵                          ****\n");
    printf("****                3.查看景点代号                          ****\n");
    printf("****                4.查询景点                              ****\n");
    printf("****                5.架设铁轨方案                          ****\n");
    printf("****                6.最佳浏览路线                          ****\n");
    printf("****                7.增添景点                              ****\n");
    printf("****                8.删除景点                              ****\n");
    printf("****                0.退出                                  ****\n");
    printf("****                                                        ****\n");
    printf("================================================================\n");
}

int main()
{
    // 导入图像路径矩阵
    SeqQueue* q = (SeqQueue*)malloc(sizeof(SeqQueue));
    memset(p, INF, sizeof(p));
    memset(px, INF, sizeof(px));
    //cin >> n >> m;
    
    FILE* fp = fopen("map.txt", "r");
    if (fp == NULL)
    {
        printf("file open error!\n");
        return 1;
    }

    fscanf(fp, "%d %d", &NodeNum,&PathNum);

    int st, ed, path;
    for(int i=1;i<=PathNum;i++)
    {
        fgetc(fp);
        fscanf(fp, "%d %d %d", &st, &ed, &path);
        p[st][ed] = path;
        
        p[ed][st] = path; // 调试 Prim 最小生成树算法，改为无向连通图
    }

    fclose(fp);

    //读入景点信息
    FILE* fq = fopen("attractions.txt", "r");
    if (fq == NULL)
    {
        printf("file open error!\n");
        return 1;
    }

    for (int i = 1; i <=NodeNum; i++)
    {
        fscanf(fq, "%s %s", name[i], Introductions[i]);
        fgetc(fq);
    }

    fclose(fq);


    while (1)
    {
        system("cls");
        Menu();
        printf("请输入操作>>");
        int key = 0;
        scanf("%d", &key);
        switch (key)
        {
        case 1:
        {
            int st = 0,ed = 0;
            printf("请输入起点>>");
            scanf("%d", &st);
            printf("请输入终点>>");
            scanf("%d", &ed);
            //Dijkstra(px, st, q);
            DijkstraSingle(px, st, ed, q);
            break;
        }
        case 2:
            for (int i = 1; i <= NodeNum; i++)
            {
                if (None_exist[i])
                    continue;
                for (int j = 1; j <= NodeNum; j++)
                {
                    if (None_exist[j])
                        continue;
                    if (p[i][j] == INF)
                    {
                        printf(" INF");
                    }
                    else
                    {
                        printf("%4d", p[i][j]);
                    }
                }
                printf("\n");
            }
            break;
        case 3:
            for (int i = 1; i <= NodeNum; i++)
            {
                if (None_exist[i]) continue;
                printf("%d ： %s\n    %s\n", i, name[i], Introductions[i]);
            }
            break;
        case 4:
            char TargetStr[20];
            printf("查询>>");
            scanf("%s", TargetStr);
            SearchVague(TargetStr);
            break;
        case 5:
            Prim();
            break;
        case 6:
        {
            int start = 0;  // 可根据实际情况让用户输入起始顶点等
            printf("请输入起始顶点编号>>");
            scanf("%d", &start);
            int path[MAXNUM] = { 0 };  // 用于记录汉密尔顿路径
            int visited[MAXNUM] = { 0 };  // 记录顶点是否被访问过
            if (HamiltonPath(start, path, visited)) {
                printf("找到汉密尔顿路径：\n");
                PrintHamiltonPath(path);
            }
            else {
                printf("未找到汉密尔顿路径\n");
            }
            break;
        }
        case 7:
            AddAttraction();
            break;
        case 8:
            DeleteAttraction();
            break;
        case 0:
            goto END;
            break;
        default:
            printf("该功能不存在，请重试！\n");
            break;
        }
        system("pause");
    }
END:
    //char save_key;
    //printf("确定保存？（Y/y）>>");
    //scanf("%c", &save_key);
    //if (save_key == 'Y' || save_key == 'y')
    //{
    //    FILE* fq= fopen("map.txt", "w");
    //    for(int i=0;i<n;i++)
    //}
    return 0;
}

/*
6 10
1 3 10
1 2 50
1 5 45
2 3 15
2 5 10
3 1 20
3 4 15
4 2 20
4 5 35
6 4 3
*/