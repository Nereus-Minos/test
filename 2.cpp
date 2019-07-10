#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

string getLCS(string& str1, string& str2)
{
	int i, j, len1 = str1.length(), len2 = str2.length();
	int maxLen = 0;		//最长子串数
	int maxEnd = 0;		//最长子串的结尾标号
	vector<vector<int>> dp(len1, vector<int>(len2, 0));
	for(i = 0; i < len1; i++)
	{
		for(j = 0; j < len2; j++)
		{
			if(str1[i] == str2[j])
			{
				if(i==0 || j==0) 	//因为没有左上角，所以要分开讨论！
					dp[i][j] = 1;
				else
					dp[i][j] = dp[i-1][j-1] + 1;
			}
			else
				dp[i][j] = 0;
			if(dp[i][j] > maxLen)  //更新最长子串
			{
				maxLen = dp[i][j];
				maxEnd = i;
			}
		}
	}
	return str1.substr(maxEnd-maxLen+1, maxLen);
}

	string getLPS(string& a)
	{
		int maxLen = 1, startIndex = 0; //startIndex为最大回文子串的起始位置
		int i, j, len = a.length();
		vector<vector<int>>dp(len, vector<int>(len, 0));
		for(i = 0; i < len; i++)	//每个单独的字符其实就是个长度为1的回文串。
			dp[i][i] = 1;
		for(i = len-2; i >= 0; i--)
		{
			for(j = i+1; j < len; j++)
			{
				if(a[i] == a[j])
				{
					if(j-i == 1)	//长度为2的回文串
						dp[i][j] = 2;
					else
					{
						if(dp[i+1][j-1] != 0)	//其子串也必须为回文
							dp[i][j] = dp[i+1][j-1] + 2;
						else
							dp[i][j] = 0;
					}
					if(maxLen < dp[i][j]) 
					{
						maxLen = dp[i][j];
						startIndex = i;
					}
				}
				else
					dp[i][j] = 0;
			}
		}
		return a.substr(startIndex, maxLen);
	}

void getNext(string& s, vector<int>& next)
	{
		int j=1, k=0;
		next[0] = next[1] = 0;
		while(j<s.size())
		{
			if(s[j] == s[k]) next[++j] = ++k; //next[j+1]=next[j]+1=k+1；
			else
			{
				if(k == 0) next[++j] = 0;  //别忘了，不然死循环
				else k = next[k];
			}
		}
	}
	int myKMP(string& s1, string& s2)
	{
		if(s1 == "" || s2 == "" || s1.length() < s2.length()) return -1;
		int i=0, j=0;
		vector<int> next(s2.length(), 0);
		getNext(s2, next);
		while(i<s1.length() && j<s2.length())
		{
			if(0 == j) i++;
			else if(s1[i] == s2[j]) { i++; j++; }
			else j = next[j];
		}
		if(j < s2.length()) return -1;
		else return i-s2.length();
	}

int main(){
	string str1 = "jkmmkl";
	string str2 = "jkl";
	int ret = myKMP(str1, str2);
	cout<<ret<<endl;
	return 0;
}