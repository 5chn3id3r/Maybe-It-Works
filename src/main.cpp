// C++ program to solve Traveling Salesman Problem
// using Branch and Bound.
#include <bits/stdc++.h>
/*using namespace std;
const int N = 4;
// final_path[] stores the final solution ie, the
// path of the salesman.
int final_path[N+1];

// visited[] keeps track of the already visited nodes
// in a particular path
bool visited[N];

// Stores the final minimum weight of shortest tour.
float final_res = INFINITY;


typedef struct BnBContext
{
	float **adj;
	int *cpath;
	bool *visited;
	int size;
	float final_res;
	int *final_path;
} BnBContext;


// Function to find the minimum edge cost
// having an end at the vertex i
int firstMin(float ** const adj, int i)
{
	float min = INFINITY;

	for (int k = 0; k < N; k++) {
		if (adj[i][k] < min && i != k) {
			min = adj[i][k];
		}
	}

	return min;
}

// function to find the second minimum edge cost
// having an end at the vertex i
float secondMin(float ** const adj, int i)
{
	float first = INFINITY;
	float second = INFINITY;

	for (int j = 0; j < N; j++)	{
		if (i != j) {
			if (adj[i][j] <= first) {
				second = first;
				first = adj[i][j];
			} else if (adj[i][j] <= second && adj[i][j] != first) {
				second = adj[i][j];
			}
		}
	}

	return second;
}

float minsSum(float ** const adj, int i)
{
	float first = INFINITY;
	float second = INFINITY;

	for (int j = 0; j < N; j++)	{
		if (i != j) {
			if (adj[i][j] <= first) {
				second = first;
				first = adj[i][j];
			} else if (adj[i][j] <= second && adj[i][j] != first) {
				second = adj[i][j];
			}
		}
	}

	return second + first;
}

// function that takes as arguments:
// curr_bound -> lower bound of the root node
// curr_weight-> stores the weight of the path so far
// level-> current level while moving in the search
//		 space tree
// curr_path[] -> where the solution is being stored which
//			 would later be copied to final_path[]
void TSPRec(float ** const adj, int curr_bound, int curr_weight, int level, int *curr_path)
{
	// base case is when we have reached level N which
	// means we have covered all the nodes once
	if (level >= N) {
		// check if there is an edge from last vertex in
		// path back to the first vertex
		if (adj[curr_path[level-1]][curr_path[0]] != 0) {
			// curr_res has the total weight of the
			// solution we got
			int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]];

			// Update final result and final path if
			// current result is better.
			if (curr_res < final_res) {
				memcpy(final_path, curr_path, N * sizeof(int));
				final_path[N] = curr_path[0];

				final_res = curr_res;
			}
		}

		return;
	}

	// for any other level iterate for all vertices to
	// build the search space tree recursively
	for (int i = 0; i < N; i++) {
		// Consider next vertex if it is not same (diagonal
		// entry in adjacency matrix and not visited
		// already)
		if (adj[curr_path[level-1]][i] != 0 && visited[i] == false) {
			int temp = curr_bound;
			curr_weight += adj[curr_path[level-1]][i];

			// different computation of curr_bound for
			// level 2 from the other levels
			if (level == 1) {
				curr_bound -= ((firstMin(adj, curr_path[level-1]) +
								firstMin(adj, i))/2);
			} else {
				curr_bound -= ((secondMin(adj, curr_path[level-1]) +
								firstMin(adj, i))/2);
			}

			// curr_bound + curr_weight is the actual lower bound
			// for the node that we have arrived on
			// If current lower bound < final_res, we need to explore
			// the node further
			if (curr_bound + curr_weight < final_res) {
				curr_path[level] = i;
				visited[i] = true;

				// call TSPRec for the next level
				TSPRec(adj, curr_bound, curr_weight, level+1, curr_path);
			}

			// Else we have to prune the node by resetting
			// all changes to curr_weight and curr_bound
			curr_weight -= adj[curr_path[level-1]][i];
			curr_bound = temp;

			// Also reset the visited array
			memset(visited, false, N * sizeof(bool));
			for (int j = 0; j <= level-1; j++) {
				visited[curr_path[j]] = true;
			}
		}
	}
}

void TSPRec_alt(BnBContext *ctx, float bound, float dist, int depth)
{
	// base case is when we have reached level N which
	// means we have covered all the nodes once
	if (depth >= ctx->size) {
		// check if there is an edge from last vertex in
		// path back to the first vertex
		if (ctx->adj[ctx->cpath[depth -1]][ctx->cpath[0]] != 0) {
			// curr_res has the total weight of the
			// solution we got
			int curr_res = dist + ctx->adj[ctx->cpath[depth -1]][ctx->cpath[0]];

			// Update final result and final path if
			// current result is better.
			if (curr_res < ctx->final_res) {
				memcpy(ctx->final_path, ctx->cpath, ctx->size * sizeof(int));
				ctx->final_path[ctx->size] = ctx->cpath[0];

				ctx->final_res = curr_res;
			}
		}

		return;
	}

	// for any other level iterate for all vertices to
	// build the search space tree recursively
	for (int i = 0; i < ctx->size; i++) {
		// Consider next vertex if it is not same (diagonal
		// entry in adjacency matrix and not visited
		// already)
		if (ctx->adj[ctx->cpath[depth -1]][i] != 0 && ctx->visited[i] == false) {
			int temp = bound;
			dist += ctx->adj[ctx->cpath[depth -1]][i];

			// different computation of curr_bound for
			// level 2 from the other levels
			if (depth == 1) {
				bound -= ((firstMin(ctx->adj, ctx->cpath[depth -1]) +
								firstMin(ctx->adj, i))/2);
			} else {
				bound -= ((secondMin(ctx->adj, ctx->cpath[depth -1]) +
								firstMin(ctx->adj, i))/2);
			}

			// curr_bound + curr_weight is the actual lower bound
			// for the node that we have arrived on
			// If current lower bound < final_res, we need to explore
			// the node further
			if (bound + dist < ctx->final_res) {
				ctx->cpath[depth] = i;
				ctx->visited[i] = true;

				// call TSPRec for the next level
				TSPRec_alt(ctx, bound, dist, depth +1);
			}

			// Else we have to prune the node by resetting
			// all changes to curr_weight and curr_bound
			dist -= ctx->adj[ctx->cpath[depth -1]][i];
			bound = temp;

			// Also reset the visited array
			memset(ctx->visited, false, ctx->size * sizeof(bool));
			for (int j = 0; j <= depth -1; j++) {
				ctx->visited[ctx->cpath[j]] = true;
			}
		}
	}
}

// This function sets up final_path[]
void TSP(float ** const adj)
{
	int *curr_path = (int *)malloc((N +1) * sizeof(int));

	// Calculate initial lower bound for the root node
	// using the formula 1/2 * (sum of first min +
	// second min) for all edges.
	// Also initialize the curr_path and visited array
	float curr_bound = 0;
	memset(curr_path, -1, (N +1) * sizeof(int));
	memset(visited, 0, N);

	// Compute initial bound
	for (int i = 0; i < N; i++) {
		curr_bound += minsSum(adj, i);
	}

	// Rounding off the lower bound to an integer
	//curr_bound = (curr_bound & 1)? curr_bound/2 + 1 : curr_bound/2;

	// We start at vertex 1 so the first vertex
	// in curr_path[] is 0
	visited[0] = true;
	curr_path[0] = 0;

	// Call to TSPRec for curr_weight equal to
	// 0 and level 1
	TSPRec(adj, curr_bound, 0, 1, curr_path);

	free(curr_path);
}

// This function sets up final_path[]
void TSP_alt(float ** const adj, int size)
{
	bool *explored = (bool *)calloc(size, sizeof(bool));
	int *fpath = (int *)malloc((size +1) * sizeof(int));
	int *cpath = (int *)malloc((size +1) * sizeof(int));

	memset(cpath, -1, (size +1) * sizeof(int));

	float curr_bound = 0;
	for (int i = 0; i < size; i++) {
		curr_bound += minsSum(adj, i);
	}

	explored[0] = true;
	cpath[0] = 0;

	struct BnBContext ctx = {
		.adj = adj,
		.cpath = cpath,
		.visited = explored,
		.size = size,
		.final_res = INFINITY,
		.final_path = fpath,
	};

	TSPRec_alt(&ctx, curr_bound, 0, 1);

	printf("Minimum cost : %f\n", ctx.final_res);
	printf("Path Taken : ");
	for (int i = 0; i <= size; i++) {
		printf("%d ", ctx.final_path[i]);
	}
	printf("\n");

	free(explored);
	free(cpath);
	free(fpath);
}*/


typedef struct BnBContext
{
	bool *visited;
	float min;
	int *best_path;
} BnBContext;

typedef struct DistMatrix
{
	/// @brief Table of pointers to array of floats.
	float **mat;

	/// @brief Width & height of mat.
	int size;
} DistMatrix;


DistMatrix *DistMatrix_create(const int size)
{
	DistMatrix *dm = (DistMatrix *)malloc(sizeof(DistMatrix));

	dm->mat = (float **)malloc(size * sizeof(float *));

	for (int i = 0; i < size; i++) {
		dm->mat[i] = (float *)malloc(size * sizeof(float));
	}

	dm->size = size;

	return dm;
}

void DistMatrix_destroy(DistMatrix *dm)
{
	if (!dm) {
		return;
	}

	for (int i = 0; i < dm->size; i++) {
		free(dm->mat[i]);
	}

	free(dm->mat);
	free(dm);
}


float firstMin(const DistMatrix *dm, const int i)
{
	float min = INFINITY;

	for (int j = 0; j < dm->size; j++) {
		if (dm->mat[i][j] < min && i != j) {
			min = dm->mat[i][j];
		}
	}

	return min;
}

float secondMin(const DistMatrix *dm, const int i)
{
	float first = INFINITY;
	float second = INFINITY;

	for (int j = 0; j < dm->size; j++)	{
		if (i != j) {
			const float v = dm->mat[i][j];
			if (v <= first) {
				second = first;
				first = v;
			} else if (v <= second && v != first) { // The most unlikely is that we get on THE minimum, so check it last.
				second = v;
			}
		}
	}

	return second;
}

float minsSum(const DistMatrix *dm, const int i)
{
	float first = INFINITY;
	float second = INFINITY;

	for (int j = 0; j < dm->size; j++)	{
		if (i != j) {
			const float v = dm->mat[i][j];
			if (v <= first) {
				second = first;
				first = v;
			} else if (v <= second && v != first) {
				second = v;
			}
		}
	}

	return second + first;
}

void tspFromBnB_rec(const DistMatrix *dm, BnBContext *ctx, int *path, float bound, float dist, int depth)
{
	// base case is when we have reached level N which
	// means we have covered all the nodes once
	if (depth >= dm->size) {
		// check if there is an edge from last vertex in
		// path back to the first vertex
		if (dm->mat[path[depth -1]][path[0]] != 0) {
			// curr_res has the total weight of the
			// solution we got
			int curr_res = dist + dm->mat[path[depth -1]][path[0]];

			// Update final result and final path if
			// current result is better.
			if (curr_res < ctx->min) {
				memcpy(ctx->best_path, path, dm->size * sizeof(int));
				ctx->best_path[dm->size] = path[0];

				ctx->min = curr_res;
			}
		}

		return;
	}

	// for any other level iterate for all vertices to
	// build the search space tree recursively
	for (int i = 0; i < dm->size; i++) {
		// Consider next vertex if it is not same (diagonal
		// entry in adjacency matrix and not visited
		// already)
		if (dm->mat[path[depth -1]][i] != 0 && ctx->visited[i] == false) {
			int temp = bound;
			dist += dm->mat[path[depth -1]][i];

			// different computation of curr_bound for
			// level 2 from the other levels
			if (depth == 1) {
				bound -= (firstMin(dm, path[depth -1]) + firstMin(dm, i))/2;
			} else {
				bound -= (secondMin(dm, path[depth -1]) + firstMin(dm, i))/2;
			}

			// curr_bound + curr_weight is the actual lower bound
			// for the node that we have arrived on
			// If current lower bound < final_res, we need to explore
			// the node further
			if (bound + dist < ctx->min) {
				path[depth] = i;
				ctx->visited[i] = true;

				// call TSPRec for the next level
				tspFromBnB_rec(dm, ctx, path, bound, dist, depth +1);
			}

			// Else we have to prune the node by resetting
			// all changes to curr_weight and curr_bound
			dist -= dm->mat[path[depth -1]][i];
			bound = temp;

			// Also reset the visited array
			memset(ctx->visited, false, dm->size * sizeof(bool));
			for (int j = 0; j <= depth -1; j++) {
				ctx->visited[path[j]] = true;
			}
		}
	}
}


// Driver code
int main()
{
	const int N = 4, size = N;
	float t0[N] = {0, 10, 15, 20};
	float t1[N] = {10, 0, 35, 25};
	float t2[N] = {15, 35, 0, 30};
	float t3[N] = {20, 25, 30, 0};

	DistMatrix *dm = DistMatrix_create(size);

	{
		memcpy(dm->mat[0], t0, size * sizeof(float));
		memcpy(dm->mat[1], t1, size * sizeof(float));
		memcpy(dm->mat[2], t2, size * sizeof(float));
		memcpy(dm->mat[3], t3, size * sizeof(float));
	}

	bool *explored = (bool *)calloc(size, sizeof(bool));
	int *result = (int *)malloc((size +1) * sizeof(int));
	int *tmp_path = (int *)malloc((size +1) * sizeof(int));

	memset(tmp_path, -1, (size +1) * sizeof(int));

	float bound = 0;
	for (int i = 0; i < size; i++) {
		bound += minsSum(dm, i);
	}

	explored[0] = true;
	tmp_path[0] = 0;

	struct BnBContext ctx = {
		.visited = explored,
		.min = INFINITY,
		.best_path = result,
	};

	tspFromBnB_rec(dm, &ctx, tmp_path, bound, 0, 1);

	printf("Minimum cost : %f\n", ctx.min);
	printf("Path Taken : ");
	for (int i = 0; i <= N; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");

	free(explored);
	free(tmp_path);
	free(result);

	return 0;
}
