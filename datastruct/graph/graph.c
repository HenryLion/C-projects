/* 深度优先搜索DFS */

/* 连通图的深度优先搜索 */
void DFS (Graph G, int v)
{
	visited[v] = TRUE; // 置v访问过标记
	visitFunc (v);  // 访问v 

	for (w = first_adj_vex (G,v); w!=0; w=next_adj_vex (G,v,w))
		if (!visited[w])
			DFS(G,w);
}

/* 非连通图的深度优先搜索 */
void DFSTraverse (Graph G, visitFunc)
{
	for (v = 0; v < G.vex_num; ++v) 
		visited[v] = FALSE; // 访问标志数组初始化
	
	for (v = 0; v < G.vex_num; ++v)
		if (!visited[v])
			DFS(G, v); //对尚未访问的定点调用DFS
}

/* 广度优先搜索BFST */
void BFSTraverse (Graph G, VisitFunc)
{
	for (v = 0; v < G.vex_num; ++v)
		visited[v] = FALSE;
	InitQueue (Q); // 因为广度优先搜索要按照已遍历邻接点的次序再访问已遍历邻接点的邻接点，所以需要用队列辅助
	for (v = 0; v < G.vex_num; ++v)
	{
		if (!visited[v]) // v尚未访问,则访问v并将v入队列
		{
			EnQueue (Q,v);
			visited[v] = TRUE; 
			VisitFunc (v);
		}
		while (!QueueEmpty (Q))
		{
			DeQueue (Q,u); // 取出队列中首元素放入u
			for (w=first_adj_vex(G,u); w!=0; w=next_adj_vex(G,u,w))
				if (!visited[w])
				{
					EnQueue (Q,w);
					visited[w] = TRUE;
					VisitFunc (w);
				}
		}
	}
}
	

