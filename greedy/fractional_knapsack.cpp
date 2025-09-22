#include<bits/stdc++.h>
using namespace std;

struct Item {
    int weight, value;
    double ratio;
};

bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cin >> n >> W; // n = số món, W = sức chứa

    vector<Item> items(n);
    for (int i = 0; i < n; i++){
        cin >> items[i].weight >> items[i].value;
        items[i].ratio = (double)items[i].value / items[i].weight; //giá trị ngon, trọng lượng rẻ
    }

    sort(items.begin(), items.end(), cmp);
    double totalValue = 0;
    int curWeight = 0; 

    for (int i = 0; i < n; i++){
        if (curWeight + items[i].weight <= W){
            //lấy hết item i
            curWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            //chỉ lấy 1 phần
            int remain = W - curWeight;
            totalValue += items[i].ratio * remain;
            break;
        }
    }
    
    cout << fixed << setprecision(2) << totalValue << "\n";
    return 0;
}