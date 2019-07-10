#include<iostream>
#include<vector>
using namespace std;

	void Merge(vector<int>& a, int left, int right)
	{	//思想：需要一个等大的向量来做中间变量,因为两个子序列都是排好序了的，所以1.先从temp中第一个子序列元素开始，如果小于第二个子序列中元素就放到a中对应位置，如果大于，就把第二子序列元素放入a中对应位置，使用count来统计放入a中元素的个数;如果有一个子序列最后剩余了就直接复制到a中
		vector<int> temp(a.begin()+left, a.begin()+right+1);
		int m = (left+right)/2;
		int i = 0, j = m+1-left, count = left;  //一定要注意i和j的起始位置！！
		while(i<=m-left && j<=right-left)
		{
			if(temp[i]<temp[j])
				a[count++] = temp[i++];
			else
				a[count++] = temp[j++];
		}
		while(i <= m-left)
			a[count++] = temp[i++];
		while(j <= right-left)
			a[count++] = temp[j++];
	}
	void mergeSort(vector<int>& a, int left, int right)
	{
		if(left == right) return ;
		//先拆分为a.szie()分子序列
		int m = (left+right)/2;
		mergeSort(a, left, m);
		mergeSort(a, m + 1, right);
		//再两两合并
		Merge(a, left, right);
	}
	
	
	int main(){
		int a[7] = {5,8,9,4,0,7,6};
		vector<int> v(a, a+7);
		mergeSort(v, 0, v.size()-1);
		for(int i=0; i<7; i++)
			cout<<v[i]<<"->";
		cout<<endl;
	}