#include "main.h"

Road::Road()
{

	int tmp[N] = {3,2,2,1,3,4,2,3,4,1,3,1,3,2,2,1,4,3,1,4};

	for (int i=0; i<N; ++i) {
		if (i==0)
			d.push_back(tmp[0]);
		else
			d.push_back(tmp[i]+d[i-1]);

		p.push_back(5);
	}
	p.at(0)=4;
	p.at(4)=10;

}

void Road::Solve()
{
	// The cost of getting to (0,i) is p(0)*i.
	for (int i=0; i<G; ++i)
		array[0][i].Value = p[0]*i;

	// Solve rows 2 to N-1.
	for (int i=1; i<N; ++i) {
		for (int g=0; g<G; ++g) {

			// Find minimum in the row above.
			int min=inf, minIndex=0;
			for (int j=0; j<G; j++) {
				if ((array[i-1][j].Value <= min) && (d[i]-d[i-1]<=j)) {
					min=array[i-1][j].Value;
					minIndex=j;
				}
			}

			int currentGas = g+(d[i]-d[i-1]);
			if ((currentGas <= G)) {
				// Update the cell's content to optimal solution for i-1.
				array[i][g].Value = array[i-1][minIndex].Value + (d[i]-d[i-1])*p[i-1];
				array[i][g].parent = &(array[i-1][minIndex]);
			} else {
				if (g>0 && array[i][g-1].Value!=inf) {
					array[i][g].Value = array[i][g-1].Value + p[i];
					array[i][g].parent = array[i][g-1].parent;
				} else {
					array[i][g].Value = inf;
				}
			}
		}
	}
	printSolution();
}

void Road::printSolution()
{
	for (int i=0; i<N; ++i) {
		printf("d=%.3d p=%.3d  ", d[i], p[i]);
		for (int j=0; j<G; ++j) {
			if (array[i][j].Value == inf)
				cout << "--- ";
			else
				printf("%.3d ", array[i][j].Value);
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	cout << "hello world" << endl;

	Road road;
	cout << "The tank size G=" << road.G << endl;
	cout << "The number of gas stations=" << road.N << endl;

	road.Solve();

	return 0;
}

