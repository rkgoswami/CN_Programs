#include <bits/stdc++.h>

using namespace std;

/*Disclaimer: Avoid using sentence with more than 10 words */

int main(){
	srand(time(NULL));

	//Step 1: Read the message 
	string msg;
	cout<<"\nEnter the message : ";
	getline(cin,msg);

	//Step 2: Split the sentence into word based on tokens
	vector<std::string> tokens;
	istringstream iss(msg);
	int i=0;
	for(string s; iss >> s; ){
		stringstream ss;
		ss<<i;
    	tokens.push_back(ss.str()+s);
    	i++;
    }

    //Step 3: Attaching frame no. to frames
    cout<<"\nFrames Generated with Sequence Numbers :\n [";
    for(int i=0;i<tokens.size();++i){
    	cout<<" "<<tokens[i];
    }
    cout<<" ]\n";

	//Step 4: Shuffling the frames
	random_shuffle(tokens.begin(),tokens.end());
	cout<<"\nShuffling the frames:\n [";
	for(int i=0;i<tokens.size();++i){
    	cout<<" "<<tokens[i];
    }
    cout<<" ]\n";

	//Step 5: Sorting back the frames
	cout<<"\nSorting the frames based on Sequence no. : \n[";
	sort(tokens.begin(),tokens.end());
	for(int i=0;i<tokens.size();++i){
    	cout<<" "<<tokens[i];
    }
    cout<<" ]\n";
}