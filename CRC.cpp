/*
	CN LABSET (Part a)
	==================
    Problem 8: Perform CRC i.e Cyclic Redundancy Check 
    BY:
        Rishav Kumar Goswami
*/

#include <bits/stdc++.h>

using namespace std;

string CRC_division(string DataWord,string Divisor){

	int dlen = Divisor.length();
	int len = DataWord.length();

	string temp = DataWord.substr(0,dlen);
	int i = dlen-1;
	
	//Main logic of CRC divisor
	/*check the leftmost bit,
			if leftmost bit is 1:
			 	then xor with generator i.e divisor 
			else 
				xor with zero
		*/

	while(i<=len){
		string result="";
		unsigned short a,b;
		
		if(temp[0]=='1'){
			for(int j=0;j<dlen;++j){
				a=(unsigned short)(temp[j]-'0');
				b=(unsigned short) (Divisor[j]-'0');
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
	return temp.substr(0,temp.length()-1);
}

int main(){

	/*	Encode operation at Sender side:
		===============================
		Step 1: Take input from user:
				Step 1.1: Length of dataword i.e (k)
				Step 1.2: DataWord of k-bit length
				Step 1.3: Generator or Divisor of (n-k+1) bit length i.e CRC-16 = (x^16 + x^12 + x^5 + 1)
		Step 2: Append the codeword to dataword ( since dataword = codeword + output of generate(remainder))
		Step 3:	Append 0's at the end of dataword to make it equal to codeword length i.e n = k+15 ( i.e n-k+1=16)
		Step 4: Perform the division operation to genearate the remainder using CRC_Divison()
		Step 5: Append the Binary String Reaminder to Codeword that is ready to be transmitted to reciever
	*/	

	string DataWord,Divisor;
	int n,k;

	cout<<"\nEnter the dataword lengths i.e ( k ) : ";
	cin>>k;
	cout<<"\nEnter the dataword : ";
	cin>>DataWord;
	
	//i.e CRC-16 = (x^16 + x^12 + x^5 + 1); length = n-k+1
	Divisor="10001000000100001";		

	cout<<"\nCRC-16 generator : "<<Divisor;
	cout<<"\nCodeword Length would be "<<(k-1)+16;

	//Step 2:
	string CodeWord = ""+DataWord;

	//Step 3:
	for(int i=0;i<16;++i){
		DataWord+="0";
	}

	//Step 4:
	string remStr = CRC_division(DataWord,Divisor);
	cout<<"\nRemainder  = "<<remStr;
	//Step 5:
	CodeWord +=remStr;
	cout<<"\nCodeword generated to send : "<<CodeWord;


	/*	Decode operation at Reciever: 
		============================
		Step 1: Perform the division operation with same divisor and recieved CodeWord i.e with or without error :
		Step 2: Convert the remainder reciever into Integer
		Step 3: Check:
				If remainder has only 0's:
					"Dataword is accepted"
				else:
					"Dataword is rejected"
	*/

	cout<<"\nEnter the Codeword recieved to verify (with or without error in any bit position ) : ";
	cin>>CodeWord;
	
	//Step 1:
	remStr = CRC_division(CodeWord,Divisor);

	//Step 2 & 3:
	int flag = 0;
	for (int i = 0; i < 16; ++i){
		if(remStr[i]=='1'){
			flag=1;
			break;
		}
	}

	if(!flag)
		cout<<"\nDataword is accepted..";
	else
		cout<<"\nDataword is rejected..";

	cout<<"\n";

	return 0;
}
