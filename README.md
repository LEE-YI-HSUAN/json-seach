
# 製作特定格式的json資料搜尋器
## 說明：
json檔案中包含一個json document 和多行雜訊，順序必為json document在上雜訊在下
### 測資說明：
txt 內包含多行測資，每一行文字都是一筆獨立的搜尋表示式。格式是由一個至多個 key string 組成，key strings 之間由 > 隔開。 > 符號表示下一層。 
每一筆搜尋表示式皆會指向一個或多個 leaf 節點，其形態為數值、字串、布林直或 null，並不會指向 object。 

### 輸出詳細說明：
1.	每一筆搜尋表示式之間的輸出須由換行隔開。 
2.	依照每一筆搜尋表示式輸出任何在 json 檔案中符合的資料。 
3.	當輸出有多項 value 時，需換行輸出。 
4.	下方的 Jackson, Scott, Joe 都可以藉由搜尋表示式「name」，搜尋到，所以分行輸出相對應的 value。 
5.	boyfriends 下一層的 name 只有兩個名字，所以輸出只會有 Scott,Joe 兩行。 
6.	範例中 key 為 numbers 時，因對應到 array 資料型態，所以輸出時需要分行輸出 array 中的值。 
7.	value 為 null, true, false, 數字型態, 字串型態時，直接輸出。 
8.	若無法依照搜尋表示式查詢到任何 value，輸出空白行。 
## 範例：
### 範例1：
- json檔案
```json=
{ 
    "name": "Jackson", 
    "age": 18, 
    "boyfriends": [ 
        { 
            "name": "Scott", 
            "age": 19 
        }, 
        { 
            "name": "Joe", 
            "age": 20 
        } 
    ], 
    "numbers": [ 
        1,2,3,4 
    ] 
} 
 
asdfjoiasj--- 包含此行以下皆是雜訊---oruhgwergnv{ dahffsdlfhaljshf()jdoasjd%@^*jhflsdfhhljrh} 
_01-1249=asdfjapsdjfpsidjfjpaijfspdfjapsidjfsdf 
---雜訊格式行數為一行以上--- 

```
- json.txt檔案
```
name
boyfriends>name
a>b>c
numbers 
```
### 輸出：
```
Jackson 
Scott 
Joe 
 
Scott 
Joe 
 
 
 
1 
2 
3 
4 
```
## 結果：

## 程式說明：
### 結構
```cpp=
class items {
	list<string> keys;
	string value;
public:
	//將key 放入list中
	void push_keys(list<string> keys);
	void push_keys(string key);
	
	void push_value(string value);
	void print();
	void judgment(string key);
	void clear();
}
```
有一筆測資過不了



