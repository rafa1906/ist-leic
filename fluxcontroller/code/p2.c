#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE (!FALSE)

typedef struct vertex {
    int e_f;
    int h;
    int connected_to_source, pos_in_source;
} * vertex;

typedef struct edge {
    int u, v;
    int c_f;
    int f, r_f;
    struct edge *prox;
} * edge;

typedef struct flow_graph {
    vertex *V;
    edge **E;
} flow_graph;

flow_graph *G;

int M, N, S, C;

void add_vertex(int u) {
    vertex v = (vertex) malloc (sizeof(struct vertex));

    v->e_f = 0;
    v->h = 0;
    v->connected_to_source = FALSE;
    v->pos_in_source = -1;

    G->V[u] = v;
}

void add_edge(int u, int v, int pos) {
    edge e = (edge) malloc (sizeof(struct edge));

    e->u = u;
    e->v = v;
    e->c_f = 1;
    e->f = 0;
    e->r_f = 0;

    G->E[u][pos] = e;
}

int read_flow_graph() {
    int i, pos, out, where;
    int x, y;
    int n_V;

    scanf("%d %d\n%d %d", &M, &N, &S, &C);

    n_V = M * N * 2 + 2;

	G->V = (vertex *) malloc(sizeof(vertex) * n_V);
    G->E = (edge **) malloc(sizeof(edge *) * n_V);

    for (i = 0; i < n_V; i++) add_vertex(i);

	for (i = 1; i <= N * M; i++) {
        out = i + N * M;

        G->E[out] = (edge *) calloc (5, sizeof(edge));
        G->E[i] = (edge *) malloc (sizeof(edge));

        if ((i - 1) % M > 0) add_edge(out, i - 1, 0);
        if (i % M != 0) add_edge(out, i + 1, 1);
        if (i + M <= M * N) add_edge(out, i + M, 2);
        if (i - M > 0) add_edge(out, i - M, 3);

        add_edge(i, out, 0);
	}

    G->E[n_V - 1] = NULL;
    for (i = 0; i < S; i++) {
        scanf("%d %d", &x, &y);

        where = M * (y - 1) + x + M * N;

        if (!G->E[where][4]) add_edge(where, n_V - 1, 4);
    }

    pos = 0;

    G->E[0] = (edge *) calloc (C + 1, sizeof(edge));
    for(i = 0; i < C; i++) {
        scanf("%d %d",&x,&y);

        where = M * (y - 1) + x;

        if (!G->V[where]->connected_to_source) {
            add_edge(0, where, pos++);

            G->V[where]->connected_to_source = TRUE;
            G->V[where]->pos_in_source = pos - 1;
        }

        G->E[0][pos] = NULL;
    }

    return n_V;
}

void init_preflow(int s, int n_V) {
    int i = 0;

    G->V[0]->h = n_V;

    while (G->E[0][i]) {
        int v = G->E[0][i]->v;

        G->E[0][i]->f = 1;
        G->E[0][i]->r_f = -1;
        G->V[v]->e_f = 1;
        G->V[0]->e_f = G->V[0]->e_f - 1;

        i++;
    }
}

void push(int u, int v, int pos, int flow) {
    G->E[u][pos]->f += flow;
    G->E[u][pos]->r_f -= flow;
    G->V[u]->e_f -= flow;
    G->V[v]->e_f += flow;
}

void relabel(int u) {
    G->V[u]->h++;
}

void discharge(int u, int is_out_node) {
    int v, cur = 0;

    while (G->V[u]->e_f > 0) {
        if (is_out_node) {
            if (cur <= 4 && G->E[u][cur]) v = G->E[u][cur]->v;

            if (cur > 4) { relabel(u); cur = 0; }
            else if (G->E[u][cur] && (G->E[u][cur]->c_f - G->E[u][cur]->f) > 0 &&
                      G->V[u]->h == (G->V[v]->h + 1)) push(u, v, cur, 1);
            else cur++;

            if (G->V[u]->e_f > 0 && G->E[u - N * M][0]->f == 1 &&
                      G->V[u]->h == (G->V[u - N * M]->h + 1)) push(u - N * M, u, 0, -1);

        } else {
            if (cur <= 0) v = G->E[u][cur]->v;

            if (cur > 0) { relabel(u); cur = 0; }
            else if ((G->E[u][cur]->c_f - G->E[u][cur]->f) > 0 &&
                      G->V[u]->h == (G->V[v]->h + 1)) push(u, v, cur, 1);
            else cur++;

            if (G->V[u]->e_f > 0 && (u - 1) % M > 0 && G->E[u - 1 + N * M][1]->f == 1 &&
                G->V[u]->h == (G->V[u - 1 + N * M]->h + 1)) push(u - 1 + N * M, u, 1, -1);
            if (G->V[u]->e_f > 0 && u % M != 0 && G->E[u + 1 + N * M][0]->f == 1 &&
                G->V[u]->h == (G->V[u + 1 + N * M]->h + 1)) push(u + 1 + N * M, u, 0, -1);
            if (G->V[u]->e_f > 0 && (u + M) <= (M * N) && G->E[u + M + N * M][3]->f == 1 &&
                G->V[u]->h == (G->V[u + M + N * M]->h + 1)) push(u + M + N * M, u, 3, -1);
            if (G->V[u]->e_f > 0 && (u - M) > 0 && G->E[u - M + N * M][2]->f == 1 &&
                G->V[u]->h == (G->V[u - M + N * M]->h + 1)) push(u - M + N * M, u, 2, -1);
            if (G->V[u]->e_f > 0 && G->V[u]->connected_to_source &&
                G->E[0][G->V[u]->pos_in_source]->f == 1 &&
                G->V[u]->h == (G->V[0]->h + 1)) push(0, u, G->V[u]->pos_in_source, -1);
        }
    }
}

int relabel_to_front(int s, int t) {
    int i, next, temp;
    int u, oldh;
    int max_flow;
    int L[t - 1];

    init_preflow(s, t + 1);

    for (i = 1; i < t; i++) L[i - 1] = i;

    u = L[0];
    next = 0;

    while (next < t - 1) {
        oldh = G->V[u]->h;

        discharge(u, u > (t - 1) / 2);

        if (G->V[u]->h > oldh) {
            temp = L[next];

            for (i = next; i > 0; i--) L[i] = L[i - 1];
            L[0] = temp;

            next = 1;

        } else next++;

        u = L[next];
    }

    max_flow = G->V[t]->e_f;

    return max_flow;
}


int main() {
	int max_flow;

    G = (flow_graph *) malloc(sizeof(flow_graph));

    int n_V = read_flow_graph();

    max_flow = relabel_to_front(0, n_V - 1);
    printf("%d\n", max_flow);

    return 0;
}
