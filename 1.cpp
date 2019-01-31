// #include <bits/stdc++.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

string findNumber(vector<int> arr, int k) {
    string answer = "NO";
    int i = 0;
    int lenOfArray;

    lenOfArray = arr.size();
    while (i < lenOfArray)
    {
        if (arr[i] == k)
        {
            answer = "YES";
            break ;
        }
        i++;
    }
    return (answer);
}

int		main()
{
	string ad;
	std::vector<int> vect;
    vect.push_back(10); 
    vect.push_back(20); 
    vect.push_back(30); 
	ad = findNumber(vect, 10);
	cout << ad;
	return (0);
}