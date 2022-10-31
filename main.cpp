#include <iostream>
#include <vector>
#include <stack>
#include "unordered_map"


using namespace std;

class satDPLL{
public:
    vector<int> DPLL(vector<vector<int>>& cnfFunction){
        vector<int> trail = findUnitClauses(cnfFunction);
        int flag = checkEmptyclauses(cnfFunction);
        if(flag == 1){
            return trail;
        }else if(flag == 0){
            return {};
        }else{
            int literal = chooseLiterals(cnfFunction);
            vector<int> trueL = {2 * literal + 1};
            vector<vector<int>> cnfL = resolution(cnfFunction, trueL);
            auto L = DPLL(cnfL);
            if(L.size() != 0){
                for(auto x: trail){
                    L.push_back(x);
                }
                L.push_back(2 * literal + 1);
                return L;
            }

            vector<int> trueR = {2 * literal};
            vector<vector<int>> cnfR = resolution(cnfFunction, trueL);
            auto R = DPLL(cnfR);
            if(R.size() != 0){
                for(auto x: trail){
                    R.push_back(x);
                }
                R.push_back(2 * literal);
                return R;
            }

            return {};
        }
    }
private:
    vector<int> findUnitClauses(vector<vector<int>>& cnfFunction){
        vector<int> unitLiterals;
        for(auto item: cnfFunction){
            int numSize = 0;
            int l = 0;
            for(int i = 0; i < item.size(); i++){
                if(item[i] == 1){
                    break;
                }else if(item[i] == 0){
                    continue;
                }else{
                    numSize++;
                    l = item[i];
                }
            }
            if(numSize == 1){
                unitLiterals.push_back(l);
            }
        }
        return unitLiterals;
    }

    vector<vector<int>> resolution(vector<vector<int>>& cnfFunction, vector<int>& literals){
        vector<vector<int>> res = cnfFunction;
        unordered_map<int, bool> literalsMap;
        for(const int literal: literals){
            const int v = literal / 2;
            const bool b = literal % 2;
            literalsMap[v] = b;
        }

        for(auto& item: res){
            for(int i = 0; i < item.size(); i++){
                const int v = item[i] / 2;
                const int b = item[i] % 2;
                if(literalsMap.find(v) != literalsMap.end()){
                    item[i] = b ^ literalsMap[v];
                }
            }
        }

        return res;
    }
    /*
     * 0: unsatisifiable
     * 1: satisifiable
     * 2: continue
     */
    int checkEmptyclauses(vector<vector<int>>& cnfFunction){
        for(const auto item: cnfFunction){
            int count = 0;
            for(const int x: item){
                if(x == 1){
                    break;
                }else if(x == 0){
                    count++;
                }else{
                    return 2;
                }
            }
            if(count == item.size()){
                return 0;
            }
        }
        return 1;
    }

    int chooseLiterals(vector<vector<int>>& cnfFunction){
        for(auto item: cnfFunction){
            for(int i = 0; i < item.size(); i++){
                if(item[i] != 0 && item[i] != 1){
                    return item[i] / 2;
                }
            }
        }
        return 0;
    }
};

void printRes(vector<int>& res){
    int n = res.size();
    for(int i = 0; i < n; i++){
        cout << res[i];
    }
    cout << ";" << endl;
}

int main() {
    satDPLL obj;
    vector<vector<int>> cnfFunction = {
            {3,5,6}
    };
    vector<int> res = obj.DPLL(cnfFunction);

    printRes(res);
}
