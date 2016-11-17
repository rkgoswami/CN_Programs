/*
	CN LABSET (Part a)
	==================
    Problem 8: Perform CRC i.e Cyclic Redundancy Check 
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>

using namespace std;

int conversionBinToInt(string s){
	int len = s.length();
	int val=0;
	for(int i=len-1,k=0;i>=0;--i,k++){
		val=val+(s[i]-'0')*pow(2,k);
	}
	return val;
}

string CRC_division(string DataWord,string Divisor){

	int dlen = Divisor.length();
	int len = DataWord.length();

	string temp = DataWord.substr(0,dlen);
	int i = dlen-1;
	
	while(i<len){
		/*check the leftmost bit,
			if leftmost bit is 1:
			 	then xor with generator i.e divisor 
			else 
				xor with zero
		*/
		
		string result="";
		
		unsigned short a;
		unsigned short b;
		if(temp[0]=='1'){
			for(int j=0;j<dlen;++j){
				a=(unsigned short)(temp[j]-'0');
				b=(unsigned short) (Divisor[j]-'0');
				cout<<"\n"<<a<<" "<<b;	
				result+=((a^b)+'0');
			}
		}
		else{
			for(int j=0;j<dlen;++j){
				a=(unsigned short)(temp[j]-'0');
				b=0;
				result+=((a^b)+'0');
			}
		}
		
		//update the temp
		temp = result.substr(1,dlen-1);
		temp+=DataWord[++i];
	} 

	cout<<"\n return val = "<<temp;

	return temp.substr(0,temp.length()-1);
}

int main(){

	/*	Encode operation at Sender side:
		===============================
		Step 1: Take input from user:
				Step 1.1: Length of codeword and dataword i.e (n,k)
				Step 1.2: DataWord of k-bit length
				Step 1.3: Generator or Divisor of (n-k+1) bit length
		Step 2: Append the codeword to dataword ( since dataword = codeword + output of generate(remainder))
		Step 3:	Append 0's at the end of dataword to make it equal to codeword length i.e 'n'
		Step 4: Perform the division operation to genearate the remainder using CRC_Divison()
		Step 5: Append the Binary String Reaminder to Codeword that is ready to be transmitted to reciever
	*/	

	string DataWord,Divisor;
	int n,k;

	cout<<"\nEnter the codeword and dataword lengths i.e ( n , k ) : ";
	cin>>n>>k;
	cout<<"\nEnter the dataword : ";
	cin>>DataWord;
	cout<<"\nEnter "<<(n-k+1)<<" bit long divisor: ";
	cin>>Divisor;
	
	//Step 2:
	string CodeWord = ""+DataWord;

	//Step 3:
	for(int i=0;i<(n-k);++i){
		DataWord+="0";
	}

	//Step 4:
	string remStr = CRC_division(DataWord,Divisor);

	//Step 5:
	CodeWord +=remStr;
	cout<<"\nCodeword generated to send : "<<CodeWord;


	/*	Decode operation at Reciever: 
		============================
		Step 1: Perform the division operation with same divisor and recieved CodeWord:
		Step 2: Convert the remainder reciever into Integer
		Step 3: Check:
				If remainder == 0:
					"Dataword is accepted"
				else:
					"Dataword is rejected"
	*/

	//Step 1:
	remStr = CRC_division(CodeWord,Divisor);

	//Step 2 & 3:
	if(conversionBinToInt(remStr)==0)
		cout<<"\nDataword is accepted..";
	else
		cout<<"\nDataword is rejected..";

	cout<<"\n";

	return 0;
}