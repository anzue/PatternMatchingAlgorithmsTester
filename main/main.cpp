#include <iostream>
#include <iomanip>

#include "test.h"
#include "algoexecutor.h"

using namespace std;

int main(){    
    vector<Algo*> algos = get_algos();
    vector<vector<float> > test_res = test(algos, 32, 10000, 32, 128);
    cout << fixed << setprecision(4);

    for(int i=0;i< test_res.size(); ++i){
        //   cout << algos[i]->name << " \t";
        for(int j=0;j< test_res[i].size(); ++j){
            cout << test_res[i][j] << " ";
        } cout <<"\n";
    }
}