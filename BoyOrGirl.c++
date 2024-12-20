/*
Those days, many boys use beautiful girls' photos as avatars in forums. So it is pretty hard to tell the
gender of a user at the first glance. Last year, our hero went to a forum and had a nice chat with a
beauty (he thought so). After that they talked very often and eventually they became a couple in the network.

But yesterday, he came to see "her" in the real world and found out "she" is actually a very strong man!
Our hero is very sad and he is too tired to love again now. So he came up with a way to recognize users'
genders by their user names.

This is his method: if the number of distinct characters in one's user name is odd, then he is a male,
otherwise she is a female. You are given the string that denotes the user name, please help our hero to
determine the gender of this user by his method.If it is a female by our hero's method, print 
"CHAT WITH HER!" , otherwise, print "IGNORE HIM!".
*/
#include <iostream>
using namespace std;
int main()
{
  string str;
  cout << "Enter the Name: ";
  cin >> str;
  int l = str.length();
  char freq[26] = {0};
  int count = 0;
  for (int i = 0; i < l; i++)
  {
    freq[str[i] - 'a']++;
  }
  for (int i = 0; i < 26; i++)
  {
    if(freq[i]!=0)
      count++;
  }
  if (count%2==0)
    cout << "CHAT WITH HER!";
  else
    cout << "IGNORE HIM!";
  return 0;
}
