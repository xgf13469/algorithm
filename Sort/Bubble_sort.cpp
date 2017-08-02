#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//ц╟ещеепР
void Bubble_sort(vector<int> &A)
{
	int len = A.size();

	for (int i = 0; i < len - 1; ++i)
		for (int j = 0; j < len - 1 - i;++j)
			if (A[j] > A[j + 1])
			{
				swap(A[j], A[j + 1]);
			}
}

int main()
{
	int a1[] = {13,3,18,5,2,17,8,12,10,9,6,4,1,11,15,14,7,16};
	vector<int> a(&a1[0], &a1[18]);

	Bubble_sort_sort(a, 0, a.size()-1);
	for (auto it : a)
		cout << it << "  ";

	system("pause");
	return 0;
}