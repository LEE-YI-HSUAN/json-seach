// 1072019.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <fstream>
#include <vector>
#include<string> 
#include <list>
using namespace std;

bool nonoutput = true;
bool output = false;

class items {
	list<string> keys;
	string value;
public:
	//將key 放入list中
	void push_keys(list<string> keys) {
		this->keys = keys;
	}
	void push_keys(string key) {
		this->keys.push_back(key);
	}
	void push_value(string value) {
		this->value = value;
	}
	void print() {
		list<string>::iterator i;
		int size = this->keys.size() - 1;
		for (i = this->keys.begin(); i != this->keys.end(); i++, size--) {
			if (size != 0) cout << *i << " -> ";
			else cout << *i << " : ";
		}
		cout << this->value << endl;
	}

	void judgment(string key) {
		string infor = "";
		list<string>::iterator it1 = this->keys.begin();

		for (; it1 != this->keys.end(); it1++)
			infor += *it1 + ">";
		int infor_len = infor.length() - 2;
		int key_len = key.length() - 1;

		if (key_len > infor_len) {
			return;
		}
		else {
			if (key_len == -1 && infor_len == -1) {
				cout << value;
				nonoutput = false;
				output = true;
				return;
			}
			else if (key_len == -1) return;

			for (; key_len >= 0; key_len--, infor_len--) {
				if (key[key_len] != infor[infor_len])
					return;
			}
			cout << value;
			nonoutput = false;
			output = true;
			return;
		}
	}
	void clear() {
		this->keys.clear();
		this->value = "";
	}
};

int main(int argc, char* argv[])
{
	items B;
	vector<items> all_items;

	ifstream fin1;
	fin1.open("json.txt");
	//fin1.open(argv[1]);
	char ch, lastch;
	list<string> keys;
	list<char> array, symbol;    //儲存{}及[]
	bool is_string_value = false, is_key = false, push = false, pop = false, pushed = false;/*看該筆資料是否放入過*/
	string key = "", value = "", p = "";
	int state = 0;
	int parantheses[2] = { 0,0 };    //用來儲存{、}個數
	int b[2] = { 0,0 }; //用來儲存[、]個數

	while (fin1.get(ch)) {   //一個一個字元跑
		cout<< "ch："<< ch << endl;
		if (is_string_value == false && is_key == false) {
			switch (ch)
			{
			case '{':
				parantheses[0]++;
				break;
			case '}':
				parantheses[1]++;
				break;
			case '[':
				b[0]++;
				break;
			case ']':
				b[1]++;
				break;
			default:
				break;
			}
			// if (ch == '{')  parantheses[0]++;
			// else if (ch == '}') parantheses[1]++;
			// else if (ch == '[')  b[0]++;
			// else if (ch == ']') b[1]++;

			//紀錄目前array object狀態
			if (ch == '[' || ch == '{') {
				symbol.push_back(ch); pushed = false;
			}
			else if (ch == ']' || ch == '}'){
				symbol.pop_back();
			}
			//最後一筆資料未放入過
			if (parantheses[0] == parantheses[1] && pushed == false && b[0] == b[1] && parantheses[0] != 0 && b[0] != 0)
				push = true;
			else if (parantheses[0] == parantheses[1] && b[0] == b[1] && parantheses[0] != 0 && b[0] != 0)
				break;

			if (ch == '{') state = 1;  //接下來是key 
			else if (state == 1 && ch == '\"') is_key = true;    //是key值
			else if (state == 2 && ch == '\"') is_string_value = true;   //是string的value
			else if (ch == ':') state = 2;    //接下來是value
			else if (ch == '[') {      
				//目前array狀況
				array.push_back(ch);
				//是[開頭的情況
				if (state == 0 && ch == '[') state = 2;

			}
			/*else if ((ch == '}' && lastch == ',') || (ch == ']' && lastch == ','))
				pushed = true;*/
			else if (ch == ']') {
				array.pop_front();
				//array完全結束且資料未放入
				if (array.empty() == true && pushed == false) {
					state = 1;
					push = true;
					pushed = true;
				}
			}
			else if (ch == ',') {
				//看資料有沒有放入過
				if (pushed != true) push = true;
				//else pushed = false;
				//pop一個key
				pop = true;
			}

			if (state == 1) {
				//不是key 就是false、true、null、數字的值
				if (is_key != true) {
					if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '-') || (ch == '+') || (ch == '.')) {
						value += ch; pushed = false;
					}
				}
			}
			else if (state == 2) {
				if (key != "") {
					if (keys.size() + 1 > parantheses[0] - parantheses[1] && keys.size() != 0)
						keys.pop_back();

					keys.push_back(key);
					key = "";
				}
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '-') || (ch == '+') || (ch == '.')) {
					value += ch; pushed = false;
				}
			}

			if (push == true) {
				if (value == "")
					value = "null";
				//以[開頭時
				if (keys.empty() == true) B.push_keys("");
				else B.push_keys(keys);

				B.push_value(value);
				value = "";

				all_items.push_back(B);
				B.clear();
				push = false;
				pushed = true;


			}
			if (pop == true) {
				if (keys.size() != 0) {
					while (keys.size() > parantheses[0] - parantheses[1])
						keys.pop_back();
				}
				list<char>::iterator i;
				i = symbol.end();
				i--;
				//若上一個是{ 狀態為1，若不是就是[狀態為2
				if (*i == '{') state = 1;
				else state = 2;
				pop = false;
			}
			if (ch != ' ' && ch != '\n' /*&& ch != '\r\n'*/) lastch = ch;
		}
		//字串型態的value
		else if (is_string_value == true) {
			pushed = false;
			if (ch == '\\' || ch == '\"') {
				if (p == "") {
					if (ch != '\"') p += ch;
					else is_string_value = false;
				}
				else {
					if (p == "\\") {
						p += ch;
						value += p; p = "";
						//value += ch; p = "";
					}
					//此value結束
					else is_string_value = false;
				}
			}
			else value += ch;
		}
		//key
		else if (is_key == true) {
			pushed = false;
			if (ch == '\\' || ch == '\"') {
				if (p == "") {
					if (ch != '\"') p += ch;
					else is_key = false;
				}
				else {
					if (p == "\\") {
						p += ch;
						key += p; p = "";
						//key += ch; p = "";
					}
					//此value結束
					else is_key = false;
				}
			}
			else key += ch;
		}
		//{=}且[=]有效資料結束，跳出
		if (parantheses[0] == parantheses[1] && b[0] == b[1] && parantheses[0] != 0 && b[0] != 0)
			break;
	}
	fin1.close();

	/*cout << "all_items:" << endl;
	for (int i = 0; i < all_items.size(); i++) {
		all_items[i].print();
	}
	cout << endl << "output:" << endl;*/
	ifstream fin2;
	//fin2.open("test.txt");
	fin2.open(argv[2]);
	bool first = true;
	key = "";

	while (getline(fin2, key)) {
		if (first == true) first = false;
		else cout << endl;

		for (int i = 0; i < all_items.size(); i++) {
			all_items[i].judgment(key);
			if (output == true) {
				cout << endl; output = false;
			}
		}

		if (nonoutput == false) nonoutput = true;
		else cout << endl;
		key = "";
	}
	fin2.close();
}
