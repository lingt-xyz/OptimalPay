import java.util.Stack;

/**
 * T[W]=max_i{v[i]+T[W-w[i]]}
 */
public class Knapsack {

	public static void main(String[] args) {
		int values[] = new int[] { 60, 100, 120 };
		int weights[] = new int[] { 10, 20, 30 };
		int W = 50;
		int n = values.length;
		System.out.println(knapsack1(values, weights, W, n));
		System.out.println(knapSackRecursive(W, weights, values, n));

		System.out.println(knapSackBottomup(W, weights, values, n));
	}

	static int knapsack1(int values[], int weights[], int W, int n) {
		int[] T = new int[W + 1];
		T[0] = 0;

		for (int i = 1; i <= W; ++i) {
			T[i] = 0;
			for (int j = 0; j < n; ++j) {
				if (i - weights[j] >= 0) {
					int tmp = values[j] + T[i - weights[j]];
					if (T[i] < tmp) {
						T[i] = tmp;
					}
				}
			}
		}
		return T[W];
	}

	static int knapsack1(int W, int values[], int weights[], int n, Stack<Integer> solution) {
		int[] T = new int[W + 1];
		int[] J = new int[W + 1];
		T[0] = 0;
		J[0] = -1;
		for (int i = 1; i <= W; ++i) {
			T[i] = 0;
			J[i] = -1;
			for (int j = 0; j < n; ++j) {
				if (i - weights[j] >= 0) {
					int tmp = values[j] + T[i - weights[j]];
					if (T[i] < tmp) {
						T[i] = tmp;
						J[i] = j;
					}
				}
			}
		}
		while (W >= 0 && J[W] >= 0) {
			solution.push(J[W]);
			W -= T[J[W]];
		}
		return T[W];
	}

	/**
	 * https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
	 */
	// A utility function that returns maximum of two integers
	static int max(int a, int b) {
		return (a > b) ? a : b;
	}

	// Returns the maximum value that can be put in a knapsack of capacity W
	static int knapSackRecursive(int W, int weights[], int values[], int n) {
		// Base Case
		if (n == 0 || W == 0)
			return 0;

		// If weight of the nth item is more than Knapsack capacity W, then
		// this item cannot be included in the optimal solution
		if (weights[n - 1] > W)
			return knapSackRecursive(W, weights, values, n - 1);

		// Return the maximum of two cases:
		// (1) nth item included
		// (2) not included
		else
			return max(values[n - 1] + knapSackRecursive(W - weights[n - 1], weights, values, n - 1), knapSackRecursive(W, weights, values, n - 1));
	}

	// Returns the maximum value that can be put in a knapsack of capacity W
	static int knapSackBottomup(int W, int wt[], int val[], int n) {
		int i, w;
		int K[][] = new int[n + 1][W + 1];

		// Build table K[][] in bottom up manner
		for (i = 0; i <= n; i++) {
			for (w = 0; w <= W; w++) {
				if (i == 0 || w == 0)
					K[i][w] = 0;
				else if (wt[i - 1] <= w)
					K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
				else
					K[i][w] = K[i - 1][w];
			}
		}

		return K[n][W];
	}
}
